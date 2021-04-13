/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 11:27:31 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse	*initail_struct(t_parse *parse)
{
	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->check_env = ft_strdup("=~\\/%#{}$*+-.:?@[]^ '\"");
	parse->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	parse->ready_p = NULL;
	parse->cmds = NULL;
	parse->f_cmd = NULL;
	parse->f_cmd = NULL;
	parse->under_score = "./minishell";
	parse->already_pipe = 0;
	return (parse);
}

void	split_semi_pipe(t_parse *parse, char *line, int i)
{
	search_replace(line, "\t", " ");
	parse->s_semi = ft_split(line, ';');
	while (*parse->s_semi)
	{
		*parse->s_semi = ft_strtrim(*parse->s_semi, " ");
		parse->s_pipe = ft_split(*parse->s_semi, '|');
		while (parse->s_pipe[i])
			i++;
		while (*parse->s_pipe)
		{
			*parse->s_pipe = ft_strtrim(*parse->s_pipe, " ");
			if (--i)
			{
				parse->already_pipe = 1;
				ft_lstadd_back_cmd(&parse->f_cmd, ft_lstnew_cmd(*parse->s_pipe, PIPE));
			}
			else
				ft_lstadd_back_cmd(&parse->f_cmd, ft_lstnew_cmd(*parse->s_pipe, END));
			parse->s_pipe++;
		}
		parse->s_semi++;
	}
}

void	parsing(t_parse *parse, char *line)
{
	int	i;

	i = 0;
	line = partition_stage(parse->smbl, line);
	if (!parse->smbl->error)
		split_semi_pipe(parse, line, i);
	while (parse->f_cmd)
	{
		parse->f_cmd->cmd = search_replace(parse->f_cmd->cmd, "\t", " ");
		parse->f_cmd->cmd = check_dollr(parse, parse->f_cmd->cmd);
		push_to_struct(parse, parse->f_cmd->cmd);
		parse->under_score = parse->f_cmd->cmd;
		parse->f_cmd = parse->f_cmd->next;
	}
}

void	ft_free_tab(char **line)
{
	while (*line)
	{
		free(line);
		line++;
	}
}

void	ft_free(t_parse *parse)
{
	ft_free_tab(parse->s_semi);
	ft_free_tab(parse->s_pipe);
	ft_free_tab(parse->env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_parse	*parse;
	int		r;

	parse = initail_struct(parse);
	parse->env = env;
	while (1337)
	{
		ft_putstr_fd(MINISHELL, 1);
		r = get_next_line(&line);
		parsing(parse, line);
		if (!strcmp(line, "exit"))
			exit(0);
		free(line);
	}
	return (0);
}
