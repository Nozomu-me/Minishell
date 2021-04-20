/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 12:02:56 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

///////////////////////////////////////////////////////////////////////
void	add_new_env_element(t_env *curr_node, char *env)
{
	int		len;

	len = 0;
	while (env[len] != '=')
		len++;
	curr_node->name = ft_substr(env, 0, len);
	curr_node->value = ft_strdup(env + len + 1);
	curr_node->next = NULL;
}

t_env	*create_env_list(char **env)
{
	t_env	*env_list;
	t_env	*curr_node;
	int		i;

	env_list = malloc(sizeof(t_env));
	curr_node = env_list;
	add_new_env_element(curr_node, env[0]);
	i = 1;
	while (env[i])
	{
		curr_node->next = malloc(sizeof(t_env));
		curr_node = curr_node->next;
		add_new_env_element(curr_node, env[i]);
		i++;
	}
	return (env_list);
}
/////////////////////////////////////////////////////////////////////////

t_parse	*initail_struct(t_parse *parse, char **env)
{
	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->check_env = "=~\\/%#{}$*+-.:?@[]^ '\"";
	parse->smbl = (t_symbol *)malloc(sizeof(t_symbol));
	parse->f_cmd = NULL;
	parse->under_score = ft_strdup("./minishell");
	parse->smbl->already_pipe = 0;
	parse->s_semi = NULL;
	parse->s_pipe = NULL;
	parse->env2 = create_env_list(env);
	return (parse);
}

void	split_pipe(t_parse *parse, char *tmp_pipe, int *j, int *len)
{
	tmp_pipe = ft_strtrim(parse->s_pipe[*j], " ");
	free(parse->s_pipe[*j]);
	parse->s_pipe[*j] = tmp_pipe;
	if (--(*len))
		lstadd_cmd(&parse->f_cmd, lstnew_cmd(parse->s_pipe[*j], PIPE));
	else
		lstadd_cmd(&parse->f_cmd, lstnew_cmd(parse->s_pipe[*j], END));
}

void	split_semi_pipe(t_parse *parse, char *line, int len, int i)
{
	char *tmp_semi;
	char *tmp_pipe;
	int	j;

	parse->s_semi = ft_split(line, ';');
	while (parse->s_semi[++i])
	{
		tmp_semi = ft_strtrim(parse->s_semi[i], " ");
		free(parse->s_semi[i]);
		parse->s_semi[i] = tmp_semi;
		parse->s_pipe = ft_split(parse->s_semi[i], '|');
		while (parse->s_pipe[len])
			len++;
		j = -1;
		while (parse->s_pipe[++j])
			split_pipe(parse, tmp_pipe, &j, &len);
		ft_free_tab(parse->s_pipe);
	}
	ft_free_tab(parse->s_semi);
}

/* void	parsing(t_parse *parse, char *line)
{
	char	*tmp;
	
	// search_replace(parse, line, "\t", " ");	
	line = partition_stage(parse->smbl, line);
	if (!parse->smbl->error)
		split_semi_pipe(parse, line, 0);
	while (parse->f_cmd)
	{
		parse->f_cmd->cmd = search_replace(parse, parse->f_cmd->cmd, "\t", " ");
		parse->f_cmd->cmd = check_dollr(parse, parse->f_cmd->cmd);
		push_to_struct(parse, parse->f_cmd->cmd);
		parse->under_score = parse->f_cmd->cmd;
		parse->f_cmd = parse->f_cmd->next;
	}
} */

void	cmd_free(t_f_cmd *next, t_parse *parse)
{
	next = parse->f_cmd->next;
	free(parse->f_cmd->cmd);
	free(parse->f_cmd);
	parse->f_cmd = next;
}

void	parsing(t_parse *parse, char *line)
{
	char	*tmp;
	char	*tmp1;
	t_f_cmd *next;

	line = partition_stage(parse->smbl, line);
	if (!parse->smbl->error)
		split_semi_pipe(parse, line, 0, -1);
	while (parse->f_cmd)
	{
		// search_replace(parse, parse->f_cmd->cmd, "\t", " ");
		parse->f_cmd->cmd = check_dollr(parse, parse->f_cmd->cmd);
		push_to_struct(parse, parse->f_cmd->cmd);
		free(parse->under_score);
		parse->under_score = ft_strdup(parse->f_cmd->cmd);
		cmd_free(next, parse);
	}
	free(line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_parse	*parse;
	
	line = NULL;
	parse = initail_struct(parse, env);
	while (1337)
	{
		ft_putstr_fd(MINISHELL, 1);
		get_next_line(&line);
		parsing(parse, line);
		if (!parse->smbl->error || !strcmp(line, "exit"))
		{
			printf("%sFREE STRUCT%s\n", BLUE, WHITE);
			free_cmds_struct(parse);
		}
		if (!strcmp(line, "exit"))
		{
			printf("%sFREE SMBL%s\n", BLUE, WHITE);
			free(parse->smbl);
			exit(0);
		}
		if (line)
		{
			free(line);
		}
	}
	return (0);
}
