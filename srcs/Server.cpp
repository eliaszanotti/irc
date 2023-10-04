/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:13 by elias             #+#    #+#             */
/*   Updated: 2023/10/04 11:43:05 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Constructors
Server::Server() {}
Server::~Server() { close(this->_serverSocket); }

Server::Server(int port, std::string password)
{
	this->_port = port;
	this->_password = password;
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	this->_serverAddress.sin_family = AF_INET;
	this->_serverAddress.sin_port = htons(port);
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;
}

// Methods
void Server::init(void)
{
	int timeout = 80 * 1000;
	std::cout << BLUE "[SERVER INITIALIZATION ON PORT " << this->_port << "]" RST << std::endl;
	std::cout << CYAN "[Password: " << this->_password << "]" RST << std::endl;
	// this->_serverSocket = -1;
	if (this->_serverSocket < 0)
		throw(std::runtime_error("socket failed"));

	// Set options
	int opt = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		close(this->_serverSocket);
		throw(std::runtime_error("setsockopt failed"));
	}

	// Bind
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) < 0)
	{
		close(this->_serverSocket);
		throw(std::runtime_error("bind failed"));
	}

	// Listen
	if (listen(this->_serverSocket, 3) < 0)
	{
		close(this->_serverSocket);
		throw(std::runtime_error("listen failed"));
	}
	
	struct pollfd fds[MAX_USERS];
	fds[0].fd = this->_serverSocket;
	fds[0].events = POLLIN;
	int nfds = 1;
	int	current_size = 0;
	bool end_server = false;
	int		new_sd = 0;
	int		close_conn;
	char	buffer[MAX_CHAR];
	bool	compress_array = false;
	while (end_server == false)
	{
		int rv;
		rv = poll(fds, nfds, timeout);
		
		if (rv < 0)
		{
			close(this->_serverSocket);
			std::cout << "poll failed" << std::endl;
		}
		
		if (rv == 0)
		{
			close(this->_serverSocket);
			std::cout << "poll timeout" << std::endl;
		}
		current_size = nfds;
		for(int i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)
			{
				std::cout << "Error revents = " << fds[i].revents << std::endl;
				end_server = true;
			}
			if (fds[i].fd == this->_serverSocket)
			{
				std::cout << "Listening socket is readable" << std::endl;
				while (new_sd != -1)
				{
					new_sd = accept(this->_serverSocket, NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cout << "accept failed" << std::endl;
							end_server = true;
						}
						break ;
					}
					std::cout << "New connection - " << new_sd << std::endl;
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
					std::cout << "Ok" << std::endl;
				}
				std::cout << "Ok1" << std::endl;
			}
			else
			{
				std::cout << "Descriptor " << fds[i].fd << " is readable" << std::endl;
				close_conn = false;
				while (true)
				{
					rv = recv(fds[i].fd, buffer, MAX_CHAR, 0);
					if (rv < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cout << "recv failed" << std::endl;
							close_conn = true;
						}
						break ;
					}
					if (rv == 0)
					{
						std::cout << " Connection closed" << std::endl;
						close_conn = true;
						break ;
					}

					int len = rv;
					std::cout << len << "  bytes received" << std::endl;
					rv = send(fds[i].fd, buffer, len, 0);
					if (rv < 0)
					{
						std::cout << "send failed" << std::endl;
						close_conn = true;
						break ;
					}
				}
				if (close_conn)
				{
					close(fds[i].fd);
					fds[i].fd = -1;
					compress_array = true;
				}
			}
			std::cout << "Ok" << std::endl;
		}
		if (compress_array)
		{
			compress_array = false;
			for (int i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for (int j = i; j < nfds; j++)
						fds[j].fd = fds[j+1].fd;
					i--;
					nfds--;
				}
			}
		}
	}
	for (int i = 0; i < nfds; i++)
	{
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}
