/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:15 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/11 16:52:18 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*add_newline(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 2));
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

void	here_doc(t_token *node, t_glob *glob)
{
	int		fd;
	char	*line;
	char	*new_line;
	char	*file;
	int		pid;
	int		wstatus;

	file = "/tmp/.HeRe_DoC";
	while (node)
	{
		if (node->word_token == HEREDOC)
		{
			pid = ft_fork();
			if (pid == 0)
			{
				fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				while (1)
				{
					line = readline(">");
					if (!line)
						break ;
					if (!*node->next->word && !*line)
						break ;
					if (strict_strncmp(node->next->word, line))
						break ;
					if (expand_triger(node->next->word))
						line = heredoc_expand(line, *glob->env);
					new_line = add_newline(line);
					ft_putstr_fd(new_line, fd);
					free(line);
					free(new_line);
				}
				close(fd);
				exit(0);
			}
			else
			{
				waitpid(pid, &wstatus, 0);
				exit_status(wstatus, glob);
				free(node->next->word);
				node->next->word = ft_strdup(file);
			}
		}
		node = node->next;
	}
}
