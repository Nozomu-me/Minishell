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

/* void	push_to_struct(t_parse	*parse, char *line)
{
	int i = 0;
	int j = 0;
	parse->cmds = (t_cmds*)malloc(sizeof(t_cmds));

	while (line[i])
	{
		if (line[i] == '<')
		{
			while (line[++i] && line[i] != ' ');
			j = ++i;
			while (line[i] != ' ' && line[i] != '>' && line[i] != '<')
				i++;
			ft_lstnew(NULL, parse->command->type, ft_substr2(line, j, i), READ);
		}
	}
} */

char	*get_file_name(t_parse *parse, char *line, char **file,  int *index)
{
	int pos;
	int start;
	int i;
	// char	*file;


	i = *index;
	pos = i;
	while (line[++i] && line[i] == ' ')
		;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		i++;
	// puts(*line);
	// *files = ft_strjoin(*files, "@");
	// *files = ft_strjoin(*files, ft_substr2(*line, start, i));
	

	*file = ft_substr2(line, start, i);
	if (pos && line[pos - 1] == '>')
		--pos;
	line[pos] = 0;
	line = ft_strjoin(line, line + i);
	// printf("line = [%s]\n", line);

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
			// line = get_file_name(parse, line, &i);
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				i++;
				line = get_file_name(parse, line, &file, &i);
				if (file)
					file_lstadd_back(&parse->cmds->file, file_lst_new(file, APPEND));
				// line = get_file_name(parse, line, &i);
			}
			else
			{
				line = get_file_name(parse, line, &file,&i);
				// printf("|%s|\t|%s|\n", file, line);
				// puts("ok");
				if (file)
					file_lstadd_back(&parse->cmds->file, file_lst_new(file, WRITE));
				// line = get_file_name(parse, line, &i);
			}
		}
		i++;
	}
	split = ft_split(line, ' ');
	parse->cmds->cmd = split;
	printf("COMMAND => ");
	while (*parse->cmds->cmd)
	{
		printf("|%s|\t", *parse->cmds->cmd);
		parse->cmds->cmd++;
	}
	puts("");
	if (parse->cmds->type == 3)
		printf("TYPES   => |%s|\n", "PIPE");
	else if (parse->cmds->type == 3)
		printf("TYPES   => |%s|\n", "END");
	while (parse->cmds->file)
	{
		if (parse->cmds->file->filetype == 0)
			printf("FILES => |%s|\t|%s|\n", parse->cmds->file->filename, "WRITE");
		else if (parse->cmds->file->filetype == 1)
			printf("FILES => |%s|\t|%s|\n", parse->cmds->file->filename, "READ");
		else if (parse->cmds->file->filetype == 2)
			printf("FILES => |%s|\t|%s|\n", parse->cmds->file->filename, "APPEND");
		parse->cmds->file = parse->cmds->file->next;
	}
	// printf("FILES NAME =>  |%s|\n", files);
	// printf("LINE       =>  |%s|\n", line);

}

/* void	push_to_struct(t_parse	*parse, char *line)
{
	int i = 0;
	int j = 0;
	int red;

	red = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '>' && line[i] != '<' && line[i + 1] != '\0')
		{
			if (line[i + 1] == '>')
				i++;
			i++;
		}
		else
		{
				if (line[i + 1] == '\0')
					i++;
			if (line[i] != '>' && line[i] != '<')
				ft_lstadd_back_to_push(&parse->ready_p, ft_lstnew_cmd_to_push(ft_substr2(line, j, i)));
			else
			{
				red = 1;
				if (line[i] == '>' && line[i + 1] == '>')
				{
					while (line[++i] == ' ')
						;
					
					ft_lstnew(NULL, parse->command->type, ft_substr2(line, j, i), APPEND);
				}
				else if (line[i] == '>')
				{
					red = 1;

					ft_lstnew(NULL, parse->command->type, ft_substr2(line, j, i), WRITE);
				}
				else if (line[i] == '<')
				{
					red = 1;
					ft_lstnew(NULL, parse->command->type, ft_substr2(line, j, i), READ);
				}
			}
			j = i + 1;
			i++;
		}
	}
	while (parse->ready_p)
	{
		printf("* COMMAND = |%s|\n", parse->ready_p->cmd);
		parse->ready_p = parse->ready_p->next;
	}
	printf("\nCMDS => ");
	while (*parse->cmds->cmd)
	{
		printf("|%s|\t", *parse->cmds->cmd);
		parse->cmds->cmd++;
	}
	printf("\n\nTYPE => |%d|\n", parse->cmds->type);
	while (parse->cmds->file->filename)
	{
		printf("FILE ==>  |%s|\t|%d|\n", parse->cmds->file->filename, parse->cmds->file->filetype);
		parse->cmds->file = parse->cmds->file->next;
	}
} */
