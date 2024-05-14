/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_putu_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:36:12 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fpf_putu_base(int fd, t_print *tab, size_t n, char *base)
{
	char	*number;
	int		len;
	int		i;

	len = pf_unbrlen_base(n, base);
	number = (char *)malloc((len + 1) * sizeof(char));
	if (number == NULL)
		return ;
	i = len;
	number[i] = '\0';
	i--;
	while (i >= 0)
	{
		number[i] = base[n % ft_strlen(base)];
		n /= ft_strlen(base);
		i--;
	}
	if (tab->txt)
		fpf_print_prefix(fd, tab);
	fpf_putstr(fd, tab, number);
	free(number);
	if (tab->txt)
		ft_putstr_fd("\033[0m", fd);
	tab->wdt = 0;
	tab->col = 0;
}
