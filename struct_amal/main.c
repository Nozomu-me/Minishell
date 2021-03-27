#include "struct_amal.h"

void	parser(t_cmds *cmds, char *line)
{
	char	*word = "hamid kamal khalid rachid";
	char	**Split;

	Split = ft_split(word, ' ');
	// ft_lstadd_back(&cmds, ft_lstnew(Split, "PIPe", ))
}

int main()
{
	char *line;
	t_cmds *cmds;

	cmds = NULL;
	line = NULL;
		parser(cmds, line);
	// while (1337)
	// {
	// 	get_next_line(&line);
	// 	free(line);
	// }
}
