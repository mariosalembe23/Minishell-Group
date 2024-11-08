/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:16:59 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:32:13 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_with_flag(char **input)
{
	int	i;

	i = 2;
	while (input[i])
	{
		if (input[i + 1] != NULL)
			printf("%s ", input[i]);
		else
			printf("%s", input[i]);
		i++;
	}
}

static void	execute_without_flag(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (input[i + 1] != NULL)
			printf("%s ", input[i]);
		else
			printf("%s\n", input[i]);
		i++;
	}
}

static void	ft_echo_utils(int has_flag, char **input)
{
	if (!has_flag)
		execute_with_flag(input);
	else
		execute_without_flag(input);
	write_in_file(0);
}

int	ft_echo(char **commands, int sig)
{
	int		has_flag;
	char	**input;
	int		i;
	int		x;

	has_flag = 0;
	input = commands;
	i = 1;
	if (sig == 0)
		return (0);
	if (!input[i])
		return (printf("\n"));
	if (input[i][0] == '-')
	{
		x = 0;
		while (input[i][++x])
		{
			if (input[i][x] != 'n')
				has_flag = 1;
		}
	}
	else
		has_flag = 1;
	ft_echo_utils(has_flag, input);
	return (0);
}
