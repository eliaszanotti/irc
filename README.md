# Internet Relay Chat (IRC)

This project aims to create a standard **IRC server** for client/server exchanges.

It was developed by [Léon Pupier](https://github.com/LeonPupier), [Thibault Giraudon](https://github.com/Thib1708) and [Elias Zanotti](https://github.com/eliaszanotti) as part of the **school 42** curriculum.

## Summary
- [How to make the executable ?](#how-to-make-the-executable)
- [How to setup the server ?](#how-to-setup-the-server)
- Commands availables:
	- [CAP](#cap-message)
	- [INVITE](#invite-message)
	- [JOIN](#join-message)
	- [KICK](#kick-message)
	- [LIST](#list-message)
	- [MODE](#mode-message)
	- [NICK](#nick-message)
	- [PART](#part-message)
	- [PASS](#pass-message)
	- [PRIVMSG](#privmsg-message)
	- [QUIT](#quit-message)
	- [TOPIC](#topic-message)
	- [USER](#user-message)
	- [WHO](#who-message)
- [Credits](#credits)

## How to make the executable ?
1. Clone the GitHub [repository](https://github.com/eliaszanotti/irc.git)
2. Open the console in the current directory
3. Compile the project with the Makefile
```shell
make
```
4. Run the executable named *ircserv*
5. Enjoy ;)

## How to setup the server ?
```
./ircserv <port> <password>
```
The server executable expects 2 arguments to be able to be executed. The **port** on which listens for incoming connections and the **password** to ensure server security.

## CAP message
```
Command: CAP
```
The **CAP** command is used for capability negotiation between a server and a client.
HexChat send **CAP** directly after the connection to the server.
The command returns to the client:
```
PASS <password>
NICK <nickname>
USER <name> 0 * :<realname>
```

## INVITE message
```
Command: INVITE <nickname> <channel>
```
The **INVITE** command is used to invite a user to a channel. The parameter **nickname** is the nickname of the person to be invited to the target channel **channel**.

```
Command: INVITE
```
If **INVITE** is executed without arguments, the client receives a list of channels where it is invited.

## JOIN message
```
Command: JOIN <channel>{,<channel>} [<key>{,<key>}]
```
The **JOIN** command indicates that the client wants to join the given channel(s), each channel using the given key for it.

## KICK message
```
Command: KICK <channel> <user> [<reason>]
```
The **KICK** command can be used to request the forced removal of a user from a channel. It causes the **user** to be removed from the **channel** by force.
The reason for the **KICK** is optional and will be sent to the **user** if provided. 

## LIST message
```
Command: LIST
```
The **LIST** command is used to get a list of channels along with some information about each channel.

## MODE message
```
Command: MODE <channel> [<mode> [<mode arguments>...]]
```
The **MODE** command is used to set or remove options (or modes) from a given **channel**.
**mode** starts with a '+' or '-' character:
- '+': Adds the following mode(s).
- '-': Removes the following mode(s).

And is made up of the following characters:
#### o : Change the operator privilege on someone
- **+o** : Add the operator privilege on user
- **-o** : Remove the operator privilege on user

For example:
```
Command: MODE #lobby +o xavier
Explanation: The user Xavier becomes an operator.
```
> [!NOTE]
> *By default, the founder of the channel is the only operator of the channel.*

#### t : Change the topic priviliege
- **+t** : Operators are the only ones who can change the topic
- **-t** : All channel users can change the topic

For example:
```
Command: MODE #lobby +t
Explanation: The topic can only be modified by operators now.
```
> [!NOTE]
> *By default, all users can change the topic of a channel.*

#### i : Change the channel on invite mode
- **+i** : Make the channel invitation only
- **-i** : Make the channel public

For example:
```
Command: MODE #lobby +i
Explanation: The channel is now on invitiation only.
```
> [!NOTE]
> *By default, the channel is public.*

#### k : Change the password of the channel
- **+k** : Add a password to the channel
- **-k** : Make the channel without password

For example:
```
Command: MODE #lobby +k welcome
Explanation: The user set the password "welcome" on the channel #lobby.
```
> [!NOTE]
> *By default, the channel has no password.*

#### l : Change the users limit on the channel
- **+l** : Add a user limit to the channel
- **-l** : Remove the channel user limit

For example:
```
Command: MODE #lobby +l 42
Explanation: The maximum number of users on the channel is 42.
```
> [!NOTE]
> *By default, the channel has no user limit.*

## NICK message
```
Command: NICK <nickname>
```
The **NICK** command is used to give the client a **nickname** or change the previous one.

## PART message
```
Command: PART <channel>{,<channel>} [<reason>]
```
The **PART** command removes the client from the given **channel**(s). On sending a successful **PART** command, the user will receive a PART message from the server for each channel they have been removed from. **reason** is the reason that the client has left the channel(s).

## PASS message
```
Command: PASS <password>
```
The **PASS** command is used to set a ‘connection password’. If set, the **password** must be set before any attempt to register the connection is made. This requires that clients send a **PASS** command before sending the **NICK** / **USER** combination.

## PRIVMSG message
```
Command: PRIVMSG <target>{,<target>} <text to be sent>
```
The **PRIVMSG** command is used to send private messages between users, as well as to send messages to channels. **target** is the nickname of a client or the name of a channel.

## QUIT message
```
Command: QUIT <reason>
```
The **QUIT** command is used to terminate a client’s connection to the server.
A **reason** can be provided to tell others why the user is leaving the server

## TOPIC message
```
Command: TOPIC <channel> [<topic>]
```
The **TOPIC** command is used to change or view the **topic** of the given **channel**.

## USER message
```
Command: USER <username> 0 * <realname>
```
The **USER** command is used at the beginning of a connection to specify the **username** and **realname** of a new user.

## WHO message
```
Command: WHO <mask>
```
This command is used to query a list of users who match the provided mask.


## Credits
The server was entirely developed by the 3 project collaborators.
*Bisous bisous <3*
```
       .-"-.            .-"-.            .-"-.           .-"-.
     _/_-.-_\_        _/.-.-.\_        _/.-.-.\_       _/.-.-.\_
    / __} {__ \      /|( o o )|\      ( ( o o ) )     ( ( o o ) )
   / //  "  \\ \    | //  "  \\ |      |/  "  \|       |/  "  \|
  / / \'---'/ \ \  / / \'---'/ \ \      \'/^\'/         \ .-. /
  \ \_/`"""`\_/ /  \ \_/`"""`\_/ /      /`\ /`\         /`"""`\
   \           /    \           /      /  /|\  \       /       \ 
```