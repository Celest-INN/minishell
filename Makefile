NAME= minishell

CFLAGS = -Wall -Wextra -Werror

SRC_DIR= src/
OBJ_DIR= obj/
INC= include/

LIBFT_DIR= libft/
LIBFT= $(LIBFT_DIR)libft.a

SRC= main.c lexer.c lexer_helper.c \
	init_env.c parser.c parser_helper.c syntax_check.c \
	expander.c rm_char.c expander_helper_var.c \
	trimmer.c helper_itoa.c helper_free.c \
	exec_utils.c exec_built_in.c  exec_path.c \
	exec.c get_heredoc.c builtin_exit.c  exec_check.c free.c heredoc.c \
	builtin_echo.c builtin_unset.c builtin_env.c  env_utils_bt.c \
    env_utils.c builtin_export.c builtin_pwd.c builtin_cd.c export_utils.c \
	file_error.c heredoc_utils.c \


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
	cc $(CFLAGS) -g -O0 -I${INC} -o $@ ${OBJ} -L. -l:${LIBFT} ${RL_LIB}

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: ${SRC_DIR}%.c | ${OBJ_DIR}
	cc $(CFLAGS) -g -O0 -I${INC} -I${LIBFT_DIR} ${RL_INC} -c $< -o $@

clean:
	make -C ${LIBFT_DIR} clean
	rm -f ${OBJ}

fclean: clean
	make -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
