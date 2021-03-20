/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:11:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 14:08:33 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_cmd(t_minishell *mini)
{
    if (check_isbuiltin(mini->cmd[0]) == 1)
        execute_builtins(mini);
    else
        execute_shell(mini);
}