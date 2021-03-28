#include "parsing.h"
#define SEMI 128
#define PIPE 129
#define ON 1
#define OFF 0

int 	count_back(char *line)
{
    int cp;

	cp = 0;
    while (*line == '\\')
    {
        cp++;
        line--;
	}
	/*	if returned 1 then \ isn't followed by ' or "	*/
	if (cp % 2 == 0)
		return (1);
    return (0);
}

char	*partition_stage(char *line)
{
	int i;
	int d_quote;
	int s_quote;

	i = -1;
	d_quote = OFF;
	s_quote = OFF;
	while (line[++i])
	{
		if (line[i] == '\'' && count_back(line + (i - 1)))
		{
			if (s_quote == OFF && d_quote == OFF)
				s_quote = ON;
			else if (s_quote == ON && d_quote == OFF)
				s_quote = OFF;
		}
		else if (line[i] == '"' && count_back(line + (i - 1)))
		{
			if (d_quote == OFF && s_quote == OFF)
				d_quote = ON;
			else if (d_quote == ON && s_quote == OFF)
				d_quote = OFF;
		}
		if (line[i] == ';' && (d_quote == ON || s_quote == ON))
			line[i] = 128;
		if (line[i] == '|' && (d_quote == ON || s_quote == ON))
			line[i] = 129;
	}
	printf("|%d|\t|%d|\n", d_quote, s_quote);
	return (line);
}

void	splitted(char *line)
{
	char	**splitted;

	line = partition_stage(line);
	splitted = ft_split(line, ';');
	while (*splitted)
	{
		puts(*splitted);
		splitted++;
	}
}
int main()
{
	char *line;
	line = NULL;

	while (1337)
	{
		get_next_line(&line);
		// splitted(line);
		partition_stage(line);
		free(line);
	}
}
/* int main(int argc, char const *argv[])
{
	char *str = ft_strdup(";;;;;;;\"kamlid;hamid\";rachid\"helo;\"");
	char **splited;
	puts(str);
	splited = ft_split(str, ';');
	while (*splited)
	{
		printf("|%s|\n", *splited);
		splited++;
	}
	puts("\n");
	str = change(str, ';', SEMI);
	puts(str);
	splited = ft_split(str, ';');
	while (*splited)
	{
		printf("|%s|\n", *splited);
		splited++;
	}
 	return 0;
} */
