//------------------------------------------------------------------------------
/* A program to create an HTTP request to the server to fetch a webpage/site. 
   Winsock enables programmers to create advanced Internet or
   other network-capable applications to transmit application data across the wire,
   independent of the network protocol being used.
*/
//------------------------------------------------------------------------------

#include <winsock2.h>                  // socket programming library for windows
#include <windows.h>				  // it is the main header file of WinAPI . winapi is related to programming in windows.(creating files,graphic modules etc etc.
#include <iostream>                  // io library in c++
#pragma comment(lib,"ws2_32.lib")   /*Applications that use Winsock must be linked with the Ws2_32.lib library file. 
                                      The #pragma comment indicates to the linker that the Ws2_32.lib file is needed.*/
using namespace std;
void search(char *pat, char *txt);
	char buffer[1000];   // create a char array "buffer" with size=1000
int main ()
 {
	WSADATA wsaData;    // The WSADATA structure contains information about the Windows Sockets implementation. wsaData is a variable.
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)  // WSAStartip initilaises the winsock sockets dll process. it returns a pointer to the WsaData.
	{ 
		cout << "WSAStartup failed.\n";                /* Tell the user that we could not find a usable WinSock DLL*/
		return 1;
	}
	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  /*The socket(winsock) function creates a socket that is bound to a specific transport service provider.
	AF_INET - is address_family function. It referes to IPv4 format . similarly for IPv6 format u could use AF_INET6.
	SOCK_STREAM - it is used to create stream socket . sockets are of 2 types . stream and datagram. 
	we created stream coz we want a 2 way reliable connection between the networks.
	IPPROTO_TCP - here we are using trasmission control protocol for sending our packets .
	if we are making stream socket we definately use a connection-oriented protocol i.e TCP.
	*/ 
	struct hostent *host;   // struct hostnet data type represents a new entry in hosts database.
	char hostName[20];
	cout<<"Enter host name:";
	cin>>hostName;
	host = gethostbyname(hostName); // mention the host address
	
	SOCKADDR_IN SockAddr;  //Used by the getaddrinfo function to hold host address information.
	
	SockAddr.sin_port=htons(80); // Convert port number 80 to network byte order and assign it to the right structure member.
	
	SockAddr.sin_family=AF_INET; // adress family is of IPv4 internet address

	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr); // here we are refering to the host address 

	cout << "Connecting ladies and gentlemen .......\n";
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0)  /* It tells whether the connection is established with that webpage or not */
	{
		cout << "No connection found";
		system("end");
		return 1;
	}
	cout << "Connected."<<endl;
	
	//send out data over a socket
	send(Socket,"GET / HTTP/2.2\nHost: example.com\nConnection: close\n\n", strlen("GET / HTTP/2.2\nHost: example.com\nConnection: close\n\n"),0);
	

	
	int Data_Length;     // take an integer variable data_length
	
	while ((Data_Length = recv(Socket,buffer,1000,0)) > 0)     
	  /* Without the below witten piece of code the buffer contains a byte that would make your loop terminate, 
	    therefore it might continue indefinitely. You must prevent this by having an extra check before accessing the array index.
	    Consider that Data_Length will always be smaller or equal to sizeof(buffer) */
	{
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')    // it is used to bind the search count returned by recv() function.
		{
//		cout << buffer[i];
			i =i+1;
		}
	}
	closesocket(Socket); /*When the client application is done receiving data, the closesocket function is called to close the socket.*/
                       
     WSACleanup();  /*When the client application is completed using the Windows Sockets DLL this WSACleanup function is called to release resources.*/
	
	char pat[] = "href=\"";
	search(pat, buffer);

	//system("end");
	return 0;
}




void search(char *pat, char *txt)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int flag=0;
	for (int i = 0; i <= N - M; i++)
	{
		int j;
		for (j = 0; j < M; j++)
			if (txt[i+j] != pat[j])
				break;
		if (j == M) 
		{
		cout<<endl;
		flag=1;
		int pos=i;
		for(int k=pos+5;buffer[k]!='>';k++)
		cout << buffer[k];
		}
		
	}
	if(flag == 0)
			cout<<"Alas..Nowhere to go :("<<endl;
}

