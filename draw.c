/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:55:06 by juportie          #+#    #+#             */
/*   Updated: 2025/02/03 17:55:11 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include <math.h>
//#include "libft/ftpf_printf.h"
//DEBUG
//#include <stdio.h>

void	put_pixel(t_img_data *img_data, t_pixel pixel)
{
	char	*pix_addr;

	pix_addr = img_data->addr + (
		pixel.y * img_data->line_length + pixel.x * (img_data->bits_per_pixel / 8)
	);
	*(unsigned int *)pix_addr = pixel.color;
}

void	draw_line(t_img_data *img_data, t_pixel pix_a, t_pixel pix_b)
{
	int	step_nbr;
	double	x_step;
	double	y_step;
	int	i;

	// FIX: if two pixels share the same position
	// but not the same color this check doesn't work.
	if (ft_memcmp(&pix_a, &pix_b, sizeof(t_pixel)) == 0)
		return;
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
