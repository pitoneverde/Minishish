/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/06 20:59:10 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, const char *argv[], const char *envp[])
{
    (void)argc;
    (void)argv;
    (void)envp;
    printf("home: \e[0;32m%s\e[0m\n", getenv("HOME"));
    printf("path: \e[0;32m%s\e[0m\n", getenv("PATH"));
    printf("unexistent: \e[0;32m%s\e[0m\n", getenv("UNDEFINED"));
    printf("term: \e[0;32m%s\e[0m\n", getenv("TERM"));
    printf("sum %d\n", sum(1, 6));

    return (0);
}