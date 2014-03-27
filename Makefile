CXX = g++

RM = rm -f

SRCS =	AModule.cpp \
	Chipset.cpp \
	CPU.cpp \
	IO.cpp \
	main.cpp \
	SOperandMaker.cpp \
	StackMemory.cpp \
	VM.cpp \

OBJS = $(SRCS:.cpp=.o)

BIN = avm


$(BIN):	$(OBJS)
	$(CXX) $(OBJS) -o $(BIN)

all:	$(BIN)

debug: CXX = clang++
debug: CXXFLAGS = -W -Wall -Wextra -g3
debug: re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all debug clean fclean re
