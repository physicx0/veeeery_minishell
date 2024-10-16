/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:45 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 15:20:08 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*parse(t_token *tokens, int flager)
{
	t_parse	prs;

	if (!tokens)
		return (NULL);
	prs.current_token = tokens;
	prs.pipe_operator = NULL;
	prs.root = NULL;
	while (prs.current_token)
	{
		if (prs.current_token->word_token == PIPE)
		{
			prs.pipe_operator = prs.current_token;
			break ;
		}
		prs.current_token = prs.current_token->next;
	}
	if (prs.pipe_operator)
	{
		prs.root = create_operator_node(prs.pipe_operator);
		prs.root->left = parse(split_tokens(tokens, prs.pipe_operator), 1);
		prs.root->right = parse(prs.pipe_operator->next, 0);
	}
	else
		prs.root = create_command_subtree(tokens, flager);
	return (prs.root);
}

t_tree	*create_command_subtree(t_token *tokens, int flager)
{
	t_tree	*root;
	t_tree	*current_node;
	t_token	*head;

	head = tokens;
	root = NULL;
	while (tokens)
	{
		current_node = create_tree_node(tokens);
		if (!root)
			root = current_node;
		else
			link_command_node(root, current_node);
		tokens = tokens->next;
	}
	if (flager == 1)
		link_free(head);
	return (root);
}

t_token	*dup_splited(t_token *tokens, t_token *operator_token)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_one;
	t_token	*looper;

	head = NULL;
	current = tokens;
	looper = tokens;
	while (looper && looper != operator_token)
	{
		new_one = dup_linker(looper);
		if (!head)
		{
			head = new_one;
			current = new_one;
		}
		else
		{
			current->next = new_one;
			current = new_one;
		}
		looper = looper->next;
		tokens = tokens->next;
	}
	return (head);
}

t_token	*split_tokens(t_token *tokens, t_token *operator_token)
{
	t_token	*head;

	if (!tokens || !operator_token)
		return (tokens);
	head = dup_splited(tokens, operator_token);
	return (head);
}

void	print_tree(t_tree *node, int caller)
{
	if (!node)
		return ;
	if (caller == 0)
		printf("ROOT->Node: %s, Type: %d\n", node->word, node->word_token);
	else if (caller == 1)
		printf("left->Node: %s, Type: %d\n", node->word, node->word_token);
	else if (caller == 2)
		printf("right->Node: %s, Type: %d\n", node->word, node->word_token);
	print_tree(node->left, 1);
	print_tree(node->right, 2);
}
