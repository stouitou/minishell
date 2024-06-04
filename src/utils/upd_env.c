/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:15:44 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:14:55 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_exe *exe, t_env *cur, char **arr, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(cur->key) + ft_strlen(cur->value) + 3;
	arr[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr[i])
		free_subshell_and_exit(exe, ERR_MALLOC, cur->key, EXIT_FAILURE);
	j = ft_strlcpy(arr[i], cur->key, ft_strlen(cur->key) + 1);
	j += ft_strlcpy(arr[i] + j, "=", 2);
	j += ft_strlcpy(arr[i] + j, cur->value, ft_strlen(cur->value) + 1);
	arr[i][j] = '\0';
}

char	**upd_env(t_exe *exe, t_env *env)
{
	char	**array;
	int		size;
	int		i;

	if (!env)
		return (NULL);
	size = env_size(env);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		free_subshell_and_exit(exe, ERR_MALLOC, "env array", EXIT_FAILURE);
	i = 0;
	while (env)
	{
		copy_env(exe, env, array, i);
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
