# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:27:07 by gdumas            #+#    #+#              #
#    Updated: 2023/11/24 15:35:55 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#General

NAME			=	libftprintf.a
INCLUDES		=	include
LIBFT_SRC_DIR	=	src/libft/
PRINTF_SRC_DIR	=	src/printf/
OBJ_DIR			=	obj/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDES)

RM			=	rm
AR			=	ar rcs


#Sources

PRINTF_SRC_FILES	=	ft_printf	ft_printf_char	ft_printf_ptr	ft_printf_nbr	ft_printf_hex
LIBFT_SRC_FILES		=	ft_itoa		ft_putchar_fd

LIBFT_SRC	=	$(addprefix $(LIBFT_SRC_DIR), $(addsuffix .c, $(LIBFT_SRC_FILES)))
PRINTF_SRC	=	$(addprefix $(PRINTF_SRC_DIR), $(addsuffix .c, $(PRINTF_SRC_FILES)))
LIBFT_OBJ	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(LIBFT_SRC_FILES)))
PRINTF_OBJ	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(PRINTF_SRC_FILES)))


#Commands

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(LIBFT_OBJ) $(PRINTF_OBJ)
				$(AR) $(NAME) $(LIBFT_OBJ) $(PRINTF_OBJ)

$(OBJ_DIR)%.o: $(LIBFT_SRC_DIR)%.c | $(OBJF)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PRINTF_SRC_DIR)%.c | $(OBJF)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
				@mkdir -p $(OBJ_DIR)

clean:
				$(RM) -rf $(OBJ_DIR)

fclean:		clean
				$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re