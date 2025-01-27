CC := cc
CFLAGS := -Wall -Werror -Wextra

MLX_DIR := ./minilibx
MLX_FLAGS := -lmlx -lXext -lX11 -L$(MLX_DIR)
LIBFT_DIR := ./libft/
LIBFT_FLAGS := -lft -L$(LIBFT_DIR)

NAME := fdf

HEADER := fdf.h
SRC := test.c
OBJ := $(SRC:%.c=%.o)


all: libft mlx $(NAME)
libft:
	make -C $(LIBFT_DIR)
mlx:
	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_FLAGS) $(MLX_FLAGS)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	rm $(MLX_DIR)/Makefile.gen

re: fclean all

.PHONY: all fdf libft mlx clean fclean re
