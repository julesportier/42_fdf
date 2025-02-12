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

static void	interpolate_color(t_grid_data *grid_data, t_pixel *cell)
{
	float	ratio;
	unsigned int	mask;
	int	color_ext;
	int	tmp_neut;
	int	tmp_ext;

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

void	store_colors(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			interpolate_color(grid_data, &grid[y][x]);
			x++;
		}
		y++;
	}
}

void	store_iso_pos(t_img_data *img_data, t_grid_data *grid_data, t_pixel **grid)
{
	int	r;
	int	c;

	r = 0;
	while (r < grid_data->height)
	{
		c = 0;
		while (c < grid_data->width)
		{
			grid[r][c].ax = (c - r)*0.71;
			grid[r][c].ay =
				-0.82 * (
					(float)grid[r][c].z / (
						(grid_data->alt_max - grid_data->alt_min)
						/ ((float)(grid_data->height + grid_data->width)/16)
					)
				)
				+ 0.41*(c + r);
			c++;
		}
		r++;
	}
}

void	store_pos_limits(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	grid_data->x_max = grid[0][0].ax;
	grid_data->x_min = grid[0][0].ax;
	grid_data->y_max = grid[0][0].ay;
	grid_data->y_min = grid[0][0].ay;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			if (grid[y][x].ax < grid_data->x_min)
				grid_data->x_min = grid[y][x].ax;
			if (grid[y][x].ax > grid_data->x_max)
				grid_data->x_max = grid[y][x].ax;
			if (grid[y][x].ay < grid_data->y_min)
				grid_data->y_min = grid[y][x].ay;
			if (grid[y][x].ay > grid_data->y_max)
				grid_data->y_max = grid[y][x].ay;
			x++;
		}
		y++;
	}
}

void	scale_limits(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			grid[y][x].ax -= grid_data->x_min;
			grid[y][x].ay -= grid_data->y_min;
			x++;
		}
		y++;
	}
	grid_data->x_max -= grid_data->x_min;
	grid_data->x_min -= grid_data->x_min;
	grid_data->y_max -= grid_data->y_min;
	grid_data->y_min -= grid_data->y_min;
}

void	store_spacing(t_grid_data *grid_data)
{
	float	height;
	float	width;

	height = ((float)HEIGHT * ZOOM) / grid_data->y_max;
	width = ((float)WIDTH * ZOOM) / grid_data->x_max;
	if (height < width)
		grid_data->spacing = height;
	else
		grid_data->spacing = width;
}

void	scale_to_win(t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			grid[y][x].x = grid[y][x].ax * grid_data->spacing + (WIDTH - (float)WIDTH * ZOOM) / 2;
			grid[y][x].y = grid[y][x].ay * grid_data->spacing + (HEIGHT - (float)HEIGHT * ZOOM) / 2;
			printf("x == %d, y == %d, alt == %d\n", grid[y][x].x, grid[y][x].y, grid[y][x].z);
			x++;
		}
		y++;
	}
}
