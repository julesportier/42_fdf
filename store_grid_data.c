/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_grid_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:35:39 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:19:04 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	store_max_alt(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	grid_data->alt_max = grid[0][0].z;
	grid_data->alt_min = grid[0][0].z;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			if (grid[y][x].z < grid_data->alt_min)
				grid_data->alt_min = grid[y][x].z;
			if (grid[y][x].z > grid_data->alt_max)
				grid_data->alt_max = grid[y][x].z;
			x++;
		}
		y++;
	}
}

void	store_spacing(t_grid_data *grid_data, t_pixel **grid)
{
	float	height;
	float	width;

	grid_data->x_max = (grid_data->width - 1) * 0.71;
	grid_data->x_min = (0 - (grid_data->height - 1)) * 0.71;
	grid_data->y_max = -0.82 * (
			(float)grid[grid_data->height - 1][grid_data->width - 1].z / (
				(grid_data->alt_max - grid_data->alt_min)
				/ ((float)(grid_data->height + grid_data->width) / 16)))
		+ 0.41 * (grid_data->width - 1 + (grid_data->height - 1));
	grid_data->y_min = -0.82 * ((float)grid[0][0].z / (
				(grid_data->alt_max - grid_data->alt_min)
				/ ((float)(grid_data->height + grid_data->width) / 16)));
	height = ((float)HEIGHT * ZOOM) / (grid_data->y_max - grid_data->y_min);
	width = ((float)WIDTH * ZOOM) / (grid_data->x_max - grid_data->x_min);
	if (height < width)
		grid_data->spacing = height;
	else
		grid_data->spacing = width;
}

static void	get_color(t_grid_data *grid_data, t_pixel *cell)
{
	unsigned int	mask;
	float			ratio;
	int				color_ext;
	int				tmp_neut;
	int				tmp_ext;

	color_ext = COLOR_H;
	if (cell->z > 0)
		ratio = (float)cell->z / grid_data->alt_max;
	else if (cell->z == 0)
		ratio = 0;
	else if (cell->z < 0)
	{
		color_ext = COLOR_L;
		ratio = (float)cell->z / grid_data->alt_min;
	}
	mask = BLUE;
	cell->color = 0;
	while (mask <= RED)
	{
		tmp_ext = color_ext & mask;
		tmp_neut = COLOR_M & mask;
		cell->color |= (int)((tmp_ext - tmp_neut) * ratio + tmp_neut) & mask;
		mask = mask << 8;
	}
}

void	store_iso_pos(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			get_color(grid_data, &grid[y][x]);
			grid[y][x].x = (float)((x - y) * 0.71 - grid_data->x_min)
				*grid_data->spacing + (WIDTH - (float)WIDTH * ZOOM) / 2;
			grid[y][x].y = (-0.82 * ((float)grid[y][x].z / (
							(grid_data->alt_max - grid_data->alt_min)
							/ ((float)(grid_data->height + grid_data->width)
								/ 16)))
					+ 0.41 * (x + y) - grid_data->y_min)
				* grid_data->spacing
				+ (HEIGHT - (float)HEIGHT * ZOOM) / 2;
			printf("x == %d, y == %d, alt == %d, color == %x\n", grid[y][x].x, grid[y][x].y, grid[y][x].z, grid[y][x].color);
			x++;
		}
		y++;
	}
}
