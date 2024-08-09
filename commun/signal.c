/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:03 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:25:03 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signo) 											//gère Ctrl-c
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); 										//efface ligne actuelle
		rl_on_new_line();												//indique a readline de commencer une nouvelle ligne
		rl_redisplay();													//reaffiche minishell :
	}
}

void sigquit_handler(int signo)											//gère Ctrl-\ */
{
	// Ne rien faire pour ignorer le signal
}