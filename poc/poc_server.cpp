#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define PORT 6667
#define BUFF_SIZE 1024

/*
	Create a server and wait to recive some text;
	Compile: g++ poc_server.cpp -o poc_server

	1: $> ./poc_server
	2: $> echo -n "Lorem ipsum dolor sit amet" | nc 127.0.0.1 6667
*/

int main(int argc, char **argv)
{
	int fd_server;
	char buff[BUFF_SIZE];
	struct sockaddr_in address;
	int address_len = sizeof(address);

	std::memset(buff, 0, BUFF_SIZE);

	/*init socket*/
	fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_server == -1)
	{
		std::cerr << "imposible to create de socket" << std::endl;
		return(EXIT_FAILURE);
	}

	/*configure address */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	/*link socket with configuration*/
	if (bind(fd_server, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) == -1) {
		std::cerr << "Error al enlazar el socket a la dirección." << std::endl;
		close(fd_server);
		return(EXIT_FAILURE);
	}

	/*listen to the socket*/
	if (listen(fd_server, 5) == -1) {
		std::cerr << "Error al poner el socket en modo escucha." << std::endl;
		close(fd_server);
		return(EXIT_FAILURE);
	}
	
	std::cout << "Servidor escuchando en el puerto : " << PORT << std::endl;

	/*waiting to recive*/
	int new_socket;
	if ((new_socket = accept(fd_server, (struct sockaddr*)&address, (socklen_t*)&address_len)) < 0)
	{ 
		std::cerr << "Error en el accept" << std::endl;
		exit(EXIT_FAILURE); 
	}

	/*print recived data*/
	int ret = read(new_socket, buff, 1024); 
	std::cout << buff << std::endl;
	close(fd_server);
	return(0);
}