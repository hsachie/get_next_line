#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	line = get_next_line(fd1);
	if (line) printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	if (line) printf("fd2: %s", line);
	free(line);
	line = get_next_line(fd1);
	if (line) printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	if (line) printf("fd2: %s", line);
	free(line);
	close(fd1);
	close(fd2);
	return (0);
}