/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:16:07 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 16:13:41 by stouitou         ###   ########.fr       */
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
	if (!token ->content[i + 1])
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

void	handle_expansions(t_entry *entry, char **env)
{
	t_token	*cur;
	t_token	*next;
	t_token	*prev;

	if (!entry->token)
		return ;
	cur = entry->token;
	while (cur)
	{
		prev = cur->prev;
		next = cur->next;
		if (cur->type == WORD && cur->quotes != SIMPLE
			&& (!prev || ft_strcmp(prev->content, "<<") != 0))
			expand_token(entry, cur, env);
		if (!cur->quotes
			&& cur->content && !cur->content[0]
			&& (!prev || (prev && prev->index != cur->index))
			&& (!next || (next && next->index != cur->index)))
			cur->content = NULL;
		cur = next;
	}
}
