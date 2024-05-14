/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peoriou <peoriou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:12:30 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/29 18:59:08 by peoriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_spaces_before(int size, int total_len)
{
	int	to_print;
	int	tmp;

	to_print = (total_len - size) / 2;
	tmp = to_print;
	ft_printf("%?90s", "|");
	while (to_print > 0)
	{
		ft_printf(" ");
		to_print--;
	}
	return (tmp);
}

static void	print_spaces_after(int size, int total_len)
{
	int	to_print;

	to_print = total_len - size;
	if (to_print < 0)
		return ;
	while (to_print)
	{
		ft_printf(" ");
		to_print--;
	}
}

static char	*reduce_content(char *content, int new_len)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (ft_isspace(content[i]))
		i++;
	if (i > 2)
	{
		new[j] = '.';
		j++;
		new[j] = '.';
		j++;
		new[j] = '.';
		j++;
	}
	while (content[i] && j < (new_len - 3))
	{
		new[j] = content[i];
		i++;
		j++;
	}
	new[j] = '.';
	j++;
	new[j] = '.';
	j++;
	new[j] = '.';
	j++;
	new[j] = '\0';
	return (new);
}

static void	print_block_content(t_token *tmp, int total_len)
{
	t_token	*tmp_bis;
	int		size;
	int		spaces_before;
	int		new_len;
	char	*new_content;

	if (!tmp)
		return ;
	tmp_bis = tmp;
	while (tmp_bis)
	{
		size = ft_strlen(tmp_bis->content);
		if (size >= total_len)
		{
			new_len = 8;
			new_content = reduce_content(tmp_bis->content, new_len);
			size = new_len;
			spaces_before = print_spaces_before(size, total_len);
			ft_printf("%s", new_content);
			free(new_content);
			print_spaces_after(size + spaces_before, total_len);
		}
		else
		{
			spaces_before = print_spaces_before(size, total_len);
			if (tmp_bis->category == CTL_OP)
				ft_printf("%?34s", tmp_bis->content);
			else
				ft_printf("%s", tmp_bis->content);
			print_spaces_after(size + spaces_before, total_len);
		}
		if (tmp_bis->next && tmp_bis->block != tmp_bis->next->block)
			break ;
		tmp_bis = tmp_bis->next;
	}
	ft_printf("\n");
}

void print_block(t_token *token)
{
	const char *cat_strings[] = {
		"",
		"COMMAND",
		"INFILE",
		"OUTFILE",
		"DELIMITER",
		"APP_OUTFILE",
		"OPTION",
		"ARGUMENT",
		"",
		"",
		"",
		"",
		"CONTROL OPERATOR",
		"REDIRECTION OPERATOR"
	};
    t_token *tmp;
	int		size;
	int		spaces_before;
	int		total_len;

    if (!token)
        return;
    tmp = token;
	total_len = 16;
	ft_printf("%?34s\n", "...");
    // ft_printf("BLOCK[%d] ", tmp->block);
    ft_printf("\033[37mBLOCK[%d] \033[0m", tmp->block);
	print_block_content(tmp, total_len);
    while (tmp)
    {
		size = ft_strlen(cat_strings[tmp->category]) + ft_nbrlen(tmp->index) + 2;
		if (!tmp->prev || tmp->prev->block != tmp->block)
			ft_printf("         ");
		spaces_before = print_spaces_before(size, total_len);
		if (tmp->category == CMD)
        	ft_printf("%?32s", cat_strings[tmp->category]);
		else
        	ft_printf("%?33s", cat_strings[tmp->category]);
		if ((tmp->prev && tmp->prev->index == tmp->index)
			|| (tmp->next && tmp->next->index == tmp->index))
        	ft_printf("[%?31d]", tmp->index);
		else
        	ft_printf("[%d]", tmp->index);
		print_spaces_after(size + spaces_before, total_len);
        if (tmp->next && tmp->next->block != tmp->block)
		{
            ft_printf("\n\n\033[37mBLOCK[%d] \033[0m", tmp->next->block);
			print_block_content(tmp->next, total_len);
		}
        tmp = tmp->next;
    }
    ft_printf("\n");
	ft_printf("%?34s\n", "...");
}
