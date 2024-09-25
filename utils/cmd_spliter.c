#include "../includes/minishell.h"

static size_t	sub_counter(char const *s, char delimiter)
{
	size_t	words;
	int		i;
    int     closed;
    char    quote;

    quote = 0;
    closed = 1;
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != delimiter)
		{
			while (s[i] && s[i] != delimiter)
            {
                if ((s[i] == 39 || s[i] == 34) && closed == 1)
                {
                    closed = 0;
                    quote = s[i];
                }
                else
                {
                    if (s[i] == quote)
                        closed = 1;
                }
                i++;
            }
            if (closed == 1)
                words++;
		}
		else if (s[i] == delimiter)
			i++;
	}
	return (words);
}

static size_t	substring_len(char const *s, char delimiter)
{
	size_t  i;
    int     closed;
    char    quote;

    quote = 0;
    closed = 1;
	i = 0;
	while (s[i])
    {
        if (s[i] == delimiter && closed == 1)
            break;
        if ((s[i] == 39 || s[i] == 34) && closed == 1)
        {
            closed = 0;
            quote = s[i];
        }
        else
        {
            if (s[i] == quote)
                closed = 1;
        }
        i++;
    }
	return (i);
}

void    ft_free(char **substring, size_t i)
{
	while (i > 0)
	{
		i--;
		free(substring[i]);
	}
	free(substring);
}

static char	**sub_filler(char const *s, char delimiter, char **substring,
		size_t sub_counts)
{
	size_t	i;
	size_t	y;
    char    quote;
    int     closed;

    quote = 0;
    closed = 1;
	i = 0;
	y = 0;
	while (i < sub_counts)
	{
		while (s[y] && s[y] == delimiter && closed == 1)
            y++;
		substring[i] = ft_substr(s, y, substring_len(&s[y], delimiter));
		if (!substring[i])
		{
			ft_free(substring, i);
			return (NULL);
		}
		while (s[y])
        {
            if (s[y] == delimiter && closed == 1)
                break;
            if ((s[y] == 39 || s[y] == 34) && closed == 1)
            {
                closed = 0;
                quote = s[y];
            }
            else
            {
                if (s[y] == quote)
                    closed = 1;
            }
            y++;
        }
		i++;
	}
	substring[i] = NULL;
	return (substring);
}

char	**commands_spliter(char const *s, char c)
{
	char	**malloca;
	size_t	sub_strings;

	if (!s)
		return (NULL);
	sub_strings = sub_counter(s, c);
	malloca = (char **)malloc(sizeof(char *) * (sub_strings + 1));
	if (!malloca)
		return (NULL);
	malloca = sub_filler(s, c, malloca, sub_strings);
	return (malloca);
}