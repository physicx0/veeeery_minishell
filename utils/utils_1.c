#include "../includes/minishell.h"

static void	little_copy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static void	little_conca(char *dst, const char *src)
{
	size_t	dlen;
	int		i;

	i = 0;
	dlen = ft_strlen(dst);
	while (src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*malloca;

	if (!s1 || !s2)
		return (NULL);
	if (*s1 == '\0' && *s2 == '\0')
	{
		malloca = (char *)malloc(1);
		if (malloca == NULL)
			return (NULL);
		*malloca = '\0';
		return (malloca);
	}
	total_len = ft_strlen(s1) + ft_strlen(s2);
	malloca = (char *)malloc(sizeof(char) * (total_len + 1));
	if (malloca == NULL)
		return (NULL);
	little_copy(malloca, s1);
	little_conca(malloca, s2);
	malloca[total_len] = '\0';
	return (malloca);
}