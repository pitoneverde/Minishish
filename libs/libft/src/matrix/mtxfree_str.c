/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxfree_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:07:56 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/02 15:11:18 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mtxfree_str(char **matrix)
{
	if (!matrix)
		return ;
	mtxfree((void **)matrix, free);
}
