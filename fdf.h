/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:11:59 by juportie          #+#    #+#             */
/*   Updated: 2025/02/06 11:35:54 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# define ZOOM 90

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
	int	color;
}	t_pixel;

typedef struct s_grid_data
{
	int	width;
	int	height;
	int	alt_max;
	int	alt_min;
	int	spacing;
	t_pixel	start_point;
}	t_grid_data;

// PARSING
t_grid_data	get_grid_size(int fd);
int			get_fd(char *filename);
int			**malloc_grid(t_grid_data grid_data);
void		fill_grid(int **grid, t_grid_data grid_data, int fd);
// STORE_GRID_DATA
void	store_spacing(t_grid_data *grid_data);
void	store_start_point(t_grid_data *grid_data);
void		store_max_alt(t_grid_data *grid_data, int **grid);
// UTILS
int			ft_splitlen(char **splits);
void		ft_free_splits(char **array);
void		ft_err_exit(char *error);
void		ft_err_free_exit(void *mem, char *error);
void		ft_err_free2d_exit(int **mem, int sub_nbr, char *error);
char		*remove_end_nl(char *str);
// DRAW
void		put_pixel(t_img_data *img_data, t_pixel pixel);
void		draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b);

//typedef struct	s_pos {
//	int	x;
//	int	y;
//}	t_pos;
//
//typedef struct	s_pos_d {
//	double	x;
//	double	y;
//}	t_pos_d;
//
#endif
