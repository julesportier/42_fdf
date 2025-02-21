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

SRC_DIR := src
vpath %.h $(SRC_DIR)
HEADER := fdf.h
vpath %.c $(SRC_DIR)
SRC := fdf.c \
       free.c \
       error.c \
       utils.c \
       mlx_utils.c \
       parsing.c \
       store_grid_data.c \
       draw.c
OBJ_DIR := build
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: ft mlx $(OBJ_DIR) $(NAME)

noerr: CFLAGS = $(CFLAGS_NE)
noerr: all

dbg: CFLAGS = $(CFLAGS_DB)
dbg: all

ft:
	make -C $(LIBFT_DIR)
mlx:
	make -C $(LIBMLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(MATH_FLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(HEADER) $(LIBFT_AR) $(LIBMLX_AR)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
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

.PHONY: all ft mlx clean fclean re noerr dbg
