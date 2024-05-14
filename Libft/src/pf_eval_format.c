/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_eval_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:29:55 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_eval_format(t_print *tab, const char *str, int i)
{
	char	*charset;

	charset = "cspdiuxX%";
	while (!ft_ischarset(str[i], charset))
	{
		if (str[i] == '?')
			tab->txt = 1;
		if (ft_isdigit(str[i]))
		{
			if (ft_atoi(&str[i]) > tab->col)
				tab->col = ft_atoi(&str[i]);
		}
		i++;
	}
	ft_checkcase(tab, str[i]);
	return (i);
}
