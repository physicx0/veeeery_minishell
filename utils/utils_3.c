/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:15 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:12:01 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_alloc_cp(t_append *ap, char **string, int delimiter, int i_word)
{
	if (i_word == 0 || !string[delimiter][i_word + 1])
		ap->orgnized_one = (char **)malloc(sizeof(char *) * (ap->size + 2));
	else
		ap->orgnized_one = (char **)malloc(sizeof(char *) * (ap->size + 3));
	while (ap->i < delimiter)
	{
		ap->orgnized_one[ap->i] = ft_strdup(string[ap->y]);
		ap->i++;
		ap->y++;
	}
	ap->y++;
	if (i_word != 0)
	{
		ap->orgnized_one[ap->i] = ft_substr(string[delimiter], 0, i_word);
		ap->i++;
	}
	ap->orgnized_one[ap->i] = ft_strdup(operation_returner(string[delimiter],
				i_word));
	ap->i++;
}
