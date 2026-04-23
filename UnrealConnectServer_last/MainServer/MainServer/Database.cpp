#include "Database.h"

DBHelper::DBHelper()
    : hEnv(SQL_NULL_HANDLE), hDbc(SQL_NULL_HANDLE), m_IsConnected(false)
{
}

DBHelper::~DBHelper()
{
    Disconnect();
}

bool DBHelper::Connect()
{
    SQLRETURN ret;

    // 1. Allocate the ODBC environment handle.
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 2. Select the ODBC 3.x API version.
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 3. Allocate the database connection handle.
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (!SQL_SUCCEEDED(ret)) return false;

    // 4. Fail fast if the login handshake takes too long.
    SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

    // 5. Open the database connection using the configured connection string.
    // Legacy DSN-based examples are kept below for reference only.
    // The active path below reads the full connection string from configuration.
    /*ret = SQLConnect(hDbc, (SQLWCHAR*)L"ClaimOfCore", SQL_NTS,
        (SQLWCHAR*)L"ServerConnection", SQL_NTS,
        (SQLWCHAR*)L"server", SQL_NTS);*/

    //SQLWCHAR connectStr[] = L"Driver={SQL Server};Server=DESKTOP-HW\SQLEXPRESS;Database=ClaimOfCore;Uid=ServerConnection;Pwd=server;";
    //SQLWCHAR connectStr[] = L"Driver={SQL Server};Server=127.0.0.1\\SQLEXPRESS;Database=ClaimOfCore;Uid=ServerConnection;Pwd=server;";

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
        //std::wcout << L"[DB] Connected Successfully!" << std::endl;
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
    }
    if (hEnv != SQL_NULL_HANDLE) { SQLFreeHandle(SQL_HANDLE_ENV, hEnv); }

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

bool DBHelper::CheckLogin(const std::wstring& userID, const std::wstring& userPW, int& playerUID)
{
    if (!m_IsConnected) { return false; }

    // Stored procedure shape kept here for reference.
    /*std::wstring query = L"{call SP_LoginAccess('";
    query += userID;
    query += L"', '";
    query += userPW;
    query += L"')}";*/

    // Allocate a fresh statement handle for this login request.
    SQLHSTMT hStmt = SQL_NULL_HANDLE;
    bool bSuccess = false;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        LOG_ERROR("Failed to Allocate Statement Handle in CheckLogin");
        return false;
    }

    // Prepare a parameterized stored procedure call.
    SQLWCHAR* query = (SQLWCHAR*)L"{call SP_LoginAccess(?, ?)}";
    if (SQLPrepare(hStmt, query, SQL_NTS) != SQL_SUCCESS) { 
        LOG_ERROR("SQL Prepare Failed!"); 
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return false; 
    }

    // SQL_NTS tells ODBC to treat the bound string as null-terminated.
    SQLLEN idLen = SQL_NTS;
    SQLLEN pwLen = SQL_NTS;

    // Bind the input values to the prepared procedure parameters.
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,
        userID.length(), 0, (SQLPOINTER)userID.c_str(), 0, &idLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,
        userPW.length(), 0, (SQLPOINTER)userPW.c_str(), 0, &pwLen);

    // Execute the stored procedure.
    if (SQLExecDirect(hStmt, query, SQL_NTS) != SQL_SUCCESS) { 
        SQLWCHAR sqlState[6], message[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message) / sizeof(SQLWCHAR), &textLength);

        LOG_ERROR("DB Query Failed! State: %ls, Msg: %ls", sqlState, message);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return false; 
    }

    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        int loginResult = 0;
        SQLLEN len = 0;

        SQLGetData(hStmt, 1, SQL_C_LONG, &loginResult, sizeof(int), &len);

        if (loginResult == 0) {
            LOG_ERROR("Failed to Server Login - ID / PW is InValid");
            SQLCloseCursor(hStmt); // Close the cursor before releasing the statement handle.
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            return false;
        }

        else {
            int accountUID = 0;
            SQLGetData(hStmt, 2, SQL_C_LONG, &accountUID, sizeof(int), &len);

            playerUID = accountUID;

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            LOG_INFO("Login to Server Successful! [UID: %d]", accountUID);
            return true;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return false;
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

bool DBHelper::CreateAccount(const std::wstring& userID, const std::wstring& userPW)
{
    if (!m_IsConnected || (!IsValidUserID(userID)) || !IsValidUserPW(userPW)) { return false; }

    SQLHSTMT hStmt = SQL_NULL_HANDLE;
    bool bSuccess = false;

    // Allocate a fresh statement handle for this account creation request.
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
        LOG_ERROR("Failed to Allocate Statement Handle in CreateAccount");
        return false;
    }

    // Prepare the stored procedure call.
    SQLWCHAR* query = (SQLWCHAR*)L"{call SP_CreateAccount(?, ?)}";
    if (SQLPrepare(hStmt, query, SQL_NTS) != SQL_SUCCESS) {
        LOG_ERROR("SQL Prepare Failed in CreateAccount");
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return false;
    }

    // Bind the input values to the prepared procedure parameters.
    SQLLEN idLen = SQL_NTS;
    SQLLEN pwLen = SQL_NTS;

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,
        userID.length(), 0, (SQLPOINTER)userID.c_str(), 0, &idLen);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR,
        userPW.length(), 0, (SQLPOINTER)userPW.c_str(), 0, &pwLen);

    // Execute the stored procedure.
    if (SQLExecDirect(hStmt, query, SQL_NTS) != SQL_SUCCESS) {
        LOG_ERROR("DB Query Failed: SP_CreateAccount for ID: %ls", userID.c_str());
        SQLFreeStmt(hStmt, SQL_CLOSE);
        return false;
    }

    // Read the stored procedure result.
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        int resultCode = 0;
        SQLLEN len = 0;

        // The first column returns either an error code or the new AccountUID.
        SQLGetData(hStmt, 1, SQL_C_LONG, &resultCode, sizeof(int), &len);

        if (resultCode == -1) {
            // -1 indicates that the requested user ID already exists.
            LOG_WARN("Create Account Failed - UserID Already Exists! [%ls]", userID.c_str());
            SQLCloseCursor(hStmt);
            return false;
        }
        else {
            // Any other value is treated as the UID of the newly created account.
            int newAccountUID = resultCode;
            LOG_INFO("Account Created Successfully! [New UID: %d]", newAccountUID);
            SQLCloseCursor(hStmt);
            return true;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return false;
}
