
#include "parsing.h"
#include <string.h>

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

/* int main()
{
	char *line = "\tkamal\thamid\tlatif";
	line = search_replace(line, "\t", " ");
	puts(line);
	return (0);
} */