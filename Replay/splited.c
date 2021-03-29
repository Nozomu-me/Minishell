/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:20:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/29 15:41:32 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#define SEMI 128
#define PIPE 129
#define LESS 130
#define GREAT 131
#define SPACE 132
#define ERROR 1
#define ON 1
#define OFF 0

int 	count_back(char *line)
{
    int cp;

	cp = 0;
    while (*line == '\\')
    {
        cp++;
        line--;
	}
	/*	if returned 1 then \ isn't followed by ' or "	*/
	if (cp % 2 == 0)
		return (1);
    return (0);
}

//  check " and ' if is closed or note     &	change ; | to non printable characters
char	*partition_stage(char *line, int *error)
{
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
				line[i] = (char)SEMI;
			if (line[i] == '|' && (d_quote == ON || s_quote == ON))
				line[i] = (char)PIPE;
			if (line[i] == '>' && (d_quote == ON || s_quote == ON))
				line[i] = (char)GREAT;
			if (line[i] == '<' && (d_quote == ON || s_quote == ON))
				line[i] = (char)LESS;
			if (line[i] == ' ' && (d_quote == ON || s_quote == ON))
				line[i] = (char)SPACE;
			i++;
		}
	//print if ' " is not closed
	if (d_quote == ON || s_quote == ON)
		ft_error("Syntax Error", RED, WHITE, error);
	return (line);
}

void	splitted(char *line)
{
	char	**splitted;
	int		error;

	error = 0;
	line = partition_stage(line, &error);
	if (!error)
	{
		splitted = ft_split(line, ';');
		while (*splitted)
		{
			printf("|%s|\n", *splitted);
			splitted++;
		}
	}
}

void	check_splited(char *str)
{

}

int main()
{
	char *line;
	line = NULL;

	while (1337)
	{
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
