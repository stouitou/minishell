/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:15:44 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 16:36:27 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**upd_env(t_exe *exe, t_env *env)
{
	char	**array;
	int		size;
	int		len;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	size = env_size(env);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
	{
		init_error(exe, ERR_MALLOC, "env array", EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	i = 0;
	while (env)
	{
		j = 0;
		len = ft_strlen(env->key) + ft_strlen(env->value) + 1;
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[i])
		{
			init_error(exe, ERR_MALLOC, env->key, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		j = ft_strlcpy(array[i], env->key, ft_strlen(env->key) + 1);
		j += ft_strlcpy(array[i] + j, "=", 2);
		j += ft_strlcpy(array[i] + j, env->value, ft_strlen(env->value) + 1);
		array[i][j] = '\0';
		env = env->next;
		i++;
	}
	array[i] = NULL;
	// print_tab(array);
	return (array);
}
