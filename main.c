/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:50:29 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 17:44:14 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void ft_sig_handler(int sig)
{
	if(sig == SIGINT)
		ft_putstr("\b\b  \b\b\n\033[33mminishell\033[0m\033[32m~$\033[0m ");
	if (sig == SIGQUIT)
		ft_putstr("\b\b  \b\b");
}

void execute_ctrld(char *line, int ret, t_builtins *builtins)
{
	if((strcmp(line, "") == 0 && ret == 0) || strcmp(line, "exit") == 0)
	{
		ft_putstr("exit\n");
		free(line);
		exit(EXIT_SUCCESS);
	}
}

void check_command(char *line, char **env, char **argv, t_builtins *built)
{
	int pid;
	char* arg[] = {argv[0], NULL};

	init_builtins (built, env);
	if (strcmp(line, "minishell") == 0)
	{
		pid = fork();
		if(pid == 0)
		{
			execve(argv[0], arg, built->env);
		}
		else if (pid < 0)
			printf("%s\n",strerror(errno));
		else 
			wait(&pid);
	}
	if (strncmp(line, "export", 6) == 0 || strncmp(line, "unset", 5) == 0)
	    parse_export_unset(line, built);
	if (ft_strncmp(line, "pwd",3) == 0)
		execute_pwd();
	// if (strncmp(line, "unset", 5) == 0)
	//     execute_unset(line, built);
	if (strncmp(line, "env", 3) == 0)
	    parse_env(line, built);
	if (ft_strncmp(line,"cd",2) == 0)
		parse_cd(line, built);
}

int main(int argc,  char **argv)
{
	char *buf;
	int ret;
	t_builtins builtins;
	extern char **environ;

	signal(SIGINT,ft_sig_handler);
	signal(SIGQUIT,ft_sig_handler);
	ret = 2;
	while(1)
	{
		if (ret != 0)
			ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		ret = get_next_line(1, &buf);
		execute_ctrld(buf, ret, &builtins);
		check_command(buf,environ, argv, &builtins);
		free(buf);
		// free_builtins(&builtins);
	}
	return (0);
}