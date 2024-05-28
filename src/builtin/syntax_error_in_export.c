/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_in_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:33:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 15:45:53 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_start_of_arg(char *arg, char c, int *status)
{
	if (!c || c == '=' || c == '\0' || ft_isdigit(c))
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
	}
}

static void	check_unauthorised_character(char *arg, char c, int *status)
{
	if (!ft_isalnum(c) && c != '_')
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
	}
}

static void	check_operator(char *arg, char fst, char sec, int *status)
{
	if (fst == '+' && sec != '=')
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
	}
}

bool	syntax_error_in_export(char *arg, int *exit_status)
{
	int		i;

	if (!arg)
		return (true);
	i = 0;
	check_start_of_arg(arg, arg[i], exit_status);
	if (*exit_status)
		return (true);
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		check_unauthorised_character(arg, arg[i], exit_status);
		if (*exit_status)
			return (true);
		i++;
	}
	if (!arg[i])
		return (true);
	check_operator(arg, arg[i], arg[i + 1], exit_status);
	if (*exit_status)
		return (true);
	return (false);
}
