/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:23 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/18 15:36:07 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *search_replace(char *str, char *org, char *rep)
{
   int i;
   int count;
   int len1;
   int len2;
   char *new;

   count = 0;
   i = 0;
   len1 = ft_strlen(rep);
   len2 = ft_strlen(org);
   while(str[i] != '\0')
   {
      if (strstr(&str[i], org) == &str[i])
      {
         count++;
         i += len2 - 1;
      }
      i++;
   }
   new = (char *)malloc(i + count * (len1 - len2) + 1);
   i = 0;
   while (*str)
   {
      if (ft_strnstr(str, org, ft_strlen(str)) == str)
      {
         strcpy(&new[i], rep);
         i += len1;
         str += len2;
      }
      else
        new[i++] = *str++;
   }
   new[i++] = '\0';
   return (new);
}

int ft_sort_str(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while(s1[i] != '\0' && s2[i] != '\0')
    {
        if(s1[i] > s2[i])
        {
            return (1);
        }
        else if (s1[i] < s2[i])
            return (2);
        i++;
    }
    return (0);
}

void ft_sort_tab(char **tab)
{
    char *s;
    int d;
    int i=0;
    int j=0;

    while(tab[i]!= NULL)
    {
        j = 0;
        while(tab[j]!=NULL)
        {
            d = ft_sort_str(tab[i], tab[j]);
            if(d == 2)
            {
                s = tab[i];
                tab[i] = tab[j];
                tab[j] = s;
            }
            j++;
        }
        i++;
    }
}

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

t_list      *init_list()
{
    t_list *list;

    list = malloc(sizeof(t_list));
    return (list);
}