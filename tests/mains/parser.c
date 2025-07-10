#include "minishell.h"
#include <stdio.h>
#include <string.h>

t_sh shell;
// Run single test case
// IF IT LEAKS: check if strdup'ed value arg in ast_new-> no need since it strdup'es again internally
void run_test(const char *input)
{
	printf("\n=== Test: '%s' ===\n", input);

	t_list *raw = tokenize(input);
	// printf("Raw tokens:\n");
	// print_raw_tokens(raw);

	t_list *lexed = lex(raw);
	// printf("Lexed tokens:\n");
	// print_lexed_tokens(lexed);

	t_ast *tree = parse(lexed);
	if (!tree)
	{
		printf("❌ Parse error: null tree\n");
		free_raw_tokens(&raw);
		free_token_list(&lexed);
		return;
	}

	// if (ast_has_error(tree))
	// {
	// 	printf("❌ Parse error\n");
	// 	free_raw_tokens(&raw);
	// 	free_token_list(&lexed);
	// 	ast_free(tree);
	// 	return;
	// }
	expand_ast(tree, &shell);
	validate_ast(&tree);

	const char *err_msg = ast_get_error(tree);
	if (err_msg)
		printf("❌ Parse error: %s\n", err_msg);
	else
		printf("AST is valid\n");

	print_ast(tree, 0);

	free_raw_tokens(&raw);
	free_token_list(&lexed);
	ast_free(tree);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	run_test("echo hello");
	run_test("ls > out.txt");
	run_test("cat file.txt | grep pattern");
	run_test("echo data > tmp.txt | cat");
	run_test("echo 'quoted arg'"); // test quoting if lex handles it
	run_test("grep \"some pattern\" < in.txt >> out.txt");
	run_test("echo hi > out.txt | cat"); // tested ownership of cmd argv issue
	run_test("cat < in.txt | grep foo > out.txt");
	run_test("echo alpha >> file1 | grep alpha >> file2");
	run_test("cat << heredoc | sort > sorted.txt");
	run_test("grep pattern < input.txt | wc -l > lines.txt");
	run_test("echo a | echo b | echo c");
	run_test("ls -la | grep '^d' | wc -l > dir_count.txt");
	run_test("cat file.txt > temp1.txt >> temp2.txt");		 // Multiple redirs chained
	run_test("sort < unsorted.txt > sorted.txt >> log.txt"); // Read, write, and append
	run_test("tr -d 'a-z' < input | sort | uniq > result");
	run_test("command < in | mid > out | tail"); // Nested redirection in a pipeline
	run_test("cat|ls"); // no space between words and operands
	run_test("$$$$$HOME$.$"); // many dollars
	run_test("echo > out.txt hello"); // args and redirs mixed
	// Should fail
	run_test("'echo"); // unclosed quote
	run_test("|");	   // lone pipe
	run_test(">");	   // lone redir
	run_test("ls |");	 // edge
	run_test("echo >");	 // redir without filename
	run_test("echo > >");	 // double redir without filename
	run_test("");		 // empty input edge
	run_test(">> file"); // start redirection
	run_test("|cat"); // start pipe
	run_test("echo hello || echo world"); // no support for logical operands
	run_test("echo hello | >");  // no command after pipe
	// run_test("||||||||");
	free_all(&shell);
	return 0;
}