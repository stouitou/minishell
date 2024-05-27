/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:50:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/27 11:54:55 by stouitou         ###   ########.fr       */
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
		free_token_and_exit(entry, ERR_MALLOC, NULL, EXIT_FAILURE);
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
		free_token_and_exit(entry, ERR_MALLOC, str, 1);
	}
	return (dup);
}

static void	upd_exe(t_entry *entry, t_exe *exe, t_token *token, int i)
{
	int		j;

	set_env(entry, exe);
	j = 0;
	while (token && token->block < i)
		token = token->next;
	while (token && token->block == i)
	{
		if (token->category == INFILE || token->category == DELIMITER
			|| token->category == OUTFILE || token->category == APP_OUTFILE)
			find_files(entry, exe, token);
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

void	init_exe(t_entry *entry, t_token *token, t_exe *exe, int i)
{
	exe->env = NULL;
	exe->files = NULL;
	exe->io_fd[0] = -1;
	exe->io_fd[1] = -1;
	exe->cmd = NULL;
	upd_exe(entry, exe, token, i);
}
