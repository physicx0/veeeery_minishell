/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:37:03 by amaaouni          #+#    #+#             */
/*   Updated: 2024/09/27 06:17:02 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	free_split(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
	return (1);
}

char	*find_path(char *ev[])
{
	char	*path;

	while (*ev)
	{
		path = ft_strnstr(*ev, "PATH=", 5);
		if (path)
			return (path);
		ev++;
	}
	return (NULL);
}

char	*no_path(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (NULL);
}

char	*no_cmd(t_path *va, char *cmd)
{
	free_split(va->env_to_free);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

char	*check_path(char *cmd, char *ev[])
{
	t_path	path_info;

	path_info.path = find_path(ev);
	if (!path_info.path || !*path_info.path)
		return (no_path(cmd));
	path_info.env_paths = ft_split(path_info.path, ':');
	path_info.env_to_free = path_info.env_paths;
	while (*path_info.env_paths)
	{
		if (!ft_strchr(cmd, '/'))
			path_info.pathname = exec_strjoin(*path_info.env_paths, cmd);
		else
			path_info.pathname = ft_strdup(cmd);
		if (access(path_info.pathname, X_OK) == 0)
		{
			free_split(path_info.env_to_free);
			return (path_info.pathname);
		}
		free(path_info.pathname);
		path_info.pathname = NULL;
		path_info.env_paths++;
	}
	return (no_cmd(&path_info, cmd));
}
