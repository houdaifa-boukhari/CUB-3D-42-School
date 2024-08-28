CC = cc
RM = rm -f
NAME = cub3D
HAEDER = cub3d.h
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRC = ./parisng/cub3d.c ./parisng/utilise2.c ./parisng/initialize.c ./parisng/utilice.c ./parisng/check_map.c \
	./parisng/handle_err.c \
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./parisng/utilice1.c ./parisng/utilise3.c\

OBJS = $(SRC:.c=.o)
LIBS = -L./libft -lft

all: libft $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	@$(RM) $(OBJS)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: libft
