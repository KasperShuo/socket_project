#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 512
#define PORT 8888

int main()
{
	struct sockaddr_in socket_server, socket_client;

	int socket_descriptor;
	char buf[BUFLEN];

	// create socket file descriptor
	if ((socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Create socket failed.");
		return 0;
	}

	// socket info setting
	memset((char *)&socket_server, 0, sizeof(socket_server));
	socket_server.sin_family = AF_INET;
	socket_server.sin_port = htons(PORT);
	socket_server.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind address to socket
	if (bind(socket_descriptor, (struct sockaddr *)&socket_server, sizeof(socket_server)) == -1)
	{
		printf("Bind socket failed.");
		return -1;
	}

	int socket_client_size = sizeof(socket_client);
	printf("Server ready. Port Number is %d. (Send \"stop\" to close the server.)\n", PORT);

	while (1)
	{
		printf("Waiting for data...\n");
		fflush(stdout);
		bzero(&buf, sizeof(buf));

		int recv_len;

		// Receive message from client
		if ((recv_len = recvfrom(socket_descriptor, buf, BUFLEN, 0, (struct sockaddr *)&socket_client, &socket_client_size)) == -1)
		{
			printf("Receive data failed.");
			return -1;
		}

		printf("Received dara from IP:%s, Port:%d\n", inet_ntoa(socket_client.sin_addr), ntohs(socket_client.sin_port));
		printf("Message: %s\n", buf);

		sleep(60); // wait for test the retry function in client.

		// Send message back to client
		if (sendto(socket_descriptor, buf, recv_len, 0, (struct sockaddr *)&socket_client, socket_client_size) == -1)
		{
			printf("Send data failed.");
			return -1;
		}

		// ready to close server
		if (strcmp(buf, "stop") == 0)
		{
			printf("Server closed.\n");
			break;
		}
	}

	close(socket_descriptor);
	return 0;
}