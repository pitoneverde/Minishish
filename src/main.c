/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/06 18:57:40 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, const char *argv[], const char *envp[])
{
    (void) argc;
    (void) argv;
    (void) envp;    
    printf("sum %d\n", sum(1, 6));
	return (0);
}