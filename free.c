/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:16:06 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/18 15:46:17 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabl(char **s)
{
	int		i;

	i = 0;
	while(s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_mini(t_mini *mini)
{
	ft_lstclear(&mini->env, free);
	ft_lstclear(&mini->export_env, free);
	ft_lstclear(&mini->unset, free);
	if (mini->splited_cmd != NULL)
		cf_lstclear(&mini->splited_cmd, free);
	if (mini->cmds.file != NULL)
		cf_lstclear(&mini->cmds.file, free);
	if (mini->history != NULL)
		ft_lstclear(&mini->history, free);
	free_tabl(mini->glob.home);
	if (mini->glob.oldpwd != NULL)
		free(mini->glob.oldpwd);
}