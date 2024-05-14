/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 13:58:40 by stouitou         ###   ########.fr       */
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

static char	**find_files(t_exe *exe, t_entry *entry, t_token *token, int cat)
{
	char	**files;
	int		nb;
	int		block;
	int		j;

	if (cat == INFILE)
		nb = exe->ioa_cnt[0];
	if (cat == OUTFILE)
		nb = exe->ioa_cnt[1];
	if (cat == APP_OUTFILE)
		nb = exe->ioa_cnt[2];
	files = (char **)malloc((nb + 1) * sizeof(char *));
	if (!files)
	{
		free_exe(exe);
		free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, EXIT_FAILURE);
	}
	block = token->block;
	j = 0;
	while (token && token->block == block)
	{
		if (token->category == cat)
		{
			files[j] = ft_strdup(token->content);
			if (!files[j])
			{
				free_exe(exe);
				free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, EXIT_FAILURE);
			}
			j++;
		}
		token = token->next;
	}
	files[j] = NULL;
	return (files);
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

static void	upd_exe(t_entry *entry, t_exe *exe, t_token *token, int i)
{
	int	j;

	j = 0;
	while (token && token->block < i)
		token = token->next;
	get_files_count(exe->ioa_cnt, token, i);
	exe->infile = find_files(exe, entry, token, INFILE);
	exe->outfile = find_files(exe, entry, token, OUTFILE);
	exe->app_outfile = find_files(exe, entry, token, APP_OUTFILE);
	while (token && token->block == i)
	{
		if (token->category == DELIMITER)
			exe->delimiter = token->content;
		else if (token->category == CMD || token->category == OPTION
			|| token->category == ARG)
		{
			if (token->category == CMD)
				exe->cmd = init_cmd(entry, exe, token);
			exe->cmd[j] = ft_strdup(token->content);
			if (!exe->cmd[j])
			{
				free_exe(exe);
				free_token_and_exit(&(entry->token), ERR_MALLOC, token->content, EXIT_FAILURE);
			}
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
