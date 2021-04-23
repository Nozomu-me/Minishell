/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/23 11:24:14 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env_element(t_env *curr_node, char *env)
{
	int		len;

	len = 0;
	while (env[len] != '=')
		len++;
	curr_node->name = ft_substr(env, 0, len);
	curr_node->value = ft_strdup(env + len + 1);
	curr_node->next = NULL;
}

void	initail_struct(t_mini *mini)
{
	mini->check_env = "=~\\/%#{}$*+-.:?@[]^ \"'";
	mini->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	mini->scmd = NULL;
	mini->under_score = ft_strdup("./minishell");
	mini->smbl->already_pipe = 0;
	mini->s_semi = NULL;
	mini->s_pipe = NULL;
	mini->file_nme = NULL;
}

void	help_splitpipesemi(t_mini *mini, char *semi, char *pipe)
{
	if (pipe != NULL)
		cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi), PIPE));
	else
		cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi), END));
}

void	splitpipesemi(t_mini *mini)
{
	int		i;
	int		j;
	char	**pipe;
	char	**semi;

	i = 0;
	mini->glob.exit_pipe = 0;
	mini->glob.fd_in = 0;
	pipe = ft_split(mini->cmdline, '|');
	mini->scmd = NULL;
	while (pipe[i] != NULL)
	{
		j = 0;
		semi = ft_split(pipe[i], ';');
		while (semi[j + 1] != NULL)
		{
			cf_lstadd_back(&mini->scmd, cf_lst_new(ft_strdup(semi[j]), END));
			j++;
		}
		help_splitpipesemi(mini, semi[j], pipe[i + 1]);
		free_tabl(semi);
		i++;
	}
	free_tabl(pipe);
}
