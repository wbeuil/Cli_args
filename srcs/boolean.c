/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:19:45 by William           #+#    #+#             */
/*   Updated: 2018/02/12 16:19:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_args.h"
#include <stdio.h>

/*
** Print true instead of 1.
*/

void				print_boolean(void)
{
	printf("true");
}

/*
** Return an array of 1 integer for the boolean value.
*/

int					*boolean_value(void)
{
	int				*value;

	if (!(value = (int *)malloc(sizeof(int))))
		return (NULL);
	*value = 1;
	return (value);
}