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

void	Server::createNewUser(pollfd pollfd)
{
	User	*newUser = new User(pollfd);
	this->_users[pollfd.fd] = newUser;
}

void	Server::waitingForNewUsers(void)
{	
	bool			serverIsRunning = true;
	int				new_sd = 0;
	int				closeConnection;
	char			buffer[MAX_CHAR];
	int				returnValue;


	while (serverIsRunning)
	{
		try
		{
			this->_processPoll();
		}
		catch(const std::exception& error)
		{
			throw (std::runtime_error(error.what()));
		}

		// Add a new user
		if (this->_pollFD[0].revents & POLLIN)
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
			this->_pollFD[this->_pollFDSize].fd = new_sd;
			this->_pollFD[this->_pollFDSize].events = POLLIN;
			this->createNewUser(this->_pollFD[this->_pollFDSize]);
			this->_pollFDSize++;
		}

		// Gestion for each client
		for (int i = 1; i < this->_pollFDSize; i++)
		{
			closeConnection = false;
			if (this->_pollFD[i].revents & POLLIN)
			{
				// Receive the message from the user
				memset(&buffer, 0, MAX_CHAR);
				returnValue = recv(this->_pollFD[i].fd, buffer, sizeof(buffer), 0);
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
					std::cout << "[-] " << this->_users[this->_pollFD[i].fd]->getNickname() << " leaved the server" << std::endl;
					closeConnection = true;
				}
				else
				{
					// Empty message
					if (returnValue == 1)
						continue ;

					if (!this->_checkCommandInsideMessage(this->_pollFD[i].fd, buffer))
					{
						if (!this->_users[this->_pollFD[i].fd]->getLogged())
							send(this->_pollFD[i].fd, "Client isn't connected\n", 23, 0);
						else
						{
							for (int j = 1; j < this->_pollFDSize; j++)
							{
								if (j == i)
									continue ;
								if (this->_users[this->_pollFD[j].fd]->getConnected())
									send(this->_pollFD[j].fd, buffer, returnValue, 0);
							}
						}
					}
				}
			}
			
			// If there is a problem with the user
			if (closeConnection)
			{
				close(this->_pollFD[i].fd);
				this->_pollFD[i].fd = -1;
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
				break ;
			}
		}
	}

	// Close all the clients if the server is down
	for (int i = 0; i < this->_pollFDSize; i++)
	{
		if (this->_pollFD[i].fd >= 0)
			close(this->_pollFD[i].fd);
	}
}

bool	Server::_checkCommandInsideMessage(int fd, std::string message)
{
	std::vector<std::string>	command;
	// size_t		stop_idx;
	size_t			i;

	std::cout << "Message received: [" << message << "]" << std::endl;
	message.erase(message.size() -1);
	command = split(message, ' ');
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

bool	Server::_join(int fd, std::vector<std::string> command)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	passwords;
	size_t						j = 0;
	
	std::cout << "join() called" << std::endl;

	if (command.size() > 3)
		return (false);
	if (command.size() < 2)
	{
		send(fd, "Usage: JOIN <channel>, joins the channel {DEBUG}", 41, 0);
		return (false);
	}
	if (command[1][0] != '#')
	{
		send(fd, " :Invalid channel name {DEBUG}", 23, 0);
		return (false);
	}

	// Names and passwords
	channels = split(command[1], ',');
	if (command.size() == 3)
		passwords = split(command[2], ',');
	
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i][0] != '#')
			return (false);

		// Connection to an existing channel
		for (j = 0; j < this->_channels.size(); j++)
		{
			if (channels[i] == this->_channels[j]->getName())
			{
				if (!this->_channels[j]->getPassword().empty())
				{
					if (i < passwords.size())
					{
						// Password gestion
						if (this->_channels[j]->getPassword() == passwords[i])
						{
							
						}
						else
						{
							
						}
					}
				}
				break ;
			}
		}

		// Create the channel and join it
		if (j == this->_channels.size())
		{
			Channel	*channel = new Channel(channels[i]);
			this->_channels.push_back(channel);

			std::string	output;
			output = ":" + this->_users[fd]->getNickname() + "!" + this->_users[fd]->getName() + "@" + IP_ADDR + " JOIN " + channel->getName() + "\r\n";
			for (size_t k = 0; k < this->_users.size(); k++)
			{
				if (this->_users[k]->getFd() != fd)
					send(this->_users[k]->getFd(), output.c_str(), output.length(), 0);
			}
			// 353
			output = ":" + SERVER("353") + this->_users[fd]->getNickname() + " " + "MODE" + " " + channel->getName() + " :" + "+nt" + this->_users[fd]->getNickname() + "\r\n";
			send(fd, output.c_str(), output.length(), 0);
			// 366
			output = ":" + SERVER("366") + this->_users[fd]->getNickname() + " " + channel->getName() + " :End of /NAMES list\r\n";
			send(fd, output.c_str(), output.length(), 0);
		}
	}
	return (true);
}

void	Server::sendTo(const User *user, const std::string &message)
{
	size_t byteSent = 0;

	while (byteSent < message.length())
	{
		long len = send(user->getFd(), message.c_str(), message.length(), 0);
		if (len < 0)
		{
			std::cerr << "send() error: server to client" << std::endl;
			break ;
		}
		byteSent += len;
	}
}
