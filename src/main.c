/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/21 18:41:18 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char ** environ;

// IN LOOP:
// legge riga da stdin
// crea processo con fork
// esegue con execvp

// segnale freccia su history
// segnale freccia giu' history


// gestisci CTRL + D (EOF)
// 1 - buffer vuoto: stampa "exit\n" ed esce
// 2 - buffer non vuoto: non fa nulla

// CTRL + C
// stampa "^C" dopo l'input e vai a capo

// Enter
// 1 - buffer vuoto: vai a capo
// 2 - buffer non vuoto: parsing comandi ecc.

int	main(int argc, const char *argv[], const char *envp[])
{
	(void)	argc;
	(void)	argv;
	(void)	envp;
	char	*line;
	struct sigaction	sa;

    sa.sa_handler = handler_sigaction;
    sa.sa_flags = SA_RESTART; // evita che readline() fallisca con NULL dopo un Ctrl-C;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

	if (argc != 1)
		return (print_error("Wrong number of arguments"), 0);

	// printf("home: \e[0;32m%s\e[0m\n", getenv("HOME"));
	// printf("path: \e[0;32m%s\e[0m\n", getenv("PATH"));
	// printf("unexistent: \e[0;32m%s\e[0m\n", getenv("UNDEFINED"));
	// printf("term: \e[0;32m%s\e[0m\n", getenv("TERM"));
	// printf("sum %d\n", sum(1, 6));
	// const char ** curr = envp;
	// char ** curr = environ;
	// while (*curr != NULL)
	// {
	//     printf(" %s\n", *curr);
	//     curr++;
	// }
	while (1)
	{
		line = readline("> ");
		// handle EOF (Ctrl + D)
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{			
			// if (ft_strncmp(line, "history", ft_strlen(line)) == 0)
			// {
			// 	printf("historyyyy\n");
			// }
			// t_list *tokens = tokenize(line);
			// print_tokens(tokens);
			add_history(line);
			// printf("line: %s\n", line);
		}
		free(line);
	}
	// rl_clear_history();
	// if (fork() == 0)
	//     execvp(argv[1], argv + 1);
	// wait(&status);
    printf("exit\n");
	return (0);
}