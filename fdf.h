/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:11:59 by juportie          #+#    #+#             */
/*   Updated: 2025/01/27 15:33:28 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_img_data;

typedef struct	s_pixel {
	int	x;
	int	y;
	int	color;
}	t_pixel;

void	put_pixel(t_img_data *img_data, t_pixel pixel);
void	draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b);
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
