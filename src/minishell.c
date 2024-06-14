/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 18:19:21 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

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
			{
				free(new[--i]);
				new[i] = NULL;
			}
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
	entry->status = g_sig;
	entry->exit = false;
	entry->sign = sa;
	entry->env = NULL;
	entry->env = dup_env(env);
	if (!entry->env)
    {
        perror("Failed to duplicate environment");
        exit(EXIT_FAILURE);
    }
}

static void	reset_status(t_entry *entry)
{
	g_sig = 0;
	entry->prev_status = entry->status;
	entry->status = 0;
}

static void	clear_and_reset_status(t_entry *entry, t_token **token)
{
	// (void)token;
	// ft_printf("In clear and reset status\n");
	free(entry->str);
	entry->str = NULL;
	token_clear(entry, token);
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
	ft_bzero(&sa, sizeof(struct sigaction));
	init_entry(&entry, env, sa);
	while (1)
	{
		// ft_printf("Hi 1\n");
		sa.sa_handler = handle_signal;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		// ft_printf("Hi 2\n");
		entry.str = readline(PROMPT);
		if (entry.str == NULL)
		{
			ft_free_str_array(entry.env);
			ft_printf("exit\n");
			rl_clear_history();
			exit(entry.prev_status);
		}
		// ft_printf("Hi 3\n");
		stash_str(&entry, &(entry.token), entry.str);
		// ft_printf("Hi 4\n");
		handle_expansions(&entry, env);
		// ft_printf("Hi 5\n");
		classify_tokens(&entry);
		// ft_printf("Hi 6\n");
		if (entry.status || !entry.token)
		{
			clear_and_reset_status(&entry, &(entry.token));
			continue ;
		}
		// ft_printf("Hi 7\n");
		exec_token(&entry, entry.token);
		ft_printf("Hi 8\n");
		clear_and_reset_status(&entry, &(entry.token));
		// ft_printf("Hi 9\n");
		if (entry.exit == true)
		{
			rl_clear_history();
			ft_free_str_array(entry.env);
			exit (entry.prev_status);
		}
	}
	ft_free_str_array(entry.env);
	rl_clear_history();
	return (0);
}
