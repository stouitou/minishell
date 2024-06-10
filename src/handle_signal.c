/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:46:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/10 17:12:59 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sgl)
{
	// t_entry	*entry;
    
	// (void)info;
	// entry = (t_entry *)ent;
	// ft_printf("signal received = %d\n", sgl);
	// (void)cont;
	// ft_printf("pid = %d\n", sa->si_pid);
	// if (sa->si_pid != 0)
	// 	printf("\n");
	// if (sa->si_pid == 0)
	// {
		if (sgl == SIGINT)
		{
			// ft_printf("it is me mario\n");
			sig_stat = 130;
			rl_replace_line("", 0);
			ft_printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
		// if (sgl == SIGQUIT)
		// {
		// 	ft_printf("sr = %d\n", sig_stat);
		// 	sig_stat = 131;
		// 	// rl_replace_line("", 0);
		// 	// printf("\n");
		// 	// rl_on_new_line();
		// 	// rl_redisplay();
		// }
		
	// }
	// exit(sgl);
}

void	handle_signal_in_subshell(int sgl)
{
		if (sgl == SIGINT)
		{
			// ft_printf("it is me mario\n");
			sig_stat = 130;
			exit (130);
		}
}
