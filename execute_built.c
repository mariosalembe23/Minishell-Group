/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:18:55 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:20:18 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_echo(char **commands, int sig)
{
    if (sig)
        exit(ft_echo(commands, sig));
    return ft_echo(commands, sig);
}

int execute_pwd(char **commands, int sig)
{
    if (sig)
        exit(ft_pwd(commands, sig));
    return ft_pwd(commands, sig);
}

int execute_cd(char **commands, int sig)
{
    if (sig)
        exit(ft_cd(commands, sig));
    return ft_cd(commands, sig);
}

int execute_env(char **commands, t_general *general, int sig)
{
    if (sig)
        exit(ft_env(commands, general->var, sig));
    return ft_env(commands, general->var, sig);
}

int execute_export(char **commands, t_general *general, int sig)
{
    if (sig)
        exit(ft_export(commands, general, sig));
    return ft_export(commands, general, sig);
}

int execute_unset(char **commands, t_general *general, int sig)
{
    if (sig)
        exit(ft_unset(commands, general->var));
    return ft_unset(commands, general->var);
}

int execute_exit(t_general *general, int sig, char **commands)
{
    exit(ft_exit(general, sig, commands));
}
