###################			MON MAIN TESTEUR			################### 

# NAME	= ft_containers

# SRC_DIR = srcs/
# OBJ_DIR = obj/

# SRCS	= ${addprefix ${SRC_DIR}, ${SRC}}
# SRC		=	main.cpp \
	
# OBJS	=	${patsubst ${SRC_DIR}%.cpp,${OBJ_DIR}%.o,${SRCS}}
# CC		= clang++
# CFLAGS	= -Wall -Wextra -Werror -std=c++98
# LIB		= 
# RM		= rm -rf

# all: $(NAME)

# ${OBJ_DIR}%.o :	${SRC_DIR}%.cpp
# 			@mkdir -p ${OBJ_DIR}
# 			@${CC} ${CFLAGS} -c $< -o $@
# 			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"
# $(NAME): $(OBJS)
# 		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

# clean:
# 		$(RM) $(OBJS)

# fclean: clean
# 		$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

###################			MAIN TESTEUR AUTRE			################### 

TARGET=main
FLAGS=-Wall -Werror -Wextra -g3  -std=c++98 -fsanitize=address
SRC=${wildcard ./tests/*.cpp}
OBJ=${SRC:%.cpp=%.o}

all: ${TARGET}

./tests/%.o: ./tests/%.cpp
	clang++ ${FLAGS} -c $< -o $@

${TARGET}: ${OBJ}
	clang++ ${FLAGS} ${OBJ} -o ${TARGET}

vector: ${TARGET}
	./${TARGET} vector

map: ${TARGET}
	./${TARGET} map

stack: ${TARGET}
	./${TARGET} stack

enable_if: ${TARGET}
	./${TARGET} enable_if

equal: ${TARGET}
	./${TARGET} equal

lexicographical_compare: ${TARGET}
	./${TARGET} lexicographical_compare

clean:
	rm -rf *.dSYM

fclean: clean
	rm -rf ${OBJ}
	rm -rf ${TARGET} ${TARGET}_test

re: fclean all

.PHONY: all ${TARGET} test