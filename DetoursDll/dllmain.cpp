// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma once
#include "pch.h"
#include "framework.h"
#include "windows.h"
#include "detours.h"
#include "stdio.h"
#include <atlbase.h>
#include <iostream>
#include <json.hpp>
#include <winsock.h>
#include <string>
#include <thread>

#include "untils.h"
#include "base64.cpp"
#include "Hook/fileHook.cpp"
#include "Hook/heapHook.cpp"
#include "Hook/msgBoxHook.cpp"
#include "Hook/regHook.cpp"
#include "Hook/socketHook.cpp"
#include "Hook/apiList.cpp"

using json = nlohmann::json;
using namespace std;
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ws2_32.lib")

//为了解决Heap Hook相关问题, D2Ppipe 在 untils.h 中定义为全局变量
//HANDLE D2Ppipe;
HANDLE P2Dpipe;
string currentFileName, currentWorkDir;




//DLL 到 Python 的管道线程 已使用阻塞方式移至untils.h


//Python 到 DLL 的管道线程
void P2DThread()
{
    char buffer[10240];
    while (true)
    {
        if (P2Dpipe != INVALID_HANDLE_VALUE)
        {
            DWORD dwByteRead;
            auto bRet = OldReadFile(P2Dpipe, buffer, sizeof(buffer), &dwByteRead, 0);
            if (bRet && dwByteRead > 0)
            {
                buffer[dwByteRead] = '\0';
                json msg = json::parse(buffer);
                json hello;
                hello["msg"] = "hello";
                OldMessageBoxA(NULL, msg.dump().c_str(), "Msg Got.", MB_OK);
            }
        }
        else
        {
            OldMessageBoxA(NULL, "INVALID_HANDLE", "Pipe", MB_OK);
        }
    }
}

void StartPipe()
{
    BOOL bRet;
    WaitNamedPipe(TEXT("\\\\.\\pipe\\d2p"), NMPWAIT_WAIT_FOREVER);
    D2Ppipe = CreateFile(TEXT("\\\\.\\pipe\\d2p"),GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (D2Ppipe == INVALID_HANDLE_VALUE)
    {
        DWORD errorCode = GetLastError();
        char buffer[2048];
        sprintf_s(buffer, "%d", errorCode);
        OldMessageBoxA(NULL, buffer, "Failed to Start Pipe!", MB_OK);
    }

    WaitNamedPipe(TEXT("\\\\.\\pipe\\p2d"), NMPWAIT_WAIT_FOREVER);
    P2Dpipe = CreateFile(TEXT("\\\\.\\pipe\\p2d"),GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (P2Dpipe == INVALID_HANDLE_VALUE)
    {
        DWORD errorCode = GetLastError();
        char buffer[2048];
        sprintf_s(buffer, "%d", errorCode);
        OldMessageBoxA(NULL, buffer, "Failed to Start Pipe!", MB_OK);
    }

    printf("Pipe Started.\n");

    //启动Pipe后台线程
    thread t1(P2DThread);
    t1.detach();
    thread t2(D2PThread);
    t2.detach();

}



BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{
    TCHAR exeFullName[MAX_PATH];
    GetModuleFileName(NULL, exeFullName, MAX_PATH);
    currentFileName = CW2A(exeFullName);

    TCHAR exeFullPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, exeFullPath);
    currentWorkDir = CW2A(exeFullPath);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);//禁用线程信号量，优化性能
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        //启动管道连接
        StartPipe();
        OldMessageBoxA(NULL, "程序启动", "Hook start", MB_OK);
        EnableDetours();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        DisableDetours();
        //关闭管道连接
        OldMessageBoxA(NULL, "程序结束", "Hook end", MB_OK);
        CloseHandle(D2Ppipe);
        CloseHandle(P2Dpipe);
        break;
    }
    return TRUE;
}
