#pragma once

#define WIN32_LEAN_AND_MEAN

#include "logger.h"

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#include <string>
#include <iostream>
#include <regex>

#pragma comment(lib, "odbc32.lib")

enum class EDBQueryResult
{
    Success,
    Failed,
    ConnectionLost
};

enum class EDBTaskType
{
    LOGIN,
    REGISTER
};

struct DBData
{
    int SessionIndex = -1;
    uint64_t SessionGeneration = 0;
    std::wstring UserID;
    std::wstring UserPW;
    EDBTaskType TaskType = EDBTaskType::LOGIN;
};

class DBHelper
{
public:
    static DBHelper* GetInstance() { static DBHelper instance; return &instance; }

    // Connects to the database once during server startup.
    bool Connect();

    // Closes the active database connection and releases ODBC handles.
    void Disconnect();
    // Check Database Connection.
    bool IsConnectionLost(SQLHANDLE handle, SQLSMALLINT type);
    // Attempt to connect to the database when the database connection is lost.
    bool Reconnect();

    // Validates login credentials and returns the matching player UID on success.
    bool CheckLogin(const std::wstring& userID, const std::wstring& userPW, int& playerUID);
    EDBQueryResult CheckLoginOnce(const std::wstring& userID, const std::wstring& userPW, int& playerUID);

    // Creates a new account after validating the requested ID and password.
    bool CreateAccount(const std::wstring& userID, const std::wstring& userPW);
    EDBQueryResult CreateAccountOnce(const std::wstring& userID, const std::wstring& userPW);

    // Applies the basic length and character rules shared by account strings.
    bool IsValidAccountString(const std::wstring& inputStr);
    // Validates the user ID format and rejects reserved words.
    bool IsValidUserID(const std::wstring& inputID);
    // Validates the password format before account creation.
    bool IsValidUserPW(const std::wstring& inputPW);

private:
    DBHelper();
    ~DBHelper();

    DBHelper(const DBHelper&) = delete;
    DBHelper& operator=(const DBHelper&) = delete;

    // Logs diagnostic information returned by the given ODBC handle.
    void PrintError(SQLHANDLE handle, SQLSMALLINT type);

private:
    SQLHENV hEnv;   // ODBC environment handle.
    SQLHDBC hDbc;   // Database connection handle.

public:
    bool m_IsConnected = false;
};