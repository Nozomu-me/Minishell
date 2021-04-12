#include "parsing.h"

// int 	count_back(char *line)
// {
//     int cp;

// 	cp = 0;
//     while (*line && *line == '\\')
//     {
//         cp++;
//         line--;
// 	}
// 	/*	1	=>	doesnt followed by quotes
// 		0	=>	followed by quotes
// 	*/
// 	if (cp % 2 == 0)
// 		return (0);
//     return (1);
// }
// char	*check_dollr_quote(t_symbol *smbl, char *line, int i)
// {
// 	if (line[i]);
// }
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

char	*last_word(char *line)
{
	int i;

	i = ft_strlen(line) - 1;
	while (line[i - 1] && line[i - 1] != ' ')
		i--;
	return (line + i);
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
	// if (ft_strchr(parse->check_env, line[1]))
	// 	path = ft_strdup("$");
	// else
	path = ft_substr(line, 0, j);
	i = 0;
	// printf("\t\t|%d|\t|%d|\t|%s|\n", parse->smbl->d_quote, parse->smbl->s_quote, path);
	while (parse->env[i])
	{
		split = ft_split(parse->env[i], '=');
		// printf("ENV   =  |%s|\tLINE   = |%s|\tPATH = |%s|\n", parse->check_env, line + j, path);
		// if (path == '_')
		// 	return (ft_strjoin(split[1], line + j));
		if (compare(path, "_"))
		{
			// puts("ok");
			// printf("|%s|\n", last_word(parse->under_score))
			if (parse->already_pipe == 0)
				return (ft_strjoin(last_word(parse->under_score), line + j));
			else
				return(line + j);
		} else 
		if (compare(split[0], path))
		{
			// puts("ok");
			return (ft_strjoin(split[1], line + j));
		}
		i++;
	}
	return (line + j);
}

char	*check_dollr(t_parse *parse, char *line)
{
	int i;
	// int j;
	char *new;

	i = 0;
	while (line[i])
	{
		// printf("[%d]\t|%d|\t|%d|\n", i, !count_back(line + (i - 1)), j);
		// if (line[i] == '$' && ft_strchr(parse->check_env, line[i + 1]))
			
		if (line[i] == '$' && !count_back(line + (i - 1)) && !ft_strchr(parse->check_env, line[i + 1]))
		{
			// j =  i + 1;
			// if (line[i])
			new = dollar(parse, line + i + 1);
			// printf("NEW = |%s|\n", new);
			line[i] = 0;
			line = ft_strjoin(line, new);
			i = 0;
		}
		else if (line[i] == '$' && count_back(line + (i - 1)))
			line[i] *= -1;
		i++;
	}
	return line;
}

/* int main(int ac, char **av, char **env)
{
	t_parse *parse;
	char	*line;
	int i = -1;
	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->env = env;
	parse->check_env = "=~\\/%{}#$*+-.:?@[]^ ";
	char *ret;
	while (42)
	{
		get_next_line(&line);
		ret = check_dollr(parse, line);
		printf("RETURN = |%s|\n", ret);
	}
	return (0);
} */