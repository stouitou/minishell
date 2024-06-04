/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:07:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/04 15:35:14 by poriou           ###   ########.fr       */
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

static char	*extract_expand(t_entry *entry, char *str, int *index)
{
	int		i;
	char	*dup;
	char	*var;
	char	*empty;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*index += i;
	dup = ft_strndup(str + 1, i - 1);
	if (!dup)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	var = get_value(entry->env, dup);
	if (var)
	{
		free(dup);
		return (var);
	}
	free(dup);
	empty = ft_strdup("");
	if (!empty)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	return (empty);
}

static char	*protected_strjoin(char *s1, char *s2, char *s3, t_entry *entry)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
	{
		free_4_str(s1, s2, s3, NULL);
		free_token_and_exit(entry, ERR_MALLOC, "expansion", EXIT_FAILURE);
	}
	return (join);
}

char	*partition_content(t_entry *entry, char *content, int i)
{
	char	*start;
	char	*expand;
	char	*tmp;
	char	*end;
	char	*new;

	start = ft_strndup(content, i);
	if (!start && errno == ENOMEM)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	expand = extract_expand(entry, content + i, &i);
	end = ft_strdup(content + i);
	if (!end)
	{
		free(start);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = protected_strjoin(start, expand, end, entry);
	free(start);
	new = protected_strjoin(tmp, end, NULL, entry);
	free_4_str(tmp, end, NULL, NULL);
	return (new);
}
