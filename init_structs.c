/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:50:04 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/03 17:56:21 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    init_builtins(t_builtins *builtins, char **env)
{
	builtins->cd_path = NULL;
	builtins->env = set_environ(env);
	// builtins->export = NULL;
}

void    free_builtins(t_builtins *builtins)
{
	if(builtins->cd_path != NULL)
	    free(builtins->cd_path);
	free_tab(builtins->env);
}
