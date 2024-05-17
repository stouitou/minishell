/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 13:04:13 by stouitou         ###   ########.fr       */
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
	int		j;

	j = 0;
	while (token && token->block < i)
		token = token->next;
	while (token && token->block == i)
	{
		if (token->category == INFILE || token->category == DELIMITER)
			find_infiles(entry, exe, token);
		if (token->category == OUTFILE || token->category == APP_OUTFILE)
			find_outfiles(entry, exe, token);
		if (token->category == CMD || token->category == OPTION
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

// static void	upd_exe(t_entry *entry, t_exe *exe, t_token *token, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (token && token->block < i)
// 		token = token->next;
// 	find_files(exe, entry, token);
// 	while (token && token->block == i)
// 	{
// 		if (token->category == CMD || token->category == OPTION
// 			|| token->category == ARG)
// 		{
// 			if (token->category == CMD)
// 				exe->cmd = init_cmd(entry, exe, token);
// 			exe->cmd[j] = protected_strdup(entry, exe, token->content);
// 			j++;
// 		}
// 		token = token->next;
// 	}
// 	if (exe->cmd)
// 		exe->cmd[j] = NULL;
// }

void	init_exe(t_entry *entry, t_exe *exe, char **env, int i)
{
	exe->env = env;
	exe->infile = NULL;
	exe->outfile = NULL;
	exe->io_fd[0] = -1;
	exe->io_fd[1] = -1;
	exe->cmd = NULL;
	upd_exe(entry, exe, entry->token, i);
}
