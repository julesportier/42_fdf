/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:13:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:12:43 by juportie         ###   ########.fr       */
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
		err_exit("get_fd() error: Wrong filename or extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror_exit("get_fd() error");
	return (fd);
}

t_grid_data	get_grid_size(int fd)
{
	t_grid_data	grid_data;
	char		*line;
	char		**splits;
	int			temp;

	ft_bzero(&grid_data, sizeof(t_grid_data));
	while (1)
	{
		line = remove_end_nl(get_next_line(fd));
		if (line == NULL && grid_data.width != 0)
			return (grid_data);
		if (line == NULL && grid_data.width == 0)
			err_exit("get_grid_size() error: file is empty");
		if (++grid_data.height < 0)
			err_free_exit(line, "get_grid_size() error: line number overflow");
		splits = ft_split(line, ' ');
		if (splits == NULL)
			err_free_exit(line, "get_grid_size() error: ft_split() error");
		temp = split_digit_len(splits);
		free_splits(splits);
		if (temp != grid_data.width && grid_data.width != 0 || temp < 0)
			err_free_exit(line, "get_grid_size() error: wrong file formating");
		grid_data.width = temp;
		free(line);
	}
}

t_pixel	**malloc_grid(t_grid_data *grid_data)
{
	t_pixel	**grid;
	int		i;

	if (grid_data->height == 1 && grid_data->width == 1)
		err_exit("map to small");
	i = 0;
	grid = malloc(grid_data->height * sizeof(t_pixel *));
	if (grid == NULL)
		perror_exit("malloc_grid() error");
	while (i < grid_data->height)
	{
		grid[i] = malloc(grid_data->width * sizeof(t_pixel));
		if (grid[i] == NULL)
			err_freegrid_exit(grid, i,
				"malloc_grid() error: subarray malloc failed");
		ft_bzero(grid[i], grid_data->width * sizeof(t_pixel));
		i++;
	}
	return (grid);
}

void	fill_grid(t_pixel **grid, t_grid_data *grid_data, int fd)
{
	char	*line;
	char	**splits;
	int		r;
	int		c;

	r = 0;
	while (r < grid_data->height)
	{
		line = remove_end_nl(get_next_line(fd));
		if (line == NULL)
			err_freegrid_exit(grid, grid_data->height, "fill_grid() error");
		splits = ft_split(line, ' ');
		free(line);
		if (splits == NULL)
			err_freegrid_exit(grid, grid_data->height, "fill_grid() error");
		c = -1;
		while (++c < grid_data->width)
			grid[r][c].z = ft_atoi(splits[c]);
		free_splits(splits);
		r++;
	}
}
