/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/01/24 16:32:58 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include <stdio.h>

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_img_data;

void	pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*pix_addr;

	pix_addr = img_data->addr + (
		y * img_data->line_length + x * (img_data->bits_per_pixel / 8)
	);
	*(unsigned int *)pix_addr = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img_data	img_data;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "HELLO");
	img_data.img = mlx_new_image(mlx, 1920, 1080);
	img_data.addr = mlx_get_data_addr(
		img_data.img,
		&img_data.bits_per_pixel,
		&img_data.line_length,
		&img_data.endian
	);
	//printf("bits_per_pixel == %d\n", img_data.bits_per_pixel);
	//printf("line_length == %d\n", img_data.line_length);
	//printf("endian == %d\n", img_data.endian);
	//pixel_put(&img_data, 150, 150, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img_data.img, 0, 0);
	int	i = 0;
	while (i < 100)
	{
		pixel_put(&img_data, 19 * i, 150, 0x00FF0000);
		pixel_put(&img_data, 19 * i + 1, 150, 0x00FF0000);
		pixel_put(&img_data, 19 * i, 151, 0x00FF0000);
		pixel_put(&img_data, 19 * i + 1, 151, 0x00FF0000);
		i++;
	}
	mlx_loop(mlx);
}
