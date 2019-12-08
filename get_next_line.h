/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 18:25:22 by omulder        #+#    #+#                */
/*   Updated: 2019/12/08 10:12:41 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	4
# endif
# define FUNCT_ERROR	-1
# define FUNCT_EOF		0
# define FUNCT_SUCCESS	1

# include <unistd.h>

/*
**	Main
*/

int				get_next_line(int fd, char **line);

/*
**	Utils
*/

typedef struct	s_fdlist
{
	int				fd;
	char			*buf;
	struct s_fdlist	*next;
}				t_fdlist;

int			ft_strfind_c(const char *s, int c);
char		*ft_strjoinfree_s1(char *s1, char *s2);
void		*ft_memalloc(size_t size);
t_fdlist	*fdlist_find_create(t_fdlist **lst, int fd);
int			free_buffer_item(t_fdlist **lst, t_fdlist *current);

#endif
