/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:16:06 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/21 11:45:01 by amouassi         ###   ########.fr       */
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

void    env_lstdelone(t_env *lst, void (*del)(void*))
{
    if (!lst || !del)
        return ;
    del(lst->name);
    del(lst->value);
    free(lst);
}
void    env_lstclear(t_env **lst, void (*del)(void*))
{
    t_env   *temp;
    if (!lst || !*lst || !del)
        return ;
    while (*lst != NULL)
    {
        temp = *lst;
        *lst = (*lst)->next;
        env_lstdelone(temp, del);
    }
    *lst = NULL;
}