/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 10:49:42 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "libft/libft.h"
#include "minilibx/mlx.h"
//#include <math.h>
#include "libft/ftpf_printf.h"
//DEBUG
#include <stdio.h>

int	main(void)
{
	t_mlx_data	mlx_data;
	t_img_data	img_data;
	char	*map = "maps/10-2.fdf";
	//char	*map = "maps/mars.fdf";
	//char	*map = "test.fdf";

	int	fd = get_fd(map);
	t_grid_data	grid_data = get_grid_size(fd);
	ft_printf("grid_data.width == %d\n", grid_data.width);
	ft_printf("grid_data.height == %d\n", grid_data.height);
	close(fd);
	t_pixel	**grid = malloc_grid(grid_data);
	fd = get_fd(map);
	fill_grid(grid, grid_data, fd);
	close(fd);
	store_max_alt(&grid_data, grid);
	ft_printf("grid max alt == %d\ngrid min alt == %d\n", grid_data.alt_max, grid_data.alt_min);
	store_colors(&grid_data, grid);
	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, WIDTH, HEIGHT, map);
	img_data.img = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
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
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, img_data.img, 0, 0);
	mlx_hook(mlx_data.win, ON_DESTROY, 1L<<3, close_win_mouse, &mlx_data);
	mlx_key_hook(mlx_data.win, close_win_esc, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
