/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:38:23 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/29 12:25:08 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);

    line = get_next_line(fd);
    printf("1回目: %s", line);
    free(line);

    line = get_next_line(fd);
    printf("2回目: %s", line);
    free(line);

    line = get_next_line(fd);
    printf("3回目: %s", line);
    free(line);

    close(fd);
    return (0);
}