/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:49 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/06 16:22:41 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "engine.h"

uint8_t init_ambient(t_engine *engine, char **args);
uint8_t init_camera(t_engine *engine, char **args);
uint8_t init_light(t_engine *engine, char **args);
uint8_t init_cylinder(t_engine *engine, char **args);
uint8_t init_plane(t_engine *engine, char **args);
uint8_t init_sphere(t_engine *engine, char **args);

#endif
