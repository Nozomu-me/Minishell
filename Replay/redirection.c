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
	while (line[i] && (line[i] != ' ' || line[i] != '\t' || line[i] != '>'
	|| line[i] != '<'))
		i++;
	return (i);
}

char	*sort_redirection(t_parse *parse, char *line)
{
	int i;
	int j;
	char *file;
	char *args;

	i = 0;
	j = 0;
	file = NULL;
	args = NULL;
	while (line[i] && (line[i] != '>' || line[i] != '<'))
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		args = ft_substr(line, 0, i);
		j = i;
	}
	while (line[++i])
	{
		i += skip_spaces(line + i);
		i += skip_sp_red(line + i);
		if (line[i] == ' ' || line[i] == '\t')
			i += skip_spaces(line + i);
		if (line[i] == '>' || line[i] == '<')
		{
			file = ft_strjoin(file, ft_substr(line, j, i - 1));
			j = i;
		}
		else if (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		{
			i += skip_sp_red(line + i);
			args = ft_strjoin(args, ft_substr(line, j, i));
			j = i;
		}
		// if (line[i] == '>' || line[i] == '<')
		// {
		// 	j = i++;
		// 	if (line[i + 1] == '>')
		// 		i++;
		// 	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		// 		i++;
		// 	while (line[i] && (line[i] != '>' && line[i] != '<' && line[i] != ' '))
		// 		i++;
		// 	if (line[i] == '>' || line[i] == '<')
		// 	{
		// 		file = ft_substr(line, j, i);
		// 		printf("|%c|\n", line[j]);
		// 		line[j] = 0;
		// 	// puts("ok");
		// 		line = ft_strjoin(line, line + i);
		// 		i = ++j;
		// 	}
		// 	// else
		// 	// {
		// 	// 	;
		// 	// }
		// }
		// i++;
	}
	// if (line[i] == '\0')
	// {

	// }
	if (j != 0)
		return (ft_strjoin(args, file));
	// line = ft_strjoin(line, file);
	return line;
}

int main()
{
	char *line;// = "echo hello > f1>f3>f4";
	t_parse *parse;
	while (1337)
	{
		get_next_line(&line);
		printf("|%s|\n", sort_redirection(parse, line));
	}
	return (0);
}
