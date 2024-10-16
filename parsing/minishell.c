/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:05 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:37:28 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_var = 0;

t_tree	*parsing_entry(char *parse_string, t_glob *glob)
{
	t_entry	var_ent;

	add_history(parse_string);
	if (!parse_string)
		exit(1);
	else if (syntax_checker(parse_string))
	{
		printf("syntax error\n");
		glob->exit_status = 2;
		free(parse_string);
		return (NULL);
	}
	entry_helper(&var_ent, glob, parse_string);
	if (g_var)
	{
		free(parse_string);
		link_free(var_ent.head);
		link_free(var_ent.prev);
		return (NULL);
	}
	var_ent.root = parse(var_ent.head, 0);
	link_free(var_ent.head);
	link_free(var_ent.prev);
	return (var_ent.root);
}

int	trim_flager(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == 34 || string[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	content_trima(t_token *head)
{
	t_trim	trim;
	char	c;

	c = 0;
	trim.closed = 1;
	trim.i = 0;
	trim.current = head;
	while (trim.current)
	{
		trim.y = 0;
		trim.i = 0;
		if (trim_flager(trim.current->word))
		{
			trim.trimed = malloc(ft_strlen(trim.current->word) + 1);
			while (trim.current->word[trim.i])
			{
				trim_whiler(&trim, &c);
				trim.i++;
			}
			trim.trimed[trim.y] = '\0';
			free(trim.current->word);
			trim.current->word = trim.trimed;
		}
		trim.current = trim.current->next;
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
