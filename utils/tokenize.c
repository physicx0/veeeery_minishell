#include "../includes/minishell.h"

t_token *token_initializer(t_tokenizer word_token, char *word)
{
	t_token *token;
	token = malloc(sizeof(t_token));
	token->word_token = word_token;
	token->word = ft_strdup(word);
	token->next = NULL;
	return (token);
}

t_tokenizer identifier(char *word)
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

char **appender(char **string, int delimiter, int i_word)
{
	int i;
	char **orgnized_one;
	int size;
	int y;
	size = word_count(string);
	if (i_word == 0 || !string[delimiter][i_word + 1])
		orgnized_one = (char **)malloc(sizeof(char *) * (size + 2));
	else
		orgnized_one = (char **)malloc(sizeof(char *) * (size + 3));
	i = 0;
	y = 0;

	while (i < delimiter)
	{
		orgnized_one[i] = ft_strdup(string[y]);
		i++;
		y++;
	}
	y++;
	if (i_word != 0)
	{
		orgnized_one[i] = ft_substr(string[delimiter], 0, i_word);
		i++;
	}
	orgnized_one[i] = ft_strdup(operation_returner(string[delimiter], i_word));
	i++;

	if (string[delimiter][i_word + 1])
	{
		orgnized_one[i] = ft_substr(string[delimiter], i_word + ft_strlen(orgnized_one[i - 1]), ft_strlen(string[delimiter]));
		i++;
	}
	while (string[y])
	{
		orgnized_one[i] = ft_strdup(string[y]);
		i++;
		y++;
	}
	orgnized_one[i] = NULL;
	return (ft_free(string, size + 1), orgnized_one);
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

char	**env_dup(char **env)
{
	int i;
	char **env_dup;

	i = word_count(env);
	env_dup = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while(env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	env_dup[i] = NULL;
	return (env_dup);
}
