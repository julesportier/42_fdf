/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/06 12:29:49 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "libft/libft.h"
#include "minilibx/mlx.h"
//#include <math.h>
#include "libft/ftpf_printf.h"
//DEBUG
//#include <stdio.h>

/*
Input coordinates:
----------
|    1   |
|-1  0  1|
|   -1   |
----------
*/
//static t_pos	scale_pixel(double x, double y, int width, int height)
//{
//	t_pos	pixel;
//
//	x = (x + 1) * 0.5;
//	y = (y + 1) * 0.5;
//	pixel.x = x * width;
//	pixel.y = y * height;
//	return (pixel);
//}
//
//static void	put_pixel(t_img_data *img_data, int x, int y, int color)
//{
//	char	*pix_addr;
//
//	pix_addr = img_data->addr + (
//		y * img_data->line_length + x * (img_data->bits_per_pixel / 8)
//	);
//	*(unsigned int *)pix_addr = color;
//}
//
//static void	put_square(t_img_data *img_data, int x, int y, int color, int size)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < size)
//	{
//		j = 0;
//		while (j < size)
//		{
//			if (x + i <= WIDTH && y + j <= HEIGHT)
//				put_pixel(img_data, x + i, y + j, color);
//			if (x + i <= WIDTH && y - j <= HEIGHT)
//				put_pixel(img_data, x + i, y - j, color);
//			if (x - i <= WIDTH && y + j <= HEIGHT)
//				put_pixel(img_data, x - i, y + j, color);
//			if (x - i <= WIDTH && y - j <= HEIGHT)
//				put_pixel(img_data, x - i, y - j, color);
//			j++;
//		}
//		i++;
//	}
//}
//

static void	put_square(t_img_data *img_data, t_pixel pixel, int size)
{
	int	i;
	int	j;
	t_pixel	pix;

	i = 0;
	pix.color = pixel.color;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (pixel.x + i <= WIDTH && pixel.y + j <= HEIGHT)
			{
				pix.x = pixel.x + i;
				pix.y = pixel.y + j;
				put_pixel(img_data, pix);
			}
			if (pixel.x + i <= WIDTH && pixel.y - j <= HEIGHT)
			{
				pix.x = pixel.x + i;
				pix.y = pixel.y - j;
				put_pixel(img_data, pix);
			}
			if (pixel.x - i <= WIDTH && pixel.y + j <= HEIGHT)
			{
				pix.x = pixel.x - i;
				pix.y = pixel.y + j;
				put_pixel(img_data, pix);
			}
			if (pixel.x - i <= WIDTH && pixel.y - j <= HEIGHT)
			{
				pix.x = pixel.x - i;
				pix.y = pixel.y - j;
				put_pixel(img_data, pix);
			}
			j++;
		}
		i++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img_data	img_data;

	int	fd = get_fd("test.fdf");
	t_grid_data	grid_data = get_grid_size(fd);
	ft_printf("grid_data.width == %d\n", grid_data.width);
	ft_printf("grid_data.height == %d\n", grid_data.height);
	close(fd);
	int	**grid = malloc_grid(grid_data);
	fd = get_fd("test.fdf");
	fill_grid(grid, grid_data, fd);
	close(fd);
	int	i = 0;
	while (i < grid_data.height)
	{
		int j = 0;
		while (j < grid_data.width)
		{
			ft_printf("grid[%d][%d] == %d\n", i, j, grid[i][j]);
			j++;
		}
		i++;
	}
	store_max_alt(&grid_data, grid);
	ft_printf("grid max alt == %d\ngrid min alt == %d\n", grid_data.alt_max, grid_data.alt_min);
	store_spacing(&grid_data);
	ft_printf("grid spacing == %d\n", grid_data.spacing);
	store_start_point(&grid_data);
	ft_printf("start.x == %d\nstart.y == %d\n", grid_data.start_point.x, grid_data.start_point.y);
	ft_err_free2d_exit(grid, grid_data.height, "free grid");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "HELLO");
	img_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_data.addr = mlx_get_data_addr(
		img_data.img,
		&img_data.bits_per_pixel,
		&img_data.line_length,
		&img_data.endian
	);
	t_pixel	pix_a = { .x = 10, .y = 81, .color = 0x00FF0000 };
	t_pixel	pix_b = { .x = 1920, .y = 1001, .color = 0x00FF0000 };
	draw_line(&img_data, pix_a, pix_b);
	mlx_put_image_to_window(mlx, mlx_win, img_data.img, 0, 0);
	mlx_loop(mlx);
}
//
//int	main(void)
//{
//	void	*mlx;
//	void	*mlx_win;
//	t_img_data	img_data;
//	t_pos	pixel;
//
//	mlx = mlx_init();
//	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "HELLO");
//	img_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
//	img_data.addr = mlx_get_data_addr(
//		img_data.img,
//		&img_data.bits_per_pixel,
//		&img_data.line_length,
//		&img_data.endian
//	);
//	//ft_printf("bits_per_pixel == %d\n", img_data.bits_per_pixel);
//	//ft_printf("line_length == %d\n", img_data.line_length);
//	//ft_printf("endian == %d\n", img_data.endian);
//	double	x = -0.5;
//	double	y = 0.5;
//	int	i = 0;
//	while (i < 2)
//	{
//		int	j = 0;
//		while (j < 2)
//		{
//			pixel = scale_pixel(x + j, y - i, WIDTH, HEIGHT);
//			ft_printf("x == %d; y == %d\n", pixel.x, pixel.y);
//			//put_pixel(&img_data, pixel.x + j, pixel.y - i, 0x00FF0000);
//			put_square(
//				&img_data, pixel.x, pixel.y, 0x00FF0000, 7
//			);
//			j++;
//		}
//		i++;
//	}
//	mlx_put_image_to_window(mlx, mlx_win, img_data.img, 0, 0);
//	t_pos	pos_a = { .x = 0, .y = 0 };
//	t_pos	pos_b = { .x = 3, .y = 1 };
//	draw_line(pos_a, pos_b);
//	mlx_loop(mlx);
//}
