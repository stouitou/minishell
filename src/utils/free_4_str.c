/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_4_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:47:09 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:36:13 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_4_str(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
	str1 = NULL;
	str2 = NULL;
	str3 = NULL;
	str4 = NULL;
}
