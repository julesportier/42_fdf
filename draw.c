/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:55:06 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:20:58 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	put_pixel(t_img_data *img_data, t_pixel pixel)
{
	char	*pix_addr;

	pix_addr = img_data->addr + (
			pixel.y * img_data->line_length
			+ pixel.x * (img_data->bits_per_pixel / 8)
			);
	*(unsigned int *)pix_addr = pixel.color;
}

static int	interpolate_color(t_pixel *pix_a, int color_b, int step_nbr, int i)
{
	int				color_ext;
	int				tmp_b;
	int				tmp_a;
	int				color;
	unsigned int	mask;

	if (i == 0)
		return (pix_a->color);
	mask = BLUE;
	color = 0;
	while (mask <= RED)
	{
		tmp_b = color_b & mask;
		tmp_a = pix_a->color & mask;
		color |= (int)((tmp_b - tmp_a) * ((float)i / step_nbr) + tmp_a) & mask;
		mask = mask << 8;
	}
	return (color);
}

void	draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b)
{
	int		step_nbr;
	double	x_step;
	double	y_step;
	int		i;
	int		color_b;

	if (pix_a.x == pix_b.x && pix_a.y == pix_b.y)
		return ;
	x_step = pix_b.x - pix_a.x;
	y_step = pix_b.y - pix_a.y;
	if (fabs(x_step) >= fabs(y_step))
		step_nbr = fabs(x_step);
	else
		step_nbr = fabs(y_step);
	x_step = x_step / step_nbr;
	y_step = y_step / step_nbr;
	color_b = pix_b.color;
	i = -1;
	while (++i <= step_nbr)
	{
		pix_b.x = roundf(pix_a.x + i * x_step);
		pix_b.y = roundf(pix_a.y + i * y_step);
		pix_b.color = interpolate_color(&pix_a, color_b, step_nbr, i);
		put_pixel(img_data, pix_b);
	}
}

void	draw_grid(t_img_data *img_data, t_grid_data *grid_data, t_pixel **grid)
{
	int		y;
	int		x;
	t_pixel	pixel;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			if (x != grid_data->width - 1)
				draw_line(img_data, grid[y][x], grid[y][x + 1]);
			if (y != grid_data->height - 1)
				draw_line(img_data, grid[y][x], grid[y + 1][x]);
			x++;
		}
		y++;
	}
}
