NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= *.c

$(NAME): 
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@make clean
	@echo "Compiled successfully."

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned philo."

re: fclean all

.PHONY: all, clean, fclean, re