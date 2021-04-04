#include "parsing.h"

char	*check_slash(char *line, int *ii)
{
	int i = *ii;
	int j = 0;
	int slash;
	char *new = malloc(sizeof(char) * 20);

	slash = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			if (slash % 2 == 1)
				new[j] = '\\';
			slash++;
		}
		else
		{
			slash = 0;
			new[j] = line[i];
		}
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

int main()
{
	char *line = "hamid\"kamal\\khalid";
	int i = 0;

	line = check_slash(line, &i);
	puts(line);
}