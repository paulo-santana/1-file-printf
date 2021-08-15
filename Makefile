NAME = libftprintf.a

SRC = ft_printf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)

%.o: %.c
	clang -Wall -Werror -Wextra -c $< -o $@


