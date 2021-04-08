#include "parsing.h"

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
	char *path;
	int i;
	int j;

	j = -1;
	i = -1;
	while (line[++j])
		if (ft_strchr(parse->check_env, line[j]))
			break;
	path = ft_substr(line, 0, j);
	i = 0;
	while (parse->env[i])
	{
		split = ft_split(parse->env[i], '=');
		// printf("ENV   =  |%s|\tLINE   = |%s|\tPATH = |%s|\n", parse->check_env, line + j, path);
		if (compare(split[0], path))
			return (ft_strjoin(split[1], line + j));
		i++;
	}
	return (line + j);
}

/* int main(int ac, char **av, char **env)
{
	t_parse *parse;
	char	*line;
	int i = -1;
	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->env = env;
	parse->check_env = "=~\\/%#$*+-.:?@[]^ ";
	char *ret;
	while (42)
	{
		get_next_line(&line);
		ret = dollar(parse, line + 1);
		printf("RETURN = |%s|\n", ret);
	}
	return (0);
} */