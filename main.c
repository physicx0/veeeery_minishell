/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:40 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:40:15 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int ac, char *av[], char *env[])
{
	t_env	*our_env;
	t_glob	glob;
    char    *line;
    t_tree  *root;
//	atexit(leaks);
	(void)ac;
	(void)av;
	our_env = env_dup(env);
	glob.env = &our_env;
	glob.exit_status = 0;
	setup_main_signals();
	while (1)
    {
        line = readline("0xhb_shell$ ");
		root = parsing_entry(line, &glob);
        if (root)
		{
			exec(root, &glob);
			printf("EXIT_STATUS: %d\n", glob.exit_status);
			unlink("/tmp/");
			free(line);
			free_tree(root);
		}
    }
}
