NAME = fdf
MAKE = make
override G += 
FLAGS = -Wall -Wextra -Werror
SRCS = main.c map.c movekeys.c validation.c drawline.c makegrid.c projection.c keymouse.c colour.c additional.c drawetc.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a
all: $(NAME)

$(NAME): $(LIBFT)
	@gcc -I /usr/local/include ./libft/libft.a $(FLAGS) $(SRCS) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

g:
	@gcc -g $(SRCS) -o $(NAME)

clean:
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(LIBFT):
	@$(MAKE) -C ./libft re

git:
	git add .
	git commit -am "$(G)"
	git push
