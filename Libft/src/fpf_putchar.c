/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:12:29 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_putchar(int fd, t_print *tab)
{
	char	c;

	c = va_arg(tab->args, int);
	if (tab->txt)
		fpf_print_prefix(fd, tab);
	tab->tl += write(fd, &c, 1);
	if (tab->txt)
		ft_putstr_fd("\033[0m", fd);
	tab->txt = 0;
	tab->col = 0;
}
