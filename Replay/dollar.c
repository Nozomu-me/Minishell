#include "parsing.h"

int 	count_back(char *line)
{
    int cp;

	cp = 0;
    while (*line && *line == '\\')
    {
        cp++;
        line--;
	}
	if (cp % 2 == 0)
		return (0);
    return (1);
}

int		compare(char *str, char *str2)
{
	while (*str || *str2)
	{
		if (*str != *str2)
			return 0;
		str++;
		str2++;
	}
	return 1;
}

char	*dollar(t_parse *parse, char *line)
{
	char **split;
	char *new;
	char *find = "=~\\/%#$*+-.:?@[]^ ";
	int i;

	i = -1;
	while (line[++i])
		if (ft_strchr(find, line[i]))
			break;
	new = ft_substr(line, 0, i);
	printf("NEW: |%s|\n", new);
	i = 0;
	while (parse->env[i])
	{
		split = ft_split(parse->env[i], '=');
		if (compare(split[0], new))
		{
			printf("|%s|\n", split[1]);
			break;
		}
		i++;
	}
	return split[1];
}

// int main()
// {
// 	char *test = "$";
// 	char *find = "=~\\/%#$*+-.:?@[]^ ";
// 	int i = 0;
// 	char *new = NULL;
// 	while (test[++i])
// 		if (ft_strchr(find, test[i]))
// 			break;
// 	new = ft_substr(test, 0, i);
// 	printf("|%s|\n", new);
// }

int main(int ac, char **av, char **env)
{
	t_parse *parse;
	char	*line;
	int i = -1;
	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->env = env;
	line = "PWD";
	//  =~\/#$%*+-.:?@[]^
	while (line[++i] != '$' && !count_back(line + (i - 1)));
	printf("i = |%d|\n", i);
	char *ret = dollar(parse, line + 1);
}
