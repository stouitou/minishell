/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:12:46 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 17:24:46 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char *extract_expand(t_entry *entry, char *str, int *index, int *keep)
// {
// 	int		i;
// 	char	*dup;
// 	char	*var;

// 	i = 1;
// 	while (str[i] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
// 	{
// 		dup = ft_strndup(str + 1, i);
// 		if (!dup)
// 			free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
// 		var = getenv(dup);
// 		if (var)
// 		{
// 			*index += (i + 1);
// 			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
// 			{
// 				free(dup);
// 				return (NULL);
// 			}
// 			free(dup);
// 			return (var);
// 		}
// 		free(dup);
// 		i++;
// 		if (str[i] == '$')
// 		{
// 			ft_printf("here\n");
// 			*keep = 1;
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }

static char *extract_expand(t_entry *entry, char *str, int *index, int *keep)
{
	int		i;
	char	*dup;
	char	*var;
	char	*empty;

	i = 1;
	(void)keep;
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
	// if (str[i])
	// 	*keep = 1;
	empty = ft_strdup("");
	if (!empty)
		free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
	return (empty);
}

static char	*partition_content(t_entry *entry, char *content, int i, int keep)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && i)
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	expand = extract_expand(entry, content + i, &i, &keep);
	// if (!keep)
	// 	return (start);
	end = ft_strdup(content + i);
	if (!end)
	{
		free(start);
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	}
	// if (!start && !expand)
	// 	return (end);
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

static void	handle_dollar(t_token *token)
{
	// char	*content;
	// char	*tmp;

	// ft_printf("i = %d\n", i);
	// ft_printf("content = %s\n", token->content);
	// content = ft_strndup(token->content, i + 1);
	// if (!content)
	// 	free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	// free(token->content);
	if (token->quotes == UNQUOTED
		&& ((token->next && token->next->index == token->index)))
	{
		// free(token->content);
		token->content = NULL;
	}
	// tmp = ft_strjoin(content, "$");
	// if (!tmp)
	// 	free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	// return (void);
}

void	expand_token(t_entry *entry, t_token *token, char **env)
{
	int		i;
	int		keep;

	if (!*env)
		return ;
	i = 0;
	keep = 0;
	if (!token->content)
		return ;
	if (!ft_strchr(token->content, '$'))
		return ;
	token->is_expand = true;
	while (token->content && token->content[i])
	{
		if (token->content[i] == '$')
		{
			if (!token->content[i + 1])
				handle_dollar(token);
			else if (token->content[i + 1] == '?')
			{
				token->content = handle_status(entry, token->content, i);
				expand_token(entry, token, env);
			}
			else
			{
				token->content = partition_content(entry, token->content, i, keep);
				if (token->content == NULL)
					return ;
				expand_token(entry, token, env);
			}
		}
		i++;
	}
}
