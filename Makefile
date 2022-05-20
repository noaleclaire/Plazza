##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC		=	Src/main.cpp				\
			Src/checkArgs.cpp			\
			Src/Core.cpp				\
			Src/Cook.cpp				\
			Src/Factory.cpp				\
			Src/Ingredients.cpp			\
			Src/Kitchen.cpp				\
			Src/Mutex.cpp				\
			Src/Parser.cpp				\
			Src/Pizza.cpp				\
			Src/ScopedLock.cpp			\

OBJ		=	$(SRC:%.cpp=%.o)

CFLAGS	=	-std=c++20 -Wall -Wextra -I./include

LDFLAGS	=	-lpthread -pthread

NAME	=	plazza

CC		=	g++

RM		=	rm -f

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

all:		$(NAME)

clean :
			$(RM) $(OBJ)

fclean :	clean
			$(RM) $(NAME)

re:			fclean all

unit_tests:	fclean all
		make -C ./tests

tests_run:	unit_tests
		./tests/unit_tests

.PHONY:	all clean fclean re