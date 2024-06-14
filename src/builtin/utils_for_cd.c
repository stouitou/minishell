/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:53:56 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:34:05 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key_value(t_env *env, char *key)
{
	t_env	*cur;
	char	*value;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			value = cur->value;
			return (value);
		}
		cur = cur->next;
	}
	return (NULL);
}

t_env	*get_in_env(t_env *env, char *key)
{
	t_env	*result;

	if (!env)
		return (NULL);
	result = env;
	while (result)
	{
		if (ft_strcmp(result->key, key) == 0)
			return (result);
		result = result->next;
	}
	return (NULL);
}

char	*find_cwd(void)
{
	char	*pwd;
	char	*buf;
	int		size;

	buf = NULL;
	size = 0;
	while (1)
	{
		pwd = getcwd(buf, size);
		if (!pwd && errno == ERANGE)
		{
			size++;
			continue ;
		}
		else if (!pwd)
			return (NULL);
		break ;
	}
	return (pwd);
}

void	upd_env_pwd(t_env *env)
{
	char	*cwd;
	t_env	*oldpwd;
	t_env	*pwd;

	cwd = find_cwd();
	oldpwd = get_in_env(env, "OLDPWD");
	pwd = get_in_env(env, "PWD");
	if (oldpwd)
	{
		if (pwd)
		{
			free(oldpwd->value);
			oldpwd->value = NULL;
			oldpwd->value = pwd->value;
		}
		else
			oldpwd->value = NULL;
	}
	if (pwd)
	{
		if (!oldpwd)
		{
			free(pwd->value);
			pwd->value = NULL;
		}
		pwd->value = cwd;
	}
}

void	free_cd_b4_return(t_entry *entry, t_exe *exe, char *err, char *arg)
{
	ft_fprintf(2, "cd: ");
	if (arg)
		ft_fprintf(2, "%s: ", arg);
	ft_fprintf(2, "%s\n", err);
	entry->status = 1;
	free_exe(exe);
}
