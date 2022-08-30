NAME = philo_bonus

CFLAGS = #-Wall -Wextra -Werror 

CC = gcc

BONUS_PART = philo.c philo_utils.c


B_OFILES = ${BONUS_PART:.c=.o}

all: $(NAME)

$(NAME): $(B_OFILES)
	$(CC) $(B_OFILES) -o $(NAME) -pthread 


re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(B_OFILES)
