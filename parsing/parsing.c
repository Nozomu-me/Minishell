/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/23 11:29:57 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initail_struct(t_mini *mini)
{
	mini->check_env = "=~\\/%#{}$*+-.:?@[]^ \"'";
	mini->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	mini->splited_cmd = NULL;
	mini->under_score = ft_strdup("./minishell");
	mini->smbl->already_pipe = 0;
	mini->file_nme = NULL;
}

void	splitpipesemi(t_mini *mini)
{
	int		i;
	int 	j;
	char	**splitpipe;
	char	**splitsemi;

	i = 0;
	mini->glob.exit_pipe = 0;
	mini->glob.fd_in = 0;
	splitpipe = ft_split(mini->cmdline, '|');
	mini->splited_cmd = NULL;
	while (splitpipe[i] != NULL)
	{
		j = 0;
		splitsemi = ft_split(splitpipe[i], ';');
		while(splitsemi[j + 1] != NULL)
		{
			cf_lstadd_back(&mini->splited_cmd, cf_lst_new(ft_strdup(splitsemi[j]), END));
			j++;
		}
		if (splitpipe[i + 1] != NULL)
			cf_lstadd_back(&mini->splited_cmd, cf_lst_new(ft_strdup(splitsemi[j]), PIPE));
		else
			cf_lstadd_back(&mini->splited_cmd, cf_lst_new(ft_strdup(splitsemi[j]), END));
		free_tabl(splitsemi);
		i++;
	}
	free_tabl(splitpipe);
}
