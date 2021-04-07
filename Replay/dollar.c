#include "parsing.h"

int main(int ac, char **av, char **env)
{
	t_parse *parse;
	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->env = env;
	while(*parse->env)
	{
		puts(*parse->env);
		parse->env++;
	}
}
