/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:15 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:37:34 by bbelarra42       ###   ########.fr       */
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

t_env	*env_dup(char **env)
{
	int		i;
	t_env	*our_env;
	t_env	*current;
	t_env	*new_one;

	our_env = NULL;
	current = our_env;
	i = 0;
	while (env[i])
	{
		new_one = new_link(env[i]);
		if (!our_env)
		{
			our_env = new_one;
			current = new_one;
		}
		else
		{
			current->next = new_one;
			current = new_one;
		}
		i++;
	}
	return (our_env);
}

int	check_help(char *string, int i, int closed)
{
	if (left_redirection_checker(&string[i], &i, closed)
		|| right_redirection_checker(&string[i], &i, closed)
		|| pipe_checker(&string[i], &i, closed) || ampersand_checker(&string[i],
			&i, closed))
		return (1);
	return (0);
}

int	caller(char *string, int y, int *i)
{
	while (string[y] == ' ' || string[y] == '>' || !string[y]
		|| string[y] == '|' || string[y] == '<' || !string[y]
		|| string[y] == '&')
	{
		if (red_helper(string, y))
			return (1);
		y++;
		(*i)++;
	}
	return (0);
}

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->word)
		free(node->word);
	free(node);
}
