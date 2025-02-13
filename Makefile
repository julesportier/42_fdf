CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_NE := -g3

LIBMLX_DIR := ./minilibx
LIBMLX_AR := $(LIBMLX_DIR)/libmlx.a
LIBMLX_FLAGS := -lmlx -lXext -lX11 -L$(LIBMLX_DIR)
LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -lft -L$(LIBFT_DIR)
MATH_FLAGS := -lm

NAME := fdf

HEADER := fdf.h
SRC := fdf.c \
       free.c \
       error.c \
       utils.c \
       mlx_utils.c \
       parsing.c \
       store_grid_data.c \
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
	make -C $(LIBMLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(MATH_FLAGS)

%.o: %.c Makefile $(HEADER) $(LIBFT_AR) $(LIBMLX_AR)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	rm -rf $(LIBMLX_DIR)/obj
	rm -f $(LIBMLX_DIR)/test/main.o

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(LIBMLX_DIR)
	rm -f $(LIBMLX_DIR)/Makefile.gen
	rm -f $(LIBMLX_DIR)/test/Makefile.gen

re: fclean all

.PHONY: all libft mlx clean fclean re no_error debug
