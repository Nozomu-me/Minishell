/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:11:33 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 15:18:48 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sort_list(t_list *list)
{ 
    t_list    *tmp;
    t_list    *index;
    char *temp;
    int d;

    tmp = list;
    index = list;
    if(list == NULL)
        return;
    else
    {  
        while(tmp != NULL)
        {  
            index = tmp->next;  
            while(index != NULL)
            {
                d = ft_sort_str(tmp->content, index->content);
                if(d == 1)
                {
                    temp = tmp->content;  
                    tmp->content = index->content;  
                    index->content = temp;  
                }
                index = index->next;  
            }
            tmp = tmp->next;  
        }
    }  
}

void    print_list(t_list *list)
{
    t_list  *tmp;

    tmp = list;
    if (list == NULL)
        return ;
    else
    {
        while (tmp != NULL)
        {
            ft_putendl_fd(tmp->content, 1);
            tmp = tmp->next;
        }
    }
}

char    **list_to_tab(t_list *list)
{
    t_list      *tmp;
    char        **tab;
    int         i;

    tmp = list;
    i = 0;
    tab = malloc((ft_lstsize(tmp) + 1)*sizeof(char*));
    while (tmp != NULL)
    {
        tab[i] = strndup(tmp->content, ft_strlen(tmp->content) - 1);
        tmp = tmp->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

t_list      *init_list()
{
    t_list *list;

    list = malloc(sizeof(t_list));
    return (list);
}

int     find_pos(t_list *list, char *name)
{
    t_list      *tmp;
    int         pos;

    tmp = list;
    pos = 0;
    while (tmp != NULL)
    {
        if (strncmp(tmp->content, name, ft_strlen(name)) == 0)
            return (pos);
        pos++;
        tmp = tmp->next;
    }
    return -1;
}

void        delete_node(t_list *list, char *name) 
{
    int         i;
    int         position;
    t_list      *next;
    t_list      *temp;

    i = 0;
    position = find_pos(list, name);
    if (position == -1)
        return ;    
    if (list == NULL) 
        return; 
    temp = list; 
    if (position == 0) 
    { 
        list = temp->next;
        free(temp);
        return; 
    } 
    while (temp!=NULL && i < position -1 )
    {
         temp = temp->next;
         i++;
    }
    if (temp == NULL || temp->next == NULL) 
         return; 
    next = temp->next->next; 
    free(temp->next);  
    temp->next = next; 
}