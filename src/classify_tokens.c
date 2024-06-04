/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:53 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 14:53:19 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	classify_operator(t_token *token)
{
	char	*operator;

	operator = token->content;
	if (ft_strcmp(operator, "|") == 0
		|| ft_strcmp(operator, "newline") == 0)
		token->category = CTL_OP;
	else
		token->category = REDIR_OP;
}

static void	determine_command(t_token *cur, int *cmd_found)
{
	if (!*cmd_found)
	{
		cur->category = CMD;
		*cmd_found = 1;
	}
	else
	{
		if (cur->content[0] == '-')
			cur->category = OPTION;
		else
			cur->category = ARG;
	}
}

static void	classify_word(t_entry *entry, t_token *cur, int *cmd_found)
{
	if (!cur)
		return ;
	if (cur->prev && ft_strcmp(cur->prev->content, "<") == 0)
		cur->category = INFILE;
	else if (cur->prev && ft_strcmp(cur->prev->content, ">") == 0)
		cur->category = OUTFILE;
	else if (cur->prev && ft_strcmp(cur->prev->content, "<<") == 0)
	{
		cur->category = DELIMITER;
		go_heredoc(entry, cur);
	}
	else if (cur->prev && ft_strcmp(cur->prev->content, ">>") == 0)
		cur->category = APP_OUTFILE;
	else
		determine_command(cur, cmd_found);
}

void	classify_tokens(t_entry *entry)
{
	t_token	*cur;
	t_token	*next;
	int		cmd_found;

	if (!entry->token)
		return ;
	upd_token(entry, entry->token);
	remove_null(&entry->token);
	cur = entry->token;
	cmd_found = 0;
	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD)
			classify_word(entry, cur, &cmd_found);
		else if (cur->type == OPERATOR)
			classify_operator(cur);
		if (cur && cur->next && cur->next->block != cur->block)
			cmd_found = 0;
		cur = next;
	}
	remove_operator(&entry->token);
	upd_token_heads_and_indexes(entry->token);
}
