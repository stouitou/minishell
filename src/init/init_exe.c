/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 17:07:06 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**init_cmd(t_entry *entry, t_exe *exe, t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	int		block;
	int		elems;

	block = token->block;
	tmp = token;
	elems = 0;
	while (tmp && tmp->block == block)
	{
		if (tmp->category == CMD
			|| tmp->category == ARG
			|| tmp->category == OPTION)
			elems++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (elems + 1));
	if (!cmd)
	{
		free_exe(exe);
		free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, EXIT_FAILURE);
	}
	return (cmd);
}

static void	get_files_count(int ioa[3], t_token *token, int i)
{
	while (token && token->block == i)
	{
		if (token->category == INFILE)
			ioa[0]++;
		if (token->category == OUTFILE)
			ioa[1]++;
		if (token->category == APP_OUTFILE)
			ioa[2]++;
		token = token->next;
	}
}

static char	*protected_strdup(t_entry *entry, t_exe *exe, char *str)
{
	char	*dup;

	if (!str)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
	{
		free_exe(exe);
		free_token_and_exit(&(entry->token), ERR_MALLOC, str, 1);
	}
	return (dup);
}

static void	upd_exe(t_entry *entry, t_exe *exe, t_token *token, int i)
{
	int	j;

	j = 0;
	while (token && token->block < i)
		token = token->next;
	get_files_count(exe->ioa_cnt, token, i);
	find_all_files(exe, entry, token);
	while (token && token->block == i)
	{
		if (token->category == DELIMITER)
			exe->delimiter = token->content;
		else if (token->category == CMD || token->category == OPTION
			|| token->category == ARG)
		{
			if (token->category == CMD)
				exe->cmd = init_cmd(entry, exe, token);
			exe->cmd[j] = protected_strdup(entry, exe, token->content);
			j++;
		}
		token = token->next;
	}
	if (exe->cmd)
		exe->cmd[j] = NULL;
}

void	init_exe(t_entry *entry, t_exe *exe, char **env, int i)
{
	exe->env = env;
	exe->infile = NULL;
	exe->outfile = NULL;
	exe->delimiter = NULL;
	exe->app_outfile = NULL;
	exe->ioa_cnt[0] = 0;
	exe->ioa_cnt[1] = 0;
	exe->ioa_cnt[2] = 0;
	exe->ioda_fd[0] = -1;
	exe->ioda_fd[1] = -1;
	exe->ioda_fd[2] = -1;
	exe->ioda_fd[3] = -1;
	exe->cmd = NULL;
	upd_exe(entry, exe, entry->token, i);
}
