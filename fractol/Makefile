# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 16:59:10 by gdumas            #+#    #+#              #
#    Updated: 2024/02/07 13:51:19 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	fractol
CC			=	gcc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS)
LFLAGS		=	-Lsrc/libft -Lminilibx-linux/ -lft -lmlx -lXext -lX11 -lm

INCS		=	includes/
HEADERS		=	$(addprefix $(INCS), fractol.h keys.h)
MLX_H		=	$(addprefix $(MLX_DIR), mlx.h)
LIBFT_H		=	$(addprefix $(LIBFT_DIR)includes/, libft.h)
IFLAGS		=	-I $(INCS) -I $(MLX_DIR) -I $(LIBFT_DIR)includes/

SRC_DIR		=	src/
OBJ_DIR		=	obj/
MLX_DIR		=	minilibx-linux/
LIBFT_DIR	=	src/libft/


# Sources & Objects #

SRC			=	color		\
				events		\
				fractol		\
				init		\
				msgs		\
				parse_args	\
				render		\
				utils

CLR_SRC		=	color_interpolated	\
				color_special		\
				color_striped
				
FRCT_SRC	=	burning_ship	\
				julia			\
				mandelbox		\
				mandelbrot		\
				tricorn

SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))						\
				$(addprefix $(SRC_DIR)color_schemes/, $(addsuffix .c, $(CLR_SRC)))		\
				$(addprefix $(SRC_DIR)fractal_sets/, $(addsuffix .c, $(FRCT_SRC)))

OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


# Rules #

.DEFAULT_GOAL	:=	all

all				:	force $(NAME)

$(NAME)			:	$(OBJS)
				@echo "Compiling fractol"
				@$(CC) $(OBJS) $(LFLAGS) -o $@
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADERS) $(MLX_H) Makefile | $(OBJ_DIR)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

force			:
				@if [ ! -f "src/libft/libft.a" ]; then	\
					echo "Making libft.a";				\
					make -sC src/libft;					\
				fi
				@if [ ! -f "minilibx-linux/libmlx.a" ]; then	\
					echo "Making libmlx.a";						\
					make -sC minilibx-linux;					\
					echo "Done !";								\
				fi

clean			:
				@if [ -d "$(OBJ_DIR)" ]; then				\
					echo "Cleaning fractol obj directory";	\
					rm -rf $(OBJ_DIR);						\
				fi
				@make -sC src/libft clean
				@make -sC minilibx-linux clean

fclean			:	clean
				@if [ -f "fractol" ]; then				\
					echo "Cleaning program: fractol";	\
					rm -f $(NAME);						\
				fi
				@make -sC src/libft fclean


re				:	fclean all


.PHONY			:	all re clean fclean force
