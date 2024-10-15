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

t_tree	*parse(t_token *tokens)
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
		prs.root->left = parse(split_tokens(tokens, prs.pipe_operator));
		prs.root->right = parse(prs.pipe_operator->next);
	}
	else
		prs.root = create_command_subtree(tokens);
	return (prs.root);
}

t_tree	*create_command_subtree(t_token *tokens)
{
	t_tree	*root;
	t_tree	*current_node;

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
	return (root);
}

t_token	*split_tokens(t_token *tokens, t_token *operator_token)
{
	t_token	*current;

	if (!tokens || !operator_token)
		return (tokens);
	current = tokens;
	while (current && current->next != operator_token)
		current = current->next;
	if (current)
		current->next = NULL;
	return (tokens);
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
