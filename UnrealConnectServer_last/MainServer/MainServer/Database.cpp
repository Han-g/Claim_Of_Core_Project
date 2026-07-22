#include "Database.h"

DBHelper::DBHelper() : hEnv(SQL_NULL_HANDLE), hDbc(SQL_NULL_HANDLE), m_IsConnected(false)
{

}

DBHelper::~DBHelper()
{
    Disconnect();
}

bool DBHelper::Connect()
{
    Disconnect();

    SQLRETURN ret;

    // 1. Allocate the ODBC environment handle.
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (!SQL_SUCCEEDED(ret)) { Disconnect(); return false; }

    // 2. Select the ODBC 3.x API version.
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret)) { Disconnect(); return false; }

    // 3. Allocate the database connection handle.
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (!SQL_SUCCEEDED(ret)) { Disconnect(); return false; }

    // 4. Fail fast if the login handshake takes too long.
    SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

    // 5. Open the database connection using the configured connection string.
    // Legacy DSN-based examples are kept below for reference only.
    // The active path below reads the full connection string from configuration.

    WCHAR exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    std::wstring dir(exePath);
    dir = dir.substr(0, dir.rfind(L'\\') + 1);
    std::wstring iniPath = dir + L"server_config.ini";

    SQLWCHAR connectStr[1024] = { 0 };

    // Read the connection string from the [Database] section of server_config.ini.
    GetPrivateProfileStringW(L"Database", L"ConnectionString", L"", connectStr, 1024, iniPath.c_str());

    // Stop early when the configuration file does not provide a connection string.
    if (wcslen(connectStr) == 0) {
        LOG_ERROR("Failed to load Database ConnectionString from server_config.ini");
        return false;
    }

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
    if (hDbc != SQL_NULL_HANDLE)
    {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        hDbc = SQL_NULL_HANDLE;
    }

    if (hEnv != SQL_NULL_HANDLE) 
    { 
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        hEnv = SQL_NULL_HANDLE;
    }

    m_IsConnected = false;
}

bool DBHelper::IsConnectionLost(SQLHANDLE handle, SQLSMALLINT type)
{
    SQLSMALLINT i = 0;
    SQLINTEGER native = 0;
    SQLWCHAR state[7] = {};
    SQLWCHAR text[256] = {};
    SQLSMALLINT len = 0;

    while (SQLGetDiagRec(type, handle, ++i, state, &native, text,
        sizeof(text) / sizeof(SQLWCHAR), &len) == SQL_SUCCESS)
    {
        if (wcsncmp((wchar_t*)state, L"08", 2) == 0)
        {
            return true;
             // 08003: connection does not exist
             // 08006: connection failure
             // 08S01: communication link failure
        }

        if (wcscmp((wchar_t*)state, L"HYT00") == 0 ||   // timeout expired
            wcscmp((wchar_t*)state, L"HYT01") == 0)     // connection timeout expired
        {
            return true;
        }
    }

    return false;
}

bool DBHelper::Reconnect()
{
    LOG_WARN("[DB] reconnect requested");
    Disconnect();

    if (!Connect())
    {
        LOG_ERROR("[DB] reconnect failed");
        return false;
    }

    LOG_INFO("[DB] reconnect success");
    return true;
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

bool DBHelper::CheckLogin(const std::wstring& userID, const std::wstring& userPW, int& playerUID)
{
    playerUID = -1;

    if (!m_IsConnected && !Reconnect())
    {
        return false;
    }

    EDBQueryResult result = CheckLoginOnce(userID, userPW, playerUID);
    if (result == EDBQueryResult::Success)
    {
        return true;
    }

    if (result == EDBQueryResult::ConnectionLost)
    {
        LOG_WARN("[DB] CheckLogin detected lost connection. retrying once.");

        if (!Reconnect())
        {
            return false;
        }

        result = CheckLoginOnce(userID, userPW, playerUID);
        return result == EDBQueryResult::Success;
    }

    return false;
}

EDBQueryResult DBHelper::CheckLoginOnce(const std::wstring& userID, const std::wstring& userPW, int& playerUID)
{
    if (!m_IsConnected)
    {
        return EDBQueryResult::ConnectionLost;
    }

    SQLHSTMT hStmt = SQL_NULL_HANDLE;

    auto CleanupStmt = [&]() {
        if (hStmt != SQL_NULL_HANDLE)
        {
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            hStmt = SQL_NULL_HANDLE;
        }
        };

    if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt)))
    {
        LOG_ERROR("Failed to Allocate Statement Handle in CheckLogin");
        return EDBQueryResult::Failed;
    }

    SQLSetStmtAttr(hStmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)5, 0);

    SQLWCHAR* query = (SQLWCHAR*)L"{call dbo.SP_LoginAccess(?, ?)}";

    if (!SQL_SUCCEEDED(SQLPrepare(hStmt, query, SQL_NTS)))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);

        bool lost = IsConnectionLost(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();

        if (lost)
        {
            m_IsConnected = false;
            return EDBQueryResult::ConnectionLost;
        }

        return EDBQueryResult::Failed;
    }

    SQLLEN idLen = SQL_NTS;
    SQLLEN pwLen = SQL_NTS;

    SQLBindParameter(
        hStmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_WCHAR,
        SQL_WVARCHAR,
        userID.length(),
        0,
        (SQLPOINTER)userID.c_str(),
        0,
        &idLen
    );

    SQLBindParameter(
        hStmt,
        2,
        SQL_PARAM_INPUT,
        SQL_C_WCHAR,
        SQL_WVARCHAR,
        userPW.length(),
        0,
        (SQLPOINTER)userPW.c_str(),
        0,
        &pwLen
    );

    SQLRETURN execRet = SQLExecute(hStmt);
    if (!SQL_SUCCEEDED(execRet))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);

        bool lost = IsConnectionLost(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();

        if (lost)
        {
            m_IsConnected = false;
            return EDBQueryResult::ConnectionLost;
        }

        return EDBQueryResult::Failed;
    }

    SQLRETURN fetchRet = SQLFetch(hStmt);
    if (!SQL_SUCCEEDED(fetchRet))
    {
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    int loginResult = 0;
    SQLLEN len = 0;

    if (!SQL_SUCCEEDED(SQLGetData(hStmt, 1, SQL_C_LONG, &loginResult, sizeof(int), &len)))
    {
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    if (loginResult == 0)
    {
        LOG_ERROR("Failed to Server Login - ID / PW is Invalid");
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    int accountUID = 0;
    if (!SQL_SUCCEEDED(SQLGetData(hStmt, 2, SQL_C_LONG, &accountUID, sizeof(int), &len)))
    {
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    playerUID = accountUID;

    CleanupStmt();
    return EDBQueryResult::Success;
} 


bool DBHelper::CreateAccount(const std::wstring& userID, const std::wstring& userPW)
{
    if (!m_IsConnected || (!IsValidUserID(userID)) || !IsValidUserPW(userPW)) { return false; }


    if (!m_IsConnected && !Reconnect()) { return false; }

    EDBQueryResult result = CreateAccountOnce(userID, userPW);
    if (result == EDBQueryResult::Success)
    {
        return true;
    }

    if (result == EDBQueryResult::ConnectionLost)
    {
        LOG_WARN("[DB] CreateAccount detected lost connection. retrying once.");

        if (!Reconnect())
        {
            return false;
        }

        result = CreateAccountOnce(userID, userPW);
        return result == EDBQueryResult::Success;
    }
    
    return false;
}

EDBQueryResult DBHelper::CreateAccountOnce(const std::wstring& userID, const std::wstring& userPW)
{
    if (!m_IsConnected)
    {
        return EDBQueryResult::ConnectionLost;
    }

    SQLHSTMT hStmt = SQL_NULL_HANDLE;
    bool bSuccess = false;


    auto CleanupStmt = [&]() {
        if (hStmt != SQL_NULL_HANDLE)
        {
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            hStmt = SQL_NULL_HANDLE;
        }
        };

    if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt)))
    {
        LOG_ERROR("Failed to Allocate Statement Handle in CreateAccount");
        return EDBQueryResult::Failed;
    }

    SQLSetStmtAttr(hStmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)5, 0);

    SQLWCHAR* query = (SQLWCHAR*)L"{call dbo.SP_CreateAccount(?, ?)}";

    if (!SQL_SUCCEEDED(SQLPrepare(hStmt, query, SQL_NTS)))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);

        bool lost = IsConnectionLost(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();

        if (lost)
        {
            m_IsConnected = false;
            return EDBQueryResult::ConnectionLost;
        }

        return EDBQueryResult::Failed;
    }

    SQLLEN idLen = SQL_NTS;
    SQLLEN pwLen = SQL_NTS;

    if (!SQL_SUCCEEDED(SQLBindParameter(
        hStmt,
        1,
        SQL_PARAM_INPUT,
        SQL_C_WCHAR,
        SQL_WVARCHAR,
        userID.length(),
        0,
        (SQLPOINTER)userID.c_str(),
        0,
        &idLen)))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    if (!SQL_SUCCEEDED(SQLBindParameter(
        hStmt,
        2,
        SQL_PARAM_INPUT,
        SQL_C_WCHAR,
        SQL_WVARCHAR,
        userPW.length(),
        0,
        (SQLPOINTER)userPW.c_str(),
        0,
        &pwLen)))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    SQLRETURN execRet = SQLExecute(hStmt);
    if (!SQL_SUCCEEDED(execRet))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);

        bool lost = IsConnectionLost(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();

        if (lost)
        {
            m_IsConnected = false;
            return EDBQueryResult::ConnectionLost;
        }

        return EDBQueryResult::Failed;
    }

    SQLRETURN fetchRet = SQLFetch(hStmt);
    if (fetchRet == SQL_NO_DATA)
    {
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    if (!SQL_SUCCEEDED(fetchRet))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);

        bool lost = IsConnectionLost(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();

        if (lost)
        {
            m_IsConnected = false;
            return EDBQueryResult::ConnectionLost;
        }

        return EDBQueryResult::Failed;
    }

    int resultCode = 0;
    SQLLEN len = 0;

    if (!SQL_SUCCEEDED(SQLGetData(hStmt, 1, SQL_C_LONG, &resultCode, sizeof(int), &len)))
    {
        PrintError(hStmt, SQL_HANDLE_STMT);
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    if (resultCode == -1)
    {
        LOG_WARN("Create Account Failed - UserID Already Exists! [%ls]", userID.c_str());
        CleanupStmt();
        return EDBQueryResult::Failed;
    }

    CleanupStmt();
    return EDBQueryResult::Success;
}


bool DBHelper::IsValidUserID(const std::wstring& inputID)
{
    // 1. Enforce an English-letter prefix and a 4-12 character alphanumeric ID.
    std::wregex pattern(L"^[a-zA-Z][a-zA-Z0-9]{3,11}$");
    if (!std::regex_match(inputID, pattern)) {
        return false;
    }

    // 2. Normalize to lowercase for case-insensitive reserved-word checks.
    std::wstring lowerID = inputID;
    std::transform(lowerID.begin(), lowerID.end(), lowerID.begin(), ::towlower);

    // 3. Keep a shared reserved-word list so repeated calls avoid reallocation.
    // Using static const avoids rebuilding the vector on every validation call.
    static const std::vector<std::wstring> forbiddenWords = {
        L"admin", L"gm", L"master", L"manager", L"system", L"test"
    };

    // 4. Reject IDs that contain any reserved word as a substring.
    for (const std::wstring& word : forbiddenWords) {
        // Reject the request as soon as a forbidden fragment is found.
        if (lowerID.find(word) != std::wstring::npos) {
            return false;
        }
    }

    return true;
}

bool DBHelper::IsValidUserPW(const std::wstring& inputPW)
{
    // ^          : start of the string
    // [a-zA-Z0-9]: letters and digits only
    // {4,12}     : 4 to 12 characters
    // $          : end of the string
    std::wregex pattern(L"^[a-zA-Z0-9]{4,12}$");

    return std::regex_match(inputPW, pattern);
}

bool DBHelper::IsValidAccountString(const std::wstring& inputStr)
{
    // ^          : start of the string
    // [a-zA-Z0-9]: letters and digits only
    // {4,12}     : 4 to 12 characters
    // $          : end of the string
    std::wregex pattern(L"^[a-zA-Z0-9]{4,12}$");

    return std::regex_match(inputStr, pattern);
}