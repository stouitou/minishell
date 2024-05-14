/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:28:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:15:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(const char *str)
{
	char	*new;
	int		i;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = ft_tolower(str[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
