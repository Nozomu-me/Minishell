#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int 	count_back(char *line)
{
    int cp;

	cp = 0;
    while (*line == '\\')
    {
        cp++;
        line--;
	}
	if (cp % 2 == 0)
		return (1);
    return (0);
}

int		quote(char *line, char c)
{
	int i;
	// int cp;

	i = 0;
	// cp = 0;
	// while (line[i] != c)
	// 	i++;
	if (line[i] == c)
		while (line[++i])
			if (line[i] == c && line[i - 1] != '\\')
				break ;
	return i;
}

char    *get_word(char *line)
{
    char *word;

    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (line[i] && line[i] != '\'' && line[i] != '"')
        i++;
    if (line[i] == '"');
        j = quote(line, '"');
    j -= i;
    word = (char*)malloc(sizeof(char) * (j + 2));
    while(k <= j)
        word[k++] = line[i++];
	puts("ok");
    word[k] = 0;
    return word;
}

int main()
{
    char *str = strdup("hamid \"   khalid \\\" rachi \"");
    printf("|%s|\n", get_word(str));
}

/* char	*get_word(char *line)
{
	int i;
	int j;
	int k;
	char *word;

	i = 0;
	j = 0;
	k = -1;
	while (line[i] && line[i] != '\'' && line[i - 1] != '"')
		i++;
	if (line[i] == '"');
		j = quote(line, '"');
	word = malloc(sizeof(char) * (j - i + 2));
	j -= i;
	while(++k <= j)
		word[k] = line[i++];
	puts("ok");
	puts(word);
	word[k] = '\0';
	return word;
}

int main()
{
	char *str = strdup("hamid \"   khalid \\\" rachi \"");
	printf("|%s|\n", get_word(str));
}
 */
