/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:43:46 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/15 15:32:40 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pipe_sequence(t_tree *root, t_glob *glob)
{
	t_pipe	strc;

	strc.prv_fd = -1;
	while (root->word_token == PIPE)
	{
		if (left_cmd(root->left, glob, &strc) == -1)
		{
			while (wait(NULL) > 0)
				;
			return ;
		}
		root = root->right;
	}
	strc.pid = right_cmd(root, glob, &strc);
	if (strc.pid == -1)
	{
		close(strc.prv_fd);
		return ;
	}
	close(strc.prv_fd);
	waitpid(strc.pid, &strc.wstatus, 0);
	while (wait(NULL) > 0)
		;
	exit_status(strc.wstatus, glob);
}

void	exec(t_tree *root, t_glob *glob)
{
	if (root)
	{
		if (root->word_token == PIPE)
			pipe_sequence(root, glob);
		else
			simple_cmd(root, glob);
	}
}

void	execute_cmd(t_cmd *strc, t_glob *glob)
{
	reset_signals();
	if (redirect_io(strc->arg))
		exit(1);
	free_split(strc->arg);
	if (!strc->fltr_arg || !*(strc->fltr_arg))
		exit(0);
	strc->path = check_path(*strc->fltr_arg, glob);
	if (!strc->path)
	{
		free_split(strc->fltr_arg);
		exit(glob->exit_status);
	}
	ft_execve(strc->path, strc->fltr_arg, env_to_arr(*glob->env));
}

void	simple_cmd(t_tree *root, t_glob *glob)
{
	t_cmd	strc;

	strc.arg = generate_arg(root);
	strc.fltr_arg = filter_arg(strc.arg);
	if (strc.fltr_arg && *strc.fltr_arg && is_builtin(*(strc.fltr_arg)))
	{
		built_cmd(strc.arg, strc.fltr_arg, glob);
		free_split(strc.arg);
		free_split(strc.fltr_arg);
		return ;
	}
	strc.pid = ft_fork();
	if (strc.pid == -1)
	{
		glob->exit_status = 1;
		free_split(strc.arg);
		free_split(strc.fltr_arg);
		return ;
	}
	if (strc.pid == 0)
		execute_cmd(&strc, glob);
	waitpid(strc.pid, &strc.wstatus, 0);
	exit_status(strc.wstatus, glob);
	free_split(strc.arg);
	free_split(strc.fltr_arg);
}
