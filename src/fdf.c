/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:31:43 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static	t_grid_data	get_map_size(char *map)
{
	int			fd;
	t_grid_data	grid_data;

	fd = get_fd(map);
	grid_data = get_grid_size(fd);
	if (close(fd))
		perror_exit("get_map_size()");
	return (grid_data);
}

static	t_pixel	**parse_map(char *map, t_grid_data *grid_data)
{
	t_pixel	**grid;
	int		fd;

	grid = malloc_grid(grid_data);
	fd = get_fd(map);
	fill_grid(grid, grid_data, fd);
	if (close(fd))
	{
		perror("parse_map()");
		freegrid(grid);
		exit(EXIT_FAILURE);
	}
	store_max_alt(grid_data, grid);
	store_spacing(grid_data, grid);
	store_iso_pos(grid_data, grid);
	return (grid);
}

static int	allocate_mlx(t_mlx_data *mlx_data, char *map)
{
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
		return (-1);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIDTH, HEIGHT, map);
	if (mlx_data->win == NULL)
	{
		free_mlx(mlx_data);
		return (-1);
	}
	mlx_data->img.img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (mlx_data->img.img == NULL)
	{
		free_mlx(mlx_data);
		return (-1);
	}
	mlx_data->img.addr = mlx_get_data_addr(
			mlx_data->img.img, &mlx_data->img.bits_per_pixel,
			&mlx_data->img.line_length, &mlx_data->img.endian);
	if (mlx_data->img.addr == NULL)
	{
		free_mlx(mlx_data);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	t_grid_data	grid_data;
	t_pixel		**grid;

	if (argc != 2)
		err_exit("missing map name argument");
	grid_data = get_map_size(argv[1]);
	grid = parse_map(argv[1], &grid_data);
	if (allocate_mlx(&mlx_data, argv[1]) == -1)
		err_freegrid_exit(-1, grid, "allocate_mlx() error");
	draw_grid(&mlx_data.img, &grid_data, grid);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img.img, 0, 0);
	mlx_hook(mlx_data.win, ON_DESTROY, 1L << 3, end_loop_mouse, &mlx_data);
	mlx_key_hook(mlx_data.win, end_loop_esc, &mlx_data);
	mlx_loop(mlx_data.mlx);
	free_mlx(&mlx_data);
	freegrid(grid);
	return (0);
}
