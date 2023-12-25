/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:36:00 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/22 23:03:05 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, const char **argv)
{
	char	*line;
	int		i;
	int		fd;

	if (argc != 2)
		return (1);
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		printf("%il:	%s", i, line);
		if (!line)
			break ;
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
