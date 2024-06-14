/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:40:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:30:11 by stouitou         ###   ########.fr       */
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
	dup = NULL;
}

void	expand_heredoc(t_entry *entry, char *str, char **env, int fd)
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
