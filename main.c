/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 22:20:49 by omulder        #+#    #+#                */
/*   Updated: 2019/12/06 23:35:58 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// void print_result(char *line)
// {
// 	if (line == NULL)
// 		printf("\n");
// 	else
// 		printf("%s\n", line);
// }

// void bonus_test_three()
// {
// 	int fd1;
// 	int fd2;
// 	int fd3;
// 	char *line;
// 	line = NULL;
// 	fd1 = open("gnl_unit_tests/test_files/easy", O_RDONLY);
// 	fd2 = open("gnl_unit_tests/test_files/standard", O_RDONLY);
// 	fd3 = open("gnl_unit_tests/test_files/data", O_RDONLY);
// 	get_next_line(fd1, &line);
// 	print_result(line);
// 	get_next_line(fd3, &line);
// 	print_result(line);
// 	get_next_line(fd2, &line);
// 	print_result(line);
// 	get_next_line(fd1, &line);
// 	print_result(line);
// 	get_next_line(fd3, &line);
// 	print_result(line);
// 	get_next_line(fd2, &line);
// 	print_result(line);
// 	get_next_line(fd2, &line);
// 	print_result(line);
// 	get_next_line(fd1, &line);
// 	print_result(line);
// 	get_next_line(fd2, &line);
// 	print_result(line);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }

int		main(int ac, char **av)
{
	int		fd;
	int		ret_value;
	char	*line;

	line = NULL;
	if (ac > 1)
		fd = open(av[1], O_RDONLY);
	else
		return (1);
	if (fd == -1)
		return (-1);
	ret_value = 1;
	while (ret_value == 1)
	{
		ret_value = get_next_line(fd, &line);
		printf("%d |>>| %s\n", ret_value, line);
		free(line);
	}
	close(fd);
	// bonus_test_three();
	return (0);
}
