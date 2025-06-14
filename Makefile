CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address
RM = rm -rf
NAME = ircserv


SRCS = main.cpp src/Server.cpp src/Client.cpp src/Channel.cpp src/CommandHandler.cpp src/utils.cpp \
		src/commands/ACommand.cpp src/commands/NickCommand.cpp src/commands/PassCommand.cpp src/commands/JoinCommand.cpp src/commands/UserCommand.cpp\
		src/commands/PrivmsgCommand.cpp src/commands/TopicCommand.cpp src/commands/InviteCommand.cpp src/commands/KickCommand.cpp \
		src/commands/ModeCommand.cpp
	   

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
	./$(NAME) $(ARGS)

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind.log ./$(NAME) $(ARGS)

.PHONY: all clean fclean re run valgrind