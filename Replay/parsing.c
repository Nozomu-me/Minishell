/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 18:09:13 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse	*initail_struct(t_parse *parse)
{
	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->check_env = "=~\\/%#{}$*+-.:?@[]^ '\"";
	parse->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	parse->f_cmd = NULL;
	parse->f_cmd = NULL;
	parse->under_score = "./minishell";
	parse->already_pipe = 0;
	return (parse);
}

void	split_semi_pipe(t_parse *parse, char *line, int i)
{
	t_parse *tmp;

	tmp = parse;
	tmp->s_semi = ft_split(line, ';');
	while (*tmp->s_semi)
	{
		*tmp->s_semi = ft_strtrim(*tmp->s_semi, " ");
		tmp->s_pipe = ft_split(*tmp->s_semi, '|');
		while (tmp->s_pipe[i])
			i++;
		while (*tmp->s_pipe)
		{
			*tmp->s_pipe = ft_strtrim(*tmp->s_pipe, " ");
			if (--i)
			{
				tmp->already_pipe = 1;
				ft_lstadd_back_cmd(&tmp->f_cmd, ft_lstnew_cmd(*tmp->s_pipe, PIPE));
			}
			else
				ft_lstadd_back_cmd(&tmp->f_cmd, ft_lstnew_cmd(*tmp->s_pipe, END));
			tmp->s_pipe++;
		}
		tmp->s_semi++;
	}
}

void	parsing(t_parse *parse, char *line)
{
	int	i;

	i = 0;
	// search_replace(line, "\t", " ");
	line = partition_stage(parse->smbl, line);
	if (!parse->smbl->error)
		split_semi_pipe(parse, line, i);
	while (parse->f_cmd)
	{
		parse->f_cmd->cmd = search_replace(parse->f_cmd->cmd, "\t", " ");
		parse->f_cmd->cmd = check_dollr(parse, parse->f_cmd->cmd);
		push_to_struct(parse, parse->f_cmd->cmd);
		// free_cmds_struct(parse->cmds);
		// ft_free(parse);
		parse->under_score = parse->f_cmd->cmd;
		parse->f_cmd = parse->f_cmd->next;
	}
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
