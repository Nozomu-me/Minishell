#include "parsing.h"

char	*check_command(t_parse *parse, char *line)
{
	char *new;
	int i = 0;
	int cp = 0;
	new = ft_strdup(line);
	int quote = OFF;
	int single = OFF;
	while (*new)
	{
		if (quote == OFF && single == OFF)
		{
			if (*new == '\\')
			{
				cp++;
				line[i++] = *(++new);
			}
			else
			{
				if (*new == '"' && cp % 2 == 0)
					quote = 1;
				else if (*new == '\'' && cp % 2 == 0)
					single = 1;
				else
					line[i++] = *new;
				cp = 0;
			}
		}
		else
		{
			if (quote == ON)
			{
				if (*new == '"')
					quote = OFF;
				else if (*new == '\\' && new[1] == '\\')
					line[i] = *(++new);
				else if (*new == '\\' && new[1] < 0)
					line[i++] = *(++new);
				else
					line[i++] = *new;
			}
			else if (single == ON)
			{
				// printf("|%c|\t|%d|\t|%d|\n", *new, quote, single);
				// if (*new == '\'')
				// 	new++;
				while (*new != '\'')
					line[i++] = *new++;
				single = OFF;
			}
		}
		printf("|%d|\n", single);
		new++;
	}
	line[i] = 0;
	// i = -1;
	// while (line[++i])
	// 	if (line[i] < 0)
	// 		line[i] *= -1;
	return line;
}