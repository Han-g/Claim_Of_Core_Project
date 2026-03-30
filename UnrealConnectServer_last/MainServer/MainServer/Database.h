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

enum class EDBTaskType
{
    LOGIN,
    REGISTER
};

struct DBData
{
    int SessionIndex;
    std::wstring UserID;
    std::wstring UserPW;
    EDBTaskType TaskType;
};

class DBHelper
{
public:
    static DBHelper* GetInstance() { static DBHelper instance; return &instance; }

    // DB에 접속하는 함수 (서버 켤 때 한 번 호출)
    bool Connect();

    // 연결을 끊는 함수
    void Disconnect();

    // 간단한 로그인 확인 함수 (예시)
    bool CheckLogin(const std::wstring& userID, const std::wstring& userPW, int& playerUID);
    bool CreateAccount(const std::wstring& userID, const std::wstring& userPW);
    bool IsValidAccountString(const std::wstring& inputStr);

private:
    DBHelper();
    ~DBHelper();

    DBHelper(const DBHelper&) = delete;
    DBHelper& operator=(const DBHelper&) = delete;

    // 에러 발생 시 로그 찍는 함수
    void PrintError(SQLHANDLE handle, SQLSMALLINT type);

private:
    SQLHENV hEnv;   // 환경 핸들
    SQLHDBC hDbc;   // 연결 핸들
    SQLHSTMT hStmt; // 쿼리 수행 핸들

public:
    bool m_IsConnected = false;
};