/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_in_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:33:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 12:00:27 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	bad_first_char(char *arg, char c, int *status)
{
	if (!c || c == '=' || c == '\0' || ft_isdigit(c))
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
		return (true);
	}
	return (false);
}

static bool	unauthorised_character(char *arg, char c, int *status)
{
	if (!ft_isalnum(c) && c != '_')
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
		return (true);
	}
	return (false);
}

static bool	wrong_operator(char *arg, char fst, char sec, int *status)
{
	if (fst == '+' && sec != '=')
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*status = 1;
		return (true);
	}
	return (false);
}

bool	syntax_error_in_export(char *arg, int *exit_status)
{
	int		i;
	bool	error;

	if (!arg)
		return (true);
	i = 0;
	error = false;
	error = bad_first_char(arg, arg[i], exit_status);
	if (error)
		return (true);
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		error = unauthorised_character(arg, arg[i], exit_status);
		if (error)
			return (true);
		i++;
	}
	if (!arg[i])
		return (true);
	error = wrong_operator(arg, arg[i], arg[i + 1], exit_status);
	if (error)
		return (true);
	return (false);
}
