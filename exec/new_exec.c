/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:39:19 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/03 12:58:05 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pipe_sequence(t_tree root, t_env env)
{
	int	fd[2];
	int	prv_fd;

	while (root)
	{
		pipe(fd);
		if (fork() == 0)
		{
			redirect_io(fd, prv_fd);
			pipe_cmd(root->left, env);
		}
		else
			close_fd(fd, prv_fd);
		root = root->right;
	}
	
}

void	op_exec(t_tree *root, t_env *env)
{
	if (root->word_token == PIPE)
		pipe_sequence(root, env);
	else
		simple_cmd(root, env);
}
