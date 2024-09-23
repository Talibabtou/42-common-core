# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 13:59:53 by gdumas            #+#    #+#              #
#    Updated: 2024/09/17 15:26:41 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	cub3D
CC			=	cc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS) $(OFLAGS)
OFLAGS		=	-Ofast -march=native -flto
IFLAGS		=	-I $(INCS) -I $(MLX_DIR) -I $(LIBFT_DIR)inc/
LFLAGS		=	-Llib/libft -Llib/minilibx-linux/ -lft -lmlx -lXext -lX11 -lm

SCREEN_WIDTH	=	450
SCREEN_HEIGHT	=	932
FOV = 70
PLAYER_STEP_SIZE = 0.02
PLAYER_ROT_SPEED = 0.0075

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
MOBILE_OBJS	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%_mobile.o, $(SRCS))
# Rules #

.DEFAULT_GOAL	:=	all

all				:	submodule force $(NAME)

mobile			:	submodule force $(NAME)_mobile

$(NAME)			:	$(OBJS)
	@echo "\nCompiling cub3d"
	@$(CC) $(FLAGS) -o $@ $(OBJS) $(LFLAGS)
	@echo "Done!"

$(NAME)_mobile	:	$(MOBILE_OBJS)
	@echo "\nCompiling cub3d mobile version"
	@$(CC) $(FLAGS) -o $@ $(MOBILE_OBJS) $(LFLAGS)
	@echo "Mobile version done!"
	
$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) $(MLX_H) Makefile | $(OBJ_DIR)
	@mkdir -p $(@D)  # Create directory if it doesn't exist
	@printf "Generating cub3d objects: %-33.33s\r" $@
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%_mobile.o	:	$(SRC_DIR)%.c $(HEADER) $(LIBFT_H) $(MLX_H) Makefile | $(OBJ_DIR)
	@mkdir -p $(@D)
	@printf "Generating cub3d mobile objects: %-33.33s\r" $@
	@$(CC) $(FLAGS) -D SCREEN_WIDTH=$(SCREEN_WIDTH) -D SCREEN_HEIGHT=$(SCREEN_HEIGHT) -D FOV=$(FOV) -D PLAYER_STEP_SIZE=$(PLAYER_STEP_SIZE) -D PLAYER_ROT_SPEED=$(PLAYER_ROT_SPEED) -c $< -o $@
	
$(OBJ_DIR)		:
	@mkdir -p $(OBJ_DIR)

submodule		:
	@if [ ! -d "./lib/minilibx-linux" ]; then 															\
		echo "Cloning minilibx-linux";																	\
		git clone https://github.com/42Paris/minilibx-linux.git ./lib/minilibx-linux > /dev/null 2>&1;	\
	fi

force			:	submodule
	@make -sC lib/libft
	@if [ ! -f "lib/libft/libft.a" ]; then	\
		make -sC lib/libft;					\
	fi
	@if [ ! -f "lib/minilibx-linux/libmlx.a" ]; then	\
		echo "Creating libmlx.a";						\
		make -sC lib/minilibx-linux > /dev/null 2>&1;	\
		echo "Done!";									\
	fi

clean			:
	@if [ -d "$(OBJ_DIR)" ]; then					\
		echo "Cleaning cub3D obj/ directory";		\
		rm -rf $(OBJ_DIR);							\
	fi
	@make -sC lib/libft clean
	@if [ -d "$(MLX_DIR)" ]; then							\
		make -sC lib/minilibx-linux clean > /dev/null 2>&1;	\
	fi

fclean			:	clean
	@if [ -f "cub3D" ]; then				\
		echo "Cleaning program: cub3D";		\
		rm -f $(NAME);						\
	fi
	@if [ -f "cub3D_mobile" ]; then				\
		echo "Cleaning program: cub3D_mobile";	\
		rm -f $(NAME)_mobile;					\
	fi
	@make -sC lib/libft fclean
	@if [ -d "$(MLX_DIR)" ]; then					\
		echo "Cleaning minilibx-linux directory";	\
		rm -rf $(MLX_DIR);							\
	fi

re				:	fclean all

re_mobile		:	fclean mobile

.PHONY			:	all re clean fclean force mobile re_mobile
