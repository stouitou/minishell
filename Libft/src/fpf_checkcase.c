/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_checkcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:00:00 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_checkcase(int fd, t_print *tab, char c)
{
	char	*hexa_low;
	char	*hexa_up;

	hexa_low = "0123456789abcdef";
	hexa_up = "0123456789ABCDEF";
	if (c == 'c')
		fpf_putchar(fd, tab);
	if (c == 's')
		fpf_putstr(fd, tab, va_arg(tab->args, char *));
	if (c == 'p')
		fpf_putptr(fd, tab);
	if (c == 'd' || c == 'i')
		fpf_putnbr(fd, tab);
	if (c == 'u')
		fpf_putu_base(fd, tab, va_arg(tab->args, unsigned int), "0123456789");
	if (c == 'x')
		fpf_putu_base(fd, tab, va_arg(tab->args, unsigned int), hexa_low);
	if (c == 'X')
		fpf_putu_base(fd, tab, va_arg(tab->args, unsigned int), hexa_up);
	if (c == '%')
		fpf_putstr(fd, tab, "%");
}
