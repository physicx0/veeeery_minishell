/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:52:55 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 11:54:50 by bbelarra42       ###   ########.fr       */
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
	char	**splited_command;
	int		i;
	int		y;
	char	quote;
	int		closed;

	closed = 1;
	quote = 0;
	y = 0;
	splited_command = commands_spliter(parse_string, ' ');
	i = 0;
	while (splited_command[i])
	{
		y = 0;
		if (identifier(splited_command[i]) == STRING
			|| identifier(splited_command[i]) == SQ_STRING
			|| identifier(splited_command[i]) == DQ_STRING)
		{
			while (splited_command[i][y])
			{
				if ((splited_command[i][y] == 39 || splited_command[i][y] == 34)
					&& closed == 1)
				{
					closed = 0;
					quote = splited_command[i][y];
				}
				else
				{
					if (splited_command[i][y] == quote)
						closed = 1;
				}
				if ((splited_command[i][y] == '|' && splited_command[i][y
					- 1] != '\\' && closed == 1)
					|| (splited_command[i][y] == '>' && splited_command[i][y
						- 1] != '\\' && closed == 1)
					|| (splited_command[i][y] == '<' && splited_command[i][y
						- 1] != '\\' && closed == 1))
				{
					splited_command = appender(splited_command, i, y);
					i = 0;
					break ;
				}
				y++;
			}
		}
		i++;
	}
	return (splited_command);
}

int	env_length(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != 32 && env[i] != '$' && env[i] != 34
		&& env[i] != 39 && env[i] != '=' && env[i] != '\\' && env[i] != '.')
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

char	*value_returner(char *search, char **env)
{
	char	*exported;
	int		i;

	exported = NULL;
	i = 0;
	while (env[i])
	{
		exported = exporter(search, env[i]);
		if (exported)
			break ;
		i++;
	}
	free(search);
	return (exported);
}
