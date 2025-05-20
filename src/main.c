/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/14 18:38:57 by plichota         ###   ########.fr       */
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

// int	main(int argc, const char *argv[], const char *envp[])
// {
// 	(void)	argc;
// 	(void)	argv;
// 	(void)	envp;
// 	char	*line;

// 	if (argc != 1)
// 		return (print_error("Wrong number of arguments"), 0);

// 	// printf("home: \e[0;32m%s\e[0m\n", getenv("HOME"));
// 	// printf("path: \e[0;32m%s\e[0m\n", getenv("PATH"));
// 	// printf("unexistent: \e[0;32m%s\e[0m\n", getenv("UNDEFINED"));
// 	// printf("term: \e[0;32m%s\e[0m\n", getenv("TERM"));
// 	// printf("sum %d\n", sum(1, 6));
// 	// const char ** curr = envp;
// 	// char ** curr = environ;
// 	// while (*curr != NULL)
// 	// {
// 	//     printf(" %s\n", *curr);
// 	//     curr++;
// 	// }
// 	line = readline("> ");
// 	while (line != NULL)
// 	{
// 		if (!line)
// 			return (print_error("No line"), 0);
// 		if (ft_strlen(line) > 0)
// 		{			
// 			// if (ft_strncmp(line, "history", ft_strlen(line)) == 0)
// 			// {
// 			// 	printf("historyyyy\n");
// 			// }
// 			// t_list *tokens = tokenize(line);
// 			// print_tokens(tokens);
// 			add_history(line);
// 			printf("line: %s\n", line);
// 		}
// 		free(line);
// 		line = readline("> ");
// 	}
// 	// rl_clear_history();
// 	// if (fork() == 0)
// 	//     execvp(argv[1], argv + 1);
// 	// wait(&status);
// 	return (0);
// }