# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 13:59:53 by gdumas            #+#    #+#              #
#    Updated: 2024/08/20 17:22:07 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	cub3d
CC			=	cc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS)
IFLAGS		=	-I $(INCS) -I $(MLX_DIR) -I $(LIBFT_DIR)
LFLAGS		=	-Llib/libft -Llib/minilibx-linux/ -lft -lmlx -lXext -lX11 -lm

INCS		=	inc/
HEADER		=	$(addprefix $(INCS), cub3d.h)
LIBFT_H		=	$(addprefix $(LIBFT_DIR), libft.h)
MLX_H		=	$(addprefix $(MLX_DIR), mlx.h mlx_int.h)


SRC_DIR		=	src/
OBJ_DIR		=	obj/
MLX_DIR		=	lib/minilibx-linux/
LIBFT_DIR	=	lib/libft/

# Sources & Objects #

DEBUG		=	print_debug

ERROR		=	manage_errors

LOOP		=	game_loop					\
				controller/keys				\
				frame/print_frame			\
				player/init					\
				player/modifs				\
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

SRCS		=	$(addprefix $(SRC_DIR)debug/, $(addsuffix .c, $(DEBUG)))		\
				$(addprefix $(SRC_DIR)error/, $(addsuffix .c, $(ERROR)))		\
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
	@$(CC) $(OBJ) $(FLAGS) -o $@ $(OBJS) $(LFLAGS)
	@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) $(MLX_H) Makefile | $(OBJ_DIR)
	@mkdir -p $(@D)  # Create directory if it doesn't exist
	@printf "Generating cub3d objects... %-33.33s\r" $@
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
	@mkdir -p $(OBJ_DIR)

submodule		:
	@if [ ! -d "./lib/minilibx-linux" ]; then 											\
		git clone https://github.com/42Paris/minilibx-linux.git ./lib/minilibx-linux;	\
	fi

force			:	submodule
	@make -sC lib/libft
	@if [ ! -f "lib/libft/libft.a" ]; then	\
		echo "Making libft.a";				\
		make -sC lib/libft;						\
	fi
	@if [ ! -f "lib/minilibx-linux/libmlx.a" ]; then	\
		echo "Making libmlx.a";							\
		make -sC lib/minilibx-linux;					\
		echo "Done !";									\
	fi


clean			:
	@if [ -d "$(OBJ_DIR)" ]; then					\
		echo "Cleaning cub3d obj/ directory";		\
		rm -rf $(OBJ_DIR);							\
	fi
	@make -sC lib/libft clean
	@make -sC lib/minilibx-linux clean

fclean			:	clean
	@if [ -f "cub3d" ]; then			\
		echo "Cleaning program: cub3d";		\
		rm -f $(NAME);						\
	fi
	@make -sC lib/libft fclean

re				:	fclean all

.PHONY			:	all re clean fclean force