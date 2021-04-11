#include "parsing.h"

int		skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		skip_sp_red(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' '  && line[i] != '\t'  && line[i] != '>'
	 && line[i] != '<')
		i++;
	return (i);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
    size_t	i;
    char	*str;

    if (!s)
        return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    i = 0;
    while (start < len)
        str[i++] = s[start++];
    str[i] = '\0';
    return (str);
}

char	*sort_redirection(char *line)
{
	int i;
	int j;
	char *file;
	char *args;

	i = 0;
	j = 0;
	args = NULL;

	while (line[i] && line[i] != '>' && line[i] != '<')
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		args = ft_substr2(line, 0, i);
		j = i;
		if (line[i + 1] == '>')
			i++;
		i++;
		i += skip_spaces(line + i);
		i += skip_sp_red(line + i);
		file = ft_substr2(line, j, i);
		j = i;
	}
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (line[i] != '>' && line[i] != '<')
		{
			i += skip_spaces(line + i);
			i += skip_sp_red(line + i);
			args = ft_strjoin(args, ft_substr2(line, j, i));
			j = i;
		}
		else
		{
			if (line[i + 1] == '>')
				i ++;
			i++;
			i += skip_spaces(line + i);
			i += skip_sp_red(line + i);
			file = ft_strjoin(file, ft_substr2(line, j, i));
			j = i;
		}
		i++;
	}
	if (j != 0)// && args && file)
	{
		return (ft_strjoin(args, file));
	}
	return line;
}
//int main()
//{
//	char *line;// = "echo hello > f1>f3>f4";
//	t_parse *parse;
//	while (1337)
//	{
//		get_next_line(&line);
//		printf("|%s|\n", sort_redirection(parse, line));
//	}
//	return (0);
//}
