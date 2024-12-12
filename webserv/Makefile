## Variables
NAME			=	webserv
CPP				=	c++
CPPFLAGS		=	-Wall -Wextra -Werror -std=c++98 -I${INCLUDES}
DEBUG_FLAGS		=	-DDEBUG_MODE
VALGRIND_FLAGS	=	valgrind -q --tool=none --track-fds=yes
INCLUDES		=	inc/
SRC_DIR			=	src/
OBJ_DIR			=	.obj/
RM				=	rm -rf
MKDIR			=	mkdir -p
SIEGE_CONFIG	=	config/siege.conf
SIEGE_CMD		=	siege -b -t 1M http://localhost:8080

# Source files
SRC_FILES		=	AHttpBuilder	\
					Client			\
					ConfigParser	\
					HttpRequest		\
					HttpResponse	\
					main			\
					Server			\
					utils			\
					Webserv

SRCS			=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_FILES)))
OBJS			=	$(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

# Header files
HEADER_HPP	=	AHttpBuilder	\
					Client			\
					ConfigParser	\
					HttpRequest		\
					HttpResponse	\
					Server			\
					Webserv

HEADER_H		=	define			\
					utils

HEADERS			=	$(addprefix $(INCLUDES), $(addsuffix .hpp, $(HEADER_HPP))) \
					$(addprefix $(INCLUDES), $(addsuffix .h, $(HEADER_H)))

# Rules
.SILENT:

all:	${NAME}

${NAME}: ${OBJS}
	echo "\nCompiling webserv"
	${CPP} ${CPPFLAGS} $^ -o $@
	echo "Done!"

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp ${HEADERS} Makefile | ${OBJ_DIR}
	mkdir -p $(dir $@)
	printf "Generating webserv objects: %-33.33s\r" $@
	${CPP} ${CPPFLAGS} -c $< -o $@

$(OBJ_DIR):
	${MKDIR} ${OBJ_DIR}

clean:
	if [ -d "$(OBJ_DIR)" ]; then \
		echo "Cleaning webserv obj/ directory"; \
		${RM} ${OBJ_DIR}; \
	fi

fclean:	clean
	if [ -f "$(NAME)" ]; then \
		echo "Cleaning $(NAME) program"; \
		${RM} ${NAME}; \
	fi

re:	fclean all

debug: CPPFLAGS += ${DEBUG_FLAGS}
debug: re

valgrind: re
	echo "Running with valgrind..."
	${VALGRIND_FLAGS} ./${NAME}

siege-server: re
	${VALGRIND_FLAGS} ./${NAME} ${SIEGE_CONFIG}

siege-test:
	echo "Starting siege test..."
	${SIEGE_CMD}

# Phony
.PHONY:	all clean fclean re debug valgrind siege-server siege-test
