#include "minishell.h"
#include <stdio.h>
#include <string.h>

// Run single test case
void run_test(const char *input)
{
	printf("\n=== Test: '%s' ===\n", input);

	t_list *raw = tokenize(input);
	printf("Raw tokens:\n");
	print_raw_tokens(raw);

	t_list *lexed = lex(raw);
	printf("Lexed tokens:\n");
	print_lexed_tokens(lexed);

	t_ast *tree = parse(lexed);
	if (!tree || ast_has_error(tree))
	{
		printf("❌ Parse error: %s\n", tree && tree->error ? tree->error : "unknown");
	}
	else
	{
		printf("AST:\n");
		print_ast(tree, 0);
	}
	ast_free(tree);
	free_raw_tokens(&raw);
	free_token_list(&lexed);
}

int main(void)
{
	run_test("echo hello");
	run_test("ls > out.txt");
	run_test("cat file.txt | grep pattern");
	run_test("echo data > tmp.txt | cat");
	run_test("ls |");			   // edge
	run_test("echo >");			   // edge
	run_test("");				   // empty input edge
	run_test(">> file");		   // lone redirection
	run_test("echo 'quoted arg'"); // test quoting if lex handles it
	run_test("grep \"some pattern\" < in.txt >> out.txt");

	return 0;
}