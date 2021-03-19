/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:34:24 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 15:48:05 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void printList(t_list *node) 
// { 
//     while (node != NULL) 
//     { 
//         printf(" %d ", node->content); 
//         node = node->next; 
//     } 
// } 

t_list   *init_env(char **environ)
{
    t_list   *env;
    int     i;

    i = 1;
    env = ft_lstnew(strdup(environ[0]));
    while(environ[i] != NULL)
    {
        // if (strncmp(environ[i], "OLDPWD", 6) != 0)
            ft_lstadd_back(&env, ft_lstnew(strdup(environ[i])));
        i++;
    }
    return (env);
}


void    print_list(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        printf("%s\n",tmp->content);
        tmp = tmp->next;
    }
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

char    **list_to_tab(t_list *list)
{
    t_list      *tmp;
    char        **tab;
    int         i;

    tmp = list;
    i = 0;
    tab = malloc(ft_lstsize(tmp)*sizeof(char*));
    while (tmp != NULL)
    {
        tab[i] = strndup(tmp->content, ft_strlen(tmp->content) - 1);
        tmp = tmp->next;
        i++;
    }
    return (tab);
}

int main()
{
    extern char **environ;
    t_list *env;
    char **tab;
    int pos;
    int size;
    
    env = init_env(environ);
    size = ft_lstsize(env);
    tab = list_to_tab(env);
    pos = 0;
    while(pos< size)
    {
        printf("%s\n",tab[pos]);
        pos++;
    }
    // print_list(env);
    // delete_node(env, "amal");
    // remove_node(env);
    // deleteNode(env,pos);
    // print_list(env);
}
