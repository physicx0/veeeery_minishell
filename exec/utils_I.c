/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_I.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:44:54 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/13 20:53:03 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	strict_strncmp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2, ft_strlen(s2)))
		return (1);
	return (0);
}

void	ft_tolower(char *c)
{
	if (*c >= 65 && *c <= 90)
		*c += 32;
}

int	ft_isnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
