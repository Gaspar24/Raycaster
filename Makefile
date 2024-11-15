NAME = raycaster.exe

SRC = main.c raycasting.c data_init.c rendering.c movement_and_actions.c
OBJ = $(SRC:.c=.o)

CC = gcc

CCFLAGS = -Wall -Werror -Wextra -g 

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX_DIR = ./minilibx-linux

MLX = ./minilibx-linux/libmlx.a

X11_LIBS = -L/usr/lib/X11 -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)
	@$(CC) $(CCFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJ)  $(MLX) $(X11_LIBS) -lm
	@rm -f $(OBJ)

	

%.o: %.c
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re : fclean all