#include "../minishell.h"

char	*delete_quote_off(t_mini *mini, char *line, int *i, int *j)
{
	if (line[*j] == '\\')
	{
		mini->cp ++;
		line[(*i)++] = line[++(*j)];
	}
	else
	{
		if (line[*j] == '"' && mini->cp % 2 == 0)
			mini->smbl->d_quote = ON;
		else if (line[*j] == '\'' && mini->cp % 2 == 0)
			mini->smbl->s_quote = ON;
		else
			line[(*i)++] = line[*j];
	}
}

char	*delete_quote_on(t_mini *mini, char *line, int *i, int *j)
{
	if (mini->smbl->d_quote == ON)
	{
		if (line[*j] == '"')
			mini->smbl->d_quote = OFF;
		else if (line[*j] == '\\' && line[(*j) + 1] == '\\')
			line[(*i)++] = line[++(*j)];
		else if (line[*j] == '\\' && line[(*j) + 1] < 0
			&& line[(*j) + 1] != '\'' * -1)
			line[(*i)++] = line[++(*j)];
		else
			line[(*i)++] = line[*j];
	}
	else if (mini->smbl->s_quote == ON)
	{
		while (line[*j] != '\'')
			line[(*i)++] = line[(*j)++];
		mini->smbl->s_quote = OFF;
	}
	return (line);
}

char	*check_f_cmd(t_mini *mini, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	mini->cp = 0;
	while (line[++j])
	{
		if (mini->smbl->d_quote == OFF && mini->smbl->s_quote == OFF)
			line = delete_quote_off(mini, line, &i, &j);
		else
			line = delete_quote_on(mini, line, &i, &j);
		if (line[j] != '\\')
			mini->cp = 0;
	}
	line[i] = 0;
	return (inverse_line(line));
}
