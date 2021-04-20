/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:32:03 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 16:49:43 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_file_name(t_mini *mini, char *line, int *index)
{
	char	*tmp;
	int		pos;
	int		start;
	int		i;

	i = *index;
	pos = i;
	while (line[++i] && line[i] == ' ')
		;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		i++;
	// if (mini->file_nme)
	// 	free(mini->file_nme);
 	mini->file_nme = ft_substr2(line, start, i);
	if (pos && line[pos - 1] == '>')
		--pos;
	line[pos] = 0;
	tmp = line;
	line = ft_strjoin(line, line + i);
	free(tmp);
	*index = --pos;
	return (line);
}

char	*push_read_apnd_strct(t_mini *mini, char *line, int *i)
{
	if (line[(*i) + 1] == '>')
	{
		(*i)++;
		line = get_file_name(mini, line, i);
		file_lstadd_back(&mini->cmds.file, file_lst_new(mini->file_nme, APPEND));
	}
	else
	{
		line = get_file_name(mini, line, i);
		file_lstadd_back(&mini->cmds.file, file_lst_new(mini->file_nme, WRITE));
	}
	return (line);
}

char	*push_file_struct(t_mini *mini, char *line, int i)
{
	char	*tmp;
	mini->cmds.file = NULL;
	mini->file_nme = NULL;

	while (line[i])
	{
		if (line[i] == '<')
		{
			line = get_file_name(mini, line, &i);
			file_lstadd_back(&mini->cmds.file, file_lst_new(mini->file_nme, READ));
		}
		else if (line[i] == '>')
			line = push_read_apnd_strct(mini, line, &i);
		i++;
	}
	if (mini->file_nme)
		free(mini->file_nme);
	return (line);
}

void	push_to_struct(t_mini *mini, char *line)
{
	int		i;
	t_cflist *tmp;
	

	// mini->cmds = (t_cmds *)malloc(sizeof(t_cmds));
	// mini->cmds.file = NULL;
	// mini->cmds.file = NULL;
	// mini->cmds.cmd = NULL;
	line = push_file_struct(mini, line, 0);
	mini->cmds.cmd = ft_split(line, ' ');
	// mini->cmds.type = mini->splited_cmd->type;
	i = -1;
	while (mini->cmds.cmd[++i])
		mini->cmds.cmd[i] = reverse_cmd(mini, mini->cmds.cmd[i], 0, -1);
	tmp = mini->cmds.file;
	while (tmp)
	{
		tmp->name = reverse_cmd(mini,
				tmp->name, 0, -1);
		tmp = tmp->next;
	}
}

// void	push_to_struct(t_parse *parse, char *line)
// {
// 	int start = 0;
// 	int pos = 0;
// 	int i = 0;
// 	char *file;
// 	parse->cmds = (t_cmds*)malloc(sizeof(t_cmds));
// 	parse->cmds->file = NULL;
// 	parse->cmds->args = NULL;
// 	// line = push_file_struct(parse, line, 0);
// 	parse->cmds->args = ft_split(line, ' ');
// 	parse->cmds->type = parse->f_cmd->type;
// 	i = -1;
// 	printf("\n=================================================\n\nARGS  => ");
// 	while (parse->cmds->args[++i])
// 	{
// 		parse->cmds->args[i] = reverse_cmd(parse, parse->cmds->args[i], 0, -1);
// 		printf("|%s|\t", parse->cmds->args[i]);
// 	}
// 	puts("\n");
// 	printf("FILES =>\n");
// 	if (!parse->cmds->file)
// 		puts("\t |NULL|");
// 	else 
// 	while (parse->cmds->file)
// 	{
// 		parse->cmds->file->filename = reverse_cmd(parse,
// 				parse->cmds->file->filename, 0, -1);
// 		if (parse->cmds->file->filetype == 0)
// 			printf("\t |%s|\t|%s|\n", parse->cmds->file->filename, "WRITE");
// 		else if (parse->cmds->file->filetype == 1)
// 			printf("\t |%s|\t|%s|\n", parse->cmds->file->filename, "READ");
// 		else if (parse->cmds->file->filetype == 2)
// 			printf("\t |%s|\t|%s|\n", parse->cmds->file->filename, "APPEND");
// 		parse->cmds->file = parse->cmds->file->next;
// 	}
// 	puts("\n");
// 	if (parse->cmds->type == 3)
// 		printf("TYPES => |%s|\n", "PIPE");
// 	else if (parse->cmds->type == 4)
// 		printf("TYPES => |%s|\n", "END");
// }