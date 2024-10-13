/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:50:47 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/06 23:42:26 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_isnum(int c)
{
    if (c >= 48 && c <= 57)
        return (1);
    return (0);
}

int	check_var(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return 0;
	while (*arg)
	{
		if (!ft_isalpha(*arg) && !ft_isnum(*arg) && *arg != '_')
			return 0;
		arg++;
	}
	return 1;
}

void	delete_node(t_env *prev, t_env *curr, t_env **env)
{
	if (prev == NULL)
		*env = curr->next;
	else
		prev->next = curr->next;
	free(curr->env_line);
	free(curr);
	return ;
}

static void	remove_var(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;
	char	*eq_sign;
	int		key_len;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		eq_sign = ft_strchr(curr->env_line, '=');
		if (eq_sign)
			key_len = eq_sign - curr->env_line;
		else
			key_len = ft_strlen(curr->env_line);
		if (ft_strncmp(curr->env_line, key, key_len) == 0
			&& key_len == ft_strlen(key))
			return (delete_node(prev, curr, env));
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	res;

	args++;
	res = 0;
	while (*args)
	{
		if (check_var(*args))
			remove_var(env, *args);
		else
		{
			ft_putstr_fd("export: ", 2);
		    ft_putstr_fd(*args, 2);
		    ft_putstr_fd(": not a valid identifier\n", 2);
		    res = 1;;
		}
		args++;
	}
	return (res);
}
