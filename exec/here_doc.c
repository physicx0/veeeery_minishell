/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:15 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/17 05:00:32 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*add_char(char *line, char c)
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
	new_line[i++] = c;
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	sub_prs(t_entry *var_ent, t_glob *glob, char *file)
{
	char	*line;
	char	*new_line;
	int		fd;

	hdoc_signals();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!*var_ent->new->next->word && !*line)
			break ;
		if (strict_strncmp(var_ent->new->next->word, line))
			break ;
		if (!expand_triger(var_ent->prev->next->word))
			line = heredoc_expand(line, *glob->env, glob);
		new_line = add_char(line, '\n');
		ft_putstr_fd(new_line, fd);
		free(new_line);
	}
	close(fd);
	free(line);
	exit(0);
}

void	hd_exit_status(int wstatus, t_glob *glob)
{
	if (WIFSIGNALED(wstatus))
	{
		glob->exit_status = WTERMSIG(wstatus);
		if (glob->exit_status == SIGINT)
		{
			g_var = 1;
			glob->exit_status = 1;
		}
	}
}

void	x_hdoc(t_entry *var_ent, t_glob *glob, char *file)
{
	int	pid;
	int	wstatus;

	pid = ft_fork();
	if (pid == 0)
		sub_prs(var_ent, glob, file);
	else
	{
		waitpid(pid, &wstatus, 0);
		hd_exit_status(wstatus, glob);
		free(var_ent->head->next->word);
		var_ent->head->next->word = ft_strdup(file);
	}
}

void	here_doc(t_entry *var_ent, t_glob *glob)
{
	t_herh	herh;

	her_init(&herh, var_ent);
	g_var = 0;
	herh.file = ft_strdup("/tmp/.HeRe_DoC");
	herh.c = 'a';
	while (var_ent->head)
	{
		if (var_ent->head->word_token == PIPE)
		{
			herh.file = add_char(herh.file, herh.c);
			herh.c++;
		}
		if (var_ent->head->word_token == HEREDOC)
			x_hdoc(var_ent, glob, herh.file);
		if (g_var)
			break ;
		var_ent->head = var_ent->head->next;
		var_ent->prev = var_ent->prev->next;
		var_ent->new = var_ent->new->next;
	}
	var_ent->head = herh.looper;
	var_ent->new = herh.looper1;
	var_ent->prev = herh.looper2;
	free(herh.file);
}
