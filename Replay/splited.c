/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/05 19:06:41 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	splitted(t_command *cmds, char *line)
{
	t_symbol smbl;
	char	**s_splited;
	char	**p_splited;
	int		i;

	i = 0;
	line = partition_stage(&smbl, line);
	if (!smbl.error)
	{
		s_splited = ft_split(line, ';');
		while (*s_splited)
		{
			*s_splited = ft_strtrim(*s_splited, " ");
			p_splited = ft_split(*s_splited, '|');
			while (p_splited[i])
				i++;
			while (*p_splited)
			{
				*p_splited = ft_strtrim(*p_splited, " ");
				if (--i)
					ft_lstadd_back_cmd(&cmds, ft_lstnew_cmd(*p_splited, PIPE));
				else
					ft_lstadd_back_cmd(&cmds, ft_lstnew_cmd(*p_splited, END));
				p_splited++;
			}
			s_splited++;
		}
	}
	while (cmds)
	{
		printf("CMD  => |%s|\nTYPE => |%s|\n\n", cmds->command, cmds->type == 3 ? "PIPE" : "END");
		cmds = cmds->next;
	}
}

int main()
{
	char *line;
	line = NULL;
	t_command *cmds;
	t_symbol *smbl;

	cmds = NULL;
	while (1337)
	{
		ft_putstr_fd(MINISHELL, 1);
		get_next_line(&line);
		splitted(cmds, line);
		free(line);
	}
}

/* int main(int argc, char const *argv[])
{
	char *str = ft_strdup(";;;;;;;\"kamlid;hamid\";rachid\"helo;\"");
	char **splited;
	puts(str);
	splited = ft_split(str, ';');
	while (*splited)
	{
		printf("|%s|\n", *splited);
		splited++;
	}
	puts("\n");
	str = change(str, ';', SEMI);
	puts(str);
	splited = ft_split(str, ';');
	while (*splited)
	{
		printf("|%s|\n", *splited);
		splited++;
	}
 	return 0;
} */
