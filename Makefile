NAME	= ft_containers

SRC_DIR = srcs/
OBJ_DIR = obj/

SRCS	= ${addprefix ${SRC_DIR}, ${SRC}}
SRC		=	main.cpp \
	
OBJS	=	${patsubst ${SRC_DIR}%.cpp,${OBJ_DIR}%.o,${SRCS}}
# OBJS	= $(SRCS:.cpp=.o)
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
LIB		= 
RM		= rm -rf

all: $(NAME)

${OBJ_DIR}%.o :	${SRC_DIR}%.cpp
			@mkdir -p ${OBJ_DIR}
			@${CC} ${CFLAGS} -c $< -o $@
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"
$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re