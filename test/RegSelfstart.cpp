#define UNICODE
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;
int main() {
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	char* szSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hKey;

	//  打开指定子键
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;     //  如果不存在不创建
	LONG lRet = RegCreateKeyExA(hRoot, szSubKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
    MessageBoxW(NULL, L"selfstart", L"selfstart", MB_OK);
    return 0;
}