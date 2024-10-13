/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:54 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 11:57:14 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	left_redirection_checker(char *string, int *i, int closed)
{
	int	y;
	int	reset;

	reset = 0;
	y = 0;
	if ((closed == 1 && string[y] == '<' && string[y - 1] != '\\'))
	{
		y++;
		(*i)++;
		reset++;
		if (string[y] == '<')
		{
			y++;
			(*i)++;
			reset++;
		}
		if (!string[y] || (string[y] == '<' && reset == 2))
			return (1);
		if (left_red_helper(string, y, i))
			return (1);
	}
	return (0);
}

int	left_red_helper(char *string, int y, int *i)
{
	while (string[y] == ' ' || string[y] == '>' || !string[y]
		|| string[y] == '|' || string[y] == '<' || !string[y]
		|| string[y] == '&')
	{
		if ((!string[y]) || (string[y] == '<' && string[y - 1] != '\\')
			|| (string[y] == '&' && string[y - 1] != '\\') || (string[y] == '>'
				&& string[y - 1] != '\\') || (string[y] == '|' && string[y
					- 1] != '\\'))
			return (1);
		y++;
		(*i)++;
	}
	return (0);
}
