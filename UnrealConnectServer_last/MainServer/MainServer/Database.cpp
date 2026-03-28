#include "Database.h"

DBHelper::DBHelper()
    : hEnv(SQL_NULL_HANDLE), hDbc(SQL_NULL_HANDLE), hStmt(SQL_NULL_HANDLE), m_IsConnected(false)
{
}

DBHelper::~DBHelper()
{
    Disconnect();
}

bool DBHelper::Connect()
{
    SQLRETURN ret;

    // 1. 환경 핸들 할당
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 2. ODBC 버전 설정
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 3. 연결 핸들 할당
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 4. 타임아웃 설정 (5초)
    SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

    // 5. DB 접속 (DSN 방식)
    // [주의] 제어판 -> 관리 도구 -> ODBC 데이터 원본 관리자에서 "NorthWind"라는 DSN을 먼저 만들어야 합니다.
    // 두 번째 인자는 DSN 이름, 네 번째 인자는 ID, 여섯 번째 인자는 암호입니다.
    /*ret = SQLConnect(hDbc, (SQLWCHAR*)L"ClaimOfCore", SQL_NTS,
        (SQLWCHAR*)L"ServerConnection", SQL_NTS,
        (SQLWCHAR*)L"server", SQL_NTS);*/

    //SQLWCHAR connectStr[] = L"Driver={SQL Server};Server=DESKTOP-HW\SQLEXPRESS;Database=ClaimOfCore;Uid=ServerConnection;Pwd=server;";
    SQLWCHAR connectStr[] = L"Driver={SQL Server};Server=127.0.0.1\\SQLEXPRESS;Database=ClaimOfCore;Uid=ServerConnection;Pwd=server;";

    SQLWCHAR outConnectStr[1024];
    SQLSMALLINT outConnectStrLen;

    ret = SQLDriverConnect(
        hDbc,
        NULL,
        connectStr,
        SQL_NTS,
        outConnectStr,
        1024,
        &outConnectStrLen,
        SQL_DRIVER_NOPROMPT
    );

    if (SQL_SUCCEEDED(ret))
    {
        m_IsConnected = true;
        //std::wcout << L"[DB] Connected Successfully!" << std::endl;

        // 미리 Statement 핸들 하나 할당해두기
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
        return true;
    }
    else
    {
        PrintError(hDbc, SQL_HANDLE_DBC);
        return false;
    }
}

void DBHelper::Disconnect()
{
    if (hStmt != SQL_NULL_HANDLE) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    if (hDbc != SQL_NULL_HANDLE)
    {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    }
    if (hEnv != SQL_NULL_HANDLE) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    m_IsConnected = false;
}

void DBHelper::PrintError(SQLHANDLE handle, SQLSMALLINT type)
{
    SQLSMALLINT i = 0;
    SQLINTEGER native;
    SQLWCHAR state[7];
    SQLWCHAR text[256];
    SQLSMALLINT len;
    SQLRETURN ret;

    do
    {
        ret = SQLGetDiagRec(type, handle, ++i, state, &native, text, sizeof(text) / sizeof(SQLWCHAR), &len);
        if (SQL_SUCCEEDED(ret)) { 
            char strState[32];
            WideCharToMultiByte(CP_ACP, 0, (wchar_t*)state, -1, strState, 32, nullptr, nullptr);

            char strText[512];
            WideCharToMultiByte(CP_ACP, 0, (wchar_t*)text, -1, strText, 512, nullptr, nullptr);

            LOG_ERROR("[DB Error] %s : %s", strState, strText);
        }
    } while (ret == SQL_SUCCESS);
}

// 예시: 로그인 확인 로직
bool DBHelper::CheckLogin(const std::wstring& userID, const std::wstring& userPW, int& playerUID)
{
    if (!m_IsConnected) { return false; }

    // Query Setting
    std::wstring query = L"{call SP_LoginAccess('";
    query += userID;
    query += L"', '";
    query += userPW;
    query += L"')}";

    std::wstring adminID = L"admin", adminPW = L"admin";

    // Execute Query
    if (SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) { 
        SQLWCHAR sqlState[6], message[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message) / sizeof(SQLWCHAR), &textLength);

        LOG_ERROR("DB Query Failed! State: %ls, Msg: %ls", sqlState, message);
        return false; 
    }

    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        int loginResult = 0;
        SQLLEN len = 0;

        SQLGetData(hStmt, 1, SQL_C_LONG, &loginResult, sizeof(int), &len);

        if (loginResult == 0) {
            LOG_ERROR("Failed to Server Login - ID / PW is InValid");
            SQLCloseCursor(hStmt); // Need to Close Cursor
            return false;
        }

        else {
            int accountUID = 0;
            SQLGetData(hStmt, 2, SQL_C_LONG, &accountUID, sizeof(int), &len);

            playerUID = accountUID;

            SQLCloseCursor(hStmt);

            LOG_INFO("Login to Server Successful! [UID: %d]", accountUID);
            return true;
        }
    }

    SQLCloseCursor(hStmt);
    return false;
}

bool DBHelper::IsValidAccountString(const std::wstring& inputStr)
{
    // ^ : 시작
    // [a-zA-Z0-9] : 알파벳 대소문자 및 숫자만
    // {4,12} : 4글자 이상 12글자 이하
    // $ : 끝
    std::wregex pattern(L"^[a-zA-Z0-9]{4,12}$");

    return std::regex_match(inputStr, pattern);
}

bool DBHelper::CreateAccount(const std::wstring& userID, const std::wstring& userPW)
{
    if (!m_IsConnected || (!IsValidAccountString(userID)) || !IsValidAccountString(userPW)) { return false; }

    // 1. 프로시저 호출 쿼리 생성
    std::wstring query = L"{call SP_CreateAccount('";
    query += userID;
    query += L"', '";
    query += userPW;
    query += L"')}";

    // 2. 쿼리 실행
    if (SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) {
        LOG_ERROR("DB Query Failed: SP_CreateAccount for ID: %ls", userID.c_str());
        SQLFreeStmt(hStmt, SQL_CLOSE);
        return false;
    }

    // 3. 결과 받아오기
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        int resultCode = 0;
        SQLLEN len = 0;

        // 첫 번째 컬럼(ResultCode) 값을 읽어옵니다.
        SQLGetData(hStmt, 1, SQL_C_LONG, &resultCode, sizeof(int), &len);

        if (resultCode == -1) {
            // 결과가 -1이면 중복된 아이디
            LOG_WARN("Create Account Failed - UserID Already Exists! [%ls]", userID.c_str());
            SQLCloseCursor(hStmt);
            return false;
        }
        else {
            // 결과가 -1이 아니면 성공! 새로 생성된 AccountUID가 반환됨
            int newAccountUID = resultCode;
            LOG_INFO("Account Created Successfully! [New UID: %d]", newAccountUID);
            SQLCloseCursor(hStmt);
            return true;
        }
    }

    SQLCloseCursor(hStmt);
    return false;
}
