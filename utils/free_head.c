/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:05 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/11 23:40:37 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*dup_linker(t_token *head)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->word = ft_strdup(head->word);
	new_node->word_token = head->word_token;
	new_node->next = NULL;
	return (new_node);
}

t_token	*dup_head(t_token *head)
{
	t_token	*prev;
	t_token	*current;
	t_token	*new_one;
	t_token	*looper;

	prev = NULL;
	current = prev;
	looper = head;
	while (looper)
	{
		new_one = dup_linker(looper);
		if (!prev)
		{
			prev = new_one;
			current = new_one;
		}
		else
		{
			current->next = new_one;
			current = new_one;
		}
		looper = looper->next;
	}
	return (prev);
}
