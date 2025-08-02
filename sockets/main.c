#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(){
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr = {
		AF_INET,
		0x8813, // 5000 
		0,
	};

	bind(socket_fd, &addr, sizeof(addr));
	listen(socket_fd, 10);
	while(1){
	int client_fd = accept(socket_fd, NULL, NULL);

	char buf[1024];

	read(client_fd, buf, sizeof(buf));

	printf("%s", buf);

	char* fileName = buf + 5;
	
	char* space = strchr(fileName, ' ');

	if(!space){
		close(client_fd);
	};

	*space = 0;

	
	char* metadata = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

	FILE* f = fopen(fileName, "r");

	if (!f){				

	        char* error_metadata = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nCouldnt Find File!";
		char response[1024] = {0};	
		memcpy(response, error_metadata, strlen(error_metadata));
		write(client_fd, response, sizeof(response));
		close(client_fd);

	}

	char response[1024] = {0};


	memcpy(response, metadata, strlen(metadata));

	fread(response, 1, 300,f );
	




	 write(client_fd, response, sizeof(response));

	close(client_fd);
	}
	//close(socket_fd);

	//close(opened_fd);

	return 0;
}
