/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_I.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 07:45:16 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/14 23:48:58 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **arg)
{
	int	new_line;

	new_line = 0;
	arg++;
	if (*arg && !ft_strcmp(*arg, "-n"))
	{
		arg++;
		new_line = 1;
	}
	while (*arg)
	{
		printf("%s", *arg);
		if (*(arg + 1))
			printf(" ");
		arg++;
	}
	if (!new_line)
		printf("\n");
	return (0);
}

void	update_env(char *cwd, char *owd, t_env **env)
{
	char	*pwd[4];

	if (!cwd || !owd)
	{
		ft_putstr_fd("error updating the env", 2);
		return ;
	}
	pwd[0] = "export";
	pwd[1] = std_strjoin("PWD=", cwd);
	pwd[2] = std_strjoin("OLDPWD=", owd);
	pwd[3] = NULL;
	ft_export(pwd, env);
	free(pwd[1]);
	free(pwd[2]);
}

int	ft_cd(char **arg, t_env **env)
{
	char	*path;
	char	owd[PATH_MAX];
	char	cwd[PATH_MAX];

	getcwd(owd, sizeof(owd));
	if (arg[1] && arg[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		return (1);
	}
	else if (!arg[1] || !arg[1][0])
		path = getenv("HOME");
	else
		path = arg[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	update_env(cwd, owd, env);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strchr(env->env_line, '='))
			printf("%s\n", env->env_line);
		env = env->next;
	}
	return (0);
}
