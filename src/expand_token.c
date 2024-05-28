/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 12:24:32 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*protected_itoa(int status, char *s1, char *s2, t_entry *entry)
{
	char	*ret;

	ret = ft_itoa(status);
	if (!ret)
	{
		free(s1);
		free_token_and_exit(entry, ERR_MALLOC, s2, EXIT_FAILURE);
	}
	return (ret);
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

static char	*handle_status(t_entry *entry, char *content, int i)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && errno == ENOMEM)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	expand = protected_itoa(entry->prev_status, start, content, entry);
	end = ft_strdup(content + i + 2);
	if (!end)
	{
		free_4_str(start, expand, NULL, NULL);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = protected_strjoin(start, expand, end, entry);
	free_4_str(start, expand, NULL, NULL);
	new = protected_strjoin(tmp, end, NULL, entry);
	free_4_str(tmp, end, NULL, NULL);
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
