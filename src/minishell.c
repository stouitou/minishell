/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 17:17:57 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_entry(t_entry *entry, char **env)
{
	entry->str = NULL;
	entry->token = NULL;
	entry->heredoc = false;
	entry->prev_status = 0;
	entry->status = 0;
	entry->env = env;
}

static void	reset_status(t_entry *entry)
{
	entry->prev_status = entry->status;
	entry->status = 0;
}

static void	clear_and_reset_status(t_entry *entry, t_token **token)
{
	token_clear(token);
	reset_status(entry);
}


int	main(int argc, char **argv, char **env)
{
	t_entry	entry;

	(void)argv;
	if (argc != 1)
		return (1);
	init_entry(&entry, env);
	while (1)
	{
		entry.str = readline(PROMPT);
		log_tests(entry.str);
		add_history(entry.str);
		stash_str(&entry, &(entry.token), entry.str);
		if (entry.status || !entry.token)
		{
			reset_status(&entry);
			log_status(entry.status);
			continue ;
		}	
		handle_expansions(&entry, env);
		classify_tokens(&entry);
		// print_token(&entry, entry.token);
		exec_token(&entry, entry.token, env);
		log_status(entry.status);
		clear_and_reset_status(&entry, &(entry.token));
		if (ft_strcmp(entry.str, "exit") == 0)
			break ;
	}
	rl_clear_history();
	return (0);
}
