/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_in_parent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:52:11 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 17:15:14 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_content(char *arg)
{
	int	i;
	
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] != '\0')
	{
		// entry->exit = true;
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	return (0);
}

static bool	beyond_limits(const char *nb)
{
	int	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	if (i > 19)
		return (true);
	return (false);
}

static int	iterate(char *nb)
{
	int	i;

	i = 0;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	return (i);
}

static int	check_exit_status(char *arg)
{
	unsigned long	res;
	int				i;

	i = iterate(arg);
	res = 0;
	if (beyond_limits(arg + i))
	{
		// entry->exit = true;
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
		// init_error(exe, "numeric argument required", arg, 2);
		// exit_builtin(exe, "exit");
	}
	while (ft_isdigit(arg[i]))
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (res > LONG_MAX)
	{
		// entry->exit = true;
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
		// init_error(exe, "numeric argument required", arg, 2);
		// exit_builtin(exe, "exit");
	}
	return (res % (unsigned)256);
}

int	handle_export_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	int		exit_status;
	char	*key;
	char	*value;
	t_env	*new;
	int		i;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "export") != 0)
		return (0);
	if (!get_files_fd_for_exit(exe, exe->files))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	i = 1;
	while (cmd[i])
	{
		key = extract_key(exe, cmd[i]);
		value = extract_value(exe, cmd[i]);
		if (exists_in_env(exe, cmd[i], key, value))
			return ;
		new = env_new(key, value);
		if (!new)
		{
			init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		env_addback(&env, new);
	}
	free_exe(exe);
	entry->status = exit_status;
	return (1);
}
