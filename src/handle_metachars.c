/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_metachars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:52:23 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/29 09:32:32 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*protected_strdup(t_entry *entry, char *str)
{
	char	*dup;

	if (!str)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
		free_token_and_exit(&(entry->token), ERR_MALLOC, str, 1);
	return (dup);
}


static int	get_operator(t_entry *entry, char *str, t_token *new)
{
	int	i;

	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			new->content = protected_strdup(entry, "<<");
		if (ft_strncmp(str, ">>", 2) == 0)
			new->content = protected_strdup(entry, ">>");
		i = 2;
	}
	else
	{
		if (ft_strncmp(str, "<", 1) == 0)
			new->content = protected_strdup(entry, "<");
		if (ft_strncmp(str, ">", 1) == 0)
			new->content = protected_strdup(entry, ">");
		if (ft_strncmp(str, "|", 1) == 0)
			new->content = protected_strdup(entry, "|");
		i = 1;
	}
	new->type = OPERATOR;
	return (i);
}

void	handle_metachars(t_entry *entry, t_token *new, int *i, int *ib)
{
	char	*str;

	str = entry->str;
	if (*i && !ft_ischarset(str[*i - 1], " \t\n\v"))
		ib[0]++;
	new->index = ib[0];
	while (str[*i] && ft_ischarset(str[*i], " \t\n\v"))
		(*i)++;
	if (str[*i] == '|')
		ib[1]++;
	if (ft_ischarset(str[*i], "|<>"))
	{
		*i += get_operator(entry, str + *i, new);
		ib[0]++;
	}
}
