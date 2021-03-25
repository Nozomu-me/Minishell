#include "libft/libft.h"

int	check_symbol(char c)
{
	if (c == ';' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
	// || c == '"' || c == '\'')
		return (1);
	return (0);
}

char	*get_word(char *line)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = -1;
	while (line[i] && !check_symbol(line[i]))
		i++;
	// if (line[i] == '"' || line[i] == '\'')
	// 	while (line[++i] != '\'' || line[i] != '"')
	// 		i++;

	if (i)
	{
		word = malloc(sizeof(char) * i + 1);
		while (++j < i)
			word[j] = line[j];
		word[j] = '\0';
	}
	printf("|%s|\n", word);
	return (line + --i);
}

int main()
{
	char *str = ft_strdup("hamid     khalid    \"rachid   	kamal\"   ok");
	//hamid     khalid    "rachid   	kamal"   ok
	int i = 0;
	while (*str)
	{
		str = get_word(str);
		// printf("|%s|\n", str);
		str++;
	}
}
