/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:51 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/10 16:58:03 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(char **env, char *key)
{
	int		i;
	int		key_len;

	if (!env)
		return (NULL);
	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

static void	extract_expand(t_entry *entry, char *str, int *index, int fd)
{
	int		i;
	char	*dup;
	char	*var;

	i = 1;
	if (str[i] == '?')
	{
		ft_fprintf(fd, "%d", entry->prev_status);
		*index += 2;
		return ;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	dup = ft_strndup(str + 1, i - 1);
	if (!dup)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	var = get_value(entry->env, dup);
	if (var)
		ft_fprintf(fd, var);
	else
		ft_fprintf(fd, "");
	free(dup);
}

static void	expand_heredoc(t_entry *entry, char *str, char **env, int fd)
{
	int		i;

	if (!*env || !str || !ft_strchr(str, '$'))
		return ;
	i = 0;
	while (str[i] && str[i] != '$')
	{
		write(fd, &str[i], 1);
		i++;
	}
	if (str[i] == '$')
	{
		if (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')
		{
			extract_expand(entry, str, &i, fd);
			expand_heredoc(entry, str + i, env, fd);
		}
	}
}

// static void handle_signal_in_hd(int sgn) {
//     if (sgn == SIGINT) {
//         // Clear the line and redisplay the prompt
//         printf("\n");
//         fflush(stdout);
// 		sig_stat = 2;
//     }
// }

// #define MAX_LINE_LENGTH 1024

// // Global variable to indicate if SIGINT was received
// volatile sig_atomic_t sigint_received = 0;

// void sigint_handler(int sig) {
//     sigint_received = 1;
// }
// char* custom_readline(const char* prompt) {
//     struct termios old_termios, new_termios;
//     char* buffer = malloc(MAX_LINE_LENGTH);
//     int i = 0;

//     if (!buffer) {
//         perror("Memory allocation error");
//         exit(EXIT_FAILURE);
//     }

//     // Save the current terminal settings
//     tcgetattr(STDIN_FILENO, &old_termios);
//     new_termios = old_termios;

//     // Disable canonical mode, enable echo, and disable signal generation
//     new_termios.c_lflag &= ~(ICANON | ECHO | ISIG);

//     // Apply the new terminal settings
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

//     // Set up SIGINT handler
//     signal(SIGINT, handle_signal_in_hd);

//     // Print the prompt
//     printf("%s", prompt);
//     fflush(stdout);

//     // Read characters until a newline or EOF is encountered
//     while (1) {
//         char c;
//         ssize_t result;
//         do {
//             result = read(STDIN_FILENO, &c, 1);
//         } while (result == -1 && errno == EINTR);

//         if (result < 0) {
//             perror("Error reading input");
//             free(buffer);
//             exit(EXIT_FAILURE);
//         }

//         if (c == '\n' || c == EOF || sig_stat == 2) {
//             buffer[i] = '\0';
//             break;
//         }

//         // Echo the character back to the terminal
//         printf("%c", c);
//         fflush(stdout);

//         buffer[i++] = c;

//         if (i >= MAX_LINE_LENGTH - 1) {
//             // Resize buffer if needed
//             char* temp = realloc(buffer, MAX_LINE_LENGTH * 2);
//             if (!temp) {
//                 perror("Memory allocation error");
//                 free(buffer);
//                 exit(EXIT_FAILURE);
//             }
//             buffer = temp;
//         }
//     }

//     // Restore the original terminal settings
//     tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

//     return buffer;
// }

static void	handle_signal_in_hd(int sgn)
{
	int pipefd[2];
	char	c;

	pipe(pipefd);
	c = '\n';
	if (sgn == SIGINT)
	{
		write(1, &c, 1);
		pid_t pid = fork();
		if (pid == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);  // Make read end of pipe be standard input
			write(pipefd[1], &c, 1);  // Write newline to pipe
			close(pipefd[1]);  // Close write end of pipe
			close(pipefd[0]);  // Close write end of pipe
			exit(0);
		}
		else
		{
			dup2(pipefd[0], STDIN_FILENO);  // Make read end of pipe be standard input
			close(pipefd[0]);  // Close read end of pipe
			close(pipefd[1]);  // Close write end of pipe
			wait(&pid);
		}
		sig_stat = 130;
	}
}

static char	*custom_readline(char *prompt)
{
	char	*ret;
	char	c[1];
	int		i;

	ret = (char *)malloc(sizeof(char) * 1);
	if (!ret)
		return (NULL);
	i = 0;
	ft_printf("%s", prompt);
	while (1)
	{
		read(STDIN_FILENO, c, 1);
		if (c[0] == '\n')
		{
			ret[i] = '\0';
			return (ret);
		}	
		ret = (char *)ft_realloc(ret, i + 2);
		if (!ret)
			return (NULL);
		ret[i] = c[0];
		i++;
	}
	return (NULL);
}

void	go_heredoc(t_entry *entry, t_token *cur)
{
	int		fd;
	char	*str;
	char	*infile;
	int		origin_fd0;
	int		origin_fd1;

	sig_stat = 0;
	fd = open(H_FILE, O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (fd == -1)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	entry->heredoc = true;
	while (1)
	{
		origin_fd0 = dup(STDIN_FILENO);
		origin_fd1 = dup(STDOUT_FILENO);
		entry->sign.sa_handler = handle_signal_in_hd;
		sigaction(SIGINT, &(entry->sign), NULL);
		str = custom_readline(H_PROMPT);
		dup2(origin_fd0, STDIN_FILENO);
		close(origin_fd0);
		dup2(origin_fd1, STDOUT_FILENO);
		close(origin_fd1);
		if (str == NULL)
		{
			ft_printf("warning: here-document delimited by end-of-file (wanted `%s')\n", cur->content);
			break ;
		}
		if (sig_stat == 130)
		{
			close(fd);
			token_clear(&(entry->token));
			return ;
		}
		if (ft_strcmp(str, cur->content) == 0)
			break ;
		if (!cur->quotes && ft_strchr(str, '$'))
			expand_heredoc(entry, str, entry->env, fd);
		else
			write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	infile = ft_strdup(H_FILE);
	if (!infile)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	close(fd);
	free(cur->content);
	cur->content = infile;
	entry->sign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &(entry->sign), NULL);
}
