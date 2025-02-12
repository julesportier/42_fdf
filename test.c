/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:33:57 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 11:31:43 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "libft/libft.h"
#include "minilibx/mlx.h"
//#include <math.h>
#include "libft/ftpf_printf.h"
//DEBUG
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	t_mlx_data	mlx_data;

	int	fd = get_fd(argv[1]);
	t_grid_data	grid_data = get_grid_size(fd);
	ft_printf("grid_data.width == %d\n", grid_data.width);
	ft_printf("grid_data.height == %d\n", grid_data.height);
	close(fd);
	t_pixel	**grid = malloc_grid(grid_data);
	fd = get_fd(argv[1]);
	fill_grid(grid, grid_data, fd);
	close(fd);
	store_max_alt(&grid_data, grid);
	ft_printf("grid max alt == %d\ngrid min alt == %d\n", grid_data.alt_max, grid_data.alt_min);
	store_colors(&grid_data, grid);
	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, WIDTH, HEIGHT, argv[1]);
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
	mlx_data.img.addr = mlx_get_data_addr(
		mlx_data.img.img,
		&mlx_data.img.bits_per_pixel,
		&mlx_data.img.line_length,
		&mlx_data.img.endian
	);
	store_iso_pos(&mlx_data.img, &grid_data, grid);
	store_pos_limits(&grid_data, grid);
	printf("grid max y == %f, grid max x == %f\n", grid_data.y_max, grid_data.x_max);
	printf("grid min y == %f, grid min x == %f\n", grid_data.y_min, grid_data.x_min);
	scale_limits(&grid_data, grid);
	printf("grid max y == %f, grid max x == %f\n", grid_data.y_max, grid_data.x_max);
	printf("grid min y == %f, grid min x == %f\n", grid_data.y_min, grid_data.x_min);
	store_spacing(&grid_data);
	printf("grid spacing == %f\n", grid_data.spacing);
	scale_to_win(&grid_data, grid);
	draw_grid(&mlx_data.img, &grid_data, grid);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img.img, 0, 0);
	mlx_hook(mlx_data.win, ON_DESTROY, 1L<<3, end_loop_mouse, &mlx_data);
	mlx_key_hook(mlx_data.win, end_loop_esc, &mlx_data);
	mlx_loop(mlx_data.mlx);
	printf("end loop\n");
	free_mlx(&mlx_data);
	freegrid(grid, grid_data.height);
	return (0);
}
