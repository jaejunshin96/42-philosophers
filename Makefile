NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= *.c

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@make clean
	@echo "philo has been created."

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@echo "philo has been deleted."

re: fclean all

.PHONY: all, clean, fclean, re
