NAME = philo

CFLAGS = -Wall -Wextra -Werror 

CC = gcc

MANDATORY_PART = philo.c philo_utils.c philo_init.c


M_OFILES = ${MANDATORY_PART:.c=.o}

all: $(NAME)

$(NAME): $(M_OFILES)
	$(CC) $(M_OFILES) -o $(NAME) -pthread 
re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(M_OFILES)
