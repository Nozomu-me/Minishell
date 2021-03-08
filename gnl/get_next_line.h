/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:01:48 by amouassi          #+#    #+#             */
/*   Updated: 2019/12/19 17:05:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#define BUFFER_SIZE 1024

size_t		ft_strlen(const char *str);
char		*ft_substr(char const*s, unsigned int start, size_t len);
char		*ft_strjoin(char const*s1, char const *s2);
char		*ft_strdup(const char *s1);
int			get_next_line(int fd, char **line);
int			find_index(char *str, char c);
#endif
