NAME = philo
BNAME = bonus/philo

CFLAGS = -Wall -Wextra -Werror

CC = gcc

MANDATORY_PART = main.c ft_atoi.c
BONUS_PART = 

M_OFILES = ${MANDATORY_PART:.c=.o}
B_OFILES =  ${BONUS_PART:.c=.o}

all: $(NAME)

$(NAME): $(M_OFILES)
	$(CC) $(M_OFILES) -o $(NAME)

bonus: $(B_OFILES)
	$(CC) $(B_OFILES) -o $(BNAME)

re: fclean all

fclean: clean
	rm -f $(NAME) $(BNAME)

clean:
	rm -f $(M_OFILES) $(B_OFILES)
