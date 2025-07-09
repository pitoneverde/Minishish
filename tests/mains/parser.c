#include "minishell.h"
#include <stdio.h>
#include <string.h>

// Run single test case
// IF IT LEAKS: check if strdup'ed value arg in ast_new-> no need since it strdup'es again internally
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
	free_raw_tokens(&raw);
	free_token_list(&lexed);
	ast_free(tree);
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
	run_test("cat|ls");
	run_test("$$$$$HOME$.$");
	run_test("echo > out.txt hello");
	run_test("'echo");
	return 0;
}