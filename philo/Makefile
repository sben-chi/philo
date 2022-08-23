NAME = philo

CFLAGS = -fsanitize=thread #-Wall -Wextra -Werror 

CC = gcc

MANDATORY_PART = philo.c ft_atoi.c


M_OFILES = ${MANDATORY_PART:.c=.o}

all: $(NAME)

$(NAME): $(M_OFILES)
	$(CC) $(M_OFILES) -o $(NAME) -pthread

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(M_OFILES)
