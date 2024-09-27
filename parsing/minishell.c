/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:05 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 11:54:09 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char	**our_env;

	our_env = env_dup(env);
	while (1)
		parsing_entry(readline("0xhb_shell$ "), our_env);
}

void	parsing_entry(char *parse_string, char **env)
{
	t_token	*head;
	t_tree	*root;
	char	**organized_input;

	if (!parse_string)
		exit(1);
	else if (syntax_checker(parse_string))
	{
		printf("syntax error\n");
		free(parse_string);
		return ;
	}
	organized_input = input_organizer(parse_string);
	head = lexer(organized_input);
	expand_flager(head, env);
	content_trimer(head);
	root = parse(head);
	print_tree(root, 0);
	link_free(head);
}

char	*trimed_returner(char *string)
{
	printf("(%s)\n", string);
	return (NULL);
}

void	content_trimer(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	while (current)
	{
		i = 0;
		while (current->word[i])
		{
			if ((current->word[i] == 34 || current->word[i] == 39) && i != 0
				&& current->word[i - 1] != '\\')
			{
				current->word = trimed_returner(current->word);
				trimed_returner(current->word);
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

t_token	*lexer(char **organized_input)
{
	int			i;
	t_token		*head;
	t_token		*current;
	t_token		*new_token;
	t_tokenizer	word_token;

	i = 0;
	head = NULL;
	while (organized_input[i])
	{
		word_token = identifier(organized_input[i]);
		new_token = token_initializer(word_token, organized_input[i]);
		if (!head)
		{
			head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
		free(organized_input[i]);
		i++;
	}
	free(organized_input[i]);
	free(organized_input);
	return (head);
}
