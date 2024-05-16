/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_full_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:18:45 by peoriou           #+#    #+#             */
/*   Updated: 2024/05/16 14:59:29 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_full_command(t_entry *entry, t_token *token)
{
	t_token	*tmp;
	int		actual_block;
	char	*str;
	int		i;
	int		pipes_found;

	if (!entry || !token || !entry->str)
		return ;
	tmp = token;
	actual_block = tmp->block;
	str = entry->str;
	pipes_found = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '|')
			pipes_found++;
		if (pipes_found == actual_block)
			ft_printf("%?37c", str[i]);
		else
			printf("\033[31m%c\033[0m", str[i]);
		i++;
	}
	// while (str[i] && pipes_found < (actual_block + 1))
	// {
	// 	if (str[i] == '|')
	// 		pipes_found++;
	// 	if (pipes_found == actual_block)
	// 		ft_printf("%?37c", str[i]);
	// 	else
	// 		ft_printf("%?30c", str[i]);
	// 	i++;
	// }
}
