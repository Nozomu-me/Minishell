/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:32:03 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 16:26:08 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	parse->cmds = (t_cmds*)malloc(sizeof(t_cmds));
	parse->cmds->file = NULL;
	parse->cmds->args = NULL;

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
	parse->cmds->args = ft_split(line, ' ');
	parse->cmds->type = parse->f_cmd->type;
	i = 0;
	printf("ARGS =>");
	while (parse->cmds->args[i])
	{
		parse->cmds->args[i] = check_f_cmd(parse, parse->cmds->args[i]);
		printf("\t|%s|", parse->cmds->args[i]);
		i++;
	}
	puts("");
	if (parse->cmds->type == 3)
		printf("TYPES   => |%s|\n", "PIPE");
	else if (parse->cmds->type == 4)
		printf("TYPES   => |%s|\n", "END");
	printf("FILES :\n");
	while (parse->cmds->file)
	{
		parse->cmds->file->filename = check_f_cmd(parse, parse->cmds->file->filename);
		if (parse->cmds->file->filetype == 0)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "WRITE");
		else if (parse->cmds->file->filetype == 1)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "READ");
		else if (parse->cmds->file->filetype == 2)
			printf("|%s|\t|%s|\n", parse->cmds->file->filename, "APPEND");
		parse->cmds->file = parse->cmds->file->next;
	}
	// free_cmds_struct(parse->cmds);
}
