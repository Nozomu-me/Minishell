/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:23 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 11:14:54 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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