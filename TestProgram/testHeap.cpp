#include <windows.h>
#include <iostream>
using namespace std;

int main() {
	HANDLE h = HeapCreate(NULL, 4, 64);
	if (h) HeapDestroy(h);

	PHANDLE ph = (PHANDLE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PHANDLE));
	HeapFree(GetProcessHeap(), NULL, (LPVOID)ph);
	cout<<"HeapFree 1"<<endl;
	HeapFree(GetProcessHeap(), NULL, (LPVOID)ph);
	cout<<"HeapFree 2"<<endl;
	return 0;
}