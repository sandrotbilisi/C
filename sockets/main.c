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

	char* f = buf + 5;
	
	//*strchr(f, ' ') = 0;
	//int opened_fd = open(f, O_RDONLY);
	//sendfile(client_fd, opened_fd, 0, 256);


	 char msg[100] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 13\r\n\r\nHello World!";

	 write(client_fd, msg, sizeof(msg));

	close(client_fd);
	}
	//close(socket_fd);

	//close(opened_fd);

	return 0;
}
