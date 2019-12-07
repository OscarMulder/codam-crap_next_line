/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:28:29 by omulder        #+#    #+#                */
/*   Updated: 2019/12/08 00:09:00 by omulder       ########   odam.nl         */
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

	find = ft_strfind_c(current->buf, '\n');
	if (find == -1)
	{
		*line = ft_strjoinfree_s1(*line, current->buf);
		free(current->buf);
		current->buf = NULL;
		return (0);
	}
	current->buf[find] = '\0';
	*line = ft_strjoinfree_s1(*line, current->buf);
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

int			free_buffer_item(t_fdlist **lst, t_fdlist *current)
{
	t_fdlist *ptr;

	free(current->buf);
	if (*lst == current)
		*lst = (*lst)->next;
	else
	{
		ptr = *lst;
		while (ptr->next != current)
			ptr = ptr->next;
		ptr->next = current->next;
	}
	free(current);
	return (FUNCT_EOF);
}

int			get_line(t_fdlist **lst, t_fdlist *current, char **line)
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
			return (free_buffer_item(lst, current));
		current->buf = read_buf;
		ret = get_from_buffer(current, line);
		if (ret == -1)
			return (FUNCT_ERROR);
		if (ret == 1)
			return (FUNCT_SUCCESS);
		if (ret == 0)
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
	ret = get_line(&lst, current, line);
	return (ret);
}
