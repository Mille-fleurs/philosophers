NAME         = philo

CC          = cc 
CFLAGS      = -Wall -Wextra -Werror -g
DEBUG_FLAGS = -g3 -O0 -fsanitize=address,undefined
RM          = rm -rf

INCLUDE     = include

SRCS    	= srcs/main.c \
			  srcs/philo.c \
			  srcs/philo_utils.c \
			  srcs/monitor.c \
			  srcs/init.c \
			  srcs/output.c \
			  srcs/set_get.c \
			  srcs/safe_handle.c \
			  srcs/parsing.c \
			  srcs/error.c \
			  srcs/utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -pthread -I$(INCLUDE) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
