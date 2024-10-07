CC = cc
RM = rm -f
NAME = cub3D
NAME_BONUS = cub3D_bonus
HAEDER = ./mandatory/cub3d.h
HAEDER_BONUS = ./bonus/cub3d_bonus.h
CFLAGS = -Wall -Wextra -Werror
SRC = ./mandatory/parsing/cub3d.c ./mandatory/parsing/utilise2.c ./mandatory/parsing/initialize.c ./mandatory/parsing/utilice.c ./mandatory/parsing/check_map.c \
	./mandatory/parsing/handle_err.c ./mandatory/parsing/utilise4.c ./mandatory/parsing/utilise5.c ./mandatory/parsing/utilice1.c ./mandatory/parsing/utilise3.c\
	./mandatory/raycasting/mainn.c ./mandatory/raycasting/intersection.c ./mandatory/raycasting/keys.c ./mandatory/raycasting/wall.c\

SRC_BONUS = ./bonus/parsing/cub3d_bonus.c ./bonus/parsing/utilise2_bonus.c ./bonus/parsing/initialize_bonus.c ./bonus/parsing/utilice_bonus.c ./bonus/parsing/check_map_bonus.c \
	./bonus/parsing/handle_err_bonus.c ./bonus/parsing/utilise4_bonus.c ./bonus/parsing/utilise5_bonus.c\
	./bonus/parsing/utilice1_bonus.c ./bonus/parsing/utilise3_bonus.c \
	./bonus/raycasting/mainn_bonus.c ./bonus/raycasting/mini_map_bonus.c ./bonus/raycasting/intersection_bonus.c ./bonus/raycasting/door_bonus.c ./bonus/raycasting/keys_bonus.c ./bonus/raycasting/wall_bonus.c\

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

LIBS = -L./libft -lft

LIB = MLX/build/libglfw3.a MLX/build/libmlx42.a  -framework Cocoa -framework OpenGL -framework IOKit

all: libft $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIB) $(LIBS) $(OBJS) -o $(NAME)

bonus: libft $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(LIB) $(LIBS) $(OBJS_BONUS) -o $(NAME_BONUS)

$(OBJS): $(HAEDER)
$(OBJS_BONUS): $(HAEDER_BONUS)

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C ./libft

re: fclean all

re_bonus: fclean bonus

.PHONY: libft
