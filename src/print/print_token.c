/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:12:30 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:51:59 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_content_line(t_token *tmp, int i)
{
	const char	*cat_strings[] = {
		"",
		"COMMAND",
		"INFILE",
		"OUTFILE",
		"DELIMITER",
		"APPEND OUTFILE",
		"OPTION",
		"ARGUMENT",
		"",
		"",
		"",
		"CONTROL OPERATOR",
		"REDIRECTION OPERATOR"
	};

	if (!tmp)
		return ;
	if (i < 9)
	{
		if (tmp->type == WORD)
		{
			if (print_utils_content_has_space(tmp->content) && tmp->category == CMD)
				ft_printf("%?32s%?32d%?32s   - [index %d]  = %?33s%s%?33s\n", "token[", i, "]", "<", ">", tmp->index, "<", tmp->content, ">");
			else if (tmp->category == CMD)
				ft_printf("%?32s%?32d%?32s   - [index %d]    = %s\n", "token[", i, "]", tmp->index, tmp->content);
			else if (print_utils_content_has_space(tmp->content))
				ft_printf("token[%d]   - [index %d]  = %?33s%s%?33s\n", i, "<", ">", tmp->index, "<", tmp->content, ">");
			else
				ft_printf("token[%d]   - [index %d]    = %s\n", i, tmp->index, tmp->content);
		}
		else
			ft_printf("%?37s%?37d%?37s %?37d%?37s%?37s (%?37s)\n", "token[", i, "]   - [index", tmp->index, "]    = ", tmp->content, cat_strings[tmp->category]);
	}
	else
	{
		if (tmp->type == WORD)
		{
			if (print_utils_content_has_space(tmp->content) && tmp->category == CMD)
				ft_printf("%?32s%?32d%?32s  - [index %d]  = %?33s%s%?33s\n", "token[", i, "]", "<", ">", tmp->index, "<", tmp->content, ">");
			else if (tmp->category == CMD)
				ft_printf("%?32s%?32d%?32s  - [index %d]    = %s\n", "token[", i, "]", tmp->index, tmp->content);
			else if (print_utils_content_has_space(tmp->content))
				ft_printf("token[%d]  - [index %d]  = %?33s%s%?33s\n", i, "<", ">", tmp->index, "<", tmp->content, ">");
			else
				ft_printf("token[%d]  - [index %d]    = %s\n", i, tmp->index, tmp->content);
		}
		else
			ft_printf("%?37s%?37d%?37s %?37d%?37s%?37s (%?37s)\n", "token[", i, "]  - [index", tmp->index, "]    = ", tmp->content, cat_strings[tmp->category]);
	}
}

static void	check_error_index(t_token *tmp)
{
	if (!tmp)
		return ;
	if (tmp->next && tmp->next->index == tmp->index)
		ft_printf("%?31s\n", "           > Careful, next token has the same index !!");
	else if (tmp->prev && tmp->prev->index == tmp->index)
		ft_printf("%?31s\n", "           > Careful, previous token has the same index !!");
	if (tmp->next && tmp->next->index != tmp->index + 1)
		ft_printf("%?31s\n", "           > Problem with indexes");
	if (tmp->prev && tmp->prev->index != tmp->index - 1)
		ft_printf("%?31s\n", "           > Problem with indexes");
}

static void	check_error_command(t_token *tmp)
{
	t_token	*tmp_bis;
	int		found;
	int		actual_block;

	if (!tmp)
		return ;
	tmp_bis = tmp;
	actual_block = tmp_bis->block;
	found = 0;
	while (tmp_bis && tmp_bis->block == actual_block)
	{
		if (tmp_bis->category == CMD)
			found++;
		tmp_bis = tmp_bis->next;
	}
	if (!found)
		ft_printf(" %?31s", "NO COMMAND IN BLOCK.");
	if (found > 1)
		ft_printf(" %?31s", "MORE THAN ONE COMMAND IN BLOCK.");
}

static void	print_category_line(t_token *tmp)
{
	const char	*cat_strings[] = {
		"",
		"COMMAND",
		"INFILE",
		"OUTFILE",
		"DELIMITER",
		"APPEND OUTFILE",
		"OPTION",
		"ARGUMENT",
		"",
		"",
		"",
		"CONTROL OPERATOR",
		"REDIRECTION OPERATOR"
	};
	const char	*quotes_strings[] = {
		"unquoted",
		"single-quoted",
		"double-quoted",
	};
	const char	*type_strings[] = {
		"word",
		"OPERATOR",
	};

	if (!tmp)
		return ;
	if (tmp->type != OPERATOR && tmp->category == CMD)
		ft_printf("           - category     = %?32s \033[90m(%s %s)\033[0m\n", cat_strings[tmp->category], quotes_strings[tmp->quotes], type_strings[tmp->type]);
	else if ((tmp->type != OPERATOR && tmp->category == ARG)
		|| (tmp->type != OPERATOR && tmp->category == OPTION))
		ft_printf("           - category     = %?34s \033[90m(%s %s)\033[0m\n", cat_strings[tmp->category], quotes_strings[tmp->quotes], type_strings[tmp->type]);
	else if (tmp->type != OPERATOR)
		ft_printf("           - category     = %?36s \033[90m(%s %s)\033[0m\n", cat_strings[tmp->category], quotes_strings[tmp->quotes], type_strings[tmp->type]);
}

static void	print_new_block(t_entry *entry, t_token *tmp, int i)
{
	if (!tmp)
		return ;
	if (!i)
	{
		ft_printf("%?32s %?32d %?32s", "### BLOCK", tmp->block, "###   ");
		check_error_command(tmp);
		print_full_command(entry, tmp);
		ft_printf("\n%?32s\n", "--------------------------------------------------------------");
	}
	else if (tmp->next && tmp->next->block != tmp->block)
	{
		ft_printf("\n%?32s %?32d %?32s", "### BLOCK", tmp->next->block, "###   ");
		check_error_command(tmp->next);
		print_full_command(entry, tmp->next);
		ft_printf("\n%?32s", "--------------------------------------------------------------");
	}
}

static void	print_header(int size, int blocks)
{
	ft_printf("%?34s\n", "...");
	ft_printf("%?34s %?32d %?34s %?32d %?34s\n", "Printing", size, "tokens divided in", blocks, "blocks...");
	ft_printf("%?34s\n\n", "...");
}

static void	print_footer(int size, int blocks)
{
	ft_printf("\n%?34s\n", "...");
	ft_printf("%?34s %?32d %?34s %?32d %?34s\n", "And...done!", size, "tokens divided in", blocks, "blocks printed...");
	ft_printf("%?34s\n", "...");
}

void	print_token(t_entry *entry, t_token *token)
{
	int		i;
	int		size;
	int		blocks;
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	i = 0;
	size = print_utils_token_size(tmp);
	blocks = print_utils_token_blocks(tmp);
	print_header(size, blocks);
	print_new_block(entry, tmp, i);
	while (tmp)
	{
		print_content_line(tmp, i);
		check_error_index(tmp);
		print_category_line(tmp);
		i++;
		print_new_block(entry, tmp, i);
		if (tmp->next)
			ft_printf("\n");
		tmp = tmp->next;
	}
	print_footer(size, blocks);
}
