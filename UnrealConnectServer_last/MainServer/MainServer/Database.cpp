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
        (SQLWCHAR*)L"guest", SQL_NTS,
        (SQLWCHAR*)L"guest", SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        m_IsConnected = true;
        std::wcout << L"[DB] Connected Successfully!" << std::endl;

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
        if (SQL_SUCCEEDED(ret))
            std::wcout << L"[DB Error] " << state << L":" << text << std::endl;
    } while (ret == SQL_SUCCESS);
}

// 예시: 로그인 확인 로직
bool DBHelper::CheckLogin(const std::wstring& userId)
{
    if (!m_IsConnected) return false;

    // 쿼리 준비 (간단한 예시)
    // 실제로는 SQLBindParameter를 써야 안전합니다 (SQL Injection 방지)
    std::wstring query = L"SELECT count(*) FROM Users WHERE UserID = '" + userId + L"'";

    if (SQL_SUCCEEDED(SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS)))
    {
        // 결과 처리 로직...
        SQLCloseCursor(hStmt); // 커서 닫기 필수
        return true;
    }

    return false;
}