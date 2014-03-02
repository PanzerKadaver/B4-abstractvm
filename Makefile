CC = g++

RM = rm -f

SRC =	AModule.cpp \
	Chipset.cpp \
	Commands.cpp \
	CPU.cpp \
	IO.cpp \
	main.cpp \
	SOperandMaker.cpp \
	StackMemory.cpp \
	VM.cpp

OBJ = $(SRC:.cpp=.o)

NAME = avm

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all

.PHONY: all clean fclean re