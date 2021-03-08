/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:07:53 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 12:22:14 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_pwd()
{
	char    buf[PATH_MAX];
	
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		error_pwd("pwd: ",errno);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf);
	}
}

void    execute_cd(t_builtins *builtins)
{
	int     check_dir;
	char	pwd[PATH_MAX];

	check_dir = chdir(builtins->cd_path);
		if (check_dir == -1 && builtins->cd_path != NULL)
			error_cd(builtins->cd_path, errno);
	getcwd(pwd, PATH_MAX);
}

void	execute_env(t_builtins *builtins, char **split, int i)
{
	char *env[i];
	int		j;

	i = 1;
	j = 0;
	while(split[i] != NULL)
	{
		env[j] = split[i];
		i++;
		j++;
	}
	env[j] = NULL;
	i = 0;
	while(builtins->env[i] != NULL)
	{
		printf("%s\n",builtins->env[i]);
		i++;
	}
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	free_tab(split);
}

void	execute_export(t_builtins *builtins, int b)
{
	int		i;
	t_export	*tmp;
	char		**tab;

	i = 0;
	if (b == 1)
	{
		ft_sort_tab(builtins->env);
		while(builtins->env[i] != NULL)
		{
			printf("declare -x %s\n",builtins->env[i]);
			i++;
		}
		sort_list(builtins->export);
		print_export(builtins);
	}
}

