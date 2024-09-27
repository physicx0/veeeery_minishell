/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:16:04 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:41:50 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	sub_counter(char const *s, char delimiter)
{
	t_splvar	sv;

	sv.quote = 0;
	sv.closed = 1;
	sv.words = 0;
	sv.i = 0;
	count_helper(&sv, s, delimiter);
	return (sv.words);
}

static size_t	substring_len(char const *s, char delimiter)
{
	size_t	i;
	int		closed;
	char	quote;

	quote = 0;
	closed = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == delimiter && closed == 1)
			break ;
		if ((s[i] == 39 || s[i] == 34) && closed == 1 && s[i - 1] != '\\')
		{
			closed = 0;
			quote = s[i];
		}
		else
		{
			if (s[i] == quote)
				closed = 1;
		}
		i++;
	}
	return (i);
}

void	ft_free(char **substring, size_t i)
{
	while (i > 0)
	{
		i--;
		free(substring[i]);
	}
	free(substring);
}

static char	**sub_filler(char const *s, char delimiter, char **substring,
		size_t sub_counts)
{
	t_splvar	sv;

	sv.quote = 0;
	sv.closed = 1;
	sv.i = 0;
	sv.y = 0;
	while (sv.i < sub_counts)
	{
		while (s[sv.y] && s[sv.y] == delimiter && sv.closed == 1)
			sv.y++;
		substring[sv.i] = ft_substr(s, sv.y, substring_len(&s[sv.y],
					delimiter));
		if (!substring[sv.i])
		{
			ft_free(substring, sv.i);
			return (NULL);
		}
		fill_helper(&sv, delimiter, substring, s);
		sv.i++;
	}
	substring[sv.i] = NULL;
	return (substring);
}

char	**commands_spliter(char const *s, char c)
{
	char	**malloca;
	size_t	sub_strings;

	if (!s)
		return (NULL);
	sub_strings = sub_counter(s, c);
	malloca = (char **)malloc(sizeof(char *) * (sub_strings + 1));
	if (!malloca)
		return (NULL);
	malloca = sub_filler(s, c, malloca, sub_strings);
	return (malloca);
}
