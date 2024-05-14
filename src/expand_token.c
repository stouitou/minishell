/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:12:46 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 12:16:45 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_expand(t_entry *entry, char *str, int *index)
{
	int		i;
	int		start;
	char	*dup;
	char	*var;

	i = 1;
	start = 1;
	if (str[start] == '{')
		start++;
	while (str[i])
	{
		dup = ft_strndup(str + start, i);
		// ft_printf("dup in extract expand = %s\n", dup);
		if (!dup)
			free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
		var = getenv(dup);
		if (var)
		{
			*index += (start + i);
			if (start == 2)
			{
				if (str[start + i] != '}')
				{
					free(dup);
					return (NULL);
				}
				(*index)++;
			}
			else
			{
				if (ft_isalpha(str[start + i]) || str[start + i] == '_')
				{
					free(dup);
					return (NULL);
				}
			}
			free(dup);
			return (var);
		}
		free(dup);
		i++;
		if (str[i] == '}')
		{
			(*index)++;
			return (NULL);
		}
	}
	return (NULL);
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
	if (!expand)
		return (start);
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

static char	*handle_dollar(t_entry *entry, t_token *token)
{
	char	*content;

	free(token->content);
	if (token->quotes == UNQUOTED
		&& (token->next && ft_strcmp(token->next->content, "newline") != 0))
		return (NULL);
	content = ft_strdup("$");
	if (!content)
		free_token_and_exit(&(entry->token), ERR_MALLOC, content, EXIT_FAILURE);
	return (content);
}

void	expand_token(t_entry *entry, t_token *token, char **env)
{
	int		i;

	if (!*env)
		return ;
	i = 0;
	if (!ft_strchr(token->content, '$'))
		return ;
	if (!token->content)
		return ;
	while (token->content && token->content[i])
	{
		if (token->content[i] == '$')
		{
			if (!token->content[i + 1])
				token->content = handle_dollar(entry, token);
			else if (token->content[i + 1] == '?')
			{
				token->content = handle_status(entry, token->content, i);
				expand_token(entry, token, env);
			}
			else if (ft_isalpha(token->content[i + 1]) || token->content[i + 1] == '{')
			{
				token->content = partition_content(entry, token->content, i);
				if (token->content == NULL)
				{
					// ft_printf("token->content = %s\n", token->content);
					return ;
				}
				expand_token(entry, token, env);
			}
		}
		i++;
	}
}

// void	expand_token(t_entry *entry, t_token *token, char **env)
// {
// 	char	*content;
// 	int		i;

// 	if (!*env)
// 		return ;
// 	content = NULL;
// 	i = 0;
// 	if (!ft_strchr(token->content, '$'))
// 		return ;
// 	ft_printf("#### In expand token, content = %?33s ####\n", token->content);
// 	while (token->content[i])
// 	{
// 		if (token->content[i] == '$')
// 		{
// 			ft_printf("In expand_token, before partition_content, content = %s\n", token->content + i);
// 			token->content = partition_content(entry, token->content, i);
// 			ft_printf("In expand_token, after partition_content, token->content = %s\n", token->content + i);
// 			expand_token(entry, token, env);
// 		}
// 		i++;
// 	}
// 	ft_printf("#### In expand token, content = %?32s ####\n", token->content);
// }
