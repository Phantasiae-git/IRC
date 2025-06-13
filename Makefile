CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address
RM = rm -rf
NAME = ircserv


SRCS = main.cpp src/Server.cpp src/Client.cpp src/Channel.cpp src/CommandHandler.cpp src/utils.cpp \
		src/commands/ACommand.cpp src/commands/NickCommand.cpp src/commands/PassCommand.cpp src/commands/JoinCommand.cpp src/commands/UserCommand.cpp

	   

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@ -I ./

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run