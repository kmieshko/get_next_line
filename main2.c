#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int i;
	char *line;
	int	fd;

	i = 1;
	fd = open(argv[1], O_RDONLY);
	//fd = 1;
	int j = 0;
	while ((j = get_next_line(fd, &line)) > 0)
	{
		printf("(%d) %s\n", j, line);
		free(line);
	}
	j = get_next_line(fd, &line);
	close(fd);
	printf("(%d) %s\n", j, line);
	system("leaks -quiet a.out");
	return (0);
}