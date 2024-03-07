#include"pch.h"
#include "untils.h"
#include "fileHook.cpp"
#include<unordered_set>
#include<unordered_map>
using namespace std;

unordered_map<DWORD,string> HeapOptions={
	{0x00000000,"NULL [默认值]"},
	{0x00040000,"HEAP_CREATE_ENABLE_EXECUTE [关闭数据执行保护]"},
	{0x00000001,"HEAP_NO_SERIALIZE [不使用序列化访问]"},
	{0x00000004,"HEAP_GENERATE_EXCEPTIONS [调用失败时引发异常]"},
	{0x00000008,"HEAP_ZERO_MEMORY [初始化为0]"},
};

unordered_set<HANDLE> AllocatedMems;
BOOL AlreadyInAlloc = false;

//跳出生命周期 防止重复捕获
json HeapAlloc_msg = {
	{"type", "Heap"},
	{"id", -1},
	{"time",GetUnixTime()},
	{"apiName", "HeapAlloc"},
	{"shortInfo", to_utf8("[申请内存]")},
	{"param", {
		{"hHeap", {{"description", "[堆句柄]"}, {"value", ""}}},
		{"dwFlags", {{"description", "[申请选项]"}, {"value", ""}}},
		{"dwBytes", {{"description", "[申请大小] Bytes"}, {"value", ""}}},
	}},
	{"return", {
		{"lpMem", {{"description", "[申请地址]"}, {"value", ""}}},
	}},
};

json HeapFree_msg={
		{"type","Heap"},
		{"id", -1},
		{"time",""},
		{"apiName","HeapFree"},
		{"shortInfo",to_utf8("[释放堆]")},
		{"param",{
			{"hHeap",{{"description","[堆句柄]"},{"value",""}}},
			{"dwFlags",{{"description","[释放选项]"},{"value",""}}},
			{"lpMem",{{"description","[释放地址]"},{"value",""}}},
		}},
		{"return",{
			{"result",{{"description","[释放结果]"},{"value",""}}},
		}},
		{"safety",{
			{"handleError",{{"description","[重复释放或非堆句柄]"},{"value",false}}},
		}},
	};
DWORD wlen;

HANDLE(WINAPI* OldHeapCreate)(
	DWORD fIOoptions,
	SIZE_T dwInitSize,
	SIZE_T dwMaxSize
	) = HeapCreate;
BOOL(WINAPI* OldHeapDestroy)(HANDLE) = HeapDestroy;
LPVOID(WINAPI* OldHeapAlloc)(
	_In_ HANDLE hHeap,
	_In_ DWORD dwFlags,
	_In_ SIZE_T dwBytes
	) = HeapAlloc;
BOOL(WINAPI* OldHeapFree)(
	HANDLE                 hHeap,
	DWORD                  dwFlags,
	_Frees_ptr_opt_ LPVOID lpMem
	) = HeapFree;



extern "C" {
	__declspec(dllexport)HANDLE WINAPI NewHeapCreate(
		DWORD fIOoptions,
		SIZE_T dwInitSize,
		SIZE_T dwMaxSize
	) {
		HANDLE hHeap = OldHeapCreate(fIOoptions, dwInitSize, dwMaxSize);
		json msg={
			{"type","Heap"},
			{"apiName","HeapCreate"},
			{"shortInfo",to_utf8("[创建堆]")},
			 {"param",{
			 	{"fIOoptions",{{"description","[申请选项]"},{"value",HeapOptions[fIOoptions]}}},
			 	{"dwInitSize",{{"description","[初始大小] Bytes"},{"value",dwInitSize}}},
			 	{"dwMaxSize",{{"description","[最大大小] Bytes"},{"value",dwMaxSize}}},
			 }},
			{"return",{
				{"hHeap",{{"description","[堆句柄]"},{"value",to_utf8(hHeap)}}},
			}},
		};
		sendMsg(msg);
		return hHeap;
	}

	__declspec(dllexport)BOOL WINAPI NewHeapDestroy(
		HANDLE hHeap
	) {
		auto ret = OldHeapDestroy(hHeap);
		json msg={
			{"type","Heap"},
			{"apiName","HeapDestroy"},
			{"shortInfo",to_utf8("[销毁堆]")},
			 {"param",{
			 	{"hHeap",{{"description","[堆句柄]"},{"value",to_utf8(hHeap)}}},
			 }},
			{"return",{
				{"result",{{"description","[销毁结果]"},{"value",ret}}},
			}},
		};
		sendMsg(msg);
		return ret;
	}

}


__declspec(dllexport)LPVOID WINAPI NewHeapAlloc(
	_In_ HANDLE hHeap,
	_In_ DWORD dwFlags,
	_In_ SIZE_T dwBytes
) {

	// DetourDetach(&(PVOID&)OldHeapAlloc, NewHeapAlloc);
    // DetourTransactionCommit();

	if (AlreadyInAlloc == true) {
		return OldHeapAlloc(hHeap, dwFlags, dwBytes);
	}
	AlreadyInAlloc = true;
	LPVOID lpMem = OldHeapAlloc(hHeap, dwFlags, dwBytes);
	AllocatedMems.insert(lpMem);

	// //printf("AllocatedMems");
	// HeapAlloc_msg["id"] = id;
	// id++;
	// HeapAlloc_msg["time"] = GetUnixTime();
	// HeapAlloc_msg["param"]["hHeap"]["value"] = to_utf8(hHeap);
	// HeapAlloc_msg["param"]["dwFlags"]["value"] = HeapOptions[dwFlags];
	// HeapAlloc_msg["param"]["dwBytes"]["value"] = dwBytes;
	// HeapAlloc_msg["return"]["lpMem"]["value"] = to_utf8(lpMem);
	// OldWriteFile(D2Ppipe, HeapAlloc_msg.dump().c_str(), HeapAlloc_msg.dump().length() + 1, &wlen, 0);
	// DetourAttach(&(PVOID &)OldHeapAlloc, NewHeapAlloc);
	// DetourTransactionCommit();
	AlreadyInAlloc = false;
	return lpMem;
}

__declspec(dllexport)BOOL WINAPI NewHeapFree(
	HANDLE                 hHeap,
	DWORD                  dwFlags,
	_Frees_ptr_opt_ LPVOID lpMem
) {
	// BOOL res = FALSE;
	// bool repeat = true;
	// if (AllocatedMems.count(hHeap)) {
	// 	AllocatedMems.erase(hHeap);
	// 	repeat = false;
	// }
	// if (repeat) {
	// 	printf("Heap Free ERROR : maybe heap Reaptedly free or Not heap HANDLE\n");
	// 	res = FALSE;
	// }
	// printf("$HOOKEND$");

	// if (!AllocatedMems.count(hHeap)) {
	//  	msg["safety"]["handleError"]["value"]=true;
	// 	sendMsg(msg);
	// 	return FALSE;
	// }

	// sendMsg(msg);
	// AllocatedMems.erase(hHeap);
	HeapFree_msg["id"] = id;
	id++;
	HeapFree_msg["time"] = GetUnixTime();
	HeapFree_msg["param"]["hHeap"]["value"] = to_utf8(hHeap);
	HeapFree_msg["param"]["dwFlags"]["value"] = HeapOptions[dwFlags];
	HeapFree_msg["param"]["lpMem"]["value"] = to_utf8(lpMem);
	
	if (!AllocatedMems.count(lpMem)) {
	 	HeapFree_msg["safety"]["handleError"]["value"]=true;
		OldWriteFile(D2Ppipe, HeapFree_msg.dump().c_str(), HeapFree_msg.dump().length() + 1, &wlen, 0);
		return FALSE;
	}
	AllocatedMems.erase(lpMem);
	OldWriteFile(D2Ppipe, HeapFree_msg.dump().c_str(), HeapFree_msg.dump().length() + 1, &wlen, 0);
	return OldHeapFree(hHeap, dwFlags, lpMem);
}