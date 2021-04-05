/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/05 19:36:50 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command		*ft_lstnew_cmd(char *v_cmd, int type)
{
	t_command *new;

	new = (t_command*)malloc(sizeof(t_command));
	if (new)
	{
		new->command = v_cmd;
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back_cmd(t_command **alst, t_command *new)
{
	t_command *list;
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

/*
t_file		*ft_lstnew_file(char *f_name, char *f_type)
{
	t_file *new;

	new = (t_file*)malloc(sizeof(t_file));
	if (new)
	{
		new->filename = f_name;
		new->filetype = f_type;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back_file(t_file **alst, t_file *new)
{
	t_file *list;

	list = NULL;
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

t_cmds		*ft_lstnew(char **v_cmd, char *v_type, char *f_name, char *f_type)
{
	t_cmds *new;

	new = (t_cmds*)malloc(sizeof(t_cmds));
	new->file = NULL;
	if (new)
	{
		new->cmd = v_cmd;
		new->type = v_type;
		ft_lstadd_back_file(&new->file, ft_lstnew_file(f_name, f_type));
		new->file->next = NULL;
		// new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back(t_cmds **alst, t_cmds *new)
{
	t_cmds *list;
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

t_cmds		*parser(t_cmds *cmds, char *line)
{
	char	*word = ft_strdup("hamid kamal khalid rachid");
	char	**Split;

	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "PIPe", "file1", "great"));
	word = "ONE TWO TREE FOUR FIVE SEXE";
	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "SEMI", "file2", "LESS"));

	word = "There is no power but of GOD";
	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "REDI", "file3", "D_red"));
	return cmds;
}

void		affichage(char *line, t_cmds *cmds)
{
	cmds = NULL;
	cmds = parser(cmds, line);
	while (cmds)
	{
		printf("CMDS ==>  ");
		while (*cmds->cmd)
			printf("|%s| ", *cmds->cmd++);
		printf("\nTYPE ==>  |%s|\n", cmds->type);
		while (cmds->file)
		{
			printf("FILE ==>  |%s|\t|%s|\n", cmds->file->filename, cmds->file->filetype);
			cmds->file = cmds->file->next;
		}
		if (cmds->next)
			puts("");
		cmds = cmds->next;
	}
}

int main()
{
	char *line = "echo hello \"word; next\" time";
	t_cmds *cmds;

	affichage(line, cmds);
	// while (1337)
	// {
	// 	get_next_line(&line);
	// 	free(line);
	// }
}*/
