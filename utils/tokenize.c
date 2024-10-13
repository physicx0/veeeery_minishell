/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:16:11 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 13:44:24 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_initializer(t_tokenizer word_token, char *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->word_token = word_token;
	token->word = ft_strdup(word);
	token->next = NULL;
	return (token);
}

t_tokenizer	identifier(char *word)
{
	if (!ft_strcmp(word, "|"))
		return (PIPE);
	else if (!ft_strcmp(word, ">"))
		return (OW_REDIRECTION);
	else if (!ft_strcmp(word, ">>"))
		return (APP_REDIRECTION);
	else if (!ft_strcmp(word, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(word, "<"))
		return (IN_OPERATOR);
	else if (word[0] == 39)
		return (SQ_STRING);
	else if (word[0] == 34)
		return (DQ_STRING);
	return (STRING);
}

char	**appender(char **string, int delimiter, int i_word)
{
	t_append	ap;

	ap.i = 0;
	ap.y = 0;
	ap.size = word_count(string);
	append_alloc_cp(&ap, string, delimiter, i_word);
	if (string[delimiter][i_word + 1])
	{
		ap.orgnized_one[ap.i] = ft_substr(string[delimiter], i_word
				+ ft_strlen(ap.orgnized_one[ap.i - 1]),
				ft_strlen(string[delimiter]));
		ap.i++;
	}
	while (string[ap.y])
	{
		ap.orgnized_one[ap.i] = ft_strdup(string[ap.y]);
		ap.i++;
		ap.y++;
	}
	ap.orgnized_one[ap.i] = NULL;
	return (ft_free(string, ap.size + 1), ap.orgnized_one);
}

char	*operation_returner(char *string, int i_word)
{
	if (string[i_word] == '>' && string[i_word + 1] != '>')
		return (">");
	else if (string[i_word] == '>' && string[i_word + 1] == '>')
		return (">>");
	else if (string[i_word] == '<' && string[i_word + 1] != '<')
		return ("<");
	else if (string[i_word] == '<' && string[i_word + 1] == '<')
		return ("<<");
	return ("|");
}

t_env	*new_link(char *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->env_line = ft_strdup(env);
	new_env->next = NULL;
	return (new_env);
}
