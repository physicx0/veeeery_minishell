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

void	entry_helper(t_entry *var_ent, t_glob *glob, char *parse_string)
{
	var_ent->organized_input = input_organizer(parse_string);
	var_ent->head = lexer(var_ent->organized_input);
	var_ent->prev = dup_head(var_ent->head);
	expand_flager(var_ent->head, *glob->env);
	content_trima(var_ent->head);
	here_doc(var_ent->head, glob, var_ent->prev);
}
