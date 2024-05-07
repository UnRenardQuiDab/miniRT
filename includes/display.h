/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:53:16 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 17:05:15 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# define WIDTH 1920
# define HEIGHT 1080
# define NAME "miniRT (lcottet & bwisniew)"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;
typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		img;
}	t_mlx;

#endif