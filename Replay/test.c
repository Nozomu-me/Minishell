#include "libft/libft.h"
#include <stdio.h>


typedef enum	e_type
{
	PIPE,
	END
}				t_type;

typedef	struct	s_cmd
{
	char			*command;
	t_type			type;
	struct s_cmd	*next;
}				t_cmd;


t_cmd		*ft_lstnew(char *v_cmd, int type)
{
	t_cmd *new;

	new = (t_cmd*)malloc(sizeof(t_cmd));
	if (new)
	{
		new->command = v_cmd;
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd *list;
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

int main()
{
	t_cmd *cmds;
	char **s_splited;
	char **p_splited;
	cmds = NULL;
	int j = 0;
	char *line = "ls -la | hamid ; khalid rachid | wahd";


	printf("%s\n\n", line);
	line = ft_strtrim(line, " ");
	s_splited = ft_split(line, ';');
	while (*s_splited)
	{
		*s_splited = ft_strtrim(*s_splited, " ");
		p_splited = ft_split(*s_splited, '|');
		while (p_splited[j])
			j++;
		while (*p_splited)
		{
			*p_splited = ft_strtrim(*p_splited, " ");
			if (--j)
				ft_lstadd_back(&cmds, ft_lstnew(*p_splited, PIPE));
			else
				ft_lstadd_back(&cmds, ft_lstnew(*p_splited, END));
			p_splited++;
		}
		s_splited++;
	}
	while (cmds)
	{
		printf("CMD  => |%s|\nTYPE => |%s|\n\n", cmds->command, cmds->type == 0 ? "PIPE" : "END");
		cmds = cmds->next;
	}
}