/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:03 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 18:00:53 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_tokens(t_entry *entry, t_token **token, int *ib)
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
		free_token_and_exit(entry, ERR_MALLOC, nl, EXIT_FAILURE);
	new->type = OPERATOR;
	new->category = CTL_OP;
	token_addback(token, new);
}

static t_token	*create_new_token(t_entry *entry, int ib[2], char *str)
{
	t_token	*new;

	new = token_new(ib);
	if (!new)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	return (new);
}

static void	update_index_and_move_forward(char *str, int *i, int *index)
{
	if (ft_ischarset(str[*i], " \t\n\v") && !ft_ischarset(str[*i - 1], "|<>"))
		(*index)++;
	while (str[*i] && ft_ischarset(str[*i], " \t\n\v"))
		(*i)++;
}

static void	stash_in_tokens(t_entry *entry, char *str, int i, int *ib)
{
	t_token	*new;

	while (str[i])
	{
		new = create_new_token(entry, ib, str);
		token_addback(&entry->token, new);
		if (ft_ischarset(str[i], METACHARACTER))
			handle_metachars(entry, new, &i, ib);
		else if (!ft_ischarset(str[i], METACHARACTER))
			handle_non_metachars(entry, new, str, &i);
		if (entry->status)
			return ;
		update_index_and_move_forward(str, &i, &ib[0]);
	}
}

void	stash_str(t_entry *entry, t_token **token, char *str)
{
	int		i;
	int		ib[2];

	if (!str)
		return ;
	ib[0] = 0;
	ib[1] = 0;
	i = 0;
	skip_whitespace(str, &i);
	if (!str[i])
	{
		entry->status = entry->prev_status;
		return ;
	}
	add_history(entry->str);
	stash_in_tokens(entry, str, i, ib);
	if (entry->status)
		return ;
	close_tokens(entry, token, ib);
	analyze_syntax(entry);
}
