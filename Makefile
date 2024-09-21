CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
NAME = philo_bonus
SRCS = srcs/main.c \
srcs/processing.c \
srcs/initialise.c \
srcs/errors.c \
srcs/simulation.c \
srcs/time.c \
srcs/monitoring.c \
srcs/monitoring_philo.c \
srcs/eating.c
OBJS = $(SRCS:.c=.o)
HEADERS = srcs/philosophers_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

srcs/%.o: srcs/%.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
