#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

#define BUFLEN 512
#define MAX_RETRY 10

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Input parameters failed. Please input \"IP\" \"Port\".");
		return -1;
	}

	char *ip = argv[1];
	char *port = argv[2];

	printf("%s\n", ip);
	printf("%s\n", port);

	struct sockaddr_in scoket_addr;
	int scoket_addr_len = sizeof(scoket_addr);
	int socket_descriptor;
	char buf_recive[BUFLEN];
	char buf_send[BUFLEN];

	// create socket file descriptor
	if ((socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Create socket failed.");
		return -1;
	}
	// socket info setting
	memset((char *)&scoket_addr, 0, sizeof(scoket_addr));
	scoket_addr.sin_family = AF_INET;
	scoket_addr.sin_port = htons(atoi(port));

	if (inet_aton(ip, &scoket_addr.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	// user input message
	printf("Enter message : ");
	gets(buf_send);

	// send message to server
	if (sendto(socket_descriptor, buf_send, strlen(buf_send), 0, (struct sockaddr *)&scoket_addr, scoket_addr_len) == -1)
	{
		printf("Send data failed.");
		return -1;
	}
	printf("Sent message.\n");

	bzero(&buf_recive, sizeof(buf_recive));

	int retry_times = 0;
	int time_clock = 0;
	int multiplier = 2;
	int base_time = 500;
	int max_wait_interval = 8000;

	time_clock = base_time;

	// set receive timeout
	struct timeval timeout = {0, 500};
	setsockopt(socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	// reveive message from server
	while (retry_times <= MAX_RETRY)
	{

		if (retry_times > 0 && time_clock < max_wait_interval)
		{
			time_clock = base_time * pow(multiplier, retry_times);
		}

		if (recvfrom(socket_descriptor, buf_recive, BUFLEN, 0, (struct sockaddr *)&scoket_addr, &scoket_addr_len) < 0)
		{
			printf("Receive data failed. ");
			retry_times++;
			if (retry_times <= MAX_RETRY)
			{
				printf("Wait for the %d-th retry after %d msec.\n", retry_times, time_clock);
			}
			else
			{
				printf("Reach the maximun numbers of retries.\n");
			}
			usleep(time_clock * 1000); // wait
			fflush(stdout);
			continue;
		}
		else
		{
			printf("Received from server: ");
			puts(buf_recive);
			break;
		}
	}

	close(socket_descriptor);

	if (retry_times > MAX_RETRY)
	{
		printf("return 1\n");
		return 1;
	}
	else
	{
		printf("return 0\n");
		return 0;
	}
	return 0;
}