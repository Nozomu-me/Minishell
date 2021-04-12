#include "parsing.h"

// char	*ft_substr2(char *s, unsigned int start, size_t len)
// {
//     size_t	i;
//     size_t  j;
//     char	*str;

//     if (!s)
//         return (NULL);
//     if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
//         return (NULL);
//     i = 0;
//     j = ft_strlen(s);
//     while (start < len)
//         str[i++] = s[start++];
//     str[i] = '\0';
//     return (str);
// }

t_ready_to_push		*ft_lstnew_cmd_to_push(char *new_cmd)
{
	t_ready_to_push *new;

	new = (t_ready_to_push*)malloc(sizeof(t_ready_to_push));
	if (new)
	{
		new->cmd = new_cmd;
		new->next = NULL;
	}
	return (new);
}

void				ft_lstadd_back_to_push(t_ready_to_push **alst, t_ready_to_push *new)
{
	t_ready_to_push *list;
	if (!alst || !new)
		return ;
	if (*alst)
	{
		list = *alst;
		while (list && list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}

char	*get_file_name(t_parse *parse, char *line, char **file,  int *index)
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
	*file = ft_substr2(line, start, i);
	if (pos && line[pos - 1] == '>')
		--pos;
	line[pos] = 0;
	line = ft_strjoin(line, line + i);
	*index = --pos;
	return (line);
}

void	push_to_struct(t_parse *parse, char *line)
{
	int start = 0;
	int pos = 0;
	int i = 0;
	char *file;
	char **split;
	parse->cmds = (t_cmds*)malloc(sizeof(t_cmds));
	parse->cmds->file = NULL;
	parse->cmds->cmd = NULL;

	while (line[i])
	{
		if (line[i] == '<')
		{
			line = get_file_name(parse, line, &file, &i);
			if (file)
				file_lstadd_back(&parse->cmds->file, file_lst_new(file, READ));
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				i++;
				line = get_file_name(parse, line, &file, &i);
				if (file)
					file_lstadd_back(&parse->cmds->file, file_lst_new(file, APPEND));
			}
			else
			{
				line = get_file_name(parse, line, &file,&i);
				if (file)
					file_lstadd_back(&parse->cmds->file, file_lst_new(file, WRITE));
			}
		}
		i++;
	}
	split = ft_split(line, ' ');
	parse->cmds->cmd = split;
	parse->cmds->type = parse->command->type;

	printf("ARGS =>");
	while (*parse->cmds->cmd)
	{
		*parse->cmds->cmd = check_command(parse, *parse->cmds->cmd);
		printf("\t|%s|", *parse->cmds->cmd);
		parse->cmds->cmd++;
	}
	puts("");
	if (parse->cmds->type == 3)
		printf("TYPES   => |%s|\n", "PIPE");
	else if (parse->cmds->type == 4)
		printf("TYPES   => |%s|\n", "END");
	printf("FILES :\n");
	while (parse->cmds->file)
	{
		parse->cmds->file->filename = check_command(parse, parse->cmds->file->filename);
		if (parse->cmds->file->filetype == 0)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "WRITE");
		else if (parse->cmds->file->filetype == 1)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "READ");
		else if (parse->cmds->file->filetype == 2)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "APPEND");
		parse->cmds->file = parse->cmds->file->next;
	}
}
