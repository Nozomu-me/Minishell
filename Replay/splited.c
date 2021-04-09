/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/09 22:03:24 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse		*initail_struct(t_parse *parse)
{
	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->cmds = (t_cmds*)malloc(sizeof(t_cmds));
	parse->command = (t_command*)malloc(sizeof(t_command));
	parse->smbl = (t_symbol*)malloc(sizeof(t_symbol));
	parse->cmds = NULL;
	parse->command = NULL;
	parse->check_env = "=~\\/%#{}$*+-.:?@[]^ '\"";
	return parse;
}

void	splitted(t_parse *parse, char *line)
{
	int		i;

	i = 0;
	line = partition_stage(parse->smbl, line);
	if (!parse->smbl->error)
	{
		parse->s_semi = ft_split(line, ';');
		while (*parse->s_semi)
		{
			*parse->s_semi = ft_strtrim(*parse->s_semi, " ");
			*parse->s_semi = ft_strtrim(*parse->s_semi, "\t");
			parse->s_pipe = ft_split(*parse->s_semi, '|');
			while (parse->s_pipe[i])
				i++;
			while (*parse->s_pipe)
			{
				*parse->s_pipe = ft_strtrim(*parse->s_pipe, " ");
				*parse->s_pipe = ft_strtrim(*parse->s_pipe, "\t");
				if (--i)
					ft_lstadd_back_cmd(&parse->command, ft_lstnew_cmd(*parse->s_pipe, PIPE));
				else
					ft_lstadd_back_cmd(&parse->command, ft_lstnew_cmd(*parse->s_pipe, END));
				parse->s_pipe++;
			}
			parse->s_semi++;
		}
	}
	while (parse->command)
	{
		// printf("FIRST  => |%s|\n", parse->command->command);
		parse->command->command = check_dollr(parse, parse->command->command);
		// printf("BEFORE => |%s|\n", parse->command->command);
		parse->command->command = check_command(parse, parse->command->command);
		parse->command->command = sort_redirection(parse, parse->command->command);
		printf("AFTER  => |%s|\nTYPE => |%s|\n\n", parse->command->command, parse->command->type == 3 ? "PIPE" : "END");
		parse->command = parse->command->next;
	}
}

int main(int ac, char **av, char **env)
{
	char *line;
	int r;


	t_parse *parse;
	parse = initail_struct(parse);
	parse->env = env;
	while (1337)
	{
		ft_putstr_fd(MINISHELL, 1);
		r = get_next_line(&line);
		splitted(parse, line);
		free(line);
	}
	return (0);
}
