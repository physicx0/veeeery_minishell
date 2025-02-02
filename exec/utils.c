/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:09:26 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/18 02:04:29 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

char	**env_to_arr(t_env *env)
{
	char	**arr;
	int		size;
	int		i;

	size = env_size(env);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = env->env_line;
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*std_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ptr = malloc(l1 + l2 + 1);
	if (!ptr)
		return (NULL);
	while (i < l1)
		ptr[j++] = s1[i++];
	i = 0;
	while (i < l2)
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

void	exit_status(int wstatus, t_glob *glob)
{
	if (WIFEXITED(wstatus))
		glob->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		glob->exit_status = WTERMSIG(wstatus);
		if (glob->exit_status == SIGINT)
			glob->exit_status = 130;
		else if (glob->exit_status == SIGQUIT)
		{
			printf("Quit: %d\n", glob->exit_status);
			glob->exit_status = 131;
		}
	}
}

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
