/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_non_metachars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:52:23 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 15:32:18 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token(const char *str, t_entry *entry, t_token *new, char *set)
{
	char	*dup;
	int		i;

	i = 0;
	if (new->quotes)
		i++;
	while (str[i] && !ft_ischarset(str[i], set))
		i++;
	if (new->quotes && str[i] == '\0')
	{
		free_token_before_return(entry, ERR_QUOTES, (char *)str, 2);
		return (0);
	}
	dup = ft_strndup(str, i);
	if (!dup)
		free_token_and_exit(&(entry->token), ERR_MALLOC, (char *)str, 1);
	new->content = ft_strtrim(dup, set);
	free(dup);
	if (!new->content)
		free_token_and_exit(&(entry->token), ERR_MALLOC, (char *)str, 1);
	if (new->quotes)
		i++;
	new->type = WORD;
	return (i);
}

void	handle_non_metachars(t_entry *entry, t_token *new, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		new->quotes = SIMPLE;
		*i += get_token(str + *i, entry, new, "'");
	}
	else if (str[*i] == '\"')
	{
		new->quotes = DOUBLE;
		*i += get_token(str + *i, entry, new, "\"");
	}
	else
		*i += get_token(str + *i, entry, new, " \t\n\v|<>\"'");
}
