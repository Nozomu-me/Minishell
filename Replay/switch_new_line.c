#include "parsing.h"

char	*check_command(t_parse *parse, char *line)
{
	char 	*new;
	int		i;
	int 	cp;
 
	new = line;
	i = 0;
	cp = 0;
	while (*new)
	{
		// if (*new == '$' && count_back(new[-1]))
		// {

		// }
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
					line[i] = *(++new);
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
