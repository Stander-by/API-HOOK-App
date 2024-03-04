#include <windows.h>

int main() {
	MessageBoxW(nullptr, L"父窗口句柄", L"hello", NULL);
	MessageBoxW(nullptr, L"父窗口句柄", L"hello", NULL);
	MessageBoxW(nullptr, L"父窗口句柄", L"hello", NULL);
	MessageBoxW(nullptr, L"父窗口句柄", L"hello", NULL);
	MessageBoxA(nullptr, "A window", "hi", NULL);
	MessageBoxA(nullptr, "Awindow", "hi", NULL);
	MessageBoxA(nullptr, "Awindow", "hi", NULL);
	MessageBoxA(nullptr, "A", "hi", NULL);
	return 0;
}