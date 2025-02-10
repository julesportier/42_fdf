/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/07 10:09:46 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "libft/libft.h"
#include "minilibx/mlx.h"
//#include <math.h>
#include "libft/ftpf_printf.h"
#include <stdio.h>
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
	t_pixel	**grid = malloc_grid(grid_data);
	fd = get_fd("test.fdf");
	fill_grid(grid, grid_data, fd);
	close(fd);
	store_max_alt(&grid_data, grid);
	ft_printf("grid max alt == %d\ngrid min alt == %d\n", grid_data.alt_max, grid_data.alt_min);
	//store_start_point(&grid_data);
	//ft_printf("start.x == %d\nstart.y == %d\n", grid_data.start_point.x, grid_data.start_point.y);
	//ft_err_free2d_exit(grid, grid_data.height, "free grid");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "HELLO");
	img_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_data.addr = mlx_get_data_addr(
		img_data.img,
		&img_data.bits_per_pixel,
		&img_data.line_length,
		&img_data.endian
	);
	store_iso_pos(&img_data, &grid_data, grid);
	store_pos_limits(&grid_data, grid);
	printf("grid max y == %f, grid max x == %f\n", grid_data.y_max, grid_data.x_max);
	printf("grid min y == %f, grid min x == %f\n", grid_data.y_min, grid_data.x_min);
	scale_limits(&grid_data, grid);
	printf("grid max y == %f, grid max x == %f\n", grid_data.y_max, grid_data.x_max);
	printf("grid min y == %f, grid min x == %f\n", grid_data.y_min, grid_data.x_min);
	store_spacing(&grid_data);
	printf("grid spacing == %f\n", grid_data.spacing);
	scale_to_win(&grid_data, grid);
	draw_grid(&img_data, &grid_data, grid);
	mlx_put_image_to_window(mlx, mlx_win, img_data.img, 0, 0);
	mlx_loop(mlx);
}
