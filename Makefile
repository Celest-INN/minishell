NAME= minishell_test

SRC_DIR= src/
OBJ_DIR= obj/
INC= include/

LIBFT_DIR= libft/
LIBFT= $(LIBFT_DIR)libft.a

SRC= tester_ec.c lexer.c lexer_helper.c \
	 init_env.c parser.c parser_helper.c syntax_check.c \
	 expander.c rm_char.c expander_helper_var.c \
	 trimmer.c helper_itoa.c helper_free.c

OBJ= ${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

UNAME= $(shell uname)
ifeq ($(UNAME), Darwin)
	RL_INC= -I/usr/local/opt/readline/include
	RL_LIB= -L/usr/local/opt/readline/lib -lreadline
else
	RL_INC=
	RL_LIB= -lreadline
endif

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	@printf "\033[0;32mCompiling %s\033[0m\n" "$@"
	@cc -Wall -Wextra -g -O0 -I${INC} -o $@ ${OBJ} ${LIBFT} ${RL_LIB}

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: ${SRC_DIR}%.c | ${OBJ_DIR}
	@printf "\033[0;32mCompiling %s\033[0m\n" "$@"
	@cc -Wall -Wextra -g -O0 -I${INC} -I${LIBFT_DIR} ${RL_INC} -c $< -o $@

clean:
	make -C ${LIBFT_DIR} clean
	rm -f ${OBJ}

fclean: clean
	make -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re