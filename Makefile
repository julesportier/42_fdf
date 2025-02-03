CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_NE := -g3

MLX_DIR := ./minilibx
MLX_FLAGS := -lmlx -lXext -lX11 -L$(MLX_DIR)
LIBFT_DIR := ./libft
LIBFT_FLAGS := -lft -L$(LIBFT_DIR)
MATH_FLAGS := -lm

NAME := fdf

HEADER := fdf.h
SRC := test.c \
       draw.c
OBJ := $(SRC:%.c=%.o)


all: libft mlx $(NAME)

no_error: CFLAGS = $(CFLAGS_NE)
no_error: all
debug: CFLAGS = $(CFLAGS_DB)
debug: all
libft:
	make -C $(LIBFT_DIR)
mlx:
	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_FLAGS) $(MLX_FLAGS) $(MATH_FLAGS)

%.o: %.c Makefile $(HEADER)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/obj
	rm -f $(MLX_DIR)/test/main.o

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(MLX_DIR)/Makefile.gen
	rm -f $(MLX_DIR)/test/Makefile.gen

re: fclean all

.PHONY: all libft mlx clean fclean re no_error debug
