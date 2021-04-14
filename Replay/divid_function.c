#include "parsing.h"

char	*divid_function(t_parse *parse, char *line, int i, int j, int cp)
{
	char *new;

	new = line;
	if (new[j] == '\\')
	{
		cp++;
		line[i++] = new[++j];
	}
	else
	{
		if (new[j] && cp % 2 == 0)
			parse->smbl->d_quote = ON;
		else if (*new == '\'' && cp % 2 == 0)
			parse->smbl->s_quote = ON;
		else
			line[i++] = *new;
		cp = 0;
	}
	return (line);
}

char	*check_f_cmd(t_parse *parse, char *line)
{
	char	*new;
	int i;
	int j;
	int cp;

	i = 0;
	j = -1;
	new = line;
	cp = 0;
	// printf("LINE = |%s|\n", line);
	while (new[++j])
	{
		
		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
		{
			if (new[j] == '\\')
			{
				cp++;
				line[i++] = new[++j];
			}
			else
			{
				if (new[j] == '"' && cp % 2 == 0)
					parse->smbl->d_quote = ON;
				else if (new[j] == '\'' && cp % 2 == 0)
					parse->smbl->s_quote = ON;
				else
					line[i++] = new[j];
				cp = 0;
			}
		}
		else
		{
			if (parse->smbl->d_quote == ON)
			{
				if (new[j] == '"')
					parse->smbl->d_quote = OFF;
				else if (new[j] == '\\' && new[j + 1] == '\\')
					line[i++] = new[++j];
				else if (new[j] == '\\' && new[j + 1] < 0 && new[j + 1] != '\'' * -1)
					line[i++] = new[++j];
				else
					line[i++] = new[j];
			}
			else if (parse->smbl->s_quote == ON)
			{
				while (new[j] != '\'')
					line[i++] = new[j++];
				parse->smbl->s_quote = OFF;
			}
		}
		if (new[j] != '\\')
			cp = 0;
	}
	line[i] = 0;
	i = -1;
	while (line[++i])
		if (line[i] < 0)
			line[i] *= -1;
	return (line);
}