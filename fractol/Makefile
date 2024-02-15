# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 16:59:10 by gdumas            #+#    #+#              #
#    Updated: 2024/02/14 15:39:11 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	fractol
CC			=	gcc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS)
LFLAGS		=	-Llib/libft -Llib/minilibx-linux/ -lft -lmlx -lXext -lX11 -lm

INCS		=	includes/
HEADERS		=	$(addprefix $(INCS), fractol.h keys.h)
MLX_H		=	$(addprefix $(MLX_DIR), mlx.h mlx_int.h)
LIBFT_H		=	$(addprefix $(LIBFT_DIR)includes/, libft.h)
IFLAGS		=	-I $(INCS) -I $(MLX_DIR) -I $(LIBFT_DIR)includes/

SRC_DIR		=	src/
OBJ_DIR		=	obj/
MLX_DIR		=	lib/minilibx-linux/
LIBFT_DIR	=	lib/libft/


# Sources & Objects #

SRC			=	arg_parsing	\
				color_utils	\
				color		\
				events		\
				fractol		\
				init		\
				msgs		\
				render		\
				utils

FRCT_SRC	=	burning_ship	\
				julia			\
				mandelbrot

SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))						\
				$(addprefix $(SRC_DIR)fractal_sets/, $(addsuffix .c, $(FRCT_SRC)))

OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


# Rules #

.DEFAULT_GOAL	:=	all

all				:	submodule force $(NAME)

$(NAME)			:	$(OBJS)
				@echo "Compiling fractol"
				@$(CC) $(OBJS) $(LFLAGS) -o $@
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADERS) $(MLX_H) $(LIBFT_H) Makefile | $(OBJ_DIR)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

submodule		:
				@if [ ! -d "./lib/minilibx-linux" ]; then 											\
					git clone https://github.com/42Paris/minilibx-linux.git ./lib/minilibx-linux;	\
				fi

force			: submodule
				@make -sC lib/libft
				@if [ ! -f "lib/libft/libft.a" ]; then	\
					echo "Making libft.a";				\
					make -sC lib/libft;					\
				fi
				@if [ ! -f "lib/minilibx-linux/libmlx.a" ]; then	\
					echo "Making libmlx.a";							\
					make -sC lib/minilibx-linux;					\
					echo "Done !";									\
				fi


clean			:
				@if [ -d "$(OBJ_DIR)" ]; then				\
					echo "Cleaning fractol obj directory";	\
					rm -rf $(OBJ_DIR);						\
				fi
				@make -sC lib/libft clean
				@make -sC lib/minilibx-linux clean

fclean			:	clean
				@if [ -f "fractol" ]; then				\
					echo "Cleaning program: fractol";	\
					rm -f $(NAME);						\
				fi
				@make -sC lib/libft fclean


re				:	fclean all


.PHONY			:	all re clean fclean force
