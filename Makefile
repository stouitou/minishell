NAME = minishell

SRC_DIR = src
PRINT_DIR = print
PRINT_SRC =	print_env.c \
			print_full_command.c \
			print_utils.c \
			print_token.c \
			print_block.c \
			print_exe.c
PRINT = ${addprefix ${PRINT_DIR}/, ${PRINT_SRC}}

TESTER_DIR = tester
TESTER_SRC =	log_tests.c \
				log_status.c
TESTER = ${addprefix ${TESTER_DIR}/, ${TESTER_SRC}}

LIST_DIR = list
LIST_SRC =	token_new.c \
			token_addback.c \
			token_clear.c \
			del_node.c
LIST = ${addprefix ${LIST_DIR}/, ${LIST_SRC}}

INIT_DIR = init
INIT_SRC =	init_exe.c \
			init_pipe.c \
			init_fork.c \
			init_dup.c \
			init_error.c
INIT = ${addprefix ${INIT_DIR}/, ${INIT_SRC}}

UTILS_DIR = utils
UTILS_SRC =	close_both_fd.c \
			close_all_fd.c \
			remove_node.c \
			upd_token_heads_and_indexes.c
UTILS = ${addprefix ${UTILS_DIR}/, ${UTILS_SRC}}

FREE_DIR = free
FREE_SRC =	free_token_and_exit.c \
			free_token_before_return.c \
			free_exe.c \
			free_cmd.c \
			free_subshell_and_exit.c
FREE = ${addprefix ${FREE_DIR}/, ${FREE_SRC}}

SRC =	minishell.c \
		stash_ent.c \
		handle_non_metachars.c \
		handle_metachars.c \
		analyze_syntax.c \
		handle_expansions.c \
		expand_token.c \
		gather_indexes.c \
		exec_token.c \
		exec_subshell.c \
		find_cmd.c \
		${PRINT} \
		${LIST} \
		${INIT} \
		${UTILS} \
		${FREE} \
		${TESTER}

OBJ_DIR = obj
OBJ = ${addprefix ${OBJ_DIR}/, ${SRC:.c=.o}}

HDR_DIR = hdr
HDR = minishell.h
INCLUDE = ${addprefix ${HDR_DIR}/, ${HDR}}

LIBFT_PATH = ./Libft
LIBFT_NAME = libft.a

RDLINE_PATH = /usr/local/lib

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror -I${HDR_DIR} -I/usr/local/include



all: ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE}
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ} ${LIBFT_PATH}/${LIBFT_NAME}
	${CC} ${CFLAGS} ${OBJ} -L${LIBFT_PATH} -lft -L${RDLINE_PATH} -lreadline -o $@

${LIBFT_PATH}/${LIBFT_NAME}:
	make -C ${LIBFT_PATH}

clean:
	rm -rf ${OBJ_DIR}
	make clean -C ${LIBFT_PATH}

fclean: clean
	rm -f ${NAME}
	rm -f ${LIBFT_PATH}/${LIBFT_NAME}

re: fclean all

.PHONY: all clean fclean re
