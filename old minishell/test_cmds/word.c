#include "libft/libft.h"

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

	i = 0;
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

    i = -1;
    j = 0;
    k = 0;
	while (line[++i])
		if (line[i] == '"' && line[i - 1] != '\\')
			break ;
    while (line[i] && line[i] != '\'' && line[i] != '"' && line[i - 1] != '\\')
        i++;
    if (line[i] == '"')
        j = quote(line + i, '"');
    word = (char*)malloc(sizeof(char) * (j + 1));
    while(k <= j)
        word[k++] = line[i++];
    word[k] = 0;
    return word;
}

int		main()
{
	char	*line;

	line = NULL;
	while(1337)
	{
		write(1, MINISHELL,ft_strlen(MINISHELL));
		get_next_line(&line);
		printf("|%s|\n", get_word(line));
		free(line);
		line = NULL;
	}
}
