/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:17:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:24:44 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putptr(t_print *tab)
{
	void	*ptr;
	char	*base;

	ptr = va_arg(tab->args, void *);
	base = "0123456789abcdef";
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
