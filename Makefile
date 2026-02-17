NAME    = philo

CC      = cc 
CFLAGS  = -Wall -Wextra -Werror -g
RM      = rm -rf

INCLUDE = include

SRCS    = srcs/main.c \
		  srcs/philo.c \
		  srcs/monitor.c \
		  srcs/init.c \
		  srcs/output.c \
		  srcs/set_get.c \
		  srcs/safe_handle.c \
		  srcs/atoi.c \
		  srcs/error.c \
		  srcs/utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
