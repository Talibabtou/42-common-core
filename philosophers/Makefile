# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 14:09:05 by gdumas            #+#    #+#              #
#    Updated: 2024/02/20 15:28:01 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME		=	philo
CC			=	gcc
FLAGS		=	-Werror -Wall -Wextra $(IFLAGS)
IFLAGS		=	-I $(INCS) -pthread

INCS		=	includes/
HEADER		=	$(addprefix $(INCS), philo.h)


# Sources & Objects #

SRC_DIR		=	src/
OBJ_DIR		=	obj/

SRC		=	main			\
			activity		\
			threads			\
			parse_init		\
			utils_philo		\
			utils_lib

SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


# Rules #

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				@echo "Compiling philosopher"
				@$(CC) $(OBJS) $(FLAGS) -o $@
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
				@echo "Compiling $<"
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

clean			:
				@if [ -d "$(OBJ_DIR)" ]; then					\
					echo "Cleaning philosopher: obj/";	\
					rm -rf $(OBJ_DIR);							\
				fi

fclean			:	clean
				@if [ -f "$(NAME)" ]; then				\
					echo "Cleaning program: $(NAME)";	\
					rm -f $(NAME);						\
				fi

re				:	fclean all

.PHONY			:	all re clean fclean