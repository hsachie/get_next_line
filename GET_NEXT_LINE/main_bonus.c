/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:23:53 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/09 12:27:22 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1;
    int fd2;
    char *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    line = get_next_line(fd1);
    printf("fd1-1回目: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("fd2-1回目: %s", line);
    free(line);

    line = get_next_line(fd1);
    printf("fd1-2回目: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}