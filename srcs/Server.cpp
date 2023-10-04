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
	int returnValue = poll(pollFD, pollFDSize, POLL_TIMEOUT);
	if (returnValue < 0)
		throw (std::runtime_error("Poll failed"));
	if (returnValue == 0)
		throw (std::runtime_error("Poll timeout"));
}

// GETTERS
int Server::getServerSocket(void) const {return (this->_serverSocket);}

// METHODS
void	Server::init(void)
{
	if (this->_serverSocket < 0)	
		throw (std::runtime_error("Socket initialization failed"));
	std::cout << BLUE "[SERVER INITIALIZATION ON PORT " << this->_port << "]" RST << std::endl;
	std::cout << CYAN "[Password: " << this->_password << "]" RST << std::endl;
	int socketOptionValue = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOptionValue, sizeof(socketOptionValue)))
		throw(std::runtime_error("Set socket option failed"));
	if (ioctl(this->_serverSocket, FIONBIO, &socketOptionValue))
		throw(std::runtime_error("Ioctl failed"));
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) < 0)
		throw(std::runtime_error("Bind failed"));
	if (listen(this->_serverSocket, 3) < 0)
		throw(std::runtime_error("Listen failed"));
}

void	Server::waitingForNewUsers(void)
{	
	struct pollfd	pollFD[MAX_USERS];
	
	std::memset(pollFD, 0 , sizeof(pollFD));
	pollFD[0].fd = this->_serverSocket;
	pollFD[0].events = POLLIN;
	int				pollFDSize = 1;
	bool			serverIsRunning = true;
	int				new_sd = 0;
	int				closeConnection;
	char			buffer[MAX_CHAR];
	int				returnValue;

	while (serverIsRunning)
	{
		try
		{
			this->_processPoll(pollFD, pollFDSize);
		}
		catch(const std::exception& error)
		{
			throw (std::runtime_error(error.what()));
		}

		// Add a new user
		if (pollFD[0].revents & POLLIN)
		{
			new_sd = accept(this->_serverSocket, NULL, NULL);
			if (new_sd < 0)
			{
				if (errno != EWOULDBLOCK)
				{
				std::cout << "accept failed" << std::endl;
				serverIsRunning = false;
				}
				break;
			}

			std::cout << "[+] Incoming connection by " << new_sd << std::endl;
			pollFD[pollFDSize].fd = new_sd;
			pollFD[pollFDSize].events = POLLIN;
			pollFDSize++;
		}

		// Gestion for each client
		for (int i = 1; i < pollFDSize; i++)
		{
			closeConnection = false;
			if (pollFD[i].revents & POLLIN)
			{
				// Receive the message from the user
				memset(&buffer, 0, MAX_CHAR);
				returnValue = recv(pollFD[i].fd, buffer, sizeof(buffer), 0);
				if (returnValue < 0)
				{
					if (errno != EWOULDBLOCK)
					{
						std::cout << "recv failed" << std::endl;
						closeConnection = true;
					}
				}
				else if (returnValue == 0)
				{
					std::cout << "[-] Connection closed by " << pollFD[i].fd << std::endl;
					closeConnection = true;
				}
				else
				{
					// Empty message
					if (returnValue == 1)
						continue ;

					if (!this->_checkCommandInsideMessage(pollFD[i].fd, buffer))
					{
						for (int j = 1; j < pollFDSize; j++)
						{
							if (j == i)
								continue ;
							send(pollFD[j].fd, buffer, returnValue, 0);
						}
					}
				}
			}
			
			// If there is a problem with the user
			if (closeConnection)
			{
				close(pollFD[i].fd);
				pollFD[i].fd = -1;
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
				break ;
			}
		}
	}

	// Close all the clients if the server is down
	for (int i = 0; i < pollFDSize; i++)
	{
		if (pollFD[i].fd >= 0)
			close(pollFD[i].fd);
	}
}

bool	Server::_checkCommandInsideMessage(int fd, std::string message)
{
	std::string	command;
	size_t		stop_idx;
	int			i;

	if (message.find(' ') == std::string::npos)
		stop_idx = message.length() - 1;
	else
		stop_idx = message.find(' ');
	command = message.substr(0, stop_idx);

	std::string		commands[]	= {
									"KICK",
									"INVITE",
									"TOPIC",
									"MODE"
	};

	(void)fd; // A ENLEVER

	for (i = 0; i < 4; i++)
	{
		if (!commands[i].compare(command))
			break ;
	}

	switch (i)
	{
		case KICK:		return this->_kick();
		case INVITE:	return this->_invite();
		case TOPIC:		return this->_topic();
		case MODE:		return this->_mode();
	}

	return (false);
}

// COMMANDS
bool	Server::_kick()
{
	std::cout << "kick() called" << std::endl;
	return (true);
}

bool	Server::_invite()
{
	std::cout << "invite() called" << std::endl;
	return (true);
}

bool	Server::_topic()
{
	std::cout << "topic() called" << std::endl;
	return (true);
}

bool	Server::_mode()
{
	std::cout << "mode() called" << std::endl;
	return (true);
}
