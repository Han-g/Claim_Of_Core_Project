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
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"ClaimOfCore", SQL_NTS,
        (SQLWCHAR*)L"ServerConnection", SQL_NTS,
        (SQLWCHAR*)L"server", SQL_NTS);

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

    // Execute Query
    if (SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS) { return false; }

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
            return true;
        }
    }

    SQLCloseCursor(hStmt);
    return false;
}