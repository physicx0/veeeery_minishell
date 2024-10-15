/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_II.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:54:15 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/13 20:54:07 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)(haystack));
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[j + i] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i + j + 1));
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	if (*s == '\0' && (char)c == '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		if (*s == '\0' && (char)c == '\0')
			return ((char *)s);
	}
	return (NULL);
}

char	*exec_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ptr = malloc(l1 + l2 + 2);
	if (!ptr)
		return (NULL);
	while (i < l1)
		ptr[j++] = s1[i++];
	ptr[j++] = '/';
	i = 0;
	while (i < l2)
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n - 1
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	return (0);
}
