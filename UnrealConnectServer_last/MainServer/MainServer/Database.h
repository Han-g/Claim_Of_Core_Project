#pragma once

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#include <string>
#include <iostream>

#pragma comment(lib, "odbc32.lib")

class DBHelper
{
public:
    DBHelper();
    ~DBHelper();

    // DB에 접속하는 함수 (서버 켤 때 한 번 호출)
    bool Connect();

    // 연결을 끊는 함수
    void Disconnect();

    // 간단한 로그인 확인 함수 (예시)
    bool CheckLogin(const std::wstring& userId);

private:
    // 에러 발생 시 로그 찍는 함수
    void PrintError(SQLHANDLE handle, SQLSMALLINT type);

private:
    SQLHENV hEnv;   // 환경 핸들
    SQLHDBC hDbc;   // 연결 핸들
    SQLHSTMT hStmt; // 쿼리 수행 핸들

public:
    bool m_IsConnected = false;
};