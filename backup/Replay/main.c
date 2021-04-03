#include "parsing.h"

t_cmds	*parser(t_cmds *cmds, char *line)
{
	char	*word = "hamid kamal khalid rachid";
	char	**Split;

	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "PIPe", "file1", "great"));

	word = "OMG ACH HADA ASIDI RBIII";
	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "SEMI", "file2", "LESS"));

	word = "There is no power but of GOD";
	Split = ft_split(word, ' ');
	ft_lstadd_back(&cmds, ft_lstnew(Split, "REDI", "file3", "D_red"));
	return cmds;
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
}
