/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:13:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/04 14:04:42 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	get_fd(char *filename)
{
	int	fd;
	int	name_len;

	name_len = ft_strlen(filename);
	if (name_len < 4 || ft_strncmp(&filename[name_len - 4], ".fdf", 4))
	{
		ft_putendl_fd("Wrong filename or extension", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open() error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_grid_data	get_grid_size(int fd)
{
	char	*line;
	char	**splits;
	t_grid_data	grid;
	int	temp;

	ft_bzero(&grid, sizeof(t_grid_data));
	while (1)
	{
		line = remove_end_nl(get_next_line(fd));
		if (line == NULL && grid.width != 0)
			return (grid);
		if (line == NULL && grid.width == 0)
			ft_err_exit("file is empty");
		if (++grid.height < 0)
			ft_err_free_exit(line, "line number overflow");
		splits = ft_split(line, ' ');
		if (splits == NULL)
			ft_err_free_exit(line, "ft_split() error");
		temp = ft_splitlen(splits);
		if (temp != grid.width && grid.width != 0)
			ft_err_free_exit(line, "wrong file formating");
		grid.width = temp;
		free(line);
		line = NULL;
	}
}
