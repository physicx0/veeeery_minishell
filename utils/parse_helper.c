/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:16:08 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 11:45:46 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*create_tree_node(t_token *token)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->word_token = token->word_token;
	new_node->word = ft_strdup(token->word);
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	link_redirection_to_tree(t_tree *command, t_tree *redirection)
{
	command->right = redirection;
}

t_tree	*create_redirection_node(t_token *token)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->word_token = token->word_token;
	new_node->word = ft_strdup(token->word);
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree	*create_operator_node(t_token *token)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->word_token = token->word_token;
	new_node->word = ft_strdup("waa serr chof token chbghiti fiya");
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	link_command_node(t_tree *root, t_tree *new_node)
{
	if (!root->right)
		root->right = new_node;
	else
		link_command_node(root->right, new_node);
}
