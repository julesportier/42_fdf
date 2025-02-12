/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:11:59 by juportie          #+#    #+#             */
/*   Updated: 2025/02/12 10:26:35 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// window
# define WIDTH 1920
# define HEIGHT 1080
# define ZOOM 0.7
// colors for extreme altitudes
# define COLOR_H 0x00FFFF00
# define COLOR_M 0x00FF7000
# define COLOR_L 0x000070FF
// rgb masks
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
// mlx
# define ON_DESTROY 17
# define ESC 65307

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
}	t_mlx_data;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	z;
	float	ax;
	float	ay;
	int	color;
}	t_pixel;

typedef struct s_grid_data
{
	int		width;
	int		height;
	int		alt_max;
	int		alt_min;
	float		y_max;
	float		y_min;
	float		x_max;
	float		x_min;
	float		spacing;
	t_pixel	start_point;
}	t_grid_data;

// MLX_UTILS
int	close_win_mouse(t_mlx_data *mlx_data);
int	close_win_esc(int keycode, t_mlx_data *mlx_data);
// PARSING
t_grid_data	get_grid_size(int fd);
int			get_fd(char *filename);
t_pixel		**malloc_grid(t_grid_data grid_data);
void		fill_grid(t_pixel **grid, t_grid_data grid_data, int fd);
// STORE_GRID_DATA
void		store_max_alt(t_grid_data *grid_data, t_pixel **grid);
void		store_colors(t_grid_data *grid_data, t_pixel **grid);
void		store_iso_pos(t_img_data *img_data, t_grid_data *grid_data, t_pixel **grid);
void		store_pos_limits(t_grid_data *grid_data, t_pixel **grid);
void		scale_limits(t_grid_data *grid_data, t_pixel **grid);
void		store_spacing(t_grid_data *grid_data);
void		scale_to_win(t_grid_data *grid_data, t_pixel **grid);
// UTILS
int			ft_splitlen(char **splits);
void		ft_free_splits(char **array);
void		ft_err_exit(char *error);
void		ft_err_free_exit(void *mem, char *error);
void		ft_err_free2d_exit(int **mem, int sub_nbr, char *error);
void		ft_err_freegrid_exit(t_pixel **mem, int sub_nbr, char *error);
char		*remove_end_nl(char *str);
// DRAW
void		put_pixel(t_img_data *img_data, t_pixel pixel);
void		draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b);
void	draw_grid(t_img_data *img_data, t_grid_data *grid_data, t_pixel **grid);

#endif
