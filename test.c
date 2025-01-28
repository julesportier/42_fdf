/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/01/27 15:33:44 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Input coordinates:
----------
|    1   |
|-1  0  1|
|   -1   |
----------
*/
static t_pos	scale_pixel(double x, double y, int width, int height)
{
	t_pos	pixel;

	x = (x + 1) * 0.5;
	y = (y + 1) * 0.5;
	pixel.x = x * width;
	pixel.y = y * height;
	return (pixel);
}

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
static void	put_pixel(t_img_data *img_data, t_pixel pixel)
{
	char	*pix_addr;

	pix_addr = img_data->addr + (
		pixel.y * img_data->line_length + pixel.x * (img_data->bits_per_pixel / 8)
	);
	*(unsigned int *)pix_addr = pixel.color;
}

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

static void	draw_line(t_img_data *img_data, t_pixel pixel, t_pos_d pos_a, t_pos_d pos_b)
{
	int	step_nbr;
	double	x_step;
	double	y_step;
	int	i;

	if (ft_memcmp(&pos_a, &pos_b, sizeof(t_pos_d)) == 0)
		return;
	x_step = pos_b.x - pos_a.x;
	y_step = pos_b.y - pos_a.y;
	if (fabs(x_step) >= fabs(y_step))
		step_nbr = fabs(x_step);
	else
		step_nbr = fabs(y_step);
	x_step = x_step / step_nbr;
	y_step = y_step / step_nbr;
	i = 0;
	while (i <= step_nbr)
	{
		printf("x[%d] == %ld\n", i, lround(pos_a.x + i * x_step));
		printf("y[%d] == %ld\n", i, lround(pos_a.y + i * y_step));
		pixel.x = roundf(pos_a.x + i * x_step);
		pixel.y = roundf(pos_a.y + i * y_step);
		put_pixel(img_data, pixel);
		i++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img_data	img_data;
	t_pixel	pixel;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "HELLO");
	img_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_data.addr = mlx_get_data_addr(
		img_data.img,
		&img_data.bits_per_pixel,
		&img_data.line_length,
		&img_data.endian
	);
	t_pos_d	pos_a = { .x = 10, .y = 81 };
	t_pos_d	pos_b = { .x = 1920, .y = 1001 };
	pixel.color = 0x00FF0000;
	draw_line(&img_data, pixel, pos_a, pos_b);
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
