/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:36:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/12 14:12:26 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_exe *exe, t_env *cur, char **arr, int i)
{
	int	j;
	int	len;

	j = 0;
	if (cur->value)
		len = ft_strlen(cur->key) + ft_strlen(cur->value) + 3;
	else
		len = ft_strlen(cur->key);
	arr[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr[i])
		free_subshell_and_exit(exe, ERR_MALLOC, cur->key, EXIT_FAILURE);
	j = ft_strlcpy(arr[i], cur->key, ft_strlen(cur->key) + 1);
	if (cur->value)
	{
		j += ft_strlcpy(arr[i] + j, "=", 2);
		j += ft_strlcpy(arr[i] + j, "\"", ft_strlen(cur->value) + 1);
		j += ft_strlcpy(arr[i] + j, cur->value, ft_strlen(cur->value) + 1);
		j += ft_strlcpy(arr[i] + j, "\"", ft_strlen(cur->value) + 1);
	}
	arr[i][j] = '\0';
}

static char	**upd_env_export_only(t_exe *exe, t_env *env)
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

static void	sort_array(char **arr, int i)
{
	char	*tmp;
	int		j;

	j = i + 1;
	while (arr[j])
	{
		if (ft_strcmp(arr[i], arr[j]) > 0)
		{
			tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
		}
		j++;
	}
}

void	export_only(t_exe *exe, t_env *env)
{
	char	**sorted;
	char	*prefix;
	int		i;

	if (!env)
		return ;
	sorted = upd_env_export_only(exe, env);
	prefix = "declare -x ";
	i = 0;
	while (sorted[i])
	{
		sort_array(sorted, i);
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
