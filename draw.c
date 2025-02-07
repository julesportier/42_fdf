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

void	draw_grid(t_img_data *img_data, t_grid_data *grid_data, int **grid)
{
	int	y;
	int	x;
	t_pixel	pixel;

	y = 0;
	pixel.color = 0x00FFFF00;
	while (y < grid_data->height)
	{
		x = 0;
		pixel.y = grid_data->start_point.y + (grid_data->spacing * y);
		while (x < grid_data->width)
		{
			pixel.x = grid_data->start_point.x + (grid_data->spacing * x);
			put_pixel(img_data, pixel);
			x++;
		}
		y++;
	}
}

void	draw_iso_grid(t_img_data *img_data, t_grid_data *grid_data, int **grid)
{
	int	r;
	int	c;
	t_pixel	pixel;

	pixel.color = 0x00FFFFFF;
	r = 0;
	while (r < grid_data->height)
	{
		c = 0;
		while (c < grid_data->width)
		{
		// replace WIDTH and HEIGHT to values that centers the grid (with ZOOM ?)
			pixel.x = (c*grid_data->spacing - r*grid_data->spacing)*0.71 + WIDTH/2;
			// replace multiplication by 2 by a difference between max_alt and min_alt
			pixel.y = -0.82*(grid[r][c]*2)
				+ 0.41*(c*grid_data->spacing + r*grid_data->spacing)
				+ HEIGHT/2;
			ft_printf("x == %d, y == %d, alt == %d\n", pixel.x, pixel.y, grid[r][c]);
			put_pixel(img_data, pixel);
			c++;
		}
		r++;
	}
}
//void	draw_iso_grid(t_img_data *img_data, t_grid_data *grid_data, int **grid)
//{
//	int	r;
//	int	c;
//	int	temp_x;
//	int	temp_y;
//	t_pixel	pixel;
//
//	r = 0;
//	pixel.color = 0x00FFFFFF;
//	while (r < grid_data->height)
//	{
//		c = 0;
//		temp_y = grid_data->start_point.y + (grid_data->spacing * r);
//		while (c < grid_data->width)
//		{
//			temp_x = grid_data->start_point.x + (grid_data->spacing * c);
//			pixel.x = (temp_x - temp_y)*0.71;
//			pixel.y = 0.82*grid[r][c] - 0.41*(temp_x + temp_y);
//			ft_printf("x == %d, y == %d, alt == %d\n", pixel.x, pixel.y, grid[r][c]);
//			put_pixel(img_data, pixel);
//			c++;
//		}
//		r++;
//	}
//}
//void	draw_iso_grid(t_img_data *img_data, t_grid_data *grid_data, int **grid)
//{
//	int	y;
//	int	x;
//	int	temp_x;
//	int	temp_z;
//	t_pixel	pixel;
//
//	y = 0;
//	pixel.color = 0x00FFFF00;
//	while (y < grid_data->height)
//	{
//		x = 0;
//		temp_z = grid_data->start_point.y + (grid_data->spacing * y);
//		while (x < grid_data->width)
//		{
//			temp_x = grid_data->start_point.x + (grid_data->spacing * x);
//			pixel.x = (temp_x - grid[y][x]) * 0.71;
//			pixel.y = 0.82*temp_z - 0.41*(temp_x + grid[y][x]);
//			ft_printf("x == %d, y == %d\n", pixel.x, pixel.y);
//			put_pixel(img_data, pixel);
//			x++;
//		}
//		y++;
//	}
//}
