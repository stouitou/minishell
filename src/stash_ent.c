/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_ent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:03 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 09:45:25 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_tokens(t_token **token, int *ib)
{
	t_token	*new;
	char	*nl;

	if (!token || !*token)
		return ;
	nl = "newline";
	ib[0]++;
	new = token_new(ib);
	if (!new)
		return ;
	new->content = ft_strdup(nl);
	if (!new->content)
		free_token_and_exit(token, ERR_MALLOC, nl, EXIT_FAILURE);
	new->type = OPERATOR;
	new->category = CTL_OP;
	token_addback(token, new);
}

void	stash_ent(t_entry *entry)
{
	int		i;
	int		ib[2];
	t_token	*new;
	char	*str;

	if (!entry->str)
		return ;
	i = 0;
	ib[0] = 0;
	ib[1] = 0;
	str = entry->str;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		new = token_new(ib);
		if (!new)
			free_token_and_exit(&(entry->token), ERR_MALLOC, str, EXIT_FAILURE);
		token_addback(&(entry->token), new);
		if (ft_ischarset(str[i], METACHARACTER))
			handle_metachars(entry, new, &i, ib);
		else if (!ft_ischarset(str[i], METACHARACTER))
			handle_non_metachars(entry, new, str, &i);
		if (entry->status)
			return ;
		if (ft_ischarset(str[i], " \t\n\v") && !ft_ischarset(str[i - 1], "|<>"))
			ib[0]++;
		while (str[i] && ft_ischarset(str[i], " \t\n\v"))
			i++;
	}
	close_tokens(&(entry->token), ib);
}

/*
	char **tab;
	tab[0] => cmd
	tab[1] => token->next->content
	...
	&tab

*/
