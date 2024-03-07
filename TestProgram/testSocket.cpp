#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
// g++ testSocket.cpp -o testSocket -lwsock32
using namespace std;

void CallMsgBox(LPCWSTR message) {
	MessageBoxW(NULL, message, L"debug", MB_OK);
}

int main() {
	// /*初始化套接字库*/
	// WORD wVersionRequested = MAKEWORD(2, 2);		//WinSock版本
	// WSADATA wsaData;		//套接字信息
	// int err = WSAStartup(wVersionRequested, &wsaData);	//加载套接字库
	// if (err) {
	// 	return 0;
	// }
	// if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
	// 	WSACleanup();
	// 	return 0;
	// }

	// /*客户端创建套接字*/
	// SOCKET socketSend = socket(AF_INET, SOCK_STREAM, 0);
	// //客户端套接字不需要绑定
	// if (socketSend == INVALID_SOCKET) {
	// 	//cout << "Socket ERROR!";
	// 	return 0;
	// }

	// /*连接服务器*/
	// //设置服务器地址端口
	// SOCKADDR_IN serverAddr;
	// serverAddr.sin_family = AF_INET;
	// serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	// serverAddr.sin_port = htons(1234);

	// if (connect(socketSend, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
	// 	return 0;
	// }
	// const int bufSize = 50;
	// char sendBuf[bufSize] = "socket client send data";		//发送数据缓冲区
	// char recvBuf[bufSize];		//接受数据缓冲区

	// int sendLen = send(socketSend, sendBuf, bufSize, 0);

	// memset(sendBuf, 0, bufSize);

	// int recvLen = recv(socketSend, recvBuf, bufSize, 0);

	// MessageBoxA(NULL, recvBuf, "recv", MB_OK);
	// cout<<recvBuf<<endl;
	// memset(recvBuf, 0, bufSize);
	// closesocket(socketSend);
	// WSACleanup();
	// return 0;

	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100] = "Hello World";
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;

	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		return 0;
	}
	else {
		CallMsgBox(L"初始化套接字库成功！");
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		CallMsgBox(L"套接字库版本号不符！");
		WSACleanup();
		return 0;
	}
	else {
		CallMsgBox(L"套接字库版本正确！");
	}

	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(1234);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		CallMsgBox(L"服务器连接失败！");
		WSACleanup();
		return 0;
	}
	else {
		CallMsgBox(L"服务器连接成功！");
	}
	//发送,接收数据
	send_len = send(s_server, send_buf, strlen(send_buf)+1, 0);
	if (send_len < 0) {
		CallMsgBox(L"发送失败！");
	}
	recv_len = recv(s_server, recv_buf, 100, 0);
	if (recv_len < 0) {
		CallMsgBox(L"接受失败！");
	}
	else {
		CallMsgBox(L"服务端信息已接收");
	}


	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;

}