/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:16:04 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:38:50 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	entry_helper(t_entry *var_ent, t_glob *glob, char *parse_string)
{
	var_ent->organized_input = input_organizer(parse_string);
	var_ent->head = lexer(var_ent->organized_input);
	var_ent->prev = dup_head(var_ent->head);
	expand_flager(var_ent->head, *glob->env, glob);
	content_trima(var_ent->head);
	here_doc(var_ent->head, glob, var_ent->prev);
}

static char	*negative_allocater(unsigned int n, int col)
{
	char	*malloca;
	int		saver;

	saver = col;
	malloca = (char *)malloc(sizeof(char) * (col + 2));
	if (malloca == NULL)
		return (NULL);
	while (0 < col)
	{
		malloca[col] = n % 10 + '0';
		n /= 10;
		col--;
	}
	malloca[0] = '-';
	malloca[saver + 1] = '\0';
	return (malloca);
}

static int	count_digit(int n)
{
	if (n / 10 == 0)
		return (1);
	return (1 + count_digit(n / 10));
}

static char	*positive_allocater(int n, int col)
{
	int		i;
	int		saver;
	char	*malloca;

	i = 0;
	saver = col;
	malloca = (char *)malloc(sizeof(char) * (col + 1));
	if (malloca == NULL)
		return (NULL);
	while (i < col)
	{
		malloca[col - 1] = n % 10 + '0';
		n /= 10;
		col--;
	}
	malloca[saver] = '\0';
	return (malloca);
}

char	*ft_itoa(int n)
{
	int				col;
	int				i;
	char			*malloca;
	unsigned int	p;

	col = count_digit(n);
	i = 0;
	if (n == 0)
	{
		malloca = (char *)malloc(2);
		if (malloca == NULL)
			return (NULL);
		malloca[i] = '0';
		malloca[i + 1] = '\0';
		return (malloca);
	}
	if (n > 0)
		return (positive_allocater(n, col));
	p = n * -1;
	return (negative_allocater(p, col));
}
