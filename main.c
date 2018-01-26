/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:12:15 by kmieshko          #+#    #+#             */
/*   Updated: 2018/01/25 13:20:44 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	while ((i = get_next_line(fd1, &line)) > 0)
	{
		printf("(%d) %s\n", i, line);
		free(line);
	}
	i = get_next_line(fd1, &line);
	printf("(%d) %s\n", i, line);
	close(fd1);
	printf("------------------\n");
	while ((j = get_next_line(fd2, &line)) > 0)
	{
		printf("(%d) %s\n", j, line);
		free(line);
	}
	j = get_next_line(fd2, &line);
	printf("(%d) %s\n", j, line);
	close(fd2);
	system("leaks -quiet a.out");
	return (0);
}
