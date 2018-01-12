/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:00:48 by kmieshko          #+#    #+#             */
/*   Updated: 2018/01/10 15:00:50 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFF_SIZE 5

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct	f_gnl
{
	int		fd;
	int		i;
	int		flag;
	char	*buf;
	char	**tmp;
}				t_gnl;

int		get_next_line(const int fd, char **line);

#endif