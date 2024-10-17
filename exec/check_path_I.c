/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_I.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:09:34 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/15 23:24:54 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_var(t_env *env_list, char *var)
{
	char	*path;

	while (env_list)
	{
		path = ft_strnstr(env_list->env_line, var, ft_strlen(var));
		if (path)
			return (path);
		env_list = env_list->next;
	}
	return (NULL);
}

int	no_prms(char *cmd, t_glob *glob)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	glob->exit_status = 126;
	return (-1);
}

int	no_path(char *cmd, t_glob *glob)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	glob->exit_status = 127;
	return (-1);
}

int	no_cmd(char *cmd, t_glob *glob)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	glob->exit_status = 127;
	return (-1);
}

int	is_dir(char *cmd, t_glob *glob)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": is a directory\n", 2);
	glob->exit_status = 126;
	return (-1);
}
