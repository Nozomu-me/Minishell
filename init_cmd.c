/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:07:47 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/17 14:44:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_cmds(t_cmds *cmds, char *buf)
{
    char    **splitpipe;
    int     i;

    i = 0;
    printf("%s\n", buf);
    cmds->cmd = ft_split(buf, ' ');
    printf("cmd[0]=%s\n", cmds->cmd[0]);
    printf("cmd[1]=%s\n", cmds->cmd[1]);
    // while(splitpipe[i] != NULL)
    // {
    //     // if (splitpipe[i + 1] != NULL)
    //     //     cmds->type = PIPE;
    //     // cmds->cmd = ft_split(splitpipe[i], ' ');
    //     cmds->cmd
    //     i++;
    // }
}

void init_cmd(t_cmds *cmds)
{
    cmds->file = NULL;
    cmds->file = cf_lst_new("amal", READ);
    cf_lstadd_back(&cmds->file, cf_lst_new("test3", WRITE));
    // cf_lstadd_back(&cmds->file, cf_lst_new("t2", READ));
    cf_lstadd_back(&cmds->file, cf_lst_new("test4", WRITE));
    cf_lstadd_back(&cmds->file, cf_lst_new("test5", APPEND));
}

void inito(t_mini *mini, char *cmd)
{
    char **split;
    int i = 0;
    int j =0;
    // mini->cmds.cmd = NULL;
    mini->cmds.file = NULL;
    split = ft_split(cmd, ' ');
    while(split[j] != NULL && ft_strcmp(split[j] ,">") != 0 && ft_strcmp(split[j] ,">>") != 0 && ft_strcmp(split[j] ,"<") != 0)
    {
        // printf("|%s|\n",mini->cmds.cmd[i]);
        j++;
    }
    // printf("j=%d\n", j);
    mini->cmds.cmd = malloc((j + 1)*sizeof(char *));
    while(split[i] != NULL && ft_strcmp(split[i] ,">") != 0 && ft_strcmp(split[i] ,">>") != 0 && ft_strcmp(split[i] ,"<") != 0)
    {
        mini->cmds.cmd[i] = ft_strdup(split[i]);
        // printf("|%s|\n",mini->cmds.cmd[i]);
        i++;
    }
    mini->cmds.cmd[i] = NULL;
    while(split[i] != NULL)
    {
        if (ft_strcmp(split[i], ">>") == 0)
        {
            cf_lstadd_back(&mini->cmds.file, cf_lst_new(ft_strdup(split[i + 1]), APPEND));
        }
        if (ft_strcmp(split[i], ">") == 0)
        {

            cf_lstadd_back(&mini->cmds.file, cf_lst_new(ft_strdup(split[i + 1]), WRITE));
        }
        if (ft_strcmp(split[i], "<") == 0)
        {

            cf_lstadd_back(&mini->cmds.file, cf_lst_new(ft_strdup(split[i + 1]), READ));
        }
        i++;
    }
    free_tabl(split);
    // printf("inito done\n")
    // cf_lstprint(mini->cmds.file);
}