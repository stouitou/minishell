/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:16:07 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 10:27:42 by stouitou         ###   ########.fr       */
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

static void	classify_word(t_token *cur, int *cmd_found)
{
	// ft_printf("in classify_word, cur = %p\n", cur);
	// ft_printf("in classify_word cur->content = %s\n", cur->content);
	// ft_printf("in classify_word cur->type = %d\n", cur->type);
	// ft_printf("in classify_word cur->category = %d\n", cur->category);
	// ft_printf("in classify_word cmd_found = %d\n", *cmd_found);
	if (!cur)
		return ;
	if (cur->prev && ft_strcmp(cur->prev->content, "<") == 0)
		cur->category = INFILE;
	else if (cur->prev && ft_strcmp(cur->prev->content, ">") == 0)
		cur->category = OUTFILE;
	else if (cur->prev && ft_strcmp(cur->prev->content, "<<") == 0)
		cur->category = DELIMITER;
	else if (cur->prev && ft_strcmp(cur->prev->content, ">>") == 0)
		cur->category = APP_OUTFILE;
	else
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
	// ft_printf("in classify_word cur->category = %d\n", cur->category);
}

static void	remove_op(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	if (!token || !*token)
		return ;
	cur = *token;
	while (cur)
	{
		next = cur->next;
		if (cur->type == OPERATOR)
			remove_node(token, cur);
		// ft_printf("inremoveop, next = %p\n", next);
		cur = next;
	}
}

static void	remove_null(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	if (!token || !*token)
		return ;
	cur = *token;
	while (cur)
	{
		next = cur->next;
		if (cur->content == NULL)
			remove_node(token, cur);
		// ft_printf("inremoveop, next = %p\n", next);
		cur = next;
	}
}

void	classify_tokens(t_entry *entry)
{
	t_token	*cur;
	t_token	*next;
	int		cmd_found;

	if (!entry->token)
		return ;
	cur = entry->token;
	cmd_found = 0;
	while (cur)
	{
		// ft_printf("%?33s cur->content = %s\n", "In classify token", cur->content);
		// ft_printf("%?33s cur->type = %d\n", "In classify token", cur->type);
		next = cur->next;
		if (cur->type == WORD)
			classify_word(cur, &cmd_found);
		else if (cur->type == OPERATOR)
			classify_operator(cur);
		if (cur && cur->next && cur->next->block != cur->block)
			cmd_found = 0;
		cur = next;
	}
	remove_op(&(entry->token));
	upd_token_heads_and_indexes(entry->token);
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
		if (cur->type == WORD && cur->quotes != SIMPLE && (!prev || ft_strcmp(prev->content, "<<") != 0))
			expand_token(entry, cur, env);
		cur = next;
	}
	gather_indexes(entry, entry->token);
	remove_null(&(entry->token));
	classify_tokens(entry);
}

// void	handle_expansions(t_entry *entry, char **env)
// {
// 	t_token	*cur;
// 	t_token	*next;

// 	if (!entry->token)
// 		return ;
// 	cur = entry->token;
// 	while (cur)
// 	{
// 		next = cur->next;
// 		if (cur->type == WORD)
// 		{
// 			if (cur->quotes != SIMPLE
// 				&& (!cur->prev || (ft_strcmp(cur->prev->content, "<<") != 0)))
// 			{
// 				expand_token(entry, cur, env);
// 				if (cur->content == NULL)
// 					remove_node(&(entry->token), cur);
// 			}
// 			gather_indexes(entry, cur);
// 		}
// 		cur = next;
// 	}
// 	classify_tokens(entry);
// }


// void	classify_tokens(t_entry *entry, char **env)
// {
// 	t_token	*cur;
// 	t_token	*next;
// 	int		cmd_found;

// 	if (!entry->token)
// 		return ;
// 	cur = entry->token;
// 	cmd_found = 0;
// 	while (cur)
// 	{
// 		next = cur->next;
// 		// ft_printf("cur->content = %s\n", cur->content);
// 		if (cur->type == WORD)
// 		{
// 			if (cur->quotes != SIMPLE
// 				&& (!cur->prev || (ft_strcmp(cur->prev->content, "<<") != 0)))
// 			{
// 				expand_token(entry, cur, env);
// 				if (cur->content == NULL)
// 					remove_node(&(entry->token), cur);
// 			}
// 			ft_printf("in classify, cur = %p\n", cur);
// 			gather_indexes(entry, cur);
// 			ft_printf("in classify, cur = %p\n", cur);
// 			classify_word(cur, &cmd_found);
// 		}
// 		else if (cur->type == OPERATOR)
// 			classify_operator(cur);
// 		if (cur && cur->next && cur->next->block != cur->block)
// 			cmd_found = 0;
// 		cur = next;
// 	}
// 	remove_op(&(entry->token));
// 	upd_token_heads_and_indexes(entry->token);
	// ft_printf("token in classify = %p\n", entry->token);
	// ft_printf("IN CLASSIFY token->content = %s\n", entry->token->content);
// }
