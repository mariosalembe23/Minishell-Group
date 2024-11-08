/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:25:15 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:30:38 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_verify_signals(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("Erro ao configurar manipulador de SIGINT");
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Erro ao configurar manipulador de SIGQUIT");
		exit(1);
	}
}
