/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:51 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:30:52 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*read_line(t_entry *entry)
{
	char	*str;
	int		reg_input;
	int		reg_output;

	reg_input = dup(STDIN_FILENO);
	reg_output = dup(STDOUT_FILENO);
	entry->sign.sa_handler = handle_signal_in_heredoc;
	sigaction(SIGINT, &(entry->sign), NULL);
	str = custom_readline(H_PROMPT);
	dup2(reg_input, STDIN_FILENO);
	dup2(reg_output, STDOUT_FILENO);
	close_both_fd(reg_input, reg_output);
	return (str);
}

static void	write_heredoc(t_entry *entry, t_token *cur, int fd)
{
	char	*str;
	char	*error;

	while (1)
	{
		str = read_line(entry);
		if (str == NULL)
		{
			error = "warning: here-document delimited by end-of-file";
			ft_printf("%s (wanted `%s')\n", error, cur->content);
			return ;
		}
		if (g_sig == 130)
			return ;
		if (ft_strcmp(str, cur->content) == 0)
			return ;
		if (!cur->quotes && ft_strchr(str, '$'))
			expand_heredoc(entry, str, entry->env, fd);
		else
			write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = NULL;
	}
}

void	go_heredoc(t_entry *entry, t_token *cur)
{
	int		fd;
	char	*infile;

	g_sig = 0;
	fd = open(H_FILE, O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (fd == -1)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	entry->heredoc = true;
	write_heredoc(entry, cur, fd);
	if (g_sig == 130)
	{
		close(fd);
		unlink(H_FILE);
		token_clear(entry, &(entry->token));
		return ;
	}
	infile = ft_strdup(H_FILE);
	if (!infile)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	close(fd);
	free(cur->content);
	cur->content = NULL;
	cur->content = infile;
	entry->sign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &(entry->sign), NULL);
}
