#include "../includes/minishell.h"

int	ft_strlen(const char *string)
{
	int i;
	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*malloca;
	size_t	i;
	size_t	y;

	y = 0;
	i = ft_strlen(str);
	malloca = (char *)malloc(sizeof(char) * (i + 1));
	if (malloca == NULL)
		return (NULL);
	while (y < i)
	{
		malloca[y] = str[y];
		y++;
	}
	malloca[y] = '\0';
	return (malloca);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*malloca;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	if (start > slen)
		len = 0;
	malloca = (char *)malloc(sizeof(char) * (len + 1));
	if (malloca == NULL)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		malloca[i] = s[i + start];
		i++;
	}
	malloca[i] = '\0';
	return (malloca);
}

int		ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i])
		i++;
	if (str1[i] != str2[i])
		return (1);
	return (0);
}

int	word_count(char **string)
{
	int count;

	count = 0;

	while (string[count])
		count++;
	return (count);
}