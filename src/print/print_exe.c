/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:34:57 by peoriou           #+#    #+#             */
/*   Updated: 2024/05/16 14:10:36 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_header(void)
{
	static int nb = 1;
	ft_printf("%?37s\n", "------------------------------------------");
	if (nb == 1)
		ft_printf("%?37s (%dst execution since program is launched.)\n", "Printing EXE...", nb);
	else if (nb == 2)
		ft_printf("%?37s (%dnd execution since program is launched.)\n", "Printing EXE...", nb);
	else if (nb == 3)
		ft_printf("%?37s (%drd execution since program is launched.)\n", "Printing EXE...", nb);
	else
		ft_printf("%?37s (%dth execution since program is launched.)\n", "Printing EXE...", nb);
	nb++;
}

static void	print_footer(void)
{
	// ft_printf("\n%?37s\n", "Done printing !!!");
	ft_printf("\n");
	ft_printf("\n");
}

static void	check_error_envir(t_exe *exe)
{
	if (*(exe->env) == NULL)
	{
		ft_printf("%?31s\n", "- Environment is NULL.");
		return ;
	}
	if (getenv("PATH") == NULL)
		ft_printf("%?31s", " path is unavailable. ");
	if (getenv("HOME") == NULL)
		ft_printf("%?31s\n", "home is unavailable. ");
}

static void	print_pipe(t_exe *exe)
{
	if (exe->pipe_fd1[0] == -1 && exe->pipe_fd1[1] == -1)
		ft_printf("\033[31m%s\033[0m\n", "- no pipe");
	else
		ft_printf("- pipe (%d|%d) activated...\n", exe->pipe_fd1[0], exe->pipe_fd1[1]);
	// ft_printf("- pipe_fd1[0] = %?37d   |   pipe_fd1[1] = %?37d\n", exe->pipe_fd1[0], exe->pipe_fd1[1]);
}

static void	print_infile(t_exe *exe)
{
	int	i;

	i = 0;
	if (!exe->infile)
		ft_printf("\033[30m- no infile\033[0m  |  ");
	else
	{
		while (exe->infile[i])
		{
			ft_printf("- \033[36minfile[%d]\033[0m = %s  |  ", i, exe->infile[i]);
			i++;
		}
	}
	ft_printf("\n");
}

static void	print_outfile(t_outfile *outfile)
{
	int	i;

	i = 0;
	if (!outfile)
		ft_printf("\033[30mno outfile\033[0m\n");
	else
	{
		while (outfile)
		{
			if (outfile->append)
				ft_printf("- \033[36moutfile[%d] (append)\033[0m = %s  |  ", i, outfile->content);
			else
				ft_printf("- \033[36moutfile[%d]\033[0m = %s  |  ", i, outfile->content);
			outfile = outfile->next;
			i++;
		}
	}
	ft_printf("\n");
}

static void	print_delimiter(t_exe *exe)
{
	if (!exe->delimiter)
		ft_printf("\033[30mno delimiter\033[0m\n");
	else
		ft_printf("\033[36mdelimiter\033[0m = %s  |  ", exe->delimiter);
}

static void	print_files(t_exe *exe)
{
	print_infile(exe);
	if (exe->outfile)
		print_outfile(exe->outfile);
	print_delimiter(exe);
}

static void	print_iofd(t_exe *exe)
{
	if (exe->iod_fd[0])
		ft_printf("\n  • \033[36minfile fd\033[0m => %d\n", exe->iod_fd[0]);
	if (exe->iod_fd[1])
		ft_printf("  • \033[36moutfile fd\033[0m => %d\n", exe->iod_fd[1]);
	if (exe->iod_fd[2])
		ft_printf("  • \033[36mdelimiter fd\033[0m => %d\n", exe->iod_fd[2]);
}

static void	print_cmd(t_exe *exe, char **env)
{
	char	**cmd;
	int		i;

	if (!exe->cmd)
	{
		ft_printf("%?31s\n", "- Executable char **cmd is NULL.");
		return ;
	}
	i = 0;
	cmd = exe->cmd;
	if (!*env)
		ft_printf("%s\n", "- execve (cmd[0] ,  \033[32mcmd\033[0m ,  \033[31menv\033[0m) :");
	else
		ft_printf("%s\n", "- execve (cmd[0] ,  \033[32mcmd\033[0m ,  \033[32menv\033[0m) :");
	while (cmd[i])
	{
		ft_printf("  • cmd[%?33d] = %?33s\n", i, cmd[i]);
		i++;
	}
	ft_printf("\n");
}

static void	highlight_in_full_command(t_entry *entry, t_token *token, int block)
{
	t_token	*tmp;

	if (!entry || !token)
		return ;
	tmp = token;
	while (tmp && tmp->block < block)
		tmp = tmp->next;
	ft_printf("\n  ");
	print_full_command(entry, tmp);
	ft_printf("\n\n");
}

void	print_exe(t_entry *entry, t_token *token, t_exe *exe, int block)
{
	print_header();
	highlight_in_full_command(entry, token, block);
	check_error_envir(exe);
	print_cmd(exe, exe->env);
	print_pipe(exe);
	print_files(exe);
	print_iofd(exe);
	print_footer();
}

