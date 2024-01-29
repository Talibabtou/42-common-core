# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 11:03:59 by gdumas            #+#    #+#              #
#    Updated: 2024/01/23 14:18:58 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME	= pipex
CC		= gcc
FLAGS	= -Werror -Wall -Wextra -MD
RM		= rm -rf

INCS	= -I includes/
SRC_DIR	= src/
LIB_DIR	= src/libft/
OBJ_DIR	= obj/


# Sources & Objects #

SRCS			=	$(wildcard $(SRC_DIR)*.c)
LIB_SRCS		=	$(wildcard $(LIB_DIR)*.c)

OBJS			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
LIB_OBJS		=	$(patsubst $(LIB_DIR)%.c,$(OBJ_DIR)%.o,$(LIB_SRCS))
DEPS			=	$(patsubst %.o,%.d,$(OBJS))
DEPS			+=	$(patsubst %.o,%.d,$(LIB_OBJS))

# Commands #

all: $(NAME)

$(NAME):		$(OBJS) $(LIB_OBJS)
			$(CC) $(FLAGS) $(OBJS) $(LIB_OBJS) -o $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR)%.o:	$(LIB_DIR)%.c | $(OBJ_DIR)
			$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
			rm -rf $(OBJ_DIR)

fclean: 		clean
			rm -f $(NAME)

re: 			fclean all

.PHONY:		all clean fclean re

-include $(DEPS)