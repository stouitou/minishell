/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:36:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/27 15:38:48 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**upd_env_export_only(t_exe *exe, t_env *env)
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
		len = ft_strlen(env->key) + ft_strlen(env->value) + 3;
		array[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[i])
		{
			init_error(exe, ERR_MALLOC, env->key, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		j = ft_strlcpy(array[i], env->key, ft_strlen(env->key) + 1);
		j += ft_strlcpy(array[i] + j, "=", 2);
		j += ft_strlcpy(array[i] + j, "\"", ft_strlen(env->value) + 1);
		j += ft_strlcpy(array[i] + j, env->value, ft_strlen(env->value) + 1);
		j += ft_strlcpy(array[i] + j, "\"", ft_strlen(env->value) + 1);
		array[i][j] = '\0';
		env = env->next;
		i++;
	}
	array[i] = NULL;
	// print_tab(array);
	return (array);
}

void	export_only(t_exe *exe, t_env *env)
{
	char	**sorted;
	char	*tmp;
	char	*prefix;
	int		i;
	int		j;

	sorted = upd_env_export_only(exe, env);
	prefix = "declare -x ";
	i = 0;
	while (sorted[i])
	{
		j = i + 1;
		while (sorted[j])
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[i];
				sorted[i] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (sorted[i])
	{
		if (ft_strncmp(sorted[i], "_=", 2) != 0)
			ft_printf("%s%s\n", prefix, sorted[i]);
		i++;
	}
}
