# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 13:59:53 by gdumas            #+#    #+#              #
#    Updated: 2024/09/12 20:19:59 by talibabtou       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	cub3D
CC			=	cc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS) $(OFLAGS)
OFLAGS		=	-Ofast -march=native -flto
IFLAGS		=	-I $(INCS) -I $(MLX_DIR) -I $(LIBFT_DIR)inc/
LFLAGS		=	-Llib/libft -Llib/minilibx-linux/ -lft -lmlx -lXext -lX11 -lm

SCREEN_WIDTH	=	1640
SCREEN_HEIGHT	=	950

INCS		=	inc/
HEADER		=	$(addprefix $(INCS), cub3d.h)
LIBFT_H		=	$(addprefix $(LIBFT_DIR)inc/, libft.h)
MLX_H		=	$(addprefix $(MLX_DIR), mlx.h mlx_int.h)

SRC_DIR		=	src/
OBJ_DIR		=	obj/
MLX_DIR		=	lib/minilibx-linux/
LIBFT_DIR	=	lib/libft/

# Sources & Objects #

ERROR		=	manage_errors

LOOP		=	game_loop					\
				controller/keys				\
				frame/print_frame			\
				frame/print_overlay			\
				player/init					\
				player/modifs				\
				player/try_move				\
				player/utils				\
				ray_casting/dda_ray_config	\
				ray_casting/dda_wall_config

INIT		=	mlx		\
				sprite	\
				struct

PARSING		=	colors_utils	\
				colors			\
				file_utils		\
				file			\
				map_utils		\
				map				\
				parsing_handler	\
				texture_utils	\
				texture

MAIN		=	main

SRCS		=	$(addprefix $(SRC_DIR)error/, $(addsuffix .c, $(ERROR)))		\
				$(addprefix $(SRC_DIR)game_loop/, $(addsuffix .c, $(LOOP)))		\
				$(addprefix $(SRC_DIR)init_struct/, $(addsuffix .c, $(INIT)))	\
				$(addprefix $(SRC_DIR)parsing/, $(addsuffix .c, $(PARSING)))	\
				$(addprefix $(SRC_DIR), $(addsuffix .c, $(MAIN)))

OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Rules #

.DEFAULT_GOAL	:=	all

all				:	submodule force $(NAME)

$(NAME)			:	$(OBJS)
	@echo "\nCompiling cub3d"
	@$(CC) $(FLAGS) -o $@ $(OBJS) $(LFLAGS)
	@echo "Done!"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) $(MLX_H) Makefile | $(OBJ_DIR)
	@mkdir -p $(@D)  # Create directory if it doesn't exist
	@printf "Generating cub3d objects: %-33.33s\r" $@
	@$(CC) $(FLAGS) -D SCREEN_WIDTH=$(SCREEN_WIDTH) -D SCREEN_HEIGHT=$(SCREEN_HEIGHT) -c $< -o $@

$(OBJ_DIR)		:
	@mkdir -p $(OBJ_DIR)

submodule		:
	@if [ ! -d "./lib/minilibx-linux" ]; then 															\
		echo "Cloning minilibx-linux";																\
		git clone https://github.com/42Paris/minilibx-linux.git ./lib/minilibx-linux > /dev/null 2>&1;	\
	fi

force			:	submodule
	@make -sC lib/libft
	@if [ ! -f "lib/libft/libft.a" ]; then	\
		make -sC lib/libft;					\
	fi
	@if [ ! -f "lib/minilibx-linux/libmlx.a" ]; then	\
		echo "Creating libmlx.a";							\
		make -sC lib/minilibx-linux > /dev/null 2>&1;	\
		echo "Done!";									\
	fi

clean			:
	@if [ -d "$(OBJ_DIR)" ]; then					\
		echo "Cleaning cub3D obj/ directory";		\
		rm -rf $(OBJ_DIR);							\
	fi
	@make -sC lib/libft clean
	@if [ -d "$(MLX_DIR)" ]; then					\
		make -sC lib/minilibx-linux clean > /dev/null 2>&1;	\
	fi

fclean			:	clean
	@if [ -f "cub3D" ]; then				\
		echo "Cleaning program: cub3D";		\
		rm -f $(NAME);						\
	fi
	@make -sC lib/libft fclean
	@if [ -d "$(MLX_DIR)" ]; then					\
		echo "Cleaning minilibx-linux directory";	\
		rm -rf $(MLX_DIR);							\
	fi

re				:	fclean all

# Mobile rule

mobile			:	SCREEN_WIDTH = 450
mobile			:	SCREEN_HEIGHT = 932
mobile			:	re

.PHONY			:	all re clean fclean force mobile
