/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_addprefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:08:49 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:16:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_addprefix(t_print *tab)
{
	char	*prefix;
	char	*color;
	char	*tmp;

	color = ft_itoa(tab->col);
	tmp = ft_strjoin("\033[1;", color);
	prefix = ft_strjoin(tmp, "m");
	free(color);
	free(tmp);
	return (prefix);
}
