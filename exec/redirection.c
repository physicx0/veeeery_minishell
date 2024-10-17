/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:11:49 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/16 16:52:41 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec.h"

int	open_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	open_out(char *filename, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redirect(char *filename, int mode)
{
	if (mode == 1)
		return (open_out(filename, mode));
	if (mode == 2)
		return (open_out(filename, mode));
	if (mode == 3)
		return (open_in(filename));
	if (mode == 4)
		return (open_in(filename));
	return (0);
}

int	redirect_io(char **arg)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], ">"))
			res = redirect(arg[i + 1], 1);
		if (!ft_strcmp(arg[i], ">>"))
			res = redirect(arg[i + 1], 2);
		if (!ft_strcmp(arg[i], "<"))
			res = redirect(arg[i + 1], 3);
		if (!ft_strcmp(arg[i], "<<"))
			res = redirect(arg[i + 1], 4);
		if (res)
			break ;
		i++;
	}
	return (res);
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
