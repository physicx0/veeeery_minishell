/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:19:56 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/16 16:59:11 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_redirect(t_pipe *strc)
{
	if (strc->prv_fd != -1)
	{
		dup2(strc->prv_fd, STDIN_FILENO);
		close(strc->prv_fd);
	}
	close(strc->fd[0]);
	dup2(strc->fd[1], STDOUT_FILENO);
	close(strc->fd[1]);
}

void	parent_redirect(t_pipe *strc)
{
	if (strc->prv_fd != -1)
		close(strc->prv_fd);
	close(strc->fd[1]);
	strc->prv_fd = dup(strc->fd[0]);
	close(strc->fd[0]);
}

int	left_cmd(t_tree *root, t_glob *glob, t_pipe *strc)
{
	if (ft_pipe(strc->fd) == -1)
	{
		glob->exit_status = 1;
		return (-1);
	}
	strc->pid = ft_fork();
	if (strc->pid == -1)
	{
		glob->exit_status = 1;
		return (-1);
	}
	if (strc->pid == 0)
	{
		child_redirect(strc);
		pipe_cmd(root, glob);
		exit(glob->exit_status);
	}
	else
		parent_redirect(strc);
	return (strc->pid);
}

int	right_cmd(t_tree *root, t_glob *glob, t_pipe *strc)
{
	strc->pid = ft_fork();
	if (strc->pid == -1)
	{
		glob->exit_status = 1;
		return (-1);
	}
	if (strc->pid == 0)
	{
		dup2(strc->prv_fd, 0);
		close(strc->prv_fd);
		pipe_cmd(root, glob);
		exit(glob->exit_status);
	}
	return (strc->pid);
}

void	pipe_cmd(t_tree *root, t_glob *glob)
{
	t_cmd	strc;

	reset_signals();
	strc.arg = generate_arg(root);
	strc.fltr_arg = filter_arg(strc.arg);
	if (strc.fltr_arg && *(strc.fltr_arg) && is_builtin(*(strc.fltr_arg)))
		return (built_cmd(strc.arg, strc.fltr_arg, glob));
	if (redirect_io(strc.arg))
		exit(1);
	free_split(strc.arg);
	if (!strc.fltr_arg || !*(strc.fltr_arg))
		exit(0);
	strc.path = check_path(*(strc.fltr_arg), glob);
	if (!strc.path)
	{
		free_split(strc.fltr_arg);
		exit(glob->exit_status);
	}
	ft_execve(strc.path, strc.fltr_arg, env_to_arr(*glob->env));
}
