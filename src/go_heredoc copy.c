/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:51 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/07 16:34:55 by stouitou         ###   ########.fr       */
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

static void	handle_signal_in_hd(int sgn)
{
	char	c;

	c = EOF;
	if (sgn == SIGINT)
	{
		// ft_printf("hd");
		rl_replace_line(&c, 0);
		ft_printf("\n");
		sig_stat = 2;
	}
}

void	go_heredoc(t_entry *entry, t_token *cur)
{
	int		fd;
	char	*str;
	char	*infile;

	fd = open(H_FILE, O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (fd == -1)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	entry->heredoc = true;
	while (1)
	{
		entry->sign.sa_handler = handle_signal_in_hd;
		sigaction(SIGINT, &(entry->sign), NULL);
		str = readline(H_PROMPT);
		ft_printf("here in go heredoc\n");
		if (str == NULL)
		{
			ft_printf("warning: here-document delimited by end-of-file (wanted `%s')\n", cur->content);
			break ;
		}
		if (sig_stat == 2)
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
	}
	infile = ft_strdup(H_FILE);
	if (!infile)
		free_token_and_exit(entry, strerror(errno), cur->content, 1);
	close(fd);
	free(cur->content);
	cur->content = infile;
}
