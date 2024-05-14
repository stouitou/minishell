/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peoriou <peoriou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:17:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/27 10:29:08 by peoriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_putptr(int fd, t_print *tab)
{
	void	*ptr;
	char	*base;
	// int		len;

	ptr = va_arg(tab->args, void *);
	// len = pf_unbrlen_base((unsigned long int)ptr, base);
	base = "0123456789abcdef";
	if (ptr == NULL)
		tab->tl += write(fd, "(nil)", 5);
	else
	{
		if (tab->txt)
			fpf_print_prefix(fd, tab);
		tab->tl += write(1, "0x", 2);
		fpf_putu_base(fd, tab, (unsigned long int)ptr, base);
		if (tab->txt)
			ft_putstr_fd("\033[0m", fd);
	}
	tab->txt = 0;
	tab->col = 0;
}
