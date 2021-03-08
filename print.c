/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:51:36 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 14:34:04 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sub_print_export(char *s)
{
    char    **split;
    
}

void sort_list(t_export *export)
{ 
    t_export    *tmp;
    t_export    *index;
    char *temp;
    int d;

    tmp = export;
    index = export;
    if(export == NULL)
        return;
    else
    {  
        while(tmp != NULL)
        {  
            index = tmp->next;  
            while(index != NULL)
            {
                d = ft_sort_str(tmp->var, index->var);
                if(d == 1)
                {  
                    temp = tmp->var;  
                    tmp->var = index->var;  
                    index->var = temp;  
                }  
                index = index->next;  
            }  
            tmp = tmp->next;  
        }      
    }  
}

int     check_caract(char *str, char c)
{
    int     i;
    int     check;
    
    i = 0;
    check = 0;
    while(str[i] != '\0')
    {
        if (str[i] == c)
            check++;
        i++;
    }
    return (check);
}

void    print_export(t_builtins *builtins)
{
    int     i;
	char		**split;
	t_export	*tmp;
    int         check;
    tmp = builtins->export;
	while(tmp != NULL)
    {
        i = 0;
        split = ft_split(tmp->var, '=');
        while(split[i] != NULL)
            i++;
        if(i == 2)
        {
            check = check_caract(split[1], '\"');
            if (check != 2)
                printf("declare -x %s=\"%s\"\n", split[0], split[1]);
            else 
                printf("declare -x %s=%s\n", split[0], split[1]);
        }
        else
            printf("declare -x %s\n", split[0]);
        tmp = tmp->next;
        free_tab(split);
    }
}