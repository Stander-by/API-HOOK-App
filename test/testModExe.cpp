#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <windows.h>

int main() {
		MessageBoxA(NULL, "CreateFileW", "Error", MB_OK);

	HANDLE hFile = CreateFileW(L"D:\\modexe.exe", GENERIC_READ | GENERIC_WRITE,
		NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		hFile = NULL;
		return 0;
	}

	char buf[128] = "abcd";
	DWORD written;
	WriteFile(hFile, buf, 4, &written, NULL);
	CloseHandle(hFile);
	return 0;
}