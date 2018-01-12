/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:04:04 by kmieshko          #+#    #+#             */
/*   Updated: 2018/01/12 14:04:06 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

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

t_gnl	endl(t_gnl gnl)
{
	size_t	i;

	i = 0;
	while (gnl.buf[i] != '\0')
	{
		printf("buf[%zu] = %c\n", i, gnl.buf[i]);
		if (gnl.buf[i + 1] == '\n')
		{
			printf("_i_buf[%zu] = %c\n", i, gnl.buf[i]);
			gnl.flag = 1;
			i++;
			printf("_i_buf[%zu] = %c\n", i, gnl.buf[i]);
			break;
		}
		i++;
	}
	if (gnl.flag == 1)
	{
		if (gnl.tmp == NULL)
		{
			printf("flag = 1 && tmp == NULL\n");
			gnl.tmp = ft_strsub(gnl.buf, 0, i);
			printf("gnl.tmp %s\n", gnl.tmp);
			gnl.tmp[i] = '\0';
		}
		else
		{
			printf("flag = 1 && tmp != NULL\n");
			gnl.tmp = join(gnl.tmp, ft_strsub(gnl.buf, i + 1, ft_strlen(gnl.buf) - i));
			printf("gnl.tmp %s\n", gnl.tmp);
			gnl.tmp[i] = '\0';
		}
		if (i < ft_strlen(gnl.buf))
		{
			printf("flag = 1 && i < ft_strlen(gnl.buf)\n");
			gnl.buf = ft_strsub(gnl.buf, i + 1, ft_strlen(gnl.buf) - i);
			endl(gnl);
			printf("gnl.tmp %s\n", gnl.tmp);
		}
	}
	else
	{
		printf("flag = 0 && i => ft_strlen(gnl.buf)\n");
		if (gnl.tmp == NULL)
		{
			printf("CREATE GNL.TMP!\n");
			gnl.tmp = ft_strnew(i);
		}
		gnl.tmp = join(gnl.tmp, gnl.buf);
		printf("gnl.tmp %s\n", gnl.tmp);
	}
	//if (i < ft_strlen(gnl.buf))
	//	endl(gnl);
	return (gnl);
}
	
int	get_next_line(int fd, char **line)
{
	t_gnl	gnl;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	gnl.fd = fd;
	gnl.i = 0;
	gnl.buf = ft_strnew(BUFF_SIZE);
	gnl.tmp = NULL;
	while (read(gnl.fd, gnl.buf, BUFF_SIZE) != '\0')
	{
		gnl = endl(gnl);
		gnl.i++;
	}
	if (gnl.i == 0)
		return (0);
	ft_strdel(&gnl.buf);
	return (1);
}
