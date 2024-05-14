/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:15:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_fd(int fd, t_print *tab, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		tab->tl += write(fd, &str[i], 1);
		i++;
	}
}

void	fpf_putstr(int fd, t_print *tab, char *str)
{
	if (str == NULL)
	{
		tab->tl += write(fd, "(null)", 6);
		return ;
	}
	if (tab->txt)
		fpf_print_prefix(fd, tab);
	ft_print_fd(fd, tab, str);
	if (tab->txt)
		ft_putstr_fd("\033[0m", fd);
	tab->txt = 0;
	tab->col = 0;
}
