#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "utest.h"

struct pointer_stack;

typedef struct pointer_stack pointer_stack_t;

struct pointer_stack {
	size_t capacity;
        size_t size;
        void **stack_bottom;
};

pointer_stack_t *make_stack(size_t capacity)
{
        if (capacity == 0) {
                capacity = 5;
        }

	pointer_stack_t *stack = malloc(sizeof(pointer_stack_t));
	if (stack == NULL) return NULL;

        void **data = malloc(sizeof(void*) * capacity);
        if (data == NULL) {
                goto err_cleanup;
        }
        stack->stack_bottom = data;
        data = NULL;
        stack->capacity = capacity;
        stack->size = 0;

        return stack;

        err_cleanup:
                free(stack);
                return NULL;
}

bool pointer_stack_reserve(pointer_stack_t *self, size_t capacity)
{
        if (capacity == self->capacity) return true;
        void **new_storage = malloc(sizeof(char*) * capacity);
        if (new_storage == NULL) return false;

        size_t future_size = self->size > capacity ? capacity : self->size;
        for (size_t idx = future_size; idx < self->size; idx++) {
                free(self->stack_bottom[idx]);
        }
        for (size_t idx = 0; idx < future_size; idx++) {
                new_storage[idx] = self->stack_bottom[idx];
        }
        free(self->stack_bottom);
        self->stack_bottom = new_storage;
        new_storage = NULL;
        self->size = future_size;
        self->capacity = capacity;

        return true;
}

bool pointer_stack_push(pointer_stack_t *self, void *item)
{
        if (self->size == self->capacity) {
		if (!pointer_stack_reserve(self, self->capacity * 2)) {
			return false;
		}
	}

        self->stack_bottom[self->size++] = item;
        item = NULL;

        return true;
}

void *pointer_stack_pop(pointer_stack_t *self)
{
        if (self->size == 0) {
                return NULL;
        }
        void *item = self->stack_bottom[--self->size];

        return item;
}

void pointer_stack_destroy(pointer_stack_t *self)
{
        if (self == NULL) return;

        for (size_t idx = 0; idx < self->size; idx++) {
                free(self->stack_bottom[idx]);
        }

        free(self);
}

struct expression_node;
typedef struct expression_node expression_node_t;

struct expression_node {
        expression_node_t *left;
        expression_node_t *right;
        char *data;
};

typedef expression_node_t expression_tree_t;

expression_node_t *make_expression_node(const char* data)
{
        char *copied = malloc(sizeof(char) * (strlen(data) + 1));
        if (copied == NULL) return NULL;

        strcpy(copied, data);

        expression_node_t *node = malloc(sizeof(expression_node_t));
        node->data = copied;
        copied = NULL;

        return node;
}

expression_tree_t *make_expression_tree(const char *expression) {
        if (expression == NULL) return NULL;

        pointer_stack_t *stack = make_stack(10);
        for (size_t idx = 0; idx < strlen(expression); idx++) {
                char c = expression[idx];
                if (isblank(c)) continue;

                switch (c) {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9': {
                                char *buffer = malloc(2);
                                buffer[1] = '\0';
                                buffer[0] = c;
                                expression_node_t *node = make_expression_node(buffer);
                                free(buffer);
                                buffer = NULL;
                                pointer_stack_push(stack, node);
                                node = NULL;
                        }
                                  break;
                        case '+':
                        case '-':
                        case '*':
                        case '/': {
                                char *buffer = malloc(2);
                                buffer[1] = '\0';
                                buffer[0] = c;
                                expression_node_t *node = make_expression_node(buffer);
                                free(buffer);
                                buffer = NULL;

                                expression_node_t *right = pointer_stack_pop(stack);
                                node->right = right;
                                right = NULL;

                                expression_tree_t *left = pointer_stack_pop(stack);
                                node->left = left;
                                left = NULL;

                                pointer_stack_push(stack, node);
                                node = NULL;
                        }
                                break;
                        default: continue;
                }
        }
        expression_node_t *root = pointer_stack_pop(stack);
        pointer_stack_destroy(stack);

        return root;
}

long operation(char operator, long operand1, long operand2);

long expression_tree_evaluate(expression_tree_t *tree)
{
        if (tree->left == NULL || tree->right == NULL) return atol(tree->data);

        char operator = tree->data[0];

	long operand1 = expression_tree_evaluate(tree->left);
	long operand2 = expression_tree_evaluate(tree->right);

	return operation(operator, operand1, operand2);
}

long operation(char operator, long operand1, long operand2)
{
        switch (operator) {
                case '+': return operand1 + operand2;
                case '*': return operand1 * operand2;
                case '-': return operand1 - operand2;
                case '/': return operand1 / operand2;
                default: return 0;
        }
}

UTEST(EXPR, SIMPLE)
{
        expression_tree_t *tree = make_expression_tree("1 2 + 3 * 9 /");
        long result = expression_tree_evaluate(tree);

        ASSERT_EQ(1, result);
}


UTEST_MAIN();