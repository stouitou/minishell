/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:51 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:31:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	dup = ft_strndup(str + 1, i - 1);
	if (!dup)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	var = getenv(dup);
	if (var)
		ft_fprintf(fd, var);
	else
		ft_fprintf(fd, "");
	free(dup);
}

static void	expand_heredoc(t_entry *entry, char *str, char **env, int fd)
{
	int		i;
	int		stop;

	if (!*env || !str || !ft_strchr(str, '$'))
		return ;
	i = 0;
	stop = 0;
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
		str = readline(H_PROMPT);
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
