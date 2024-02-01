# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 11:03:59 by gdumas            #+#    #+#              #
#    Updated: 2024/02/01 10:38:11 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME	=	pipex
CC		=	gcc
FLAGS	=	-Werror -Wall -Wextra -I $(INCS)
LFLAGS	=	-L src/libft -lft

INCS	=	includes/
HEADER	=	$(addprefix $(INCS), pipex.h)
SRC_DIR	=	src/
OBJ_DIR	=	obj/


# Sources & Objects #

SRC				=	pipex		\
					utils

SRCS			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJS			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))


# Rules #

.DEFAULT_GOAL	:=	all

all				:	force $(NAME)

$(NAME)			:	$(OBJS) src/libft/libft.a
				@echo "Creating program: pipex"
				@$(CC) $(FLAGS) $(OBJS) $(LFLAGS) -o $@
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) $(FLAGS) -c $< -o $@

force			:
				@make -sC src/libft

clean			:
				@if [ -d "$(OBJ_DIR)" ]; then		\
					echo "Cleaning pipex obj directory";	\
					rm -rf $(OBJ_DIR);				\
				fi
				@make -sC src/libft clean

fclean			:	clean
				@if [ -f "pipex" ]; then	\
					echo "Cleaning program: pipex";	\
					rm -f $(NAME);			\
				fi
				@make -sC src/libft fclean

re				:	fclean all


.PHONY			:	all clean fclean re force
