/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:15:40 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 11:54:33 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand(char *env_var, t_env *env, int i)
{
	char	*search;
	char	*first_part;
	char	*second_part;
	char	*var;

	search = ft_substr(env_var, i + 1, env_length(&env_var[i + 1]));
	var = ft_strdup(search);
	if (!env_var[i + ft_strlen(search) + 1] && i != 0)
	{
		first_part = ft_substr(env_var, 0, i);
		search = value_returner(search, env);
		if (search)
			return (free(var), free(env_var), ft_strjoin(first_part, search));
		return (free(var), free(env_var), (first_part));
	}
	else if (env_var[i + ft_strlen(search) + 1] && i != 0)
	{
		first_part = ft_substr(env_var, 0, i);
		search = value_returner(search, env);
		if (search)
		{
			second_part = ft_substr(env_var, ft_strlen(first_part)
					+ ft_strlen(var) + 1, ft_strlen(env_var));
			return (free(var), free(env_var), ft_strjoin(ft_strjoin(first_part,
						search), second_part));
		}
		second_part = ft_substr(env_var, ft_strlen(first_part) + ft_strlen(var)
				+ 1, ft_strlen(env_var));
		return (free(var), free(env_var), ft_strjoin(first_part, second_part));
	}
	else if (i == 0 && !env_var[i + ft_strlen(search) + 1])
	{
		search = value_returner(search, env);
		if (search)
			return (free(var), free(env_var), (search));
		return (free(var), free(env_var), NULL);
	}
	search = value_returner(search, env);
	first_part = ft_substr(env_var, ft_strlen(var) + 1, ft_strlen(env_var));
	if (search)
		return (free(var), free(env_var), ft_strjoin(search, first_part));
	return (free(var), free(env_var), first_part);
}

void	expand_flager(t_token *head, t_env *env)
{
	t_token	*current;
	int		i;
	char	quote;
	int		closed;
	char	*exported;
	int		flager;

	flager = 0;
	closed = 1;
	quote = 0;
	current = head;
	while (current)
	{
		i = 0;
		while (current->word[i])
		{
			if (current->word[i] == 39 && closed == 1 && current->word[i - 1] != '\\')
				closed = 0;
			else
			{
				if (current->word[i] == 39 && current->word[i - 1] != '\\')
					closed = 1;
			}
			if ((closed == 1) && current->word[i] == '$'
				&& current->word[i - 1] != '\\' && current->word[i + 1] != '$')
			{
				exported = expand(current->word, env, i);
				if (!exported)
				{
					current->word_token = EMPTY;
					current->word = ft_strdup("");
					current = head;
					flager = 1;
					break ;
				}
				current->word = exported;
				current = head;
				flager = 1;
				break ;
			}
			i++;
		}
		if (flager == 0)
			current = current->next;
		flager = 0;
	}
}
