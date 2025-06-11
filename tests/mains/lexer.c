#include "minishell.h"

// !! IMPORTANT !!
// For the lexer to work first check the tokenizer
// To avoid lower level issues
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"command line string\"\n", argv[0]);
		return (1);
	}

	const char *input = argv[1];

	// Step 1: Tokenizer
	t_list *raw_tokens = tokenize(input);
	if (!raw_tokens)
	{
		fprintf(stderr, "Tokenizer failed.\n");
		return (1);
	}

	printf("=== Raw Tokens ===\n");
	print_raw_tokens(raw_tokens);

	// Step 2: Lexer
	t_list *lexed = lex(raw_tokens);
	if (!lexed)
	{
		fprintf(stderr, "Lexer failed.\n");
		free_raw_tokens(&raw_tokens);
		return (1);
	}

	printf("\n=== Lexed Tokens ===\n");
	print_lexed_tokens(lexed);

	// Cleanup
	free_raw_tokens(&raw_tokens);
	free_token_list(&lexed);
	return (0);
}
