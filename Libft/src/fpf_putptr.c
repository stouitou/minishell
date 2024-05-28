/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:17:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:23:24 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_putptr(int fd, t_print *tab)
{
	void	*ptr;
	char	*base;

	ptr = va_arg(tab->args, void *);
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
