##
## Makefile for C++ in /home/fontan_n/Desktop/C++Avancee/Serveur
##
## Made by Nicolas Fontanet
## Login   <fontan_n@epitech.net>
##
## Started on  Sun Apr 10 01:09:17 2016 Nicolas Fontanet
## Last update Wed Dec 21 07:58:21 2016 Nicolas Fontanet
##

NAME    =       Serveur

SRC     =       $(wildcard src/*.cpp) \

INCLUDE =       -I./inc/

CC      =       g++

RM      =       @rm -rf

OBJS    =       $(SRC:.cpp=.o)

CPPFLAGS=       -W -std=c++11 -Wall -Werror -Wextra $(INCLUDE)

all:             $(NAME)

$(NAME):        $(OBJS)
		@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
		@echo -e "\e[0;32m\n[Compiled]\e[0m successfully $(NAME)."
		@echo -e "\e[032m-------------------------------\e[0m"
		@echo ""

clean:
		@echo -e "\e[0;31m[Efface]\e[0mLes fichier temporaires ..."
	        $(RM) $(OBJS)

fclean:         clean
		@echo -e "\e[0;31m[Efface]\e[0mLes anciens binary ..."
		@echo -e "\e[0;32m-----------------------------------\e[0m"

re:		fclean all

.PHONY:		all clean fclean re
