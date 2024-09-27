/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:05 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:48:54 by bbelarra42       ###   ########.fr       */
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
	int i = 0;
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

int	trim_flager(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (string[i] == 34 || string[i] == 39 || string[i] == '\\')
			return 1;
		i++;
	}
	return 0;
}

void	content_trimer(t_token *head)
{
	t_token	*current;
	int		i;
	int		y;
	char	*trimed;
	int     closed;

    closed = 1;
	i = 0;
	current = head;
	while (current)
	{
		y = 0;
		i = 0;
		if (trim_flager(current->word))
		{
			trimed = malloc(ft_strlen(current->word) + 1);
			while (current->word[i])
			{
                if ((current->word[i] == 39) && closed == 1 && current->word[i - 1] == '\\')
                    closed = 0;
                else
                {
                    if (current->word[i] == 39)
                        closed = 1;
                }
				if (current->word[i] != '\\' && current->word[i] != 39 || (current->word[i] == 39 && current->word[i - 1] == '\\'))
				{
					if (current->word[i] == 34 && closed == 0)
					{
						trimed[y] = current->word[i];
						y++;
					}
					else if (current->word[i] != 34)
					{
						trimed[y] = current->word[i];
						y++;
					}
				}
				i++;
			}
			trimed[y] = '\0';
			free(current->word);
			current->word = trimed;
		}
		current = current->next;
	}
}

t_token	*lexer(char **organized_input)
{
	t_tokvar	tok_var;

	tok_var.i = 0;
	tok_var.head = NULL;
	while (organized_input[tok_var.i])
	{
		tok_var.word_token = identifier(organized_input[tok_var.i]);
		tok_var.new_token = token_initializer(tok_var.word_token,
				organized_input[tok_var.i]);
		if (!tok_var.head)
		{
			tok_var.head = tok_var.new_token;
			tok_var.current = tok_var.new_token;
		}
		else
		{
			tok_var.current->next = tok_var.new_token;
			tok_var.current = tok_var.new_token;
		}
		free(organized_input[tok_var.i]);
		tok_var.i++;
	}
	free(organized_input[tok_var.i]);
	free(organized_input);
	return (tok_var.head);
}
