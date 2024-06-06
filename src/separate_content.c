/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:43:30 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 09:44:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_new_content(t_entry *entry, t_token *cur, size_t *index)
{
	char	*new;
	size_t	i;
	int		trim;

	i = 0;
	while (ft_ischarset(cur->content[i], " \t\n\v\f"))
		i++;
	trim = i;
	while (cur->content[i] && !ft_ischarset(cur->content[i], " \t\n\v\f"))
		i++;
	new = ft_strndup(cur->content + trim, i - trim);
	if (!new)
		free_token_and_exit(entry, ERR_MALLOC, cur->content, EXIT_FAILURE);
	*index = i;
	return (new);
}

static void	upd_cur(t_token *cur, char *content)
{
	free(cur->content);
	cur->content = content;
}

static t_token	*create_token(t_entry *entry, t_token *cur, char *content)
{
	t_token	*new;
	int		ib[2];

	ib[0] = cur->index;
	ib[1] = cur->block;
	new = token_new(ib);
	if (!new)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	new->content = content;
	new->quotes = cur->quotes;
	new->type = cur->type;
	new->category = cur->category;
	new->head = cur->head;
	new->prev = cur;
	new->next = cur->next;
	return (new);
}

void	separate_content(t_entry *entry, t_token *cur, t_token *next)
{
	t_token	*new;
	size_t	i;
	char	*start;
	char	*end;

	i = 0;
	start = create_new_content(entry, cur, &i);
	while (ft_ischarset(cur->content[i], " \t\n\v\f"))
		i++;
	if (i == ft_strlen(cur->content))
	{
		upd_cur(cur, start);
		return ;
	}
	end = ft_strdup(cur->content + i);
	if (!end)
		free_token_and_exit(entry, ERR_MALLOC, cur->content, EXIT_FAILURE);
	upd_cur(cur, start);
	new = create_token(entry, cur, end);
	cur->next = new;
	if (next)
		next->prev = new;
}
