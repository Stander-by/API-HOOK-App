#pragma once 
#include "pch.h"
#include <json.hpp>
#include <queue>
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert

#include "pch.h"
using json = nlohmann::json;
using namespace std;    

extern queue<json> MsgQueue;
queue<json> MsgQueue=queue<json>();
extern HANDLE D2Ppipe;
HANDLE D2Ppipe=INVALID_HANDLE_VALUE;
extern int id;
int id=0;

BOOL(WINAPI* OldWriteFile)(
	HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped
	) = WriteFile;

std::string to_utf8(LPCWSTR str)
{
    wstring wide_string=wstring(str);
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    return utf8_conv.to_bytes(wide_string);
}

std::string to_utf8(std::wstring wide_string)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    return utf8_conv.to_bytes(wide_string);
}

std::string to_utf8(LPCSTR str)
{
   return string(str);
}

std::string to_utf8(HWND hWnd)
{
    if(int(hWnd)==0)
    {
        return "NULL";
    }
    char buffer[50];
    int n = sprintf(buffer,  "%#p", hWnd);  
    std::string tmp = buffer;
    return tmp;
}

std::string to_utf8(HANDLE handle)
{
    char buffer[50];
    int n = sprintf(buffer,  " 0x%p", handle);  
    std::string tmp = buffer;
    return tmp;
}



std::string to_utf8(SYSTEMTIME time)
{
    char buffer[50];
    int n = sprintf(buffer,"%d-%d-%02d %02d:%02d:%02d:%03d", time.wYear, time.wMonth,
		time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);  
    std::string tmp = buffer;
    return tmp;
}
std::string to_utf8(SOCKET sock)
{
    char buffer[50];
    int n = sprintf(buffer,"%#x", sock);  
    std::string tmp = buffer;
    return tmp;
}


static __int64 GetUnixTime()
{
	string nowTimeUnix;
	string cs_uninxtime;
	string cs_milliseconds;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	time_t unixTime;
	time(&unixTime);
	char buf[30], buf1[30];
	sprintf_s(buf, sizeof(buf), "%I64d", (INT64)unixTime);
	sprintf_s(buf1, sizeof(buf1), "%03I64d", (INT64)sysTime.wMilliseconds);
	nowTimeUnix = string(buf) + string(buf1);
	return _atoi64(nowTimeUnix.c_str());
}

void sendMsg(json msg)
{
    // DetourDetach(&(PVOID &)OldHeapAlloc, NewHeapAlloc);
    // DetourTransactionCommit();
    DWORD wlen = 0;
    if (D2Ppipe != INVALID_HANDLE_VALUE)
    {
        msg["id"] = id;
        id++;
        msg["time"] = GetUnixTime();
        OldWriteFile(D2Ppipe, msg.dump().c_str(), msg.dump().length() + 1, &wlen, 0);
    }
    else
    {
        //OldMessageBoxA(NULL, "INVALID_HANDLE", "sendMsg", MB_OK);
    }    
    // DetourAttach(&(PVOID &)OldHeapAlloc, NewHeapAlloc);
	// DetourTransactionCommit();
}

