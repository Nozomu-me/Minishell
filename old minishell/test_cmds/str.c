#include "libft/libft.h"


int	check_symbol2(char c)
{
	if (c == ';' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t'
	|| c == '"' || c == '\'')
		return (1);
	return (0);
}

int 	count_back(char *line, int i)
{
    int cp = 0;
    while (line[i - 1] == '\\')
    {
        cp++;
        i--;;
	}
	if (cp && cp % 2 == 0)
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

char *get(char *line)
{
	int i = -1;
	int end;
	char *word = NULL;
	while (line[++i] && (line[i] == ' ' || line[i] == '\t'));
	while (line[i] && !check_symbol2(line[i]) && count_back(line, i))
		i++;
	if (line[i] == '"' && count_back(line, i))
	{
		end = quote(line + i, '"');
		word = ft_substr(line, i, end);
	}
	return word;
}

int main()
{
	char *str = "    \"kamal    \"\\  ;abdo  \" khalid    ";
	printf("|%s|\n", get(str));
}
