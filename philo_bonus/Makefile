SRCS = ft_atoi_bonus.c garb_col_bonus.c parse_bonus.c philo_bonus.c time_bonus.c routine_bonus.c create_philo.c
		

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
