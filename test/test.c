#include "parsing.h"

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
    size_t	i;
    size_t  j;
    char	*str;

    if (!s)
        return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    i = 0;
    j = ft_strlen(s);
    while (start < len)
        str[i++] = s[start++];
    str[i] = '\0';
    return (str);
}

char	*get_file_name(char *line, char **files, int *index)
{
	int pos;
	int start;
	int i;

	i = *index;
	pos = i;
	while (line[++i] && line[i] == ' ')
		;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		i++;
	*files = ft_strjoin(*files, "@");
	*files = ft_strjoin(*files, ft_substr2(line, start, i));
	line[pos] = 0;
	line = ft_strjoin(line, line + i);
	*index = --pos;
	return (line);
}

void	push_to_struct(char *line)
{
	int start = 0;
	int pos = 0;
	int i = 0;
	char *files = " ";

	while (line[i])
	{
		if (line[i] == '<')
			line = get_file_name(line, &files, &i);
		else
		{
			if (line[i] == '>' && line[i + 1] == '>')
				line = get_file_name(line, &files, &i);
			else if (line[i] == '>')
				line = get_file_name(line, &files, &i);
		}
		i++;
	}
	printf("FILES NAME =>  |%s|\n", files);
	printf("LINE       =>  |%s|\n", line);
}


int main()
{
	char *line;// = "echo hello >file world <file2 again >>file3";

	while (1)
	{
		get_next_line(&line);
		printf("%s\n\n", line);
		push_to_struct(line);
		free(line);
	}
}