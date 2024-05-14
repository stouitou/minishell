/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:26 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 10:12:49 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_entry(t_entry *entry)
{
	entry->str = NULL;
	entry->token = NULL;
	entry->status = 0;
	entry->prev_status = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_entry	entry;

	(void)argv;
	if (argc != 1)
		return (1);
	init_entry(&entry);
	while (1)
	{
		entry.status = 0;
		entry.str = readline(PROMPT);
		log_tests(entry.str);
		add_history(entry.str);
		stash_ent(&entry);
		if (entry.status || !entry.token)
		{
			entry.prev_status = entry.status;
			log_status(entry.status);
			continue ;
		}
		analyze_syntax(&entry);
		if (entry.status)
		{
			entry.prev_status = entry.status;
			log_status(entry.status);
			continue ;
		}
		handle_expansions(&entry, env);
		exec_token(&entry, entry.token, env);
		// ft_printf("status = %d\n", entry.status);
		token_clear(&(entry.token));
		entry.prev_status = entry.status;
		log_status(entry.status);
		if (ft_strcmp(entry.str, "exit") == 0)
			break ;
	}
	rl_clear_history();
	return (0);
}

/* Take care of:
	1 - $ signs
	2 - syntax error on pipes with nothing after
*/
