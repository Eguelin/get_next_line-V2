/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:09:44 by eguelin           #+#    #+#             */
/*   Updated: 2023/12/22 22:52:26 by eguelin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int		ft_read(\
int fd, t_list **list, char buf[BUFFER_SIZE + 1], int *is_end);
static char		*ft_join_list(t_list *list);
static size_t	ft_size_of_join(t_list *list);
static char		*ft_dupbuf(char buf[BUFFER_SIZE + 1], int *is_end);

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	int			is_end;
	char		*line;
	t_list		*list;

	if (fd < 0)
		return (NULL);
	is_end = 0;
	list = NULL;
	if (buf[fd][0])
	{
		line = ft_dupbuf(buf[fd], &is_end);
		if (!line)
			return (NULL);
		list = ft_lstnew(line);
		if (!list)
			return (free(line), NULL);
	}
	line = NULL;
	if (ft_read(fd, &list, buf[fd], &is_end))
		ft_memset(buf[fd], 0, BUFFER_SIZE + 1);
	else
		line = ft_join_list(list);
	ft_lstclear(&list, free);
	return (line);
}

static int	ft_read(\
int fd, t_list **list, char buf[BUFFER_SIZE + 1], int *is_end)
{
	ssize_t	read_return;
	char	*str;
	t_list	*new;

	read_return = BUFFER_SIZE;
	while (read_return == BUFFER_SIZE && !(*is_end))
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return == -1)
			return (1);
		str = ft_dupbuf(buf, is_end);
		if (!str)
			return (1);
		new = ft_lstnew(str);
		if (!new)
		{
			free(str);
			return (1);
		}
		ft_lstadd_back(list, new);
	}
	return (0);
}

static char	*ft_join_list(t_list *list)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!list)
		return (NULL);
	i = ft_size_of_join(list);
	if (!i)
		return (NULL);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (list)
	{
		j = 0;
		while (list->content && ((char *)(list->content))[j])
			line[i++] = ((char *)(list->content))[j++];
		list = list->next;
	}
	line[i] = 0;
	return (line);
}

static size_t	ft_size_of_join(t_list *list)
{
	size_t	size;

	if (!list)
		return (0);
	size = 0;
	while (list->next)
	{
		size += BUFFER_SIZE;
		list = list->next;
	}
	if (list->content)
		size += ft_strlen(list->content);
	return (size);
}

static char	*ft_dupbuf(char buf[BUFFER_SIZE + 1], int *is_end)
{
	size_t	i;
	size_t	j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(BUFFER_SIZE + 1);
	if (!copy)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		copy[i++] = buf[i];
	if (buf[i] == '\n')
	{
		*is_end = 1;
		copy[i++] = buf[i];
		copy[i] = 0;
		while (buf[i])
			buf[j++] = buf[i++];
	}
	else
		copy[i] = 0;
	ft_memset(buf + j, 0, BUFFER_SIZE - j);
	return (copy);
}
