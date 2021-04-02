/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/02 23:01:40 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


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
	if (cp % 2 == 0)// && cp != 0)
		return (0);
	// if (cp == 0)
	// 	return 2;
    return (1);
}

void	initial_symbol(t_symbol *sbl)
{
	sbl->pipe = OFF;
	// puts("t");
	sbl->semi = OFF;
	sbl->s_quote = OFF;
	sbl->d_quote = OFF;
	sbl->great = OFF;
	sbl->less = OFF;
	sbl->d_great = OFF;
}

//  check " and ' if is closed or note     &	change ; | to non printable characters
char	*partition_stage(char *line, int *error)
{
	t_symbol *smbl;
	t_symbol smbl2;
	int i;

	i = 0;
	smbl = &smbl2;
	// puts("ok");
	initial_symbol(smbl);
	line = ft_strtrim(line, " ");
	if (line[0] == '|' || line[0] == ';')
		ft_error("Syntax error", RED, WHITE);
	while (line[i])
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
		else
		{
			int sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
			if (sum && line[i] != ' ')
			{
				smbl->d_great = 0;
				smbl->less = 0;
				smbl->great = 0;
				smbl->semi = 0;
				smbl->pipe = 0;
			}
		}
		i++;
	}
	if (smbl->d_great || smbl->d_quote || smbl->s_quote || smbl->pipe || smbl->great || smbl->less)
		ft_error("Syntax Error hhh", RED, WHITE);
	printf("D_Q \t=> |%d|\nS_Q \t=> |%d|\nL \t=> |%d|\nG \t=> |%d|\nD_G \t=> |%d|\nP \t=> |%d|\nS \t=> |%d|\n\n",
	smbl->d_quote, smbl->s_quote, smbl->less, smbl->great, smbl->d_great, smbl->pipe, smbl->semi);
	printf("=> |%s|\n", line);
	return line;
}

/* {
	int i;
	int d_quote;
	int s_quote;

	i = 0;
	d_quote = OFF;
	s_quote = OFF;
	//skip space and tab
	line = ft_strtrim(line, " ");
	if (line[0] == ';' || line[0] == '|')
		ft_error("SYNTAX ERROR ; |", RED, WHITE, error);
	//check if " or ' is closed
	else
		while (line[i])
		{
			if (line[i] == '\'')
			{
				if (s_quote == ON)
					s_quote = OFF;
				else if (s_quote == OFF && count_back(line + (i - 1)))
					if (d_quote == OFF)
						s_quote = ON;
			}
			else if (line[i] == '"' && count_back(line + (i - 1)))
			{
				if (d_quote == OFF && s_quote == OFF)
					d_quote = ON;
				else if (d_quote == ON && s_quote == OFF)
					d_quote = OFF;
			}
			// Change ; | to NON PRINTABLE characters
			if (line[i] == ';' && line[i + 1] == ';' && d_quote == OFF && s_quote == OFF)
			{
				ft_error("Syntax error ';", RED, WHITE, error);
				break ;
			}
			if (line[i] == ';' && (d_quote == ON || s_quote == ON))
				line[i] = ';';
			if (line[i] == '|' && (d_quote == ON || s_quote == ON))
				line[i] = '|';
			if (line[i] == '>' && (d_quote == ON || s_quote == ON))
				line[i] = '>';
			if (line[i] == '<' && (d_quote == ON || s_quote == ON))
				line[i] = '<';
			if (line[i] == ' ' && (d_quote == ON || s_quote == ON))
				line[i] = ' ';
			i++;
		}
	//print if ' " is not closed
	if (d_quote == ON || s_quote == ON)
		ft_error("Syntax Error", RED, WHITE, error);
	return (line);
} */

void	splitted(char *line)
{
	char	**splitted;
	int		error;

	error = 0;
	line = partition_stage(line, &error);
	// if (!error)
	// {
	// 	splitted = ft_split(line, ';');
	// 	while (*splitted)
	// 	{
	// 		printf("|%s|\n", *splitted);
	// 		splitted++;
	// 	}
	// }
}

int main()
{
	char *line;
	line = NULL;

	while (1337)
	{
		ft_putstr_fd(MINISHELL, 1);
		get_next_line(&line);
		splitted(line);
		// partition_stage(line);
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
