#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include <windows.h>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
# define BUFFER_SIZE 10240 // The size of the buffer used to store the content being sent or received.
int main()
{
	// Create the socket network enviroment
	SOCKET sock_Client; 
	WSADATA WSAData;
	char receBuf[BUFFER_SIZE]; 
	char sendBuf[BUFFER_SIZE]; 
	char test[500];
	test[499] = '\0'; // Add the '\0' at the end of the character array，otherwise there will be garbled characters.

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	double time;

	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("sdll!");
		return -1;
	}

	sock_Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addr_server; // The information of server address
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(1234); // Make sure it is same as the server's port
	//addr_server.sin_addr.S_un.S_addr = inet_addr("192.168.0.131"); // Server's IP address

	SOCKADDR_IN sock;
	int len = sizeof(sock);
	// Process the received data from here
	while (true)
	{
		system("pause");

		// The method of measuring the latency
		/*
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		// Put the process which latency needs to be measured here
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		printf("%f us \n", time * 1000000);*/



		// Simple transmission system
		/*
		cout << "Send:";
		cin >> sendBuf;
		sendto(sock_Client, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
		int last = recvfrom(sock_Client, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&sock, &len);
		if (last > 0)
		{
			receBuf[last] = '\0'; // Add the '\0' at the end of the character array，otherwise there will be garbled characters.
			if (strcmp(receBuf, "bye") == 0)
			{
				// If received data is 'bye', close the socket system.
				cout << "Offline..." << endl;
				closesocket(sock_Client);
				break;
			}
			else
			{
				printf("receive: %s\n", receBuf);
			}

		}*/



		// Send large quantity of data
		/*
		for (int a = 0; a < 10000; a++) {
			sendto(sock_Client, test, sizeof(test), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
			//recvfrom(sock_Client, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&sock, &len); // If you want to receive some data
		} // Send 10000 times data
		*/


		// To test whether the received data is in wrong order, send '1','2','3'...'1000' to the server.
		/*
		for (float a = 0; a < 1000; a++) {
			char b[10];
			sprintf(b, "%g", a);
			sendto(sock_Client, b, sizeof(b), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
		}*/


		
		// Send the pointer to the logical address
		/*
		int sd = 10;
		//float sd = 1329.367188;
		//float sd[15] = { 1329.367188, 234.15152, 167.54421, 1519.12414, 1414.26262 ,2345,1414,37.363333,153.3535,12313 };
		for (int a = 0; a < 1; a++) {
			sendto(sock_Client, (char*)&sd, sizeof(sd), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
		}*/



		// Send the image coordinate data

		float coorarr[100];
		vector<Point2f> imgvec;
		Point2f pt;
		for (int a = 0; a < 10; a++) {
			// Create an unordered float point coordinate
			pt.x = a * 100 + a * 20 + a * 4 + a * 0.4 + a * 0.07 + a * 0.002 + a * 0.00009 + a * 0.000008;
			pt.y = a * 200 + a * 80 + a * 3 + a * 0.1 + a * 0.09 + a * 0.006 + a * 0.00005 + a * 0.000003;
			imgvec.push_back(pt);// Create a coordinate vector
			//cout << sizeof(imgvec[a]) << endl;
		}
		for (int a = 0; a < 10; a++) {
			// Create an unordered float point sequence
			coorarr[2 * a] = imgvec[a].x;
			coorarr[2 * a + 1] = imgvec[a].y;
		}
		//for (int a = 0; a < 10; a++) {
		//	cout << imgvec[a] << endl;
		//}
		sendto(sock_Client, (char*)&coorarr, sizeof(coorarr), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
					   		 
	}
	closesocket(sock_Client);
	WSACleanup();
	return 0;
}