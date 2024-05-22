/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:38:32 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/21 12:40:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_array_len(char **array)
{
	int	len;
	
	if (array == NULL)
		return (0);
	len = 0;
	while(array[len])
		len++;
	return (len);
}
