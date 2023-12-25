/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:36:00 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/22 23:04:20 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

int	main(int argc, const char **argv)
{
	int		i;
	char	*line;
	char	*line2;
	int		fd;
	int		fd2;

	i = 0;
	if (argc != 3)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open(argv[2], O_RDONLY);
	if (fd2 == -1)
		return (close(fd), 1);
	while (1)
	{
		line = get_next_line(fd);
		line2 = get_next_line(fd2);
		printf("%il:	%s%il:	%s", i, line, i, line2);
		if (!line || !line2)
			break ;
		free(line);
		free(line2);
		i++;
	}
	free(line);
	free(line2);
	close(fd);
	close(fd2);
	return (0);
}
