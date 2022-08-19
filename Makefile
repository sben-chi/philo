NAME = philo
BNAME = bonus/philo

CFLAGS = -Wall -Wextra -Werror

CC = gcc

MANDATORY_PART = philo.c ft_atoi.c


M_OFILES = ${MANDATORY_PART:.c=.o}
B_OFILES =  ${BONUS_PART:.c=.o}

all: $(NAME)

$(NAME): $(M_OFILES)
	$(CC) $(M_OFILES) -o $(NAME) -pthread



re: fclean all

fclean: clean
	rm -f $(NAME) $(BNAME)

clean:
	rm -f $(M_OFILES) $(B_OFILES)
