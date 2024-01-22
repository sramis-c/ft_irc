#include <iostream>
#include <poll.h>
#include <unistd.h>

int main(void)
{
	struct pollfd fds[2];

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	fds[1].fd = STDOUT_FILENO;
	fds[1].events = POLLOUT;

	while(1){
		int ret = poll(fds, 2, -1); 
		if (ret == -1) {
			perror("poll"); 
			exit(1);
		}

		if (fds[0].revents & POLLIN) {
			char buffer[256];
			int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
			if (bytesRead > 0) {
				std::cout << "Input recived: " << std::string(buffer, bytesRead) << std::endl;
			}
		}

		if (fds[1].revents & POLLOUT) {
			if(fds[0].revents & POLLIN)
				std::cout << "Output polled: "<< std::endl;// Puedes realizar operaciones de escritura en stdout aquí si es necesario
		}
	}
}