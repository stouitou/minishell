/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:03:31 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/04 17:14:46 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(const char *s, char *charset)
{
	size_t	count;
	int		i;

	if (s == NULL || charset == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (ft_ischarset(s[i], charset))
			i++;
		if (s[i])
			count += 1;
		while (s[i] && !ft_ischarset(s[i], charset))
			i++;
	}
	return (count);
}
