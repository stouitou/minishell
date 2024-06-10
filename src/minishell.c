/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/10 16:47:03 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sig_stat;

static char	**dup_env(char **env)
{
	char	**new;
	int		i;
	int		arr_len;

	arr_len = ft_str_array_len(env);
	new = (char **)malloc((arr_len + 1) * sizeof(char *));
	if (!new)
		exit (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			while (i)
				free(new[--i]);
			free(new);
			new = NULL;
			exit (1);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	init_entry(t_entry *entry, char **env, struct sigaction sa)
{
	entry->str = NULL;
	entry->token = NULL;
	entry->heredoc = false;
	entry->prev_status = 0;
	entry->status = sig_stat;
	entry->exit = false;
	entry->sign = sa;
	entry->env = NULL;
	entry->env = dup_env(env);
}

static void	reset_status(t_entry *entry)
{
	// sig_stat = 0;
	entry->prev_status = entry->status;
	entry->status = 0;
}

static void	clear_and_reset_status(t_entry *entry, t_token **token)
{
	free(entry->str);
	token_clear(token);
	reset_status(entry);
	entry->heredoc = false;
}



int	main(int argc, char **argv, char **env)
{
	t_entry				entry;
	struct sigaction	sa;
	
	(void)argv;
	if (argc != 1)
		return (1);
	// ft_printf("ici 1\n");
	ft_bzero(&sa, sizeof(struct sigaction));
	// sa.sa_handler = handle_signal;
	// ft_printf("ici 2\n");
	// sa.sa_flags = SA_SIGINFO, t_entry;
	// sigemptyset(&sa.sa_mask);
	// ft_printf("ici 3\n");
	init_entry(&entry, env, sa);
	while (1)
	{
		// ft_printf("sig_stat = %d\n", sig_stat);
		// sigaction(SIGKILL, &sa, NULL);
		// ft_printf("here in main\n");
		sa.sa_handler = handle_signal;
		sigaction(SIGINT, &sa, NULL);
		// sigaction(SIGQUIT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		// ft_printf("ici 3b\n");
		entry.str = readline(PROMPT);
		// ft_printf("entry.str = <%s>\n", entry.str);
		if (entry.str == NULL)
		{
			ft_free_str_array(entry.env);
			ft_printf("exit\n");
			exit(entry.prev_status);
		}
		// ft_printf("ici 3c\n");
		// ft_printf("ici 3b\n");
		// ft_printf("ici 3c\n");
		log_tests(entry.str);
		add_history(entry.str);
		// ft_printf("ici 3d\n");
		stash_str(&entry, &(entry.token), entry.str);
		// ft_printf("ici 4\n");
		handle_expansions(&entry, env);
		classify_tokens(&entry);
		if (entry.status || !entry.token)
		{
			// ft_printf("here\n");
			log_status(entry.status);
			clear_and_reset_status(&entry, &(entry.token));
			continue ;
		}
		exec_token(&entry, entry.token);
		// if (listen_signals())
		// 	continue ;
		// ft_printf("ici 5\n");
		log_status(entry.status);
		// break ;
		// }
		clear_and_reset_status(&entry, &(entry.token));
		if (entry.exit == true)
		{
			rl_clear_history();
			ft_free_str_array(entry.env);
			exit (entry.prev_status);
		}
		// ft_printf("ici 6\n");
	}
	ft_free_str_array(entry.env);
	rl_clear_history();
	return (0);
}
