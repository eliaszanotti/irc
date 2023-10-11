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

	// std::memset(this->_pollFD, 0 , sizeof(this->_pollFD));
	pollfd	new_pollfd;
	new_pollfd.fd = this->_serverSocket;
	new_pollfd.events = POLLIN;
	this->_pollFD.push_back(new_pollfd);
	this->_serverIsRunning = true;
}

// PRIVATE METHODS
void	Server::_processPoll(void)
{
	this->_pollFDSize = poll(&this->_pollFD[0], this->_pollFD.size(), POLL_TIMEOUT);
	if (this->_pollFDSize < 0)
		throw (std::runtime_error("Poll failed"));
	if (this->_pollFDSize == 0)
		throw (std::runtime_error("Poll timeout"));
}

void Server::_addNewUser(void)
{		
	int	newFD = 0;
	if (this->_pollFD[0].revents & POLLIN)
	{
		newFD = accept(this->_serverSocket, NULL, NULL);
		if (newFD < 0)
			throw (std::runtime_error("Error when trying to add new user"));
		if (newFD == 0)
			throw (std::runtime_error("Error when trying to add new user by index 0"));
		std::cout << PLUS_ICON << newFD << " is connected" << std::endl;
		pollfd new_pollfd;
		new_pollfd.fd = newFD;
		new_pollfd.events = POLLIN;
		new_pollfd.revents = 0;
		this->_pollFD.push_back(new_pollfd);
		User *newUser = new User(new_pollfd);
		this->_users[new_pollfd.fd] = newUser;
		this->_pollFDSize--;
	}
}

void Server::_processMessage(std::string buffer, int currentIndex)
{
	int	currentFD = this->_pollFD[currentIndex].fd;
	std::vector<std::string> split_message;
	split_message = split(buffer, '\n');
	for (size_t i = 0; i < split_message.size(); i++)
	{
		if (split_message[i].empty())
			continue;
		if (this->_users[currentFD]->getLogged() || this->_isExecutableCommand(split_message[i]))
			this->_executeUserCommand(currentFD, split_message[i]);
		else if (!this->_users[currentFD]->getLogged())
			ERR_ALREADYREGISTERED(this->_users[currentFD]);

	}
}

void Server::_closeCurrentUser(int currentIndex)
{
	for (size_t i = 0; i < this->_pollFD.size(); i++) 
	{
		if (this->_pollFD[i].fd == currentIndex) {
			this->_pollFD.erase(this->_pollFD.begin() + i);
			break;
		}
	}
	delete (this->_users[currentIndex]);
	this->_users.erase(currentIndex);
	close(currentIndex);
}

void Server::_connectEachUser(void)
{
	char			buffer[MAX_CHAR];
	int				returnValue;

	for (size_t i = 1; i < this->_pollFD.size() && this->_pollFDSize; i++)
	{
		try
		{
			if (this->_pollFD[i].revents & POLLIN)
			{
				memset(&buffer, 0, MAX_CHAR);
				returnValue = recv(this->_pollFD[i].fd, buffer, sizeof(buffer), 0);
				if (returnValue <= 0)
				{
					if (returnValue < 0)
						std::cout << "recv command failed" << std::endl;
					std::vector<std::string> command;
					command.push_back("QUIT");
					command.push_back(":Leaving");
					this->_quit(i, command);
					break;
				}
				else if (returnValue > 0)
				{
					this->_processMessage(buffer, i);
				}
			}
		}
		catch(const std::exception& error)
		{
			throw (std::runtime_error(error.what()));
		}
	}
}

bool Server::_isExecutableCommand(std::string message)
{
	std::vector<std::string>	command = split(message, ' ');
	std::string		commands[]	= {
		"CAP",
		"PASS",
		"NICK",
		"USER",
	};
	for (size_t i = 0; i < commands->size() + 1; i++)
		if (!commands[i].compare(command[0]))
			return (true);
	return (false);
}

void	Server::_executeUserCommand(int fd, std::string message)
{
	std::cout << L_ARROW_ICON << " " << fd << " {" << message << "}" << std::endl;
	std::vector<std::string>	command = split(message, ' ');

	if (command[0] == "KICK")
		this->_kick(fd, command);
	else if (command[0] == "INVITE")
		this->_invite(fd, command);
	else if (command[0] == "TOPIC")
		this->_topic(fd, command);
	else if (command[0] == "MODE")
		this->_mode(fd, command);
	else if (command[0] == "CAP")
		this->_cap(fd);
	else if (command[0] == "PASS")
		this->_pass(fd, command);
	else if (command[0] == "NICK")
		this->_nick(fd, command);
	else if (command[0] == "USER")
		this->_user(fd, command);
	else if (command[0] == "JOIN")
		this->_join(fd, command);
	else if (command[0] == "PRIVMSG")
		this->_privmsg(fd, command);
	else if (command[0] == "WHO")
		this->_who(fd, command);
	else if (command[0] == "PART")
		this->_part(fd, command);
	else if (command[0] == "QUIT")
		this->_quit(fd, command);
	else
		ERR_UNKNOWNCOMMAND(this->_users[fd], command[0]);
}

// GETTERS
int		Server::getServerSocket(void) const {return (this->_serverSocket);}

// METHODS
void	Server::init(void)
{
	if (this->_serverSocket < 0)	
		throw (std::runtime_error("Socket initialization failed"));
	std::cout << BLUE "[SERVER INITIALIZATION ON PORT " << this->_port << "]" RST << std::endl;
	std::cout << CYAN "[PASSWORD: " << this->_password << "]" RST << std::endl;
	int socketOptionValue = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socketOptionValue, sizeof(socketOptionValue)) == -1)
		throw(std::runtime_error("Set socket option failed"));
	if (ioctl(this->_serverSocket, FIONBIO, &socketOptionValue))
		throw(std::runtime_error("Ioctl failed"));
	if (bind(this->_serverSocket, (struct sockaddr*)&this->_serverAddress, sizeof(this->_serverAddress)) < 0)
		throw(std::runtime_error("Bind failed"));
	if (listen(this->_serverSocket, 10) < 0)
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
