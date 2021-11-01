#include <stdbool.h>

/*
 * Constants
 */
#define LINE_SIZE 1024   // array size for reading with fgets
#define TABLE_SIZE 1873  // default hash table elements
#define MIN_TABLE_SIZE 3 // Smallest allowable has table size
#define CITYNAMESZ 100   // Buffer size for reading city names from file
#define STATENAMESZ 20   // Buffer size for reading state names from file
#define POPSTRSZ 20      // Buffer size for reading population numbers from file

/*
 * Hash table chains are of the following type
 */
typedef struct node {
	char* city;
	char* state;
	int pop;
	struct node* next;
} node;

extern void print_population(node **table, char *str, unsigned long size, int hash_by_city);
extern node *node_lookup(node *front, char *city, char *state, int pop);
extern node *add_front(node *front, char *city, char *state, int pop);
extern unsigned long hash(char *str);
extern void print_info(node **table, unsigned long size);
extern bool parse_opts(
	int argc,
	char *argv[],
	char **filename,
	unsigned long *size,
	bool *info,
	char **city,
	char **state,
	int *hash_by_city
);
extern int load_table(node **table, unsigned long size, char *filename, int hash_by_city);
extern void delete_table(node **table, unsigned long size);
