/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 19:11:50 by pbondoer          #+#    #+#             */
/*   Updated: 2017/12/06 04:44:01 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

static char		*join(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*arr;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !(arr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		arr[i] = s2[j];
		i++;
		j++;
	}
	arr[i] = '\0';
	ft_strdel(&s1);
	return (arr);
}

static t_gnl	*create_gnl(t_gnl **gnl, char *buf, int fd)
{
	t_gnl	*tmp;

	tmp = *gnl;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp)
	{
		if (!(tmp->content = join((char *)tmp->content, buf)))
			return (NULL);
		tmp->content_size = ft_strlen(tmp->content);
	}
	else
	{
		if (!(tmp = (t_gnl *)ft_lstnew((void *)buf, ft_strlen(buf) + 1)))
			return (NULL);
		tmp->fd = fd;
		ft_lstadd((t_list **)gnl, (t_list *)tmp);
	}
	return (tmp);
}

int		check(t_gnl *gnl, char **line)
{
	char	*buf;
	char	*arr;
	int		i;

	i = 0;
	buf = gnl->content;

	if (buf == NULL)
		return (0);
	while (buf[i] != '\n' && buf[i])
		i++;
	if (i == 0 && ft_strstr(buf, "\n") == NULL)
		return (0);
	arr = ft_strsub(buf, 0, i);
	ft_strdel(&buf);
	*line = arr;
	gnl->content = ft_strsub(gnl->content, i + 1, gnl->content_size);
	gnl->content_size = gnl->content_size - i - 1;
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl	*gnl;
	int j;
	char	*buf;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	buf = ft_strnew(BUFF_SIZE);
	while ((j = read(fd, buf, BUFF_SIZE)))
	{
		buf[j] = '\0';
		gnl = create_gnl(&gnl, buf, fd);
		if (ft_strchr(buf, '\n') != NULL)
		{
			if (check(gnl, line) == 1)
				return (1);
		}
	}
	if (gnl->content_size > 0)
		if (check(gnl, line) == 1)
			return (1);
	ft_strdel(&buf);
	if (*line != NULL)
		*line = "\0";
	return (0);
}