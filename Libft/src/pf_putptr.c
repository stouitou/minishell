/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peoriou <peoriou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:17:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/27 10:28:06 by peoriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putptr(t_print *tab)
{
	void	*ptr;
	char	*base;
	// int		len;

	ptr = va_arg(tab->args, void *);
	base = "0123456789abcdef";
	// len = pf_unbrlen_base((unsigned long int)ptr, base);
	if (ptr == NULL)
		tab->tl += write(1, "(nil)", 5);
	else
	{
		if (tab->txt)
			pf_print_prefix(tab);
		tab->tl += write(1, "0x", 2);
		pf_putu_base(tab, (unsigned long int)ptr, base);
		if (tab->txt)
			ft_putstr_fd("\033[0m", 1);
	}
	tab->txt = 0;
	tab->col = 0;
}
