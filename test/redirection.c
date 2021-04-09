#include "libft.h"

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

char	*sort_redirection(char *line)
{
	int i;
	int j;
	char *file;
	char *args;

	i = 0;
	j = 0;
	file = NULL;
	args = NULL;
	// printf("|%d|\t|%c|\t|%s|\n", i, line[i], line);
	while (line[i] && line[i] != 'A' && line[i] != '<')
		i++;
	// printf("|%d|\t|%c|\t|%s|\n", i, line[i], line);
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
		// puts("ok");
		}
	}
	// if (line[i] == '\0')
	// {

	// }
	// puts("ok");
	if (j != 0 && args && file)
	{
		printf("ARGS = |%s|\tFILE = |%s|\n", args, file);
		return (ft_strjoin(args, file));
	}
	// line = ft_strjoin(line, file);
	return line;
}

int main()
{
	char *line = NULL;// = "echo hello > f1>f3>f4";
	while (1337)
	{
		get_next_line(&line);
		line = sort_redirection(line);
		// puts("ok");
		printf("|%s|\n",line);
	}
	return (0);
}
