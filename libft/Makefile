# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:27:07 by gdumas            #+#    #+#              #
#    Updated: 2024/01/31 16:54:01 by gdumas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Aliases #

NAME	=	libft.a
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -I $(INCS)
SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCS	=	includes/
HEADER	=	$(addprefix $(INCS), libft.h)

AR		=	ar rcs


# Sources & Objects #

LST_SRC =	ft_lstadd_back	\
			ft_lstadd_front	\
			ft_lstclear		\
			ft_lstdelone	\
			ft_lstiter		\
			ft_lstlast		\
			ft_lstmap		\
			ft_lstnew		\
			ft_lstsize

MEM_SRC =	ft_calloc	\
			ft_memchr	\
			ft_memcmp	\
			ft_memcpy	\
			ft_memmove	\
			ft_memset

NB_SRC =	ft_atoi		\
			ft_bzero	\
			ft_isalnum	\
			ft_isalpha	\
			ft_isascii	\
			ft_isdigit	\
			ft_isprint	\
			ft_itoa

PRT_SRC =	ft_printf_char	\
			ft_printf_hex	\
			ft_printf_nbr	\
			ft_printf_ptr	\
			ft_printf

PUT_SRC =	ft_putchar_fd	\
			ft_putendl_fd	\
			ft_putnbr_fd	\
			ft_putstr_fd

STR_SRC =	ft_split	\
			ft_strchr	\
			ft_strdup	\
			ft_strjoin	\
			ft_strlcat	\
			ft_strlcpy	\
			ft_strlen	\
			ft_strmapi	\
			ft_strncmp	\
			ft_strnstr	\
			ft_strrchr	\
			ft_strtrim	\
			ft_substr	\
			ft_tolower	\
			ft_toupper

GNL_SRC =	get_next_line	

SRCS	=	$(addprefix $(SRC_DIR)ft_lst/, $(addsuffix .c, $(LST_SRC)))		\
			$(addprefix $(SRC_DIR)ft_mem/, $(addsuffix .c, $(MEM_SRC)))		\
			$(addprefix $(SRC_DIR)ft_nb/, $(addsuffix .c, $(NB_SRC)))		\
			$(addprefix $(SRC_DIR)ft_printf/, $(addsuffix .c, $(PRT_SRC)))	\
			$(addprefix $(SRC_DIR)ft_put/, $(addsuffix .c, $(PUT_SRC)))		\
			$(addprefix $(SRC_DIR)ft_str/, $(addsuffix .c, $(STR_SRC)))		\
			$(addprefix $(SRC_DIR)gnl/, $(addsuffix .c, $(GNL_SRC)))

OBJS	=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))


# Rules #

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				@echo "Creating libft.a"
				@$(AR) $(NAME) $^
				@echo "Done !"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER)| $(OBJ_DIR)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)

clean			:
				@if [ -d "$(OBJ_DIR)" ]; then			\
					echo "Cleaning obj directory";	\
					rm -rf $(OBJ_DIR);					\
				fi

fclean			:	clean
				@if [ -f "libft.a" ]; then				\
					echo "Cleaning libft.a";		\
					rm -f $(NAME);						\
				fi

	
re				:	fclean all


.PHONY			:	all clean fclean re