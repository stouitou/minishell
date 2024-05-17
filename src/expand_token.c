/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 13:19:00 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_expand(t_entry *entry, char *str, int *index)
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
		free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
	var = getenv(dup);
	if (var)
	{
		free(dup);
		return (var);
	}
	free(dup);
	empty = ft_strdup("");
	if (!empty)
		free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
	return (empty);
}

static char	*partition_content(t_entry *entry, char *content, int i)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && i)
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	expand = extract_expand(entry, content + i, &i);
	end = ft_strdup(content + i);
	if (!end)
	{
		free(start);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = ft_strjoin(start, expand);
	if (!tmp)
	{
		free(start);
		free(end);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	free(start);
	new = ft_strjoin(tmp, end);
	if (!new)
	{
		free(end);
		free(tmp);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	free(tmp);
	free(end);
	return (new);
}

static char	*handle_status(t_entry *entry, char *content, int i)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && i)
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	expand = ft_itoa(entry->prev_status);
	if (!expand)
	{
		free(start);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	end = ft_strdup(content + i + 2);
	if (!end)
	{
		free(start);
		free(expand);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = ft_strjoin(start, expand);
	if (!tmp)
	{
		free(start);
		free(expand);
		free(end);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	free(start);
	free(expand);
	new = ft_strjoin(tmp, end);
	if (!new)
	{
		free(tmp);
		free(end);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
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

// void	expand_token(t_entry *entry, t_token *token, char *content, char **env)
// {
// 	int		i;

// 	if (!*env || !content || !ft_strchr(content, '$'))
// 		return ;
// 	i = 0;
// 	while (content && content[i])
// 	{
// 		if (content[i] == '$')
// 		{
// 			if (content[i + 1] == '?')
// 			{
// 				free(token->content);
// 				token->content = handle_status(entry, content, i);
// 				expand_token(entry, token, content, env);
// 			}
// 			else if (!content[i + 1]
// 				|| !(ft_isalpha(content[i + 1])
// 				|| content[i + 1] == '_'))
// 				handle_dollar(token, i);
// 			else
// 			{
// 				free(token->content);
// 				token->content = partition_content(entry, content, i);
// 				if (content == NULL)
// 					return ;
// 				expand_token(entry, token, content, env);
// 			}
// 		}
// 		i++;
// 	}
// }

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
