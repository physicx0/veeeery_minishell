/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:40 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/17 02:21:43 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clear_files(void)
{
	char	*file;
	int		c;

	file = ft_strdup("/tmp/.HeRe_DoC");
	c = 'a';
	while (1)
	{
		if (access(file, F_OK) != 0)
			break ;
		unlink(file);
		file = add_char(file, c);
		c++;
	}
	free(file);
}

int	main(int ac, char *av[], char *env[])
{
	t_env	*our_env;
	t_glob	glob;
	char	*line;
	t_tree	*root;

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
			clear_files();
			free(line);
			free_tree(root);
		}
	}
}
