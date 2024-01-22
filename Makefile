.DELETE_ON_ERROR:

NAME = ircserv
CXX = c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98
DIR_SRC = ./src/
DIR_TEST = ./test/
DIR_BIN	= ./bin

# SOURCES = $(ADDPREFIX $(SRC_PATH, $(SRCS_FILE)
# OBJS = $(SOURCES:%.cpp=%.o)

OBJS = $(SRC_PATH:.cpp=.o)

SRC_FILE	 = main.cpp\
				Server.cpp\
				SocketHandler.cpp\
				SocketListener.cpp\
				Client.cpp\
				Channel.cpp\
				Message.cpp\
				CommandParser.cpp\
				Database.cpp\
				Logger.cpp\
				ArgParser.cpp\
				Command.cpp\
				CommandInvoker.cpp\
				ClientManager.cpp\
				User.cpp\
				commands/UserCommand.cpp\
				commands/NickCommand.cpp\
				commands/PrivMsgCommand.cpp\
				commands/JoinCommand.cpp


				

SRC_PATH = $(addprefix $(DIR_SRC), $(SRC_FILE))

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all


