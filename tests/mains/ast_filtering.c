#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Sample Predicate Functions for Testing
int is_command(const t_ast *node) {
    return node->type == AST_COMMAND;
}

int is_pipe(const t_ast *node) {
    return node->type == AST_PIPE;
}

void test_ast_filter() {
    // Test Case 1: Empty Tree (root is NULL)
    t_ast *root = NULL;
    t_ast **result = ast_filter(root, is_command);
    assert(result == NULL); // No nodes should be returned
    free(result);

    // Test Case 2: Tree with No Matches
    // A tree that has no COMMAND nodes (e.g., only PIPE nodes)
    root = ast_binary_op(AST_PIPE, "|", 
                        ast_new(AST_LITERAL, "left"), 
                        ast_new(AST_LITERAL, "right"));
    result = ast_filter(root, is_command);
    assert(result == NULL); // No matches for COMMAND
    free(result);

    // Test Case 3: Tree with One Node (COMMAND)
    root = ast_new(AST_COMMAND, "echo");
    result = ast_filter(root, is_command);
    assert(result != NULL);
    assert(result[0]->type == AST_COMMAND); // The match is a COMMAND
    assert(strcmp(result[0]->value, "echo") == 0);
    free(result);

    // Test Case 4: Multiple Matching Nodes (COMMAND nodes)
    root = ast_binary_op(AST_PIPE, "|", 
                        ast_cmd((char *[]){"echo", "hello", NULL}), 
                        ast_cmd((char *[]){"echo", "world", NULL}));
    result = ast_filter(root, is_command);
    assert(result != NULL);
    assert(result[0]->type == AST_COMMAND);
    assert(strcmp(result[0]->value, "echo") == 0);
    assert(result[1]->type == AST_COMMAND);
    assert(strcmp(result[1]->value, "echo") == 0);
    free(result);

    // Test Case 5: Tree with One Type of Node (No Matches)
    root = ast_binary_op(AST_PIPE, "|", 
                        ast_new(AST_PIPE, "|"), 
                        ast_new(AST_PIPE, "|"));
    result = ast_filter(root, is_command);
    assert(result == NULL); // No COMMAND nodes
    free(result);

    // Test Case 6: Predicate Always Returns False
    root = ast_cmd((char *[]){"echo", "hello", NULL});
    result = ast_filter(root, is_pipe); // Always returns false
    assert(result == NULL); // No matching nodes for PIPE
    free(result);

    // Test Case 7: Predicate Always Returns True
    result = ast_filter(root, is_command); // Always returns true
    assert(result != NULL); // Should return all nodes
    assert(result[0]->type == AST_COMMAND); // The only node is a COMMAND
    free(result);

    // Test Case 8: Complex Tree with Different Node Types
    t_ast *left = ast_new(AST_COMMAND, "echo");
    t_ast *right = ast_new(AST_LITERAL, "<<");
    t_ast *root_complex = ast_binary_op(AST_PIPE, "|", left, right);
    
    result = ast_filter(root_complex, is_command);
    assert(result != NULL);
    assert(result[0]->type == AST_COMMAND);
    assert(strcmp(result[0]->value, "echo") == 0);
    free(result);

    // Free all allocated memory
    ast_free(root);
    ast_free(root_complex);
}

void test_ast_filter_n() {
    // Similar edge cases for ast_filter_n
    // Test Case 1: Empty Tree
    t_ast *root = NULL;
    size_t dim = 0;
    t_ast **result = ast_filter_n(root, is_command, &dim);
    assert(result == NULL); // No nodes should be returned
    assert(dim == 0);
    free(result);

    // Test Case 2: Tree with No Matches
    root = ast_binary_op(AST_PIPE, "|", 
                        ast_new(AST_LITERAL, "left"), 
                        ast_new(AST_LITERAL, "right"));
    result = ast_filter_n(root, is_command, &dim);
    assert(result == NULL);
    assert(dim == 0);
    free(result);

    // Test Case 3: Tree with One Node (COMMAND)
    root = ast_new(AST_COMMAND, "echo");
    result = ast_filter_n(root, is_command, &dim);
    assert(result != NULL);
    assert(dim == 1);
    assert(result[0]->type == AST_COMMAND);
    assert(strcmp(result[0]->value, "echo") == 0);
    free(result);

    // Test Case 4: Multiple Matching Nodes
    root = ast_binary_op(AST_PIPE, "|", 
                        ast_cmd((char *[]){"echo", "hello", NULL}), 
                        ast_cmd((char *[]){"echo", "world", NULL}));
    result = ast_filter_n(root, is_command, &dim);
    assert(result != NULL);
    assert(dim == 2);
    assert(result[0]->type == AST_COMMAND);
    assert(strcmp(result[0]->value, "echo") == 0);
    assert(result[1]->type == AST_COMMAND);
    assert(strcmp(result[1]->value, "echo") == 0);
    free(result);
}

/*
samu sei fantastico ma per favore pusha i main commentati se li lasci nei srcs principali pls ç.ç

int main() {
    test_ast_filter();
    test_ast_filter_n();
    printf("All tests passed!\n");
    return 0;
}
*/
