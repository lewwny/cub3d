#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int	main(int argc, char *argv[])
{
	int					sock;
	struct sockaddr_in	server_addr;
	char				buffer[BUFFER_SIZE];
	char				*server_ip;
	int					port;
	ssize_t				bytes_received;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	server_ip = argv[1];
	port = atoi(argv[2]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		return (EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0)
	{
		perror("inet_pton");
		close(sock);
		return (EXIT_FAILURE);
	}
	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect");
		close(sock);
		return (EXIT_FAILURE);
	}
	printf("Connecté au serveur %s:%d\n", server_ip, port);
	char last_buffer[BUFFER_SIZE] = {0};

	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		bytes_received = read(sock, buffer, BUFFER_SIZE - 1);
		if (bytes_received < 0)
		{
			perror("read");
			break ;
		}
		else if (bytes_received == 0)
		{
			printf("Connexion fermée par le serveur.\n");
			break ;
		}
		if (strcmp(buffer, last_buffer) != 0)
		{
			printf("%s\n", buffer);
			strcpy(last_buffer, buffer);
		}
	}
	close(sock);
	return (0);
}

