/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:44:52 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/04 15:58:52 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_contents(t_entry *entry, t_token *cur, t_token *prev)
{
	char	*new;

	if (!cur || (!cur->content && !prev->content))
		return ;
	new = ft_strjoin(prev->content, cur->content);
	if (!new)
		free_token_and_exit(entry, ERR_MALLOC, cur->content, EXIT_FAILURE);
	free(prev->content);
	prev->content = NULL;
	cur->content = new;
	if (prev->quotes && !cur->quotes)
		cur->quotes = prev->quotes;
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

static void	upd_cur(t_token *cur, char *content)
{
	free(cur->content);
	cur->content = content;
}

static void	separate_content(t_entry *entry, t_token *cur, t_token *next)
{
	t_token	*new;
	size_t	i;
	int		trim;
	char	*start;
	char	*end;

	i = 0;
	while (ft_ischarset(cur->content[i], " \t\n\v\f"))
		i++;
	trim = i;
	while (cur->content[i] && !ft_ischarset(cur->content[i], " \t\n\v\f"))
		i++;
	start = ft_strndup(cur->content + trim, i - trim);
	if (!start)
		free_token_and_exit(entry, ERR_MALLOC, cur->content, EXIT_FAILURE);
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

void	upd_token(t_entry *entry, t_token *token)
{
	t_token	*cur;
	bool	split;

	if (!token)
		return ;
	cur = token;
	split = false;
	while (cur)
	{
		if (!cur->quotes && cur->content && ft_strchr(cur->content, ' '))
		{
			separate_content(entry, cur, cur->next);
			split = true;
		}
		else if (!split && cur->prev && cur->prev->index == cur->index)
		{
			join_contents(entry, cur, cur->prev);
			split = false;
		}
		cur = cur->next;
	}
}
