/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/03 17:55:18 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *ft_strndup(char *s, size_t len)
{
    size_t     i;
    char    *str;

    i = 0;
    str = malloc((len + 1)*sizeof(char));
    while(i < len)
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

char    *ft_strncpy(char *str, int n)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc((ft_strlen(str) - 1)*sizeof(char));
	while(i < n)
	{
		s[i] = str[i];
		i++;
	}
	return (s);
}

int     ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] != '\0' || s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}

int		ft_maxlen(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(s1[i]!='\0')
		i++;
	while(s2[j] != '\0')
		j++;
	if ( i > j)
		return (i);
	else
		return (j);
}

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
      if (strstr(&str[i], org) == &str[i]) {
         count++;
         i += len2 - 1;
      }
      i++;
   }
   new = (char *)malloc(i + count * (len1 - len2) + 1);
   i = 0;
   while (*str) {
      if (ft_strnstr(str, org, ft_strlen(str)) == str) {
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

t_export		*ft_lstnew(void *var)
{
	t_export	*head;

	head = (t_export *)malloc(sizeof(t_export));
	if (head == NULL)
		return (NULL);
	head->var = var;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back(t_export **alst, t_export *new)
{
	t_export		*temp;

	if (!alst || !new)
		return ;
	temp = *alst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}

int		ft_lstsize(t_export *lst)
{
	t_export	*temp;
	int		size;

	if (!lst)
		return (0);
	temp = lst;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

void	ft_lstclear(t_export *lst)
{
	t_export	*temp;

	if (!lst || !lst)
		return ;
	while (lst != NULL)
	{
		free(lst->var);
		free(lst);
		lst = lst->next;
	}
	lst = NULL;
}

void	ft_lstdelone(t_export *lst)
{
	if (!lst)
		return ;
	free(lst->var);
	free(lst);
}