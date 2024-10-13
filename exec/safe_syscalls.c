/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_syscalls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:55:39 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/06 21:33:30 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pipe(int fd[])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

int	ft_execve(char *path, char **arg, char **env)
{
	if (execve(path, arg, env) == -1)
	{
		perror("execve");
		free_split(arg);
		free_split(env);
		free(path);
		exit(1);
	}
	return (0);
}
