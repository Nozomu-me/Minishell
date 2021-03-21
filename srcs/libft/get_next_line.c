#include "../../includes/lexer.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}


int		is_n(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*my_strcut(char *str, int n)
{
	int		len;
	int		i;
	char	*new;

	i = 0;
	len = ft_strlen(str);
	if (len > n)
		len = n;
	new = malloc(sizeof(char) * (len + 1));
	while (*str && len--)
		new[i++] = *str++;
	new[i] = '\0';
	return (new);
}

int		fill_line(char **content, char **line)
{
	int		end;
	char	*tmp;

	end = 0;
	while ((*content)[end] != '\n' && (*content)[end] != '\0')
		end++;
	if ((*content)[end] == '\n')
	{
		*line = my_strcut(*content, end);
		tmp = ft_strdup(*content + end + 1);
		free(*content);
		*content = tmp;
		return (1);
	}
	else if ((*content[end]) == '\0')
	{
		*line = ft_strdup(*content);
		free(*content);
	}
	return (0);
}

int		get_next_line(char **line)
{
	int				r;
	static char		*content;
	char			*tmp;
	char			*buff;

	if (content == NULL)
		content = ft_strdup("");
	buff = malloc(sizeof(char) * 101);
	if (!(is_n(content)))
		while ((r = read(0, buff, 100)) > 0)
		{
			buff[r] = '\0';
			tmp = ft_strjoin(content, buff);
			free(content);
			content = tmp;
			if (is_n(buff))
				break;
		}
	free(buff);
	return (fill_line(&content, line));
}
