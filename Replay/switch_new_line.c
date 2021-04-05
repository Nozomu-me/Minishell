#include "parsing.h"

int 	count_back2(char *line)
{
    int cp;

	cp = 0;
    while (*line && *line == '\\')
    {
        cp++;
        line--;
	}
    return (cp);
}

int retu(char c)
{
	if (c == '"' || c == '\\' || c == '\'')
		return (1);
	return (0);
}
char	*check_slash(char *line)
{
	int i = -1;
	int p = 0;
	int quote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] == '\\')
			line[i + 1] *= -1;
		else if (line[i] == '\\' && retu(line[i + 1]))// line[i + 1] == '"')
			line[i] *= -1;
		else if (line[i] == '"' && line[i - 1] == '\\' * -1)
			line[i] *= -1;
		// else if (line[i] == '\'' && );
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] != '\\' * -1 && line[i] != '"' && line[i - 1] != '\\')
			p++;
	}
	printf("|%d|\n", p);
	char *new = malloc(sizeof(char) * p + 1);
	p = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] > 0)
			i++;
		if (line[i] != '\\' * - 1 && line[i] != '"')
		{
			if (line[i] < 0)
				new[p++] = line[i] * -1;
			else
				new[p++] = line[i];
		}
	}
	new[p] = 0;
	return (new);
}

int main()
{
	char *line;
	int i = 0;

	while (1337)
	{
		get_next_line(&line);
		line = check_slash(line);
		puts(line);
		free(line);
	}
}