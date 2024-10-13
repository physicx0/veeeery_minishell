/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:37:03 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/06 19:10:30 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	xf_ok(char *cmd, char *pathname, t_glob *glob)
{
	struct stat	f_info;

	if (access(pathname, F_OK) != 0)
		return (no_path(cmd, glob));
	stat(pathname, &f_info);
	if (S_ISDIR(f_info.st_mode))
		return (is_dir(cmd, glob));
	if (access(pathname, X_OK) != 0)
		return (no_prms(cmd, glob));
	return (0);
}

char	*x_path(char *cmd, t_path *path_info, t_glob *glob)
{
	path_info->env_paths = ft_split(path_info->path, ':');
	path_info->env_to_free = path_info->env_paths;
	while (*path_info->env_paths)
	{
		path_info->pathname = exec_strjoin(*path_info->env_paths, cmd);
		if (access(path_info->pathname, F_OK) == 0)
		{
			free_split(path_info->env_to_free);
			return (path_info->pathname);
		}
		free(path_info->pathname);
		path_info->pathname = NULL;
		path_info->env_paths++;
	}
	free_split(path_info->env_to_free);
	no_cmd(cmd, glob);
	return (NULL);
}

char	*check_path(char *cmd, t_glob *glob)
{
	t_path	path_info;

	if (ft_strchr(cmd, '/'))
	{
		if (xf_ok(cmd, cmd, glob) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_info.path = find_path(*glob->env);
	if (!path_info.path || !*path_info.path)
	{
		getcwd(path_info.cwd, sizeof(path_info.cwd));
		path_info.pathname = exec_strjoin(path_info.cwd, cmd);
		if (xf_ok(cmd, path_info.pathname, glob) == -1)
		{
			free(path_info.pathname);
			return (NULL);
		}
		else
			return (path_info.pathname);
	}
	return (x_path(cmd, &path_info, glob));
}
