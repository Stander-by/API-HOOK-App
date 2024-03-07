#include "pch.h"
#include <string>
#include"untils.h"
#include <unordered_map>
using namespace std;
extern queue<json> MsgQueue;

unordered_map<UINT,string>  MessageBoxType= {
	{MB_OK,"MB_OK[确定]"},	
	{MB_OKCANCEL,"MB_OKCANCEL[确定/取消]"},
	{MB_ABORTRETRYIGNORE,"MB_ABORTRETRYIGNORE[中止/重试/忽略]"},
	{MB_YESNO,"MB_YESNO[是/否]"},
	{MB_YESNOCANCEL,"MB_YESNOCANCEL[是/否/取消]"},
	{MB_RETRYCANCEL,"MB_RETRYCANCEL[重试/取消]"},
	{MB_CANCELTRYCONTINUE,"MB_CANCELTRYCONTINUE[取消/重试/继续]"},
	{MB_HELP,"MB_HELP[添加帮助按钮]"},
};


int (WINAPI* OldMessageBoxA)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType
	) = MessageBoxA;

int (WINAPI* OldMessageBoxW)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_ UINT uType
	) = MessageBoxW;


extern "C" {
	__declspec(dllexport)int WINAPI NewMessageBoxA(
		HWND hWnd,
		LPCSTR lpText,
		LPCSTR lpCaption,
		UINT uType
	) {
		json msg= {
			{"type","MessageBox"},
			{"apiName","MessageBoxA"},
			{"shortInfo",to_utf8("[弹窗 ")+to_utf8(lpText)+to_utf8("]")},
			{"param",{
			{"hWnd",{{"description","[父窗口句柄]"},{"value",to_utf8(hWnd)}}},
			{"lpText",{{"description","[消息内容]"},{"value",to_utf8(lpText)}}},
			{"lpCaption",{{"description","[标题]"},{"value",to_utf8(lpCaption)}}},
			{"uType",{{"description","[消息框类型]"},{"value",MessageBoxType[uType]}}},
			}},
		};
		sendMsg(msg);
		return OldMessageBoxA(hWnd, lpText, lpCaption, uType);
	}


	__declspec(dllexport)int WINAPI NewMessageBoxW(
		HWND hWnd,
		LPCWSTR lpText,
		LPCWSTR lpCaption,
		UINT uType
	) {
		json msg = {
			{"type","MessageBox"},
			{"apiName","MessageBoxW"},
			{"shortInfo",to_utf8("[弹窗 ")+to_utf8(lpText)+to_utf8("]")},
			{"param",{
			{"hWnd",{{"description","[父窗口句柄]"},{"value",to_utf8(hWnd)}}},
			{"lpText",{{"description","[消息内容]"},{"value",to_utf8(lpText)}}},
			{"lpCaption",{{"description","[标题]"},{"value",to_utf8(lpCaption)}}},
			{"uType",{{"description","[消息框类型]"},{"value",MessageBoxType[uType]}}},
			}}
		};
		sendMsg(msg);
		return OldMessageBoxW(hWnd, lpText, lpCaption, uType);
	}

}