#include "../includes/minishell.h"

// char	*find_path(char *ev[])
// {
// 	char	*path;

// 	while (*ev)
// 	{
// 		path = ft_strnstr(*ev, "PATH=", 5);
// 		if (path)
// 			return (path);
// 		ev++;
// 	}
// 	return (NULL);
// }

// char	*no_path(char *cmd)
// {
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": No such file or directory\n", 2);
// 	return (NULL);
// }

// char	*no_cmd(t_path *va, char *cmd)
// {
// 	free_split(va->env_to_free);
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": command not found\n", 2);
// 	return (NULL);
// }

// char	*check_path(char *cmd, char *ev[])
// {
// 	t_path	va;

// 	va.path = find_path(ev);
// 	if (!va.path || !*va.path)
// 		return (no_path(cmd));
// 	va.env_paths = ft_split(va.path, ':');
// 	va.env_to_free = va.env_paths;
// 	while (*va.env_paths)
// 	{
// 		if (!ft_strchr(cmd, '/'))
// 			va.pathname = ft_strjoin(*va.env_paths, cmd);
// 		else
// 			va.pathname = ft_strdup(cmd);
// 		if (access(va.pathname, X_OK) == 0)
// 		{
// 			free_split(va.env_to_free);
// 			return (va.pathname);
// 		}
// 		free(va.pathname);
// 		va.pathname = NULL;
// 		va.env_paths++;
// 	}
// 	return (no_cmd(&va, cmd));
// }