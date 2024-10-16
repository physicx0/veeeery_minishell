/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:16:04 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/15 23:38:50 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fla_helper(t_token *head, t_env *env, t_fla *var_f, t_glob *glob)
{
	fla_helper_1(head, env, var_f);
	if ((var_f->closed == 1) && var_f->current->word[var_f->i] == '$'
		&& var_f->current->word[var_f->i + 1] != '$'
		&& var_f->current->word[var_f->i + 1] != 39
		&& var_f->current->word[var_f->i + 1] != 34
		&& var_f->current->word[var_f->i + 1] != ' '
		&& var_f->current->word[var_f->i + 1] != '\0')
	{
		var_f->exported = expand(var_f->current->word, env, var_f->i, glob);
		if (!var_f->exported)
		{
			var_f->current->word_token = EMPTY;
			var_f->current->word = ft_strdup("");
			var_f->current = head;
			var_f->flager = 1;
			return (1);
		}
		var_f->current->word = var_f->exported;
		var_f->current = head;
		var_f->flager = 1;
		return (1);
	}
	return (0);
}

void	expand_flager(t_token *head, t_env *env, t_glob *glob)
{
	t_fla	var_f;

	var_f.flager = 0;
	var_f.closed = 1;
	var_f.quote = 0;
	var_f.current = head;
	while (var_f.current)
	{
		var_f.i = 0;
		while (var_f.current->word[var_f.i])
		{
			if (fla_helper(head, env, &var_f, glob))
				break ;
			var_f.i++;
		}
		if (var_f.flager == 0)
			var_f.current = var_f.current->next;
		var_f.flager = 0;
	}
}
