#include "pch.h"
#include "untils.h"
#include<unordered_map>
using namespace std;

unordered_map<DWORD,string> RegeditHkey= {
	{0x80000000,"HKEY_CLASSES_ROOT"},
	{0x80000001,"HKEY_CURRENT_USER"},
	{0x80000002,"HKEY_LOCAL_MACHINE"},
	{0x80000003,"HKEY_USERS"},
	{0x80000005,"HKEY_CURRENT_CONFIG"},
};
unordered_map<DWORD,string> RegeditOptions= {
	{0x00000000,"REG_OPTION_NON_VOLATILE [此键不易失]"},
	{0x00000001,"REG_OPTION_VOLATILE [此键易失]"},
	{0x00000002,"REG_OPTION_CREATE_LINK [此键为符号链接]"},
	{0x00000004,"REG_OPTION_BACKUP_RESTORE [使用备份/恢复权限打开]"},
	{0x00000008,"REG_OPTION_OPEN_LINK [此键为符号链接]"},
};
unordered_map<DWORD,string> RegeditKeyAccess= {
	{0xF003F,"KEY_ALL_ACCESS [全部权限]"},
	{0x20019,"KEY_READ [读取键相关权限]"},
	{0x20006,"KEY_WRITE [写键相关权限]"},
	{0x0020,"KEY_CREATE_LINK [保留供系统使用]"},
	{0x0004,"KEY_CREATE_SUB_KEY [创建子项]"},
	{0x0008,"KEY_ENUMERATE_SUB_KEYS [枚举子项]"},
	{0x0010,"KEY_NOTIFY [请求更改通知]"},
	{0x0001,"KEY_QUERY_VALUE [查询值]"},
	{0x0002,"KEY_SET_VALUE [设置值]"},
	{0x0000,"NULL [继承父键]"},
};
unordered_map<DWORD,string> RegeditDisposition= {
	{0x00000000,"[无处置信息]"},
	{0x00000001,"REG_CREATED_NEW_KEY [键不存在并已创建]"},
	{0x00000002,"REG_OPENED_EXISTING_KEY [键存在并打开]"},
};
unordered_map<DWORD,string> RegeditType= {
	{0,"REG_NONE [无类型]"},
	{1,"REG_SZ [Unicode字符串]"},
	{2,"REG_EXPAND_SZ [含环境变量字符串]"},
	{3,"REG_BINARY [二进制类型]"},
	{4,"REG_DWORD [32位字符]"},
	{5,"REG_DWORD_BIG_ENDIAN [32位大端存储]"},
	{6,"REG_LINK [含符号字符串]"},
	{7,"REG_MULTI_SZ [多个字符串]"},
	{11,"REG_QWORD [64位数字]"},
};


static LSTATUS(WINAPI* OldRegCreateKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) = RegCreateKeyExA;
static LSTATUS(WINAPI* OldRegOpenKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) = RegOpenKeyExA;
static LSTATUS(WINAPI* OldRegCloseKey)(HKEY hKey) = RegCloseKey;
static LSTATUS(WINAPI* OldRegQueryValueExA)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) = RegQueryValueExA;
static LSTATUS(WINAPI* OldRegSetValueExA)(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData) = RegSetValueExA;


extern "C" __declspec(dllexport) LSTATUS WINAPI NewRegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) {
    auto status = OldRegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
	json msg= {
		{"type","Reg"},
		{"apiName","RegCreateKeyExA"},
		{"shortInfo","[创建/打开注册表项 "+RegeditHkey[(int(hKey))&(0xFFFFFFFF)]+"\\"+to_utf8(lpSubKey)+"]"},
		{"param",{
			{"hKey",{{"description","[主键]"},{"value",RegeditHkey[((int(hKey))&(0xFFFFFFFF))]}}},//与操作是必要的...
			{"lpSubKey",{{"description","[子键]"},{"value",to_utf8(lpSubKey)}}},
			{"Reserved",{{"description","[保留]"},{"value",Reserved}}},
			{"lpClass",{{"description","[用户定义类类型]"},{"value",lpClass == NULL?"NULL":to_utf8(lpClass)}}},
			{"dwOptions",{{"description","[选项]"},{"value",RegeditOptions[dwOptions]}}},
			{"samDesired",{{"description","[访问权限]"},{"value",RegeditKeyAccess[samDesired]}}},
			{"lpSecurityAttributes",{{"description","[安全参数结构指针]"},{"value",to_utf8(lpSecurityAttributes)}}},
		}},
		{"return",{
			{"phkResult",{{"description","[返回操作句柄]"},{"value",to_utf8(phkResult)}}},
			{"lpdwDisposition",{{"description","[处置信息]"},{"value",lpdwDisposition==NULL?"NULL":RegeditDisposition[*lpdwDisposition]}}},
			{"status",{{"description","[返回状态]"},{"value",status}}},
		}},
		{"safety",{
			{"selfstart",{{"description","[自启动项修改]"},{"value",false}}},
		}},
	};
	if ((hKey == HKEY_CURRENT_USER ||hKey == HKEY_LOCAL_MACHINE)&& strcmp(lpSubKey,
											"Software\\Microsoft\\Windows\\CurrentVersion\\Run") == 0)
	{
		msg["safety"]["selfstart"]["value"] = true;
	}
	sendMsg(msg);
    return status;
}

extern "C" __declspec(dllexport) LSTATUS WINAPI NewRegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
    auto status = OldRegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	json msg= {
		{"type","Reg"},
		{"apiName","RegOpenKeyExA"},
		{"shortInfo","[打开注册表项 "+RegeditHkey[(int(hKey))&(0xFFFFFFFF)]+"\\"+to_utf8(lpSubKey)+"]"},
		{"param",{
			{"hKey",{{"description","[主键]"},{"value",RegeditHkey[((int(hKey))&(0xFFFFFFFF))]}}},
			{"lpSubKey",{{"description","[子键]"},{"value",to_utf8(lpSubKey)}}},
			{"ulOptions",{{"description","[选项]"},{"value",RegeditOptions[ulOptions]}}},
			{"samDesired",{{"description","[访问权限]"},{"value",RegeditKeyAccess[samDesired]}}},
		}},
		{"return",{
			{"phkResult",{{"description","[返回操作句柄]"},{"value",to_utf8(phkResult)}}},
			{"status",{{"description","[返回状态]"},{"value",status}}},
		}},
		{"safety",{
			{"selfstart",{{"description","[自启动项修改]"},{"value",false}}},
		}},
	};
	if ((hKey == HKEY_CURRENT_USER ||hKey == HKEY_LOCAL_MACHINE) && strcmp(lpSubKey,
											"Software\\Microsoft\\Windows\\CurrentVersion\\Run") == 0)
	{
		msg["safety"]["selfstart"]["value"] = true;
	}
    sendMsg(msg);
    return status;
}

extern "C" __declspec(dllexport) LSTATUS WINAPI NewRegCloseKey(HKEY hKey) {
    auto status = OldRegCloseKey(hKey);
    
    json msg= {
		{"type","Reg"},
		{"apiName","RegCloseKey"},
		{"shortInfo","[关闭注册表项 "+RegeditHkey[(int(hKey))&(0xFFFFFFFF)]+"]"},
		{"param",{
			{"hKey",{{"description","[主键]"},{"value",RegeditHkey[((int(hKey))&(0xFFFFFFFF))]}}},
		}},
		{"return",{
			{"status",{{"description","[返回状态]"},{"value",status}}},
		}},
	};
    sendMsg(msg);
    return status;
}

// RegQueryValueExA 代替函数
extern "C" __declspec(dllexport) LSTATUS WINAPI NewRegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
    auto status = OldRegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
    
    json msg= {
		{"type","Reg"},
		{"apiName","RegQueryValueExA"},
		{"shortInfo","[查询注册表项 "+RegeditHkey[(int(hKey))&(0xFFFFFFFF)]+"\\"+to_utf8(lpValueName)+"]"},
		{"param",{
			{"hKey",{{"description","[主键]"},{"value",RegeditHkey[((int(hKey))&(0xFFFFFFFF))]}}},
			{"lpValueName",{{"description","[键名]"},{"value",to_utf8(lpValueName)}}},
			{"lpReserved",{{"description","[保留]"},{"value",to_utf8(lpReserved)}}},
			{"lpType",{{"description","[键值类型指针]"},{"value",to_utf8(lpType)}}},
			{"lpTypeValue",{{"description","[键值类型]"},{"value",lpType==NULL?"NULL":RegeditType[*lpType]}}},

			{"lpData",{{"description","[键值内容指针]"},{"value",to_utf8(lpData)}}},
			{"lpcbData",{{"description","[键值长度指针]"},{"value",to_utf8(lpcbData)}}},
			{"lpcbDataValue",{{"description","[键值长度]"},{"value",lpcbData==NULL?"NULL":to_string(*lpcbData)}}},
			{"lpDataValue",{{"description","[键值内容]"},{"value",lpData==NULL?"NULL":string((char*)lpData)}}},
		}},
		{"return",{
			{"status",{{"description","[返回状态]"},{"value",status}}},
		}},
	};
	sendMsg(msg);
    return status;
}

// RegSetValueExA 代替函数
extern "C" __declspec(dllexport) LSTATUS WINAPI NewRegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE * lpData, DWORD cbData) {
    auto status = OldRegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);
    json msg= {
		{"type","Reg"},
		{"apiName","RegSetValueExA"},
		{"shortInfo","[设置注册表项 "+RegeditHkey[(int(hKey))&(0xFFFFFFFF)]+"\\"+to_utf8(lpValueName)+"]"},
		{"param",{
			{"hKey",{{"description","[主键]"},{"value",RegeditHkey[((int(hKey))&(0xFFFFFFFF))]}}},
			{"lpValueName",{{"description","[键名]"},{"value",to_utf8(lpValueName)}}},
			{"Reserved",{{"description","[保留]"},{"value",Reserved}}},
			{"dwType",{{"description","[键值类型]"},{"value",RegeditType[dwType]}}},
			{"lpData",{{"description","[键值内容]"},{"value",string((char*)lpData)}}},
			{"cbData",{{"description","[键值长度]"},{"value",cbData}}},
		}},
		{"return",{
			{"status",{{"description","[返回状态]"},{"value",status}}},
		}},
	};

	sendMsg(msg);
    return status;
}