/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:30:28 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar(t_entry *entry, t_token *token, char *content, int i)
{
	char	*start;

	if (!token->content[i + 1])
	{
		if (token->quotes == UNQUOTED
			&& ((token->next && token->next->index == token->index)))
		{
			start = ft_strndup(content, i);
			if (!start && errno == ENOMEM)
				free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
			free(token->content);
			token->content = NULL;
			token->content = start;
		}
	}
}

static void	check_case(t_entry *entry, t_token *token, char *exp, int i)
{
	if (exp[i + 1] == '?')
	{
		token->content = handle_status(entry, exp, i);
		expand_token(entry, token, entry->env);
	}
	else if (!exp[i + 1] || !(ft_isalnum(exp[i + 1]) || exp[i + 1] == '_'))
		handle_dollar(entry, token, exp, i);
	else
	{
		token->content = partition_content(entry, exp, i);
		if (token->content == NULL)
			return ;
		expand_token(entry, token, entry->env);
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
			check_case(entry, token, token->content, i);
		if (token->content == NULL)
			return ;
		i++;
	}
}
