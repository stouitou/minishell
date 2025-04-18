/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:18:08 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 10:11:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-s2[0]);
	if (s2 == NULL)
		return (s1[0]);
	i = 0;
	while ((s1[i] || s2[i])
		&& s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
