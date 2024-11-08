/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:07:57 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:03:12 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int	ft_execution(t_general *general)
{
	t_token	*head;

	head = NULL;
	general->commands = ft_split(general->initial_command, ' ');
	tokenize(general->initial_command, &head);
	if (process_command(&head))
		return (1);
	exec_command(&head, general);
	return (1);
}

static int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	init_proccess(t_general *general)
{
	while (1)
	{
			general->initial_command = readline("\033[1;36mminishell$ \033[1;0m");
		if (general->initial_command == NULL)
		{
			ft_exit(general, 1, general->commands);
			exit(0);
		}
		if (is_empty(general->initial_command))
		{
			free(general->initial_command);
			continue ;
		}
		add_history(general->initial_command);
		if (!ft_execution(general))
		{
			free(general->initial_command);
			exit(1);
		}
		free(general->initial_command);
	}
}

void	ft_add_var(t_var **var, char **ev)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (ev[i])
	{
		key = find_key(ev[i]);
		value = find_value(ev[i]);
		if (value == NULL)
			value = ft_strdup("");
		add_new_var(var, key, value);
		free(key);
		i++;
	}
}

int	main(int ac, char **av, char **ev)
{
	t_general	general;
	
	(void)ac;
	(void)av;
	general.var = malloc(sizeof(t_var *));
	ft_add_var(general.var, ev);
	if (access(".data", F_OK) == 0)
		write_in_file(0);
	ft_copy_vars(&general, ev);
	ft_verify_signals();
	init_proccess(&general);
}
