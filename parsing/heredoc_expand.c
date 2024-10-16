/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:40 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:40:15 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*heredoc_expand(char *string, t_env *env, t_glob *glob)
{
	int		i;
	char	*exported;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$' && string[i + 1] != '$')
		{
			exported = expand(string, env, i, glob);
			if (!exported)
			{
				string = ft_strdup("");
				break ;
			}
			string = exported;
		}
		i++;
	}
	return (string);
}

int	expand_triger(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
			return (1);
		i++;
	}
	return (0);
}
