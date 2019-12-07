/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:28:06 by omulder        #+#    #+#                */
/*   Updated: 2019/12/07 23:02:49 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

int		ft_strfind_c(const char *s, int c)
{
	int		i;

	i = 0;
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

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s1[size] != '\0')
		size++;
	s2 = (char*)malloc(size + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoinfree_s1(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = ft_memalloc(ft_strfind_c(s1, '\0') + ft_strfind_c(s2, '\0') + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		join[i] = s2[j];
		j++;
		i++;
	}
	free(s1);
	return (join);
}

t_fdlist	*fdlist_add_new(t_fdlist **lst, int fd)
{
	t_fdlist	*new;

	new = ft_memalloc(sizeof(t_fdlist));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->buf = NULL;
	new->next = *lst;
	*lst = new;
	return (new);
}
