/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/14 15:55:55 by plichota         ###   ########.fr       */
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

int	main(int argc, const char *argv[], const char *envp[])
{
	(void)	argc;
	(void)	argv;
	(void)	envp;
	char	*line;

	if (argc != 1)
		return (print_error("Wrong numbers of arguments"), 0);

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
	line = readline("> ");
	while (line != NULL)
	{
		if (!line)
			return (print_error("Wrong line"), 0);
		if (ft_strlen(line) > 0)
		{			
			if (ft_strncmp(line, "history", ft_strlen(line)) == 0)
			{
				printf("historyyyy\n");
			}
			t_list *tokens = tokenize(line);
			print_tokens(tokens);
			add_history(line);
		}
		free(line);
		line = readline("> ");
	}
	// rl_clear_history();
	// if (fork() == 0)
	//     execvp(argv[1], argv + 1);
	// wait(&status);
	return (0);
}


// int main(void)
// {
// 	const char *input = "echo hello world";
// 	t_list *tokens = tokenize(input);
// 	t_list *tmp = tokens;

// 	while (tmp)
// 	{
// 		printf("token: [%s]\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	free_raw_tokens(&tokens);
// 	return 0;
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s \"command line string\"\n", argv[0]);
// 		return (1);
// 	}

// 	const char *input = argv[1];

// 	// Step 1: Tokenizer
// 	t_list *raw_tokens = tokenize(input);
// 	if (!raw_tokens)
// 	{
// 		fprintf(stderr, "Tokenizer failed.\n");
// 		return (1);
// 	}

// 	printf("=== Raw Tokens ===\n");
// 	print_raw_tokens(raw_tokens);

// 	// Step 2: Lexer
// 	t_list *lexed = lex(raw_tokens);
// 	if (!lexed)
// 	{
// 		fprintf(stderr, "Lexer failed.\n");
// 		free_raw_tokens(&raw_tokens);
// 		return (1);
// 	}

// 	printf("\n=== Lexed Tokens ===\n");
// 	print_lexed_tokens(lexed);

// 	// Cleanup
// 	free_raw_tokens(&raw_tokens);
// 	free_token_list(&lexed);
// 	return (0);
// }