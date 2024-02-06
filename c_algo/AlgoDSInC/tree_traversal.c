#include <stdlib.h>
#include <stdbool.h>

struct tree_node;
typedef struct tree_node tree_node_t;

struct tree_node {
	tree_node_t *left;
	tree_node_t *right;
	void *data;
};

typedef tree_node_t expression_tree_t;

tree_node_t *make_tree_node(const void *data)
{
	tree_node_t *node = malloc(sizeof(tree_node_t));
	node->data = data;
        data = NULL;

        return node;
}

