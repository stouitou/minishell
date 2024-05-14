/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:32:20 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_putnbr(int fd, t_print *tab)
{
	long int	d;
	int			len;

	d = va_arg(tab->args, int);
	len = ft_nbrlen(d);
	if (tab->txt)
		fpf_print_prefix(fd, tab);
	ft_putnbr_fd(d, fd);
	tab->tl += len;
	if (tab->txt)
		ft_putstr_fd("\033[0m", fd);
	tab->txt = 0;
	tab->col = 0;
}
