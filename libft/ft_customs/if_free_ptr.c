/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:55:59 by ngordobi          #+#    #+#             */
/*   Updated: 2025/07/22 12:55:59 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	if_free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
		return (0);
	}
	return (1);
}
