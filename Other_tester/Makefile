#USE = make -> ./main all        or ./main $NAMEOFCONTAINER

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