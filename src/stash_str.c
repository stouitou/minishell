/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:03 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 15:07:34 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_index_and_block(int ib[2])
{
	ib[0] = 0;
	ib[1] = 0;
}

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

static t_token	*create_new_token(t_token **token, int ib[2], char *str)
{
	t_token	*new;

	new = token_new(ib);
	if (!new)
		free_token_and_exit(token, ERR_MALLOC, str, EXIT_FAILURE);
	return (new);
}

static void	update_index_and_move_forward(char *str, int *i, int *index)
{
	if (ft_ischarset(str[*i], " \t\n\v") && !ft_ischarset(str[*i - 1], "|<>"))
		(*index)++;
	while (str[*i] && ft_ischarset(str[*i], " \t\n\v"))
		(*i)++;
}

void	stash_str(t_entry *entry, t_token **token, char *str)
{
	int		i;
	int		ib[2];
	t_token	*new;

	if (!str)
		return ;
	init_index_and_block(ib);
	i = 0;
	skip_whitespace(str, &i);
	while (str[i])
	{
		new = create_new_token(token, ib, str);
		token_addback(token, new);
		if (ft_ischarset(str[i], METACHARACTER))
			handle_metachars(entry, new, &i, ib);
		else if (!ft_ischarset(str[i], METACHARACTER))
			handle_non_metachars(entry, new, str, &i);
		if (entry->status)
			return ;
		update_index_and_move_forward(str, &i, &ib[0]);
	}
	close_tokens(token, ib);
	analyze_syntax(entry);
}
