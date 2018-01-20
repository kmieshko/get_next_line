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

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

#define BUFF_SIZE 32

typedef struct		s_gnl
{
	void			*content;
	size_t			content_size;
	struct s_gnl	*next;
	int				fd;
}					t_gnl;

char	*join(char *s1, char *s2)
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
		if (!(tmp = (t_gnl *)ft_lstnew((void *)buf, ft_strlen(buf))))
			return (NULL);
		tmp->fd = fd;
		ft_lstadd((t_list **)gnl, (t_list *)tmp);
	}
	return (tmp);
}

char		*endl(t_gnl *gnl)
{
	int 	i;
	char	*buf;
	char	*arr;

	i = 0;
	buf = gnl->content;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	i = i == 1 ? i + 1 : i;
	arr = ft_strsub(buf, 0, i);
	ft_strdel(&buf);
	return (arr);
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl	*gnl;
	char			*buf;
	char			*str;
	int				i;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	buf = ft_strnew(BUFF_SIZE);
	while (read(fd, buf, BUFF_SIZE))
	{
		gnl = create_gnl(&gnl, buf, fd);
		if (ft_strchr(gnl->content, '\n') != NULL)
		{
			if (!(str = endl(gnl)))
				return (0);
			i = ft_strlen(str);
			gnl->content = ft_strsub(gnl->content, i, gnl->content_size - i);
			*line = str;
			gnl->content_size = ft_strlen(gnl->content);
			ft_strdel(&buf);
			return (1);
		}
	}
	if (gnl->content_size > 0)
	{
		if (!(str = endl(gnl)))
			return (0);
		i = ft_strlen(str);
		gnl->content = ft_strsub(gnl->content, i, gnl->content_size - i);
		*line = str;
		gnl->content_size = ft_strlen(gnl->content);
		ft_strdel(&buf);
		return (1);
	}
	ft_strdel(&buf);
	if (*line != NULL)
	{
		*line = "\0";
	}
	return (0);
}