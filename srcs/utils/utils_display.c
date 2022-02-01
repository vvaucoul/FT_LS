/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintz <vintz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:55:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/27 13:20:31 by vintz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

//****************************************************************************//
//							  	 	 DISPLAY			     				  //
//****************************************************************************//

void ft_putstr(char *str) {
	write(1, str, ft_strlen(str));
}

void ft_putendl(char *str) {
	ft_putstr(str);
	ft_putstr("\n");
}

void display_error(char *str) {
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void display_error_to_free(char *str, bool to_free) {
	display_error(str);
	if (to_free)
		free(str);
}
