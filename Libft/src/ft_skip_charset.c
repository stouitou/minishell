/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_charset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:44:08 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 14:57:26 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_charset(char *str, const char *charset)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && ft_ischarset(str[i], charset))
		i++;
	return (str + i);
}
