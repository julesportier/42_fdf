/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:55:06 by juportie          #+#    #+#             */
/*   Updated: 2025/02/07 14:52:04 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ftpf_printf.h"
//#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
//#include "libft/ftpf_printf.h"
//DEBUG
//#include <stdio.h>

void	put_pixel(t_img_data *img_data, t_pixel pixel)
{
	char	*pix_addr;

	pix_addr = img_data->addr + (
			pixel.y * img_data->line_length
			+ pixel.x * (img_data->bits_per_pixel / 8)
			);
	*(unsigned int *)pix_addr = pixel.color;
}

void	draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b)
{
	int		step_nbr;
	double	x_step;
	double	y_step;
	int		i;

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
	i = 0;
	while (i <= step_nbr)
	{
		//printf("x[%d] == %ld\n", i, lround(pix_a.x + i * x_step));
		//printf("y[%d] == %ld\n", i, lround(pix_a.y + i * y_step));
		pix_b.x = roundf(pix_a.x + i * x_step);
		pix_b.y = roundf(pix_a.y + i * y_step);
		put_pixel(img_data, pix_b);
		i++;
	}
}

void	draw_grid(t_img_data *img_data, t_grid_data *grid_data, t_pixel **grid)
{
	int	y;
	int	x;
	t_pixel	pixel;

	y = 0;
	while (y < grid_data->height)
	{
		x = 0;
		while (x < grid_data->width)
		{
			grid[y][x].color = 0x00FFFFFF;
			put_pixel(img_data, grid[y][x]);
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
				-0.82*((float)grid[r][c].z/((grid_data->alt_max - grid_data->alt_min)*2))
				+ 0.41*(c + r);
			printf("x == %f, y == %f, alt == %d\n", grid[r][c].ax, grid[r][c].ay, grid[r][c].z);
			c++;
		}
		r++;
	}
}
