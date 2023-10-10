# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 17:08:00 by elias             #+#    #+#              #
#    Updated: 2023/10/10 14:54:52 by lpupier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE

NAME			=	ircserv

LIST_SRCS		=	main.cpp					\
					Server.cpp					\
					Channel.cpp					\
					User.cpp					\
					\
					${DIR_COMMAND}cap.cpp		\
					${DIR_COMMAND}invite.cpp	\
					${DIR_COMMAND}join.cpp		\
					${DIR_COMMAND}kick.cpp		\
					${DIR_COMMAND}mode.cpp		\
					${DIR_COMMAND}nick.cpp		\
					${DIR_COMMAND}pass.cpp		\
					${DIR_COMMAND}privmsg.cpp	\
					${DIR_COMMAND}topic.cpp		\
					${DIR_COMMAND}user.cpp		\
					${DIR_COMMAND}part.cpp		\
					\
					${DIR_UTILS}sendTo.cpp		\
					${DIR_UTILS}split.cpp		\
					

LIST_INCS		=	irc.hpp		\
					Server.hpp	\
					Channel.hpp	\
					User.hpp

# DIRECTORY
DIR_OBJS		=	.objs/

DIR_SRCS		=	srcs/

DIR_COMMAND		=	command/

DIR_UTILS		=	utils/

DIR_INCS		=	includes/

# CONSTANT

PRINT 			= 	@printf

FLAGS			=	-Wall -Wextra -Werror -g3

STD				=	-std=c++98

MAKEFLAGS		+=	--no-print-directory

CC 				=	c++

OBJS 			=	$(patsubst %.cpp, $(DIR_OBJS)%.o, $(SRCS))

SRCS			=	${addprefix ${DIR_SRCS}, ${LIST_SRCS}}

INCLUDES		=	${addprefix ${DIR_INCS}, ${LIST_INCS}}

# COLOR

RED 			=	\033[1;31m
GREEN 			=	\033[1;32m
YELLOW 			=	\033[1;33m
SUPPR   		=	\r\033[2K
DEFAULT 		=	\033[0m

# RULES

all				:	ascii ${NAME}

${DIR_OBJS}%.o 	:	%.cpp Makefile  ${INCLUDES}
				@mkdir -p $(shell dirname $@)
				@${PRINT} "${YELLOW}${SUPPR}Creating ${NAME}'s objects : $@${DEFAULT}"
				@${CC} ${FLAGS} ${STD} -I ${DIR_INCS} -c $< -o $@ 

${NAME}			:	${OBJS} ${INCLUDES}
				@${PRINT} "${GREEN}${SUPPR}Creating ${NAME}'s objects : DONE${DEFAULT}"
				@${PRINT} "\n${YELLOW}Compiling ${NAME}...${DEFAULT}"
				@${CC} ${OBJS} -o ${NAME} -fsanitize=address
				@${PRINT} "\r${GREEN}Compiling ${NAME} : DONE${DEFAULT}\n\n"

ascii			:
				@${PRINT} "$$ASCII"

clean			:
				@${PRINT} "${RED}Deleting objects : DONE\n"
				@rm -rf ${DIR_OBJS}

fclean			:	clean
				@${PRINT} "${RED}Deleting executable : DONE\n\n${DEFAULT}"
				@rm -f ${NAME}

re				:	fclean all

${DIR_OBJS}		:
				mkdir -p ${DIR_OBJS}

.PHONY		: all clean fclean re

define		ASCII
${C_C}
       .-"-.            .-"-.            .-"-.           .-"-.
     _/_-.-_\_        _/.-.-.\_        _/.-.-.\_       _/.-.-.\_
    / __} {__ \      /|( o o )|\      ( ( o o ) )     ( ( o o ) )
   / //  "  \\\ \    | //  "  \\\ |      |/  "  \|       |/  "  \|
  / / \'---'/ \ \  / / \'---'/ \ \      \'/^\'/         \ .-. /
  \ \_/`"""`\_/ /  \ \_/`"""`\_/ /      /`\ /`\         /`"""`\\
   \           /    \           /      /  /|\  \       /       \\ 
${C_RST}
endef

export		ASCII
