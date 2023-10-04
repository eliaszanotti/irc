/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 13:37:1 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// CONSTRUCTORS
Server::Server() {}
Server::~Server() {close(this->_serverSocket);}

Server::Server(int port, std::string password)
{
	this->_port = port;
	this->_password = password;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	std::memset(&this->_serverAddress, 0, sizeof(this->_serverAddress));
	this->_serverAddress.sin_family = AF_INET;
	std::memcpy(&this->_serverAddress.sin_addr, &in6addr_any, sizeof(in6addr_any));
	this->_serverAddress.sin_port = htons(port);
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
}

// PRIVATE METHODS
void	Server::_processPoll(struct pollfd *pollFD, int pollFDSize)
{
	std::cout << "Waiting poll" << std::endl;
	int returnValue = poll(pollFD, pollFDSize, POLL_TIMEOUT);
	if (returnValue < 0)
	{
		close(this->_serverSocket);
		std::cout << "Poll failed" << std::endl;
	}
	if (returnValue == 0)
	{
		close(this->_serverSocket);
		std::cout << "Poll timeout" << std::endl;
	}
}

// METHODS
void	Server::init(void)
{
	if (this->_serverSocket < 0)
		throw(std::runtime_error("Socket initialization failed"));
	std::cout << BLUE "[SERVER INITIALIZATION ON PORT " << this->_port << "]" RST << std::endl;
	std::cout << CYAN "[Password: " << this->_password << "]" RST << std::endl;
	int socketOptionValue = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOptionValue, sizeof(socketOptionValue)))
	{
		close(this->_serverSocket);
		throw(std::runtime_error("Set socket option failed"));
	}
	if (ioctl(this->_serverSocket, FIONBIO, &socketOptionValue))
	{
		close(this->_serverSocket);
		throw(std::runtime_error("Ioctl failed"));
	}
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) < 0)
	{
		close(this->_serverSocket);
		throw(std::runtime_error("Bind failed"));
	}
	if (listen(this->_serverSocket, 3) < 0)
	{
		close(this->_serverSocket);
		throw(std::runtime_error("Listen failed"));
	}
}

void	Server::waitingForNewUsers(void)
{	
	struct pollfd	pollFD[MAX_USERS];
	
	std::memset(pollFD, 0 , sizeof(pollFD));
	pollFD[0].fd = this->_serverSocket;
	pollFD[0].events = POLLIN;
	int				pollFDSize = 1;
	int				current_size = 0;
	bool			end_server = false;
	int				new_sd = 0;
	int				closeConnection;
	char			buffer[MAX_CHAR];
	bool			compress_array = false;
	
	int rv = 1;
	while (end_server == false)
	{
		this->_processPoll(pollFD, pollFDSize);


		current_size = pollFDSize;
		for (int i = 0; i < current_size; i++)
		{
			if (pollFD[i].revents == 0)
				continue;
			if (pollFD[i].revents != POLLIN)
			{
				std::cout << "Error revents = " << pollFD[i].revents << std::endl;
				end_server = true;
				break ;
			}
			if (pollFD[i].fd == this->_serverSocket)
			{
				do
				{
					new_sd = accept(this->_serverSocket, NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
						std::cout << "accept failed" << std::endl;
						end_server = true;
						}
						break;
					}

					printf("  New incoming connection - %d\n", new_sd);
					pollFD[pollFDSize].fd = new_sd;
					pollFD[pollFDSize].events = POLLIN;
					pollFDSize++;

				}
				while (new_sd != -1);
			}
			else
			{
				std::cout << "Descriptor " << pollFD[i].fd << " is readable" << std::endl;
				closeConnection = false;
				do
				{
					for (int j = 0; j < pollFDSize; j++)
					{
						if (j == i)
							continue;
						rv = recv(pollFD[j].fd, buffer, sizeof(buffer), 0);
					}
					if (rv < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cout << "recv failed" << std::endl;
							closeConnection = true;
						}
						break ;
					}
					if (rv == 0)
					{
						std::cout << " Connection closed" << std::endl;
						closeConnection = true;
						break ;
					}

					int len = rv;
					std::cout << len << "  bytes received" << std::endl;
					
					rv = send(pollFD[i].fd, buffer, len, 0);
					if (rv < 0)
					{
						std::cout << "send failed" << std::endl;
						closeConnection = true;
						break ;
					}
				}
				while(true);

				if (closeConnection)
				{
					close(pollFD[i].fd);
					pollFD[i].fd = -1;
					compress_array = true;
				}
			}
		}
		if (compress_array)
		{
			compress_array = false;
			for (int i = 0; i < pollFDSize; i++)
			{
				if (pollFD[i].fd == -1)
				{
					for (int j = i; j < pollFDSize; j++)
						pollFD[j].fd = pollFD[j+1].fd;
					i--;
					pollFDSize--;
				}
			}
		}
	}
	for (int i = 0; i < pollFDSize; i++)
	{
		if (pollFD[i].fd >= 0)
			close(pollFD[i].fd);
	}
}