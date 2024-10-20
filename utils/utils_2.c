/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:52:55 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/18 02:38:32 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	link_free(t_token *head)
{
	t_token	*holder;

	while (head)
	{
		free(head->word);
		holder = head;
		head = head->next;
		free(holder);
	}
}

char	**input_organizer(char *parse_string)
{
	t_orgvar	ov;

	init_orgvar(&ov, parse_string);
	while (ov.splited_command[ov.i])
	{
		ov.y = 0;
		if (string_checker(&ov))
		{
			while (ov.splited_command[ov.i][ov.y])
			{
				close_open(&ov);
				if (append_caller(&ov))
				{
					ov.splited_command = appender(ov.splited_command, ov.i,
							ov.y);
					ov.i = 0;
					break ;
				}
				ov.y++;
			}
		}
		ov.i++;
	}
	return (ov.splited_command);
}

int	env_length(char *env)
{
	int	i;

	i = 0;
	if (env[0] == '?' 
		|| (env[0] >= '0' && env[0] <= '9'))
		return (1);
	while ((env[i] && (env[i] >= 65 && env[i] <= 90))
		|| (env[i] >= 97 && env[i] <= 122)
		|| (env[i] >= '0' && env[i] <= '9') || env[i] == '_')
		i++;
	return (i);
}

char	*exporter(char *search, char *env_line)
{
	int	i;

	i = 0;
	while (search[i] == env_line[i])
		i++;
	if (!search[i] && env_line[i] == '=')
		return (ft_substr(env_line, i + 1, ft_strlen(env_line)));
	return (NULL);
}

char	*value_returner(char *search, t_env *env, t_glob *glob)
{
	char	*exported;
	t_env	*current;

	current = env;
	exported = NULL;
	if (!ft_strcmp(search, "?"))
		return (free(search), ft_itoa(glob->exit_status));
	while (current)
	{
		exported = exporter(search, current->env_line);
		if (exported)
			break ;
		current = current->next;
	}
	free(search);
	return (exported);
}
