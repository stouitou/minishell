/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peoriou <peoriou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:06:13 by peoriou           #+#    #+#             */
/*   Updated: 2024/05/01 12:07:16 by peoriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_utils_token_size(t_token *token)
{
	t_token	*tmp;
	int		size;

	if (!token)
		return (0);
	tmp = token;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

int	print_utils_token_blocks(t_token *token)
{
	t_token	*tmp;
	int		blocks;

	if (!token)
		return (0);
	blocks = 1;
	tmp = token;
	while (tmp)
	{
		if (tmp->next && tmp->next->block != tmp->block)
			blocks++;
		tmp = tmp->next;
	}
	return (blocks);
}

int	print_utils_content_has_space(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (ft_isspace(content[i]))
			return (1);
		i++;
	}
	return (0);
}
