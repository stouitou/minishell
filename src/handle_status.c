/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:52:32 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/07 11:56:34 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*protected_itoa(int prev_status, char *s1, char *s2, t_entry *entry)
{
	char	*ret;
	int		status;

	if (sig_stat)
		status = sig_stat;
	else
		status = prev_status;
	ret = ft_itoa(status);
	sig_stat = 0;
	if (!ret)
	{
		free(s1);
		free_token_and_exit(entry, ERR_MALLOC, s2, EXIT_FAILURE);
	}
	
	return (ret);
}

static char	*protected_strjoin(char *s1, char *s2, char *s3, t_entry *entry)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
	{
		free_4_str(s1, s2, s3, NULL);
		free_token_and_exit(entry, ERR_MALLOC, "expansion", EXIT_FAILURE);
	}
	return (join);
}

char	*handle_status(t_entry *entry, char *content, int i)
{
	char	*new;
	char	*expand;
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strndup(content, i);
	if (!start && errno == ENOMEM)
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	expand = protected_itoa(entry->prev_status, start, content, entry);
	end = ft_strdup(content + i + 2);
	if (!end)
	{
		free_4_str(start, expand, NULL, NULL);
		free_token_and_exit(entry, ERR_MALLOC, content, EXIT_FAILURE);
	}
	tmp = protected_strjoin(start, expand, end, entry);
	free_4_str(start, expand, NULL, NULL);
	new = protected_strjoin(tmp, end, NULL, entry);
	free_4_str(tmp, end, NULL, NULL);
	return (new);
}
