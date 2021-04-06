#include "../parsing.h"


void	initial_symbol(t_symbol *sbl)
{
	sbl->pipe = OFF;
	sbl->semi = OFF;
	sbl->s_quote = OFF;
	sbl->d_quote = OFF;
	sbl->great = OFF;
	sbl->less = OFF;
	sbl->d_great = OFF;
	sbl->error = OFF;
}

void	off_flags(t_symbol *smbl)
{
	smbl->d_great = 0;
	smbl->less = 0;
	smbl->great = 0;
	smbl->semi = 0;
	smbl->pipe = 0;
}

void	ft_error(t_symbol *smbl, char *str, char *first_color, char *second_color)
{
	ft_putstr_fd(first_color, 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(second_color, 1);
	smbl->error = ON;
}

int		check_flags(t_symbol *smbl)
{
	int sum;

	sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
	return (sum);
}

int 	count_back(char *line)
{
    int cp;

	cp = 0;
    while (*line && *line == '\\')
    {
        cp++;
        line--;
	}
	/*	1	=>	doesnt followed by quotes
		0	=>	followed by quotes
	*/
	if (cp % 2 == 0)
		return (0);
    return (1);
}

//  check " and ' if is closed or note     &	change ; | to non printable characters
char	*partition_stage(t_symbol *smbl, char *line)
{
	int i;

	i = 0;
	initial_symbol(smbl);
	line = ft_strtrim(line, " ");
	if (line[0] == '|')
		ft_error(smbl, "bash: syntax error near unexpected token `|'", RED, WHITE);
	if (line[0] == ';')
		ft_error(smbl, "bash: syntax error near unexpected token `;'", RED, WHITE);
	while (line[i] && !smbl->error)
	{
		if (line[i] == '"')
			line = check_d_quote(smbl, line, i);
		else if (line[i] == '\'')
			line = check_s_quote(smbl, line, i);
		else if (line[i] == '|')
			line = check_pipe(smbl, line, i);
		else if (line[i] == ';')
			line = check_semicolone(smbl, line, i);
		else if (line[i] == '>' && line[i + 1] == '>')
				line = check_redirection(smbl, line, i++, &smbl->d_great);
		else if (line[i] == '>')
			line = check_redirection(smbl, line, i, &smbl->great);
		else if (line[i] == '<')
			line = check_redirection(smbl, line, i, &smbl->less);
		else if (check_flags(smbl) && line[i] != ' ')
				off_flags(smbl);
		i++;
	}
	if (!smbl->error && (smbl->d_great || smbl->d_quote || smbl->s_quote || smbl->pipe || smbl->great || smbl->less))
		ft_error(smbl, "syntax error near unexpected token `newline'", RED, WHITE);
		// multiple_line
		//syntax error near unexpected token `newline'
	// printf("D_Q \t=> |%d|\nS_Q \t=> |%d|\nL \t=> |%d|\nG \t=> |%d|\nD_G \t=> |%d|\nP \t=> |%d|\nS \t=> |%d|\n\n",
	// smbl->d_quote, smbl->s_quote, smbl->less, smbl->great, smbl->d_great, smbl->pipe, smbl->semi);
	printf("=> |%s|\n\n\n", line);
	return line;
}
