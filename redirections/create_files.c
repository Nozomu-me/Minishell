/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:19:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/17 15:59:01 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_perm(t_cflist *file)
{
	struct stat		buf;
	int				status;

	status = stat(file->name, &buf);
	if (status == 0)
	{
		if ((buf.st_mode & S_IRUSR) == 0)
			return (1);
		if ((buf.st_mode & S_IWUSR) == 0)
			return (1);
		return (2);
	}
	return (0);
}

int	create_write(t_cflist *tmp, int *fd, t_cflist **w)
{
	int	perm;

	if (tmp->name[0] == '$' && tmp->file_dollar)
	{
		g_check.exit_status = -2;
		error_nodir(tmp->name);
		return (-1);
	}
	*fd = open(tmp->name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	perm = check_file_perm(tmp);
	if (perm == 1)
	{
		ft_putendl_fd("permission denied", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (perm == 2 && *fd == -1)
	{
		ft_putendl_fd("is a directory1", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (*fd == -1)
	{
		error_nodir(tmp->name);
		g_check.exit_status = -2;
		return (-1);
	}
	close(*fd);
	*w = tmp;
	return (0);
}

int	create_read(t_cflist *tmp, int *fd, t_cflist **r)
{
	int	perm;

	if (tmp->name[0] == '$' && tmp->file_dollar)
	{
		g_check.exit_status = -2;
		error_nodir(tmp->name);
		return (-1);
	}
	*fd = open(tmp->name, O_RDONLY);
	perm = check_file_perm(tmp);
	if (perm == 1)
	{
		ft_putendl_fd("permission denied", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (perm == 2 && *fd == -1)
	{
		ft_putendl_fd("is a directory2", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (*fd == -1)
	{
		error_nodir(tmp->name);
		g_check.exit_status = -2;
		return (-1);
	}
	close(*fd);
	*r = tmp;
	return (0);
}

int	create_append(t_cflist *tmp, int *fd, t_cflist **w)
{
	int	perm;
	if (tmp->name[0] == '$' && tmp->file_dollar)
	{
		g_check.exit_status = -2;
		error_nodir(tmp->name);
		return (-1);
	}
	*fd = open(tmp->name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	perm = check_file_perm(tmp);
	if (perm == 1)
	{
		ft_putendl_fd("permission denied", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (perm == 2 && *fd == -1)
	{
		ft_putendl_fd("is a directory3", 1);
		g_check.exit_status = -2;
		return (-1);
	}
	if (*fd == -1)
	{
		error_nodir(tmp->name);
		g_check.exit_status = -2;
		return (-1);
	}
	close(*fd);
	*w = tmp;
	return (0);
}

int	create_files(t_mini *mini, t_cflist **w, t_cflist **r, int *fd)
{
	t_cflist	*tmp;

	tmp = mini->cmds.file;
	while (tmp != NULL)
	{
		if (tmp->type == WRITE)
		{
			if (create_write(tmp, fd, w) == -1)
				return (-1);
		}
		if (tmp->type == READ)
		{
			if (create_read(tmp, fd, r) == -1)
				return (-1);
		}
		else if (tmp->type == APPEND)
		{
			if (create_append(tmp, fd, w) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
