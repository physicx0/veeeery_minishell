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

void	here_doc(t_token *node, t_glob *glob, t_token *prev)
{
	t_heredo	v_here;

	v_here.flager = 0;
	v_here.file = "/tmp/.HeRe_DoC";
	while (node)
	{
		if (node->word_token == HEREDOC)
		{
			v_here.pid = ft_fork();
			if (v_here.pid == 0)
				here_helper(node, glob, &v_here, prev);
			else
			{
				waitpid(v_here.pid, &v_here.wstatus, 0);
				exit_status(v_here.wstatus, glob);
				free(node->next->word);
				node->next->word = ft_strdup(v_here.file);
			}
		}
		node = node->next;
		prev = prev->next;
	}
}

int	here_helper(t_token *node, t_glob *glob, t_heredo *v_here, t_token *prev)
{
	if (expand_triger(prev->next->word))
		v_here->flager = 1;
	v_here->fd = open(v_here->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		v_here->line = readline(">");
		if (!v_here->line)
			break ;
		if (!*node->next->word && !*v_here->line)
			break ;
		if (strict_strncmp(node->next->word, v_here->line))
			break ;
		if (v_here->flager == 0)
			v_here->line = heredoc_expand(v_here->line, *glob->env);
		v_here->new_line = add_newline(v_here->line);
		ft_putstr_fd(v_here->new_line, v_here->fd);
		free(v_here->line);
		free(v_here->new_line);
	}
	close(v_here->fd);
	exit (0);
}
