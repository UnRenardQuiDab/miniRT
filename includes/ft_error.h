/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:52:07 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 08:11:52 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <stdint.h>

# define ERR_VALUE_COUNT "Not enough value"
# define ERR_INVALID_INT "Invalid string for type INT"
# define ERR_INVALID_FLOAT "Invalid string for type FLOAT"
# define ERR_ARGS_COUNT "Invalid args count"
# define ERR_RANGE "Number not in valid range"
# define ERR_REDEFINITION "Unique object is being defined twice"
# define ERR_NOT_FOUND "Scene element not found"
# define ERR_NO_CAMERA "No camera defined"
# define ERR_NO_AMBIENT "No ambient light defined"
# define ERR_MLX_INIT "Failed to initialize MLX"
# define ERR_USAGE "Usage: ./miniRT <filename>"

uint8_t	err(char *err);
uint8_t	custom_error(char *err, char *msg);

#endif
