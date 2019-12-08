/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:28:06 by omulder        #+#    #+#                */
/*   Updated: 2019/12/08 10:12:33 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int		ft_strfind_c(const char *s, int c)
{
	int		i;

	i = 0;
	if (s == NULL && c == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

void		*ft_memalloc(size_t size)
{
	void	*new;
	size_t	i;

	new = malloc(size);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char*)new)[i] = 0;
		i++;
	}
	return (new);
}

char	*ft_strjoinfree_s1(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = ft_memalloc(ft_strfind_c(s1, '\0') + ft_strfind_c(s2, '\0') + 1);
	if (join == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		join[i] = s2[j];
		j++;
		i++;
	}
	if (s1 != NULL)
		free(s1);
	return (join);
}

t_fdlist	*fdlist_find_create(t_fdlist **lst, int fd)
{
	t_fdlist	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	current = ft_memalloc(sizeof(t_fdlist));
	if (current == NULL)
		return (NULL);
	current->fd = fd;
	current->buf = NULL;
	current->next = *lst;
	*lst = current;
	return (current);
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