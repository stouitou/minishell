/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:51:15 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/08 12:40:14 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;
	size_t	cpy;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = (void *)malloc(size);
	if (new == NULL)
		return (NULL);
	if (ft_strlen((char *)ptr) < size)
		cpy = ft_strlen((char *)ptr);
	else
		cpy = size;
	ft_memcpy(new, ptr, cpy);
	free (ptr);
	return (new);
}
