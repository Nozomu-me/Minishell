#include "../includes/lexer.h"
#include <stdio.H>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len && (size_t)start < ft_strlen(s))
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

t_bool	check_symbol2(char c)
{
	if (c == ';' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t'
	|| c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

t_bool	check_symbol(char c)
{
	if (c == ';' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

char	*skip_space(char *line)
{
	while (check_symbol2(*line))
		line++;
	return (line);
}

int 	count_back(char *line)
{
    int cp = 0;
    while (*line == '\\')
    {
        cp++;
        line--;
	}
	if (cp % 2 == 0)
		return (1);
    return (0);
}

char	*get_word(char *line)
{
	char *word;
	int i;
	int j;

	i = 0;
	line = skip_space(line);
	if (line[i] == '"' && count_back(line + i))
		line = skip_space(line);
	j = i;
	if (line[i] == '"')
		while (line[++j] != '"' && count_back(line[j]));
	line = ft_substr(word, i, j);
	printf("|%s|\n", word);
	return (line + --j);
}

int		main()
{
	char	*line;

	line = NULL;
	while(1337)
	{
		write(1, MINISHELL,ft_strlen(MINISHELL));
		get_next_line(&line);
		line = get_word(line);
		free(line);
		line = NULL;
	}
}


/* 
#define opened 1
#define closed 0

int		backslash;

backslash = 0;

while (str[i])
{
	if (str[i] == '"')
		open_and_close_double_quotes();
	else if (str[i] == '\'')
		open_and_close_single_quotes();
	if (str[i] == '\\' && backslash == 0)
		backslash = 1
	else
		backslash = 0;
	i++;
}
//hello
========================================

treat_double_quotes()
{
	int i;

	i = 1;
	while (str[i] != '\0' && double_quotes == opened)
	{
		if (str[i] == '"' && backslash == 0)
			double_quotes = closed;
		i++;
	}
	token = ft_substr(str, 0, i);
}
\\"hello world" echo
while (str[i])
{
	if (str[i] == '"' && backslash == 0)
		treat_double_quotes(str + i);

	i++;
} */