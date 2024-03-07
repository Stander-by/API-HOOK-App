#define UNICODE
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;
int main() {
    HKEY hk = NULL;
	HKEY hk2 = NULL;
	LPCSTR keyname = "SOFTWARE\\HUSTCSE\\TEST";
	long unsigned int dwType = REG_SZ;
	char buffer[257] = { 0 };
	DWORD dwLen = 256;
	auto res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, keyname , 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hk, NULL);
	cout<<"RegCreateKeyExA"<<endl;
	RegCloseKey(hk);
	RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyname, 0, KEY_ALL_ACCESS, &hk2);
	cout<<"RegOpenKeyExA"<<endl;
	RegSetValueExA(hk2, "Hello", 0, REG_SZ, (PBYTE)"Hello HUST", 11);
	cout<<"RegSetValueExA"<<endl;
	RegQueryValueExA(hk2, "Hello", NULL, &dwType, (BYTE*)buffer, &dwLen);
	cout<<"RegQueryValueExA"<<endl;
	RegCloseKey(hk2);
	cout<<"RegCloseKey"<<endl;
    MessageBoxW(NULL, L"Hello", L"Hello", MB_OK);
    return 0;
}