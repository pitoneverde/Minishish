/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/06/19 17:41:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// extern char ** environ;

// IN LOOP:
// legge riga da stdin
// crea processo con fork	shell.env = envp_to_env(envp);
// esegue con execvp

// Enter
// 1 - buffer vuoto: vai a capo
// 2 - buffer non vuoto: parsing comandi ecc.

// t_ast	*create_mock_ast(void)
// {
//     t_ast *left = ast_cmd((char *[]){"echo", "ciaoleft", NULL});
//     t_ast *right = ast_cmd((char *[]){"echo", "ciaoright", NULL});
//     t_ast *root = ast_binary_op(AST_PIPE, "|", left, right);
// 	return (root);
// }

// void	parse_and_execute(char *line)
// {
// 	t_list *tokens;
// 	t_list *lexed;

// 	if (ft_strlen(line) > 0)
// 	{
// 		tokens = tokenize(line);
// 		if (!tokens)
// 			return ; // error status code??
// 		// print_raw_tokens(tokens);
// 		lexed = lex(tokens);
// 		if (!lexed)
// 			return ; // error status code??
// 		// print_lexed_tokens(lexed);
		
// 		// parser (albero) ->flatten (lista) oppure filtrare
// 		t_ast *ast = create_mock_ast();
//         executor(ast);

// 		free_raw_tokens(&tokens);
// 		free_token_list(&lexed);
// 		add_history(line);
// 	}
// }

int	main(int argc, char *argv[], char *envp[])
{
	(void)	argc;
	(void)	argv;
	char	*line;
	t_sh	shell;
	t_list	*env;

	shell.env = envp_to_env(envp);
	shell.last_code = 0;
	shell.is_interactive = isatty(STDIN_FILENO);

	init_signals();
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
		t_ast *tree = read_command_line(line);
		// expand tree: transform args in argv and $var/$? in values
		if (tree)
			executor(tree, STDIN_FILENO, &shell); // restituisce status code
		if (line)
			free(line);
	}
	rl_clear_history();
	free_env(env);
	(void)shell;
    printf("exit\n");
	return (0);
}