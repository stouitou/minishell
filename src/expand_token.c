/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:02:31 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar(t_token *token, int i)
{
	if (!token->content[i + 1])
	{
		if (token->quotes == UNQUOTED
			&& ((token->next && token->next->index == token->index)))
			token->content = NULL;
	}
}

static void	check_case(t_entry *entry, t_token *token, char *exp, int i)
{
	if (exp[i + 1] == '?')
	{
		token->content = handle_status(entry, exp, i);
		expand_token(entry, token, entry->env);
	}
	else if (!exp[i + 1] || !(ft_isalpha(exp[i + 1]) || exp[i + 1] == '_'))
		handle_dollar(token, i);
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
