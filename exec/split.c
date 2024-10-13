/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:00:20 by amaaouni          #+#    #+#             */
/*   Updated: 2024/09/23 03:06:59 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ptr_count(const char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			count++;
		i++;
		if (!str[i])
			count++;
	}
	return (count);
}

static char	**split_free(char **ary, int index)
{
	while (index >= 0)
	{
		free(ary[index]);
		index--;
	}
	free(ary);
	return (NULL);
}

static char	*find_sub(const char *s, char c, int *p_to_len)
{
	char		*array;
	const char	*ptr;
	size_t		end;

	end = 0;
	while (*s && *s == c)
	{
		(*p_to_len)++;
		s++;
	}
	ptr = s;
	while (*s && *s != c)
	{
		s++;
		(*p_to_len)++;
		end++;
	}
	array = ft_substr(ptr, 0, end);
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;
	int		i;
	int		*p_to_len;
	int		len;

	p_to_len = &len;
	len = 0;
	i = 0;
	if (!s)
		return (NULL);
	count = ptr_count(s, c);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (*s && count)
	{
		array[i] = find_sub(s + len, c, p_to_len);
		if (!array[i])
			return (split_free(array, i));
		i++;
		count--;
	}
	array[i] = NULL;
	return (array);
}
