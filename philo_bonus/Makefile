NAME         = philo_bonus

CC          = cc 
CFLAGS      = -Wall -Wextra -Werror
DEBUG_FLAGS = -g3 -O0 -fsanitize=address,undefined
RM          = rm -rf

INCLUDE     = include

SRCS    	= srcs/main.c \
			  srcs/philo.c \
			  srcs/monitor.c \
			  srcs/init.c \
			  srcs/output.c \
			  srcs/parsing.c \
			  srcs/cleanup.c \
			  srcs/exit.c \
			  srcs/time.c \
			  srcs/utils.c

OBJS    	= $(SRCS:.c=.o)

ifeq ($(DEBUG),1)
    CFLAGS += -g3 -O0 -fno-omit-frame-pointer -DDEBUG=1
endif

ifeq ($(ASAN),1)
    CFLAGS += -fsanitize=address,undefined
endif

ifeq ($(TSAN),1)
    CFLAGS += -fsanitize=thread
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -pthread -I$(INCLUDE) -c $< -o $@

debug:
	$(MAKE) DEBUG=1 re

tsan:
	$(MAKE) TSAN=1 re

asan:
	$(MAKE) ASAN=1 re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug asan tsan
