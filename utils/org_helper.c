/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:30:41 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:09:57 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	string_checker(t_orgvar *ov)
{
	if (identifier(ov->splited_command[ov->i]) == STRING
		|| identifier(ov->splited_command[ov->i]) == SQ_STRING
		|| identifier(ov->splited_command[ov->i]) == DQ_STRING)
		return (1);
	return (0);
}

int	append_caller(t_orgvar *ov)
{
	if ((ov->splited_command[ov->i][ov->y] == '|'
		&& ov->splited_command[ov->i][ov->y - 1] != '\\' && ov->closed == 1)
		|| (ov->splited_command[ov->i][ov->y] == '>'
		&& ov->splited_command[ov->i][ov->y - 1] != '\\' && ov->closed == 1)
		|| (ov->splited_command[ov->i][ov->y] == '<'
		&& ov->splited_command[ov->i][ov->y - 1] != '\\'
		&& ov->closed == 1))
		return (1);
	return (0);
}

int	closer(t_orgvar *ov)
{
	if ((ov->splited_command[ov->i][ov->y] == 39
		|| ov->splited_command[ov->i][ov->y] == 34) && ov->closed == 1)
		return (1);
	return (0);
}

void	close_open(t_orgvar *ov)
{
	if (closer(ov))
	{
		ov->closed = 0;
		ov->quote = ov->splited_command[ov->i][ov->y];
	}
	else
	{
		if (ov->splited_command[ov->i][ov->y] == ov->quote)
			ov->closed = 1;
	}
}

void	init_orgvar(t_orgvar *ov, char *parse_string)
{
	ov->closed = 1;
	ov->quote = 0;
	ov->y = 0;
	ov->splited_command = commands_spliter(parse_string, ' ');
	ov->i = 0;
}
