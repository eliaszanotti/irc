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

	std::memset(this->_pollFD, 0 , sizeof(this->_pollFD));
	this->_pollFD[0].fd = this->_serverSocket;
	this->_pollFD[0].events = POLLIN;
	this->_pollFDSize = 1;
	this->_serverIsRunning = true;
}

// PRIVATE METHODS
void	Server::_processPoll(void)
{
	int returnValue = poll(this->_pollFD, this->_pollFDSize, POLL_TIMEOUT);
	if (returnValue < 0)
		throw (std::runtime_error("Poll failed"));
	if (returnValue == 0)
		throw (std::runtime_error("Poll timeout"));
}

void Server::_addNewUser(void)
{		
	int	newFD = 0;
	if (this->_pollFD[0].revents & POLLIN)
	{
		newFD = accept(this->_serverSocket, NULL, NULL);
		if (newFD < 0 && errno != EWOULDBLOCK)
			throw (std::runtime_error("Error when trying to add new user"));
		std::cout << "[+] Incoming connection by " << newFD << std::endl;
		this->_pollFD[this->_pollFDSize].fd = newFD;
		this->_pollFD[this->_pollFDSize].events = POLLIN;
		User *newUser = new User(this->_pollFD[this->_pollFDSize]);
		this->_users[this->_pollFD[this->_pollFDSize].fd] = newUser;
		this->_pollFDSize++;
	}
}

void Server::_processMessage(std::string buffer, int currentIndex)
{
	int	currentFD = this->_pollFD[currentIndex].fd;
	std::vector<std::string> split_message;
	split_message = split(buffer, "\n");
	for (size_t idx = 0; idx < split_message.size(); idx++)
	{
		if (split_message[idx].empty())
			continue;
		if (!this->_checkCommandInsideMessage(currentFD, split_message[idx]))
		{
			if (!this->_users[currentFD]->getLogged())
				send(currentFD, "Client isn't connected\n");
			else
			{
				for (int j = 1; j < this->_pollFDSize; j++)
				{
					if (j == currentIndex)
						continue ;
					if (this->_users[this->_pollFD[j].fd]->getConnected())
						send(this->_pollFD[j].fd, split_message[idx].c_str());
				}
			}
		}
	}
}

void Server::_closeCurrentUser(int currentIndex)
{				
	delete (this->_users[this->_pollFD[currentIndex].fd]);
	close(this->_pollFD[currentIndex].fd);
	this->_pollFD[currentIndex].fd = -1;
	for (int i = 0; i < this->_pollFDSize; i++)
	{
		if (this->_pollFD[i].fd == -1)
		{
			for (int j = i; j < this->_pollFDSize; j++)
				this->_pollFD[j].fd = this->_pollFD[j+1].fd;
			i--;
			this->_pollFDSize--;
		}
	}
}

void Server::_connectEachUser(void)
{
	char			buffer[MAX_CHAR];
	int				returnValue;

	for (int i = 1; i < this->_pollFDSize; i++)
	{
		try
		{
			if (this->_pollFD[i].revents & POLLIN)
			{
				memset(&buffer, 0, MAX_CHAR);
				returnValue = recv(this->_pollFD[i].fd, buffer, sizeof(buffer), 0);
				if (returnValue < 0 && errno != EWOULDBLOCK)
				{
					this->_closeCurrentUser(i);
					throw (std::runtime_error("recv command failed"));
				}
				else if (returnValue == 0)
				{
					std::cout << "[-] " << this->_pollFD[i].fd << " leaved the server" << std::endl;
					this->_closeCurrentUser(i);
					break;
				}
				else if (returnValue > 1)
					this->_processMessage(buffer, i);
			}
		}
		catch(const std::exception& error)
		{
			throw (std::runtime_error(error.what()));
		}
	}
}

// GETTERS
int			Server::getServerSocket(void) const {return (this->_serverSocket);}

// METHODS
void	Server::init(void)
{
	if (this->_serverSocket < 0)	
		throw (std::runtime_error("Socket initialization failed"));
	std::cout << BLUE "[SERVER INITIALIZATION ON PORT " << this->_port << "]" RST << std::endl;
	std::cout << CYAN "[Password: " << this->_password << "]" RST << std::endl;
	int socketOptionValue = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOptionValue, sizeof(socketOptionValue)) == -1)
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
	while (this->_serverIsRunning)
	{
		// Wait for new connections
		try
		{
			this->_processPoll();
		}
		catch(const std::exception& error)
		{
			throw (std::runtime_error(error.what()));
		}
		// Add new user
		try
		{
			this->_addNewUser();
			this->_connectEachUser();
		}
		catch(const std::exception& error)
		{
			for (int i = 0; i < this->_pollFDSize; i++)
			{
				if (this->_pollFD[i].fd >= 0)
					close(this->_pollFD[i].fd);
			}
			throw (std::runtime_error(error.what()));
		}
	}
}

bool	Server::_checkCommandInsideMessage(int fd, std::string message)
{
	std::vector<std::string>	command;
	size_t						i;

	std::cout << "Message received: [" << message << "]" << std::endl;

	command = split(message, " ");
	std::string		commands[]	= {
									"KICK",
									"INVITE",
									"TOPIC",
									"MODE",
									"CAP",
									"PASS",
									"NICK",
									"USER",
									"JOIN",
									"PRIVMSG"
	};

	for (i = 0; i < 10; i++)
	{
		if (!commands[i].compare(command[0]))
			break ;
	}
	switch (i)
	{
		case KICK:		return this->_kick();
		case INVITE:	return this->_invite();
		case TOPIC:		return this->_topic();
		case MODE:		return this->_mode();
		case CAP:		return this->_cap(fd);
		case PASS:		return this->_pass(fd, command);
		case NICK:		return this->_nick(fd, command);
		case USER:		return this->_user(fd, command);
		case JOIN:		return this->_join(fd, command);
		case PRIVMSG:	return this->_privmsg(fd, command);
	}

	return (false);
}

// COMMANDS
void	Server::sendTo(const User *user, const std::string &message)
{
	size_t byteSent = 0;

	while (byteSent < message.length())
	{
		long len = send(user->getFd(), message.c_str());
		if (len < 0)
		{
			std::cerr << "send() error: server to client" << std::endl;
			break ;
		}
		byteSent += len;
	}
}
