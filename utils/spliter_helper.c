/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:31:23 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:40:30 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_helper(t_splvar *sv, int delimiter, char **substring,
		const char *s)
{
	while (s[sv->y])
	{
		if (s[sv->y] == delimiter && sv->closed == 1)
			break ;
		if ((s[sv->y] == 39 || s[sv->y] == 34) && sv->closed == 1 && s[sv->y
				- 1] != '\\')
		{
			sv->closed = 0;
			sv->quote = s[sv->y];
		}
		else
		{
			if (s[sv->y] == sv->quote)
				sv->closed = 1;
		}
		sv->y++;
	}
}

void	count_helper(t_splvar *sv, char const *s, char delimiter)
{
	while (s[sv->i])
	{
		if (s[sv->i] != delimiter)
		{
			while (s[sv->i] && s[sv->i] != delimiter)
			{
				if ((s[sv->i] == 39 || s[sv->i] == 34) && sv->closed == 1
					&& s[sv->i - 1] != '\\')
				{
					sv->closed = 0;
					sv->quote = s[sv->i];
				}
				else
				{
					if (s[sv->i] == sv->quote)
						sv->closed = 1;
				}
				sv->i++;
			}
			if (sv->closed == 1)
				sv->words++;
		}
		else if (s[sv->i] == delimiter)
			sv->i++;
	}
}

void	seter(t_trim *trim)
{
	if (trim->current->word[trim->i] == 39)
		trim->closed = 1;
}

void	trim_whiler(t_trim *trim)
{
	if ((trim->current->word[trim->i] == 39) && trim->closed == 1
		&& trim->current->word[trim->i - 1] != '\\')
		trim->closed = 0;
	else
		seter(trim);
	if ((trim->current->word[trim->i] != '\\'
			&& trim->current->word[trim->i] != 39)
		|| (trim->current->word[trim->i] == 39 && trim->current->word[trim->i
				- 1] == '\\'))
	{
		if ((trim->current->word[trim->i] == 34) && trim->closed == 0)
		{
			trim->trimed[trim->y] = trim->current->word[trim->i];
			trim->y++;
		}
		else if (trim->current->word[trim->i] != 34
			|| trim->current->word[trim->i] == 39 && trim->current->word[trim->i
				- 1] == '\\')
		{
			trim->trimed[trim->y] = trim->current->word[trim->i];
			trim->y++;
		}
	}
}

int	red_helper(char *string, int y)
{
	if ((!string[y]) || (string[y] == '<' && string[y - 1] != '\\')
		|| (string[y] == '&' && string[y - 1] != '\\') || (string[y] == '>'
			&& string[y - 1] != '\\') || (string[y] == '|' && string[y
				- 1] != '\\'))
		return (1);
	return (0);
}
