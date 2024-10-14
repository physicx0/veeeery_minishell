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

char	*expan_helper_1(char *env_var, t_env *env, int i, t_expan *v_exp)
{
	v_exp->first_part = ft_substr(env_var, 0, i);
	v_exp->search = value_returner(v_exp->search, env);
	if (v_exp->search)
		return (free(v_exp->var), free(env_var), ft_strjoin(v_exp->first_part,
				v_exp->search));
	return (free(v_exp->var), free(env_var), (v_exp->first_part));
}

char	*expan_helper_2(char *env_var, t_env *env, int i, t_expan *v_exp)
{
	v_exp->first_part = ft_substr(env_var, 0, i);
	v_exp->search = value_returner(v_exp->search, env);
	if (v_exp->search)
	{
		v_exp->second_part = ft_substr(env_var, ft_strlen(v_exp->first_part)
				+ ft_strlen(v_exp->var) + 1, ft_strlen(env_var));
		return (free(v_exp->var), free(env_var),
			ft_strjoin(ft_strjoin(v_exp->first_part, v_exp->search),
				v_exp->second_part));
	}
	v_exp->second_part = ft_substr(env_var, ft_strlen(v_exp->first_part)
			+ ft_strlen(v_exp->var) + 1, ft_strlen(env_var));
	return (free(v_exp->var), free(env_var), ft_strjoin(v_exp->first_part,
			v_exp->second_part));
}

char	*expand(char *env_var, t_env *env, int i)
{
	t_expan	v_exp;

	v_exp.search = ft_substr(env_var, i + 1, env_length(&env_var[i + 1]));
	v_exp.var = ft_strdup(v_exp.search);
	if (!env_var[i + ft_strlen(v_exp.search) + 1] && i != 0)
		return (expan_helper_1(env_var, env, i, &v_exp));
	else if (env_var[i + ft_strlen(v_exp.search) + 1] && i != 0)
		return (expan_helper_2(env_var, env, i, &v_exp));
	else if (i == 0 && !env_var[i + ft_strlen(v_exp.search) + 1])
	{
		v_exp.search = value_returner(v_exp.search, env);
		if (v_exp.search)
			return (free(v_exp.var), free(env_var), (v_exp.search));
		return (free(v_exp.var), free(env_var), NULL);
	}
	v_exp.search = value_returner(v_exp.search, env);
	v_exp.first_part = ft_substr(env_var, ft_strlen(v_exp.var) + 1,
			ft_strlen(env_var));
	if (v_exp.search)
		return (free(v_exp.var), free(env_var), ft_strjoin(v_exp.search,
				v_exp.first_part));
	return (free(v_exp.var), free(env_var), v_exp.first_part);
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
			if (current->word[i] == 39 && closed == 1 && current->word[i
				- 1] != '\\')
				closed = 0;
			else
			{
				if (current->word[i] == 39 && current->word[i - 1] != '\\')
					closed = 1;
			}
			if ((closed == 1) && current->word[i] == '$' && current->word[i
				- 1] != '\\' && current->word[i + 1] != '$')
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
