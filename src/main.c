/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/05/22 19:32:01 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char ** environ;

// IN LOOP:
// legge riga da stdin
// crea processo con fork
// esegue con execvp

// Enter
// 1 - buffer vuoto: vai a capo
// 2 - buffer non vuoto: parsing comandi ecc.

t_ast	*create_mock_ast(void)
{
    t_ast *left = ast_cmd((char *[]){"echo", "ciaoleft", NULL});
    t_ast *right = ast_cmd((char *[]){"echo", "ciaoright", NULL});
    t_ast *root = ast_binary_op(AST_PIPE, "|", left, right);
	return (root);
}

void	parse_and_execute(char *line)
{
	t_list *tokens;
	t_list *lexed;

	if (ft_strlen(line) > 0)
	{
		tokens = tokenize(line);
		if (!tokens)
			return ; // error status code??
		print_raw_tokens(tokens);
		lexed = lex(tokens);
		if (!lexed)
			return ; // error status code??
		print_lexed_tokens(lexed);
		
		// parser (albero) ->flatten (lista) oppure filtrare
		t_ast *list = create_mock_ast();
		print_ast(list, 1);

		free_raw_tokens(&tokens);
		free_token_list(&lexed);
		add_history(line);
	}
}

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
	signal(SIGQUIT, SIG_IGN);

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
		// handle End Of transmission (Ctrl + D)
		if (!line)
			break ;
		parse_and_execute(line);
		free(line);
	}
	rl_clear_history();
	// if (fork() == 0)
	//     execvp(argv[1], argv + 1);
	// wait(&status);
    printf("exit\n");
	return (0);
}