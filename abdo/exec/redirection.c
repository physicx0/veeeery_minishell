/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:11:49 by amaaouni          #+#    #+#             */
/*   Updated: 2024/09/26 05:28:47 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec.h"

void	redirect(char *filename, int mode)
{
	int	fd;

	if (mode == 1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
	}
	else if (mode == 2)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, 1);
	}
	else if (mode == 3)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror(filename);
			exit(1);
		}
		dup2(fd, 0);
	}
}

void	redirect_io(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], ">"))
			redirect(arg[i + 1], 1);
		else if (!ft_strcmp(arg[i], ">>"))
			redirect(arg[i + 1], 2);
		else if (!ft_strcmp(arg[i], "<"))
			redirect(arg[i + 1], 3);
		else if (!ft_strcmp(arg[i], "<<"))
			redirect(arg[i + 1], 4);
		i++;
	}
}

int	is_redirction(char *arg)
{
	if (!ft_strcmp(arg, ">"))
		return (1);
	if (!ft_strcmp(arg, ">>"))
		return (1);
	if (!ft_strcmp(arg, "<"))
		return (1);
	if (!ft_strcmp(arg, "<<"))
		return (1);
	return (0);
}
