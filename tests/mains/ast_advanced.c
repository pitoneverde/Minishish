#include "ast.h"

void test_is_operator(void) {
    printf("Testing ast_is_operator:\n");
    printf("AST_PIPE: %d (expected 1)\n", ast_is_operator(AST_PIPE));
    printf("AST_COMMAND: %d (expected 0)\n", ast_is_operator(AST_COMMAND));
    printf("\n");
}

void test_is_command(void) {
    printf("Testing ast_is_command:\n");
    char *argv[] = {"echo", "hello", NULL};
    t_ast *cmd = ast_cmd(argv);
    t_ast *not_cmd = ast_new(AST_LITERAL, "hello");

    printf("AST_COMMAND node: %d (expected 1)\n", ast_is_command(cmd));
    printf("AST_LITERAL node: %d (expected 0)\n", ast_is_command(not_cmd));

    ast_free(cmd);
    ast_free(not_cmd);
    printf("\n");
}

void test_has_error(void) {
    printf("Testing ast_has_error:\n");
    t_ast *err = ast_error("some error");
    t_ast *cmd = ast_cmd((char *[]){"ls", NULL});

    printf("AST_ERROR node: %d (expected 1)\n", ast_has_error(err));
    printf("AST_COMMAND node: %d (expected 0)\n", ast_has_error(cmd));

    ast_free(err);
    ast_free(cmd);
    printf("\n");
}

void test_is_valid(void) {
    printf("Testing ast_is_valid:\n");

    t_ast *good = ast_cmd((char *[]){"ls", NULL});
    t_ast *bad = ast_binary_op(AST_PIPE, "|", good, ast_error("fail"));

    printf("Valid AST: %d (expected 1)\n", ast_is_valid(good));
    printf("AST with error subtree: %d (expected 0)\n", ast_is_valid(bad));

    ast_free(bad); // Frees both good and error
    printf("\n");
}

void simple_mapper(t_ast *node) {
    printf("Visited: %s\n", node_type_name(node->type));
}

void test_ast_map_and_replace(void) {
    printf("Testing ast_map and ast_replace_subtree:\n");

    t_ast *left = ast_cmd((char *[]){"echo", "left", NULL});
    t_ast *right = ast_cmd((char *[]){"echo", "right", NULL});
    t_ast *root = ast_binary_op(AST_PIPE, "|", left, right);

    printf("Before replace:\n");
    print_ast(root, 0);

    // Replace right subtree with error node
    t_ast *err = ast_error("replacement error");
    ast_replace_subtree(&root->right, err);

    printf("After replace:\n");
    print_ast(root, 0);

    printf("Mapped AST:\n");
    ast_map(root, simple_mapper);

    ast_free(root); // Frees all
    printf("\n");
}

int main(void) {
    test_is_operator();
    test_is_command();
    test_has_error();
    test_is_valid();
    test_ast_map_and_replace();

    return 0;
}
