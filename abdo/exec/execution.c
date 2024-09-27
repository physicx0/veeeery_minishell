/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:43:46 by amaaouni          #+#    #+#             */
/*   Updated: 2024/09/27 06:10:18 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_tree *root, char **env)
{
	static int	exit_status = 0;
	int			fd[2];

	if (root == NULL)
		return ;
	if (root->word_token == PIPE)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			exec(root->left, env);
			exit(1);
		}
		if (fork() == 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			exec(root->right, env);
			exit(1);
		}
		close(fd[0]);
		close(fd[1]);
		wait(&exit_status);
		wait(&exit_status);
	}
	else
	{
		simple_cmd(root, env);
	}
	return ;
}

void	simple_cmd(t_tree *root, char **env)
{
	char	**arg;
	char	**farg;
	char	*path;

	arg = generate_arg(root, env);
	farg = filter_arg(arg);
	if (fork() == 0)
	{
		redirect_io(arg);
		free_split(arg);
		if (!farg)
			exit(1);
		path = check_path(farg[0], env);
		if (!path)
		{
			free_split(farg);
			exit(1);
		}
		execve(path, farg, env);
		perror("execve");
		free_split(farg);
		exit(1);
	}
	wait(NULL);
	free_split(arg);
	free_split(farg);
}
