/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:14:10 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/02 06:35:47 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec.h"

int	get_farg_size(char **arg)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (is_redirction(arg[i]))
			i += 2;
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	**filter_arg(char **arg)
{
	char	**filtered_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	filtered_arg = malloc(sizeof(char *) * (get_farg_size(arg) + 1));
	while (arg[i])
	{
		if (is_redirction(arg[i]))
			i += 2;
		else
		{
			filtered_arg[j] = ft_strdup(arg[i]);
			i++;
			j++;
		}
	}
	filtered_arg[j] = NULL;
	return (filtered_arg);
}

char	**generate_arg(t_tree *root)
{
	t_tree	*dup_root;
	char	**arg;
	int		alloc_size;
	int		i;

	alloc_size = 1;
	dup_root = root;
	while (dup_root != NULL)
	{
		alloc_size++;
		dup_root = dup_root->right;
	}
	arg = malloc(sizeof(char *) * (alloc_size + 1));
	i = 0;
	while (root)
	{
		arg[i] = ft_strdup(root->word);
		root = root->right;
		i++;
	}
	arg[i] = NULL;
	return (arg);
}
