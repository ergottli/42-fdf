/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmills <kmills@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 06:07:14 by kmills            #+#    #+#             */
/*   Updated: 2019/04/13 16:00:17 by kmills           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err_map(void)
{
	ft_putstr("error_map\n");
	exit(0);
}

void	freefdf(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map.height)
	{
		free(fdf->map.point[i]);
		i++;
	}
	free((*fdf).koord);
	free((*fdf).map.point);
	exit(0);
}
