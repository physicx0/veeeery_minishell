#include "../includes/minishell.h"

t_tree		*parse(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    t_tree  *root;
    t_tree  *operator_node;
    t_token *logical_operator;
    t_token *pipe_operator;
    t_token *current_token;

    current_token = tokens;
    logical_operator = NULL;
    pipe_operator = NULL;
    root = NULL;
    while (current_token)
    {
        if (current_token->word_token == OR || current_token->word_token == AND)
        {
            logical_operator = current_token;
            break;
        }
        else if (current_token->word_token == PIPE && !pipe_operator)
            pipe_operator = current_token;
        current_token = current_token->next;
    }
    if (logical_operator)
    {
        root = create_operator_node(logical_operator);
        root->left = parse(split_tokens(tokens, logical_operator));
        root->right = parse(logical_operator->next);
    }
    else if (pipe_operator)
    {
        root = create_operator_node(pipe_operator);
        root->left = parse(split_tokens(tokens, pipe_operator));
        root->right = parse(pipe_operator->next);
    }
    else
        root = create_command_subtree(tokens);
    return root;
}


t_tree *create_command_subtree(t_token *tokens)
{
    t_tree  *root;
    t_tree  *current_node;
    t_tree  *redirection_node;
    root = NULL;

    while (tokens)
    {
        if (tokens->word_token == STRING || tokens->word_token == DQ_STRING
            || tokens->word_token == SQ_STRING)
        {
            current_node = create_tree_node(tokens);
            if (!root)
                root = current_node;
            else
                link_command_node(root, current_node);
        }
        else if (tokens->word_token == APP_REDIRECTION || tokens->word_token == OW_REDIRECTION || 
                 tokens->word_token == IN_OPERATOR || tokens->word_token == HEREDOC)
        {
            redirection_node = create_redirection_node(tokens);
            if (root)
                link_redirection_to_tree(root, redirection_node);
            else
                root = redirection_node;
        }
        tokens = tokens->next;
    }
    return (root);
}

t_token *split_tokens(t_token *tokens, t_token *operator_token)
{
    if (!tokens || !operator_token)
        return (tokens);
    t_token *current;

    current = tokens;

    while(current && current->next != operator_token)
        current = current->next;
    if (current)
        current->next = NULL;
    return (tokens);
}

void print_tree(t_tree *node, int caller)
{
    if (!node)
        return;
    if (caller == 0)
        printf("ROOT->Node: %s, Type: %d\n", node->word, node->word_token);
    else if (caller == 1)
        printf("left->Node: %s, Type: %d\n", node->word, node->word_token);
    else if (caller == 2)
        printf("right->Node: %s, Type: %d\n", node->word, node->word_token);
    print_tree(node->left, 1);
    print_tree(node->right, 2);
}