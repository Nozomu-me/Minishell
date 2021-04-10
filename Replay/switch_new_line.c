#include "parsing.h"

char	*ret(char *line, int i)
{
	char *new;
	int j;

	j = -1;
	new = malloc(sizeof(char) * i + 1);
	while (++j < i)
		new[j] = line[j];
	new[j] = 0;
	return (new);
}

char	*check_command(t_parse *parse, char *line)
{
	char 	*new;
	int		i;
	int 	cp;
	int		ret;

	new = line;
	ret = -1;
	i = 0;
	cp = 0;
	while (*new)
	{
		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
		{
			if (*new == '\\')
			{
				cp++;
				line[i++] = *(++new);
			}
			else
			{
				if (*new == '"' && cp % 2 == 0)
					parse->smbl->d_quote = 1;
				else if (*new == '\'' && cp % 2 == 0)
					parse->smbl->s_quote = 1;
				else
					line[i++] = *new;
				cp = 0;
			}
		}
		else
		{
			if (parse->smbl->d_quote == ON)
			{
				if (*new == '"')
					parse->smbl->d_quote = OFF;
				else if (*new == '\\' && new[1] == '\\')
					line[i++] = *(++new);
				else if (*new == '\\' && new[1] < 0)
					line[i++] = *(++new);
				else
					line[i++] = *new;
			}
			else if (parse->smbl->s_quote == ON)
			{
				while (*new != '\'')
					line[i++] = *new++;
				parse->smbl->s_quote = OFF;
			}
		}
		if (*new != '\\')
			cp = 0;
		new++;
	}
		line[i] = 0;
		i = -1;
		while (line[++i])
			if (line[i] < 0)
				line[i] *= -1;
	return line;
}
