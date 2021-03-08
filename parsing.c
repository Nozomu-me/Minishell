/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:07:40 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 15:15:30 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cd(char *line, t_builtins *builtins)
{
	int		count;
	char	**split;
	char	**home;
	char	*reptab;
	char	oldpwd[PATH_MAX];

	count = 0;
	reptab = search_replace(line, "\t", " ");
	split = ft_split(reptab, ' ');
	while (split[count] != NULL)
		count++;
	home = ft_getenv("HOME", builtins->env);
	if ((ft_strcmp(split[0], "cd") == 0 ||
	ft_strcmp(split[0], "cd\n") == 0) && count == 1)
		builtins->cd_path = ft_strdup(home[1]);
	else if (split[1][0] == '~')
		builtins->cd_path = search_replace(split[1], "~", home[1]);
	else
		builtins->cd_path = ft_strdup(split[1]);
	getcwd(oldpwd, PATH_MAX);
	modify_env(builtins->env, "OLDPWD", builtins->cd_path);
	free_tab(split);
	free_tab(home);
	free(reptab);
	execute_cd(builtins);
}

int		check_env(char *s)
{
	int i;
	char **split;

	split = ft_split(s, '=');
	i = 0;
	while (split[i] != NULL)
		i++;
	if (i > 1)
	{
		free_tab(split);
		return (1);
	}
	free_tab(split);
	return (0);
}

void	parse_env(char *line, t_builtins *builtins)
{
	int		i;
	char	**split;
	char	*reptab;

	i = 1;
	reptab = search_replace(line, "\t", " ");
	split = ft_split(reptab, ' ');
	free(reptab);
	while (split[i] != NULL)
	{
		if (check_env(split[i]) == 0)
		{
			if(strcmp(split[i],"=") == 0 || strcmp(split[i], "==") == 0)
				printf("env: setenv %s: Invalid argument\n", split[i]);
			else 
				printf("env: %s: No such file or directory\n", split[i]);
			free_tab(split);
			return ;
		}
		i++;
	}
	execute_env(builtins, split, i);
}

// int 	sub_check_export_valid(char *line)
// {
	
// 	int		check;
// 	int		eq;
// 	int		i;

// 	eq = 0;
// 	i = 0;
// 	check = check_caract(line, '\"');
// 	while(line[i] != '\0')
// 	{
// 		if(line[i])
// 	}
// 	if (check == 2 && eq == 0)
// 		return (1);
// }

int		check_export_valid(char *var)
{
	int		i;
	if (ft_strcmp(var, "=") == 0 || ft_strcmp(var, "==") == 0)
		return (1);
	i = 0;
	while(var[i] != '\0')
	{
		if(var[i] == '=' && i == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_name_exist(t_builtins *builtins, char *name)
{
	t_export	*tmp;
	char		**split1;
	char		**split2;

	tmp = builtins->export;

	while(tmp != NULL)
	{
		split1 = ft_split(tmp->var, '=');
		split2 = ft_split(name, '=');
		if(ft_strcmp(split1[0], split2[0]) == 0)
		{
			tmp->var = ft_strdup(name);
			free_tab(split1);
			free_tab(split2);
			return (1);
		}
		tmp = tmp->next;
		free_tab(split1);
		free_tab(split2);
	}
	return (0);
}

void	parse_export(char *line, t_builtins *builtins)
{
	t_export	*test;
	char		*str;
	int			i;
	char		**split;
	char		*reptab;

	reptab = search_replace(line, "\t", " ");
	split = ft_split(reptab, ' ');
	i = 1;
	while(split[i] != NULL)
	{
		if(check_export_valid(split[i]) == 1)
			error_export(split[i]);
		else
		{
			if(check_name_exist(builtins, split[i]) == 0)
			{
				str = ft_strdup(split[i]);
				test = ft_lstnew(str);
				ft_lstadd_back(&builtins->export, test);
			}
		}			
		i++;
	}
	free(reptab);
	free_tab(split);
	execute_export(builtins, i);
}

void	parse_export_unset(char *line, t_builtins *builtins)
{
	parse_export(line, builtins);
}
