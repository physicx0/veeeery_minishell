/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:55:33 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/13 18:16:03 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	setup_main_signals(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	main_sigint(int sigint)
{
	(void)sigint;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	hdoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
}
