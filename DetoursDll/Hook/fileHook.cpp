#pragma once
#include"pch.h"
#include "untils.h"
#include <unordered_map>
using namespace std;

unordered_map<DWORD,string>  FileAccessMask= {
	{0x80000000,"GENERIC_READ [读权限]"},
	{0x40000000,"GENERIC_WRITE [写权限]"},
};
unordered_map<DWORD,string>  FileShareMode= {
	{0x00000000,"[阻止其它进程访问]"},
	{0x00000001,"FILE_SHARE_READ [允许读取访问权限]"},
	{0x00000002,"FILE_SHARE_WRITE [允许写访问权限]"},
	{0x00000004,"FILE_SHARE_DELETE [允许删除访问权限]"},
};
unordered_map<DWORD, string> FileCreationDisposition = {
	{1, "CREATE_NEW [不存在时创建文件]"},
	{2, "CREATE_ALWAYS [总是创建文件]"},
	{3, "OPEN_EXISTING [文件存在时打开文件]"},
	{4, "OPEN_ALWAYS [总是打开文件]"},
	{5, "TRUNCATE_EXISTING [文件存在时清空文件]"},
};
unordered_map<DWORD, string> FileFlagsAndAttributes = {
	{128, "FILE_ATTRIBUTE_NORMAL [无属性]"},
};
//工具方法
unordered_map<HANDLE, wstring> fileMap;


wstring getFileExt(const wstring& filepath) {
	auto idx = filepath.find_last_of(L'.');
	if (idx == wstring::npos) return L"";
	return filepath.substr(idx + 1);
}

bool judgeExe(HANDLE hFile) {
	if (fileMap.count(hFile) == 0) return false;
	auto ext = getFileExt(fileMap[hFile]);
	return ext == L"exe" || ext == L"dll" || ext == L"ocx";
}

bool judgeExe(const WCHAR* filepath) {
	auto ext = getFileExt(filepath);
	return ext == L"exe" || ext == L"dll" || ext == L"ocx";
}


HANDLE(WINAPI* OldCreateFile)(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	) = CreateFileW;
BOOL(WINAPI* OldDeleteFile)(
	LPCTSTR lpFileName
	) = DeleteFile;
// BOOL(WINAPI* OldWriteFile)(
// 	HANDLE hFile,
// 	LPCVOID lpBuffer,
// 	DWORD nNumberOfBytesToWrite,
// 	LPDWORD lpNumberOfBytesWritten,
// 	LPOVERLAPPED lpOverlapped
// 	) = WriteFile;
BOOL(WINAPI* OldReadFile)(
	HANDLE hFile,
	LPVOID lpBuffer,
	DWORD nNumberOfBytesToRead,
	LPDWORD lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
	) = ReadFile;
BOOL(WINAPI* OldCopyFile)(
	LPCWSTR lpExistingFileName,
	LPCWSTR lpNewFileName,
	BOOL bFailIfExists
	) = CopyFile;


	__declspec(dllexport)HANDLE WINAPI NewCreateFile(
		LPCWSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile
	) {
		HANDLE hFile=OldCreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
			dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		if (GetFileType(hFile) != FILE_TYPE_DISK) {
			return hFile;
		}
		fileMap[hFile]=wstring(lpFileName);


		json msg = {
			{"type","File"},
			{"apiName","CreateFile"},
			{"shortInfo",to_utf8("[打开或创建文件]")},
			{"param",{
				{"lpFileName",{{"description","[文件名称]"},{"value",to_utf8(lpFileName)}}},
				{"dwDesiredAccess",{{"description","[访问权限]"},{"value",FileAccessMask[dwDesiredAccess]}}},
				{"dwShareMode",{{"description","[共享模式]"},{"value",FileShareMode[dwShareMode]}}},
				{"dwCreationDisposition",{{"description","[创建模式]"},{"value",FileCreationDisposition[dwCreationDisposition]}}},
				{"dwFlagsAndAttributes",{{"description","[文件属性]"},{"value",FileFlagsAndAttributes[dwFlagsAndAttributes]}}},
				{"hTemplateFile",{{"description","[模板文件句柄]"},{"value",to_utf8(hTemplateFile)}}},
			}},
			{"return",{
				{"hFile",{{"description","[文件句柄]"},{"value",to_utf8(hFile)}}},
			}},
			{"safety",{
				{"isExe",{{"description","[是否为可执行文件]"},{"value",judgeExe(lpFileName)}}},
			}},
		};
		sendMsg(msg);
		return hFile;
	}



	__declspec(dllexport)BOOL WINAPI NewDeleteFile(
		LPCTSTR lpFileName 
	) {
		bool isExe = judgeExe(lpFileName);

		json msg = {
			{"type","File"},
			{"apiName","DeleteFile"},
			{"shortInfo",to_utf8("[删除文件 ")+to_utf8(lpFileName)+to_utf8("]")},
			{"param",{
				{"lpFileName",{{"description","[文件名称]"},{"value",to_utf8(lpFileName)}}},
			}},
			{"safety",{
				{"isExe",{{"description","[是否为可执行文件]"},{"value",isExe}}},
			}},
		};
		sendMsg(msg);
		return OldDeleteFile(lpFileName);
	}

	__declspec(dllexport)BOOL WINAPI NewReadFile(
		HANDLE hFile,
		LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead,
		LPDWORD lpNumberOfBytesRead,
		LPOVERLAPPED lpOverlapped
	) {
		BOOL ret = OldReadFile(hFile, lpBuffer, nNumberOfBytesToRead,
			lpNumberOfBytesRead, lpOverlapped);
		
		if (GetFileType(hFile) != FILE_TYPE_DISK) {
			return ret;
		}
		int len = (lpNumberOfBytesRead ? *lpNumberOfBytesRead : 0);
		WCHAR filename[260];
		GetFinalPathNameByHandle(hFile,filename,260,0);
		
		json msg = {
			{"type","File"},
			{"apiName","ReadFile"},
			{"shortInfo",to_utf8("[读取文件 ")+to_utf8(filename)+to_utf8("]")},
			{"param",{
				{"filename",{{"description","[文件名称]"},{"value",to_utf8(filename)}}},
				{"hFile",{{"description","[文件句柄]"},{"value",to_utf8(hFile)}}},
				{"nNumberOfBytesToRead",{{"description","[欲读取字节数]"},{"value",nNumberOfBytesToRead}}},
				{"lpOverlapped",{{"description","[重叠结构]"},{"value",int(lpOverlapped)}}},
			}},
			{"return",{
				{"ret",{{"description","[返回值]"},{"value",ret}}},
				{"len",{{"description","[读取字节数]"},{"value",len}}},
			}},
			{"safety",{
				{"isExe",{{"description","[是否为可执行文件]"},{"value",judgeExe(filename)}}},
			}},
		};

		// if(len<2048 && len>0){
		// 	msg["param"]["lpBuffer"]={{"description","[缓冲区]"},{"value",string((char*)lpBuffer,len)}};
		// }
		// else if(len>2048){
		// 	msg["param"]["lpBuffer"]={{"description","[缓冲区]"},{"value","[数据过长]"}};
		// }
		sendMsg(msg);
		return ret;
	}


	__declspec(dllexport)BOOL WINAPI NewCopyFile(
		LPCWSTR lpExistingFileName,
		LPCWSTR lpNewFileName,
		BOOL bFailIfExists
	) {
		WCHAR curFile[MAX_PATH];
		WCHAR copiedFile[MAX_PATH];
		GetModuleFileName(NULL, curFile, MAX_PATH);
		GetFullPathName(lpExistingFileName, MAX_PATH, copiedFile, NULL);

		json msg = {
			{"type","File"},
			{"apiName","CopyFile"},
			{"shortInfo",to_utf8("[复制文件 ")+to_utf8(lpExistingFileName)+to_utf8("]")},
			{"param",{
				{"lpExistingFileName",{{"description","[源文件名称]"},{"value",to_utf8(lpExistingFileName)}}},
				{"lpNewFileName",{{"description","[目标文件名称]"},{"value",to_utf8(lpNewFileName)}}},
				{"bFailIfExists",{{"description","[是否覆盖]"},{"value",bFailIfExists}}},
			}},
			{"return",{
				{"curFile",{{"description","[当前文件]"},{"value",to_utf8(curFile)}}},
				{"copiedFile",{{"description","[复制文件]"},{"value",to_utf8(copiedFile)}}},
			}},
			{"safety",{
				{"isExe",{{"description","[是否为可执行文件]"},{"value",judgeExe(lpExistingFileName)}}},
				{"selfcopy",{{"description","[是否为自复制]"},{"value",wcscmp(curFile, copiedFile) == 0}}},
			}},
		};
		sendMsg(msg);
		return OldCopyFile(lpExistingFileName, lpNewFileName, bFailIfExists);
	}


	__declspec(dllexport)BOOL WINAPI NewWriteFile(
		HANDLE hFile,
		LPCVOID lpBuffer,
		DWORD nNumberOfBytesToWrite,
		LPDWORD lpNumberOfBytesWritten,
		LPOVERLAPPED lpOverlapped
	) {
		BOOL ret = OldWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite,
			lpNumberOfBytesWritten, lpOverlapped);
		if (GetFileType(hFile) != FILE_TYPE_DISK) {
			return ret;
		}
		int len = (lpNumberOfBytesWritten ? *lpNumberOfBytesWritten : 0);
		WCHAR filename[260];
		GetFinalPathNameByHandleW(hFile,filename,260,0);
		json msg = {
			{"type","File"},
			{"apiName","WriteFile"},
			{"shortInfo",to_utf8("[写入文件 ")+to_utf8(filename)+to_utf8("]")},
			{"param",{
				{"filename",{{"description","[文件名称]"},{"value",to_utf8(filename)}}},
				{"hFile",{{"description","[文件句柄]"},{"value",to_utf8(hFile)}}},
				{"nNumberOfBytesToWrite",{{"description","[欲写入字节数]"},{"value",nNumberOfBytesToWrite}}},
				{"lpOverlapped",{{"description","[重叠结构]"},{"value",int(lpOverlapped)}}},
				{"lpBuffer",{{"description","[写入缓冲区]"},{"value",string((char*)lpBuffer, len)}}},
			}},
			{"return",{
				{"ret",{{"description","[返回值]"},{"value",ret}}},
				{"len",{{"description","[写入字节数]"},{"value",len}}},
			}},
			{"safety",{
				{"isExe",{{"description","[是否为可执行文件]"},{"value",judgeExe(filename)}}},
			}},
			
		};
		sendMsg(msg);
		return ret;
	}
