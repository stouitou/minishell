NAME = minishell

SRC_DIR = src
PRINT_DIR = print
PRINT_SRC =	print_tab.c \
			print_env.c \
			print_full_command.c \
			print_token.c \
			print_block.c \
			print_exe.c \
			print_utils.c
PRINT = ${addprefix ${PRINT_DIR}/, ${PRINT_SRC}}

TESTER_DIR = tester
TESTER_SRC =	log_tests.c \
				log_status.c
TESTER = ${addprefix ${TESTER_DIR}/, ${TESTER_SRC}}

UTILS_DIR = utils
UTILS_SRC =	skip_whitespace.c \
			remove_null.c \
			remove_operator.c \
			close_both_fd.c \
			close_all_fd.c \
			remove_node.c \
			upd_token_heads_and_indexes.c \
			upd_env.c \
			free_4_str.c
UTILS = ${addprefix ${UTILS_DIR}/, ${UTILS_SRC}}

FREE_DIR = free
FREE_SRC =	free_token_and_exit.c \
			free_token_before_return.c \
			free_exe.c \
			free_cmd.c \
			free_subshell_and_exit.c \
			exit_builtin.c
FREE = ${addprefix ${FREE_DIR}/, ${FREE_SRC}}

INIT_DIR = init
INIT_SRC =	init_exe.c \
			init_pipe.c \
			init_fork.c \
			init_dup.c \
			init_error.c \
			init_pipe_fd_and_block.c
INIT = ${addprefix ${INIT_DIR}/, ${INIT_SRC}}

LIST_DIR = list
LIST_SRC =	token_new.c \
			token_addback.c \
			token_clear.c \
			del_node.c \
			files_new.c \
			files_addback.c \
			files_clear.c \
			env_new.c \
			env_addback.c \
			env_size.c \
			env_clear.c
LIST = ${addprefix ${LIST_DIR}/, ${LIST_SRC}}

BUILTIN_DIR = builtin
BUILTIN_SRC =	is_builtin.c \
				handle_builtin.c \
				handle_exit_in_parent.c \
				handle_export_in_parent.c \
				handle_unset_in_parent.c \
				export_only.c \
				export_variable.c \
				syntax_error_in_export.c \
				utils_for_export.c \
				handle_echo.c \
				handle_exit.c \
				get_exit_status.c \
				handle_unset.c \
				get_files_fd_for_builtin.c \
				handle_env.c \
				handle_export.c
BUILTIN = ${addprefix ${BUILTIN_DIR}/, ${BUILTIN_SRC}}

SRC =	minishell.c \
		stash_str.c \
		handle_metachars.c \
		handle_non_metachars.c \
		analyze_syntax.c \
		expand_token.c \
		handle_expansions.c \
		partition_content.c \
		handle_status.c \
		classify_tokens.c \
		go_heredoc.c \
		gather_indexes.c \
		exec_token.c \
		set_env.c \
		find_files.c \
		exec_subshell.c \
		get_files_fd.c \
		find_cmd.c \
		check_path.c \
		execute_command.c \
		${BUILTIN} \
		${LIST} \
		${INIT} \
		${FREE} \
		${UTILS} \
		${PRINT} \
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
