/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_grid_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:35:39 by juportie          #+#    #+#             */
/*   Updated: 2025/02/06 13:03:08 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	store_max_alt(t_grid_data *grid_data, int **grid)
{
	int	y;
	int	x;

	y = 0;
	grid_data->alt_max = grid[0][0];
	grid_data->alt_min = grid[0][0];
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			if (grid[y][x] < grid_data->alt_min)
				grid_data->alt_min = grid[y][x];
			if (grid[y][x] > grid_data->alt_max)
				grid_data->alt_max = grid[y][x];
			x++;
		}
		y++;
	}
}

void	store_spacing(t_grid_data *grid_data)
{
	int	height;
	int	width;

	height = (HEIGHT * ZOOM / 100) / grid_data->height;
	width = (WIDTH * ZOOM / 100) / grid_data->width;
	if (height < width)
		grid_data->spacing = height;
	else
		grid_data->spacing = width;
}

void	store_start_point(t_grid_data *grid_data)
{
	grid_data->start_point.y = (
			(HEIGHT - grid_data->spacing * (grid_data->height - 1)) / 2);
	grid_data->start_point.x = (
			(WIDTH - grid_data->spacing * (grid_data->width - 1)) / 2);
}
