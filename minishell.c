/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:07:57 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 12:08:32 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	has_other_delimiter(char *command)
// {
// 	int			i;
// 	const char	*operators[] = {"|", ">>", "<<", ">", "<", NULL};
// 	int			len;
// 	int			j;

// 	i = -1;
// 	while (command[++i] != '\0')
// 	{
// 		j = 0;
// 		while (operators[j] != NULL)
// 		{
// 			len = strlen(operators[j]);
// 			if (strncmp(&command[i], operators[j], len) == 0)
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static int	choose_command(t_general *general, char **commands, t_env **env)
{
	if (general->initial_command[0] == '\0')
		return (1);
	else if (ft_strcmp(commands[0], "echo") == 0)
		return (ft_echo(commands, env));
	else if (ft_strcmp(commands[0], "pwd") == 0)
		return (ft_pwd(commands));
	else if (ft_strcmp(commands[0], "cd") == 0)
		return (ft_cd(commands));
	else if (ft_strcmp(commands[0], "env") == 0)
		return (ft_env(commands, general->envs, env));
	else if (ft_strcmp(commands[0], "export") == 0)
		return (ft_export(commands, general->envs, env));
	else if (ft_strcmp(commands[0], "unset") == 0)
		return (ft_unset(general->commands, env, general->envs));
	else if (ft_strcmp(commands[0], "exit") == 0)
		return (ft_exit(general));
	else
		return (ft_any_command());
	return (0);
}

static int	ft_execution(t_general *general, t_env **env)
{
	char	**commands;
	t_token	*head;
	
	head = NULL;
	//if (has_other_delimiter(general->initial_command))
	//{
		tokenize(general->initial_command, &head);
		exec_command(&head);
		return (1);
	//}
	general->commands = ft_split(general->initial_command, ' ');
	commands = general->commands;
	if (!choose_command(general, commands, env))
		return (0);
	return (1);
}

static void	init_proccess(t_general *general, t_env **env)
{
	while (1)
	{
		general->initial_command = readline("\033[1;36mminishell$ \033[1;0m");
		if (general->initial_command)
		{
			add_history(general->initial_command);
			if (!ft_execution(general, env))
			{
				printf("ERROR\n");
				exit(1);
			}
			free(general->initial_command);
		}
		else
		{
			free(general->initial_command);
			exit(1);
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;
	t_general	general;


	(void)ac;
	(void)av;
	general.env = NULL;
	ft_verify_signals(av, ac);
	ft_copy_vars(&general, ev);
	init_proccess(&general, &env);
}
