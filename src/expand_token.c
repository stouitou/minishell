/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:37:11 by stouitou         ###   ########.fr       */
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
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
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

static char	*protected_strjoin(char *str1, char *str2, char *str3, t_entry *entry)
{
	char	*join;
	
	join = ft_strjoin(str1, str2);
	if (!join)
	{
		free_4_str(str1, str2, str3, NULL);
		free_token_and_exit(entry, ERR_MALLOC, "expansion", EXIT_FAILURE);
	}
	return (join);
}

static char	*partition_content(t_entry *entry, char *content, int i)
{
	char	*start;
	char	*expand;
	char	*tmp;
	char	*end;
	char	*new;

	// start = ft_strndup(content, i);
	start = ft_strndup(content, i);
	if (!start && errno == ENOMEM)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	// if (!start && i)
	// 	free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	expand = extract_expand(entry, content + i, &i);
	end = ft_strdup(content + i);
	if (!end)
	{
		free(start);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = protected_strjoin(start, expand, end, entry);
	free_4_str(start, expand, NULL, NULL);
	new = protected_strjoin(tmp, end, NULL, entry);
	free_4_str(tmp, end, NULL, NULL);
	return (new);
}

// static char	*partition_content(t_entry *entry, char *content, int i)
// {
// 	char	*start;
// 	char	*expand;
// 	char	*tmp;
// 	char	*end;
// 	char	*new;

// 	start = ft_strndup(content, i);
// 	if (!start && errno == ENOMEM)
// 		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
// 	// if (!start && i)
// 	// 	free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
// 	expand = extract_expand(entry, content + i, &i);
// 	end = ft_strdup(content + i);
// 	if (!end)
// 	{
// 		free(start);
// 		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
// 	}
// 	tmp = ft_strjoin(start, expand);
// 	if (!tmp)
// 	{
// 		free_4_str(start, expand, end, NULL);
// 		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
// 	}
// 	free_4_str(start, expand, NULL, NULL);
// 	new = ft_strjoin(tmp, end);
// 	if (!new)
// 	{
// 		free_4_str(tmp, end, NULL, NULL);
// 		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
// 	}
// 	free_4_str(tmp, end, NULL, NULL);
// 	return (new);
// }

static char	*handle_status(t_entry *entry, char *content, int i)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && i)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	expand = ft_itoa(entry->prev_status);
	if (!expand)
	{
		free(start);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	end = ft_strdup(content + i + 2);
	if (!end)
	{
		free(start);
		free(expand);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = ft_strjoin(start, expand);
	if (!tmp)
	{
		free(start);
		free(expand);
		free(end);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	free(start);
	free(expand);
	new = ft_strjoin(tmp, end);
	if (!new)
	{
		free(tmp);
		free(end);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	free(tmp);
	free(end);
	return (new);
}

static void	handle_dollar(t_token *token, int i)
{
	if (!token->content[i + 1])
	{
		if (token->quotes == UNQUOTED
			&& ((token->next && token->next->index == token->index)))
			token->content = NULL;
	}
}

void	expand_token(t_entry *entry, t_token *token, char **env)
{
	int		i;

	if (!*env || !token->content || !ft_strchr(token->content, '$'))
		return ;
	i = 0;
	while (token->content && token->content[i])
	{
		if (token->content[i] == '$')
		{
			if (token->content[i + 1] == '?')
			{
				token->content = handle_status(entry, token->content, i);
				expand_token(entry, token, env);
			}
			else if (!token->content[i + 1]
				|| !(ft_isalpha(token->content[i + 1])
				|| token->content[i + 1] == '_'))
				handle_dollar(token, i);
			else
			{
				token->content = partition_content(entry, token->content, i);
				if (token->content == NULL)
					return ;
				expand_token(entry, token, env);
			}
		}
		i++;
	}
}
