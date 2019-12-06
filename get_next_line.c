/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:28:29 by omulder        #+#    #+#                */
/*   Updated: 2019/12/06 23:31:30 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_fdlist	*fdlist_find_create(t_fdlist **lst, int fd)
{
	t_fdlist	*current;

	if (lst == NULL || *lst == NULL)
		return (fdlist_add_new(lst, fd));
	current = *lst;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (fdlist_add_new(lst, fd));
}

int			get_from_buffer(t_fdlist *current, char **line)
{
	int		find;
	char	*tmp;

	free(*line);
	find = ft_strfind_c(current->buf, '\n');
	if (find == -1)
	{
		*line = ft_strdup(current->buf);
		free(current->buf);
		current->buf = NULL;
		return (0);
	}
	current->buf[find] = '\0';
	*line = ft_strdup(current->buf);
	find++;
	tmp = ft_strdup(&(current->buf[find]));
	free(current->buf);
	current->buf = NULL;
	if (tmp == NULL)
		return (-1);
	if (*tmp != '\0')
		current->buf = tmp;
	else
		free(tmp);
	return (1);
}

int			check_read_buf(t_fdlist *current, char **line, char *read_buf,
int ret)
{
	int		find;

	find = 0;
	find = ft_strfind_c(read_buf, '\n');
	if (find != -1)
		read_buf[find] = '\0';
	*line = ft_strjoinfree_s1(*line, read_buf);
	if (*line == NULL)
		return (-1);
	if (find != -1)
	{
		find++;
		current->buf = ft_strdup(&(read_buf[find]));
		if (current->buf == NULL)
			return (-1);
		free(read_buf);
		return (1);
	}
	free(read_buf);
	if (ret < BUFFER_SIZE)
		return (0);
	return (2);
}

int			get_line(t_fdlist *current, char **line)
{
	int		ret;
	char	*read_buf;

	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE)
	{
		read_buf = ft_memalloc(BUFFER_SIZE + 1);
		ret = read(current->fd, read_buf, BUFFER_SIZE);
		if (ret == 0 || ret == -1)
			free(read_buf);
		if (ret == -1)
			return (FUNCT_ERROR);
		if (ret == 0)
			return (FUNCT_EOF);
		ret = check_read_buf(current, line, read_buf, ret);
		if (ret == 1)
			return (FUNCT_SUCCESS);
		if (ret == 0)
			return (FUNCT_EOF);
		if (ret == -1)
			return (FUNCT_ERROR);
		if (ret == 2)
			ret = BUFFER_SIZE;
	}
	return (FUNCT_SUCCESS);
}

int			get_next_line(int fd, char **line)
{
	static t_fdlist	*lst;
	t_fdlist		*current;
	int				ret;

	if (fd < 0 || line == NULL)
		return (FUNCT_ERROR);
	current = fdlist_find_create(&lst, fd);
	if (current == NULL)
		return (FUNCT_ERROR);
	*line = ft_memalloc(1);
	if (current->buf != NULL)
	{
		ret = get_from_buffer(current, line);
		if (ret == -1)
			return (FUNCT_ERROR);
		if (ret == 1)
			return (FUNCT_SUCCESS);
	}
	if (*line == NULL)
		return (FUNCT_ERROR);
	ret = get_line(current, line);
	return (ret);
}
