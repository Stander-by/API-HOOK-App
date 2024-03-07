#include "pch.h"
#include <string>
#include <WinSock2.h>
using namespace std;


string getSocketAf(int af) {
	switch (af) {
	case AF_UNSPEC:
		return "AF_UNSPEC [地址族未指定]";
	case AF_INET:
		return "AF_INET (IPv4)";
	case AF_IPX:
		return "AF_IPX";
	case AF_APPLETALK:
		return "AF_APPLETALK";
	case AF_NETBIOS:
		return "AF_NETBIOS";
	case AF_INET6:
		return "AF_INET6 (IPv6)";
	case AF_IRDA:
		return "AF_IRDA";
	case AF_BTH:
		return "AF_BTH";
	default:
		return "";
	}
}

string getSocketType(int type) {
	switch (type) {
	case SOCK_STREAM:
		return "SOCK_STREAM";
	case SOCK_DGRAM:
		return "SOCK_DGRAM";
	case SOCK_RAW:
		return "SOCK_RAW";
	case SOCK_SEQPACKET:
		return "SOCK_SEQPACKET";
	case SOCK_RDM:
		return "SOCK_RDM";
	default:
		return "[未指定]";
	}
}

string getSocketProt(int prot) {
	switch (prot) {
	case IPPROTO_ICMP:
		return "ICMP";
	case IPPROTO_IGMP:
		return "IGMP";
	case IPPROTO_TCP:
		return "TCP";
	case IPPROTO_UDP:
		return "UDP";
	case IPPROTO_ICMPV6:
		return "ICMPV6";
	case IPPROTO_PGM:
		return "PGM";
	default:
		return "[未指定]";
	}
}

SOCKET(WSAAPI* OldSocket)(
	_In_ int af,
	_In_ int type,
	_In_ int protocol
	) = socket;
int (WSAAPI* OldConnect)(
	_In_ SOCKET s,
	_In_reads_bytes_(namelen) const struct sockaddr FAR* name,
	_In_ int namelen
	) = connect;
int (WSAAPI* OldSend)(
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR* buf,
	_In_ int len,
	_In_ int flags
	) = send;
int (WSAAPI* OldRecv)(
	_In_ SOCKET s,
	_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,
	_In_ int len,
	_In_ int flags
	) = recv;


extern "C" {
	__declspec(dllexport) SOCKET WSAAPI NewSocket(
		_In_ int af,
		_In_ int type,
		_In_ int protocol
	) {
		auto sock = OldSocket(af, type, protocol);
		json msg={
			{"type","Socket"},
			{"apiName","NewSocket"},
			{"shortInfo",to_utf8("[socket启动]")},
			{"param",{
				{"addressFamily",{{"description","[地址族]"},{"value",getSocketAf(af)}}},
				{"socketType",{{"description","[套接字类型]"},{"value",getSocketType(type)}}},
				{"protocol",{{"description","[协议]"},{"value",getSocketProt(protocol)}}},
			}},
			{"return",{
				{"socketDescriptor",{{"description","[套接字描述符]"},{"value",to_utf8(sock)}}},
			}}
		};
		sendMsg(msg);
		return sock;
	}

	__declspec(dllexport) int WSAAPI NewConnect(
		_In_ SOCKET s,
		_In_reads_bytes_(namelen) const struct sockaddr FAR* name,
		_In_ int namelen
	) {
		printf("Hook API: connect\n");
		

		printf("socket descriptor: %#x\n", s);
		SOCKADDR_IN* sockAddr = (SOCKADDR_IN*)name;
		printf("sockaddr:     \n");
		printf("\tsin_family: %d - %s\n",
			sockAddr->sin_family, getSocketAf(sockAddr->sin_family).c_str());
		printf("\tsin_addr: %s\n", inet_ntoa(sockAddr->sin_addr));
		printf("\tsin_port: %hu\n", ntohs(sockAddr->sin_port));
		printf("sizeof(sockaddr): %d\n", namelen);
		printf("$HOOKEND$");
		//json msg=
		return OldConnect(s, name, namelen);
	}

	__declspec(dllexport) int WSAAPI NewSend(
		_In_ SOCKET s,
		_In_reads_bytes_(len) const char FAR* buf,
		_In_ int len,
		_In_ int flags
	) {
		printf("Hook API: send\n");

		printf("socket descriptor: %#x\n", s);
		printf("buf: 0x%p\n", buf);
		printf("len: %d\n", len);
		printf("send data: ");
		for (int i = 0; i < len && buf[i]!=0; ++i) {
			putchar(buf[i]);
		}
		putchar('\n');
		printf("flags: %d\n", flags);
		printf("$HOOKEND$");
		return OldSend(s, buf, len, flags);
	}

	__declspec(dllexport) int WSAAPI NewRecv(
		_In_ SOCKET s,
		_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,
		_In_ int len,
		_In_ int flags
	) {
		int ret = OldRecv(s, buf, len, flags);
		printf("Hook API: recv\n");
		

		printf("socket descriptor: %#x\n", s);
		printf("buf: 0x%p\n", buf);
		printf("len: %d\n", len);
		printf("recv data: ");
		for (int i = 0; i < len && buf[i]; ++i) {
			putchar(buf[i]);
		}
		putchar('\n');
		printf("flags: %d\n", flags);
		printf("$HOOKEND$");
		return ret;
	}
}