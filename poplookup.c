/*
 * CSE30 FA21 HW6
 * CSE30 username: cs30fa21cXX (TODO: Fill in)
 */

#include "poplookup.h"

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * main
 *
 * Arguments: argc, argv
 *
 * Operation: Main driver for the program, calls other funttions to:
 *	          parse the options, allocate the hash table, load the table, print out the table stats
 *            and make print population stats of the desired city/state
 * Returns:   EXIT_SUCESS if all ok, EXIT_FAILURE otherwise
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
int main(int argc, char *argv[]) {
	node **table;
	unsigned long size = TABLE_SIZE;
	// name of csv file
	char *filename;
	bool info = false;
	char *city;
	char *state;
	// indicates if the hash is to be done by city or state
	bool hash_by_city = true;

	if (!parse_opts(argc, argv, &filename, &size, &info, &city, &state, &hash_by_city)) {
		return EXIT_FAILURE;
	}

	if ((table = calloc(size, sizeof(node*))) == NULL) {
		fprintf(stderr, "%s: Unable to allocate space for hash table\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (load_table(table, size, filename, hash_by_city)) {
		return EXIT_FAILURE;
	}

	if (info) print_info(table, size);

	if (hash_by_city) {
		print_population(table, city, size, hash_by_city);
	} else {
		print_population(table, state, size, hash_by_city);
	}

	delete_table(table, size);

	return EXIT_SUCCESS;
}

/*
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * parse_opts
 *
 * Arguments: argc, argv, pointer to filename, pointer to hash table size, pointer to info flag,
 *            pointer to city name, pointer to state name, pointer to hash_by_city
 *
 * Operation: parses argv for ALL the allowable flags
 *            -i sets info to 1 (0 otherwise)
 *	          -t set the hash table size after converting the arguement to an unsigned long
 *	              >= MIN_TABLE_SIZE
 *            -c copies the city name to city
 *            -s copies the state name to state
 *            copies the name of the file to filename
 * returns:   true if success and false otherwise
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
bool parse_opts(
	int argc,
	char* argv[],
	char** filename,
	unsigned long* size,
	bool* info,
	char** city,
	char** state,
	bool *hash_by_city
) {
	int opt;
	char *endptr;
	bool fail = false;
	extern int errno;

	opterr = 0;
	*filename = NULL;
	*city = NULL;
	*state = NULL;
	while ((opt = getopt(argc, argv, "it:c:s:")) != -1) {
		switch (opt) {
			case 'i':
				*info = true;
				break;
			case 't':
				errno = 0;
				if (((*size = strtoul(optarg, &endptr, 10)) < MIN_TABLE_SIZE)
					|| (errno != 0)
					|| (*endptr != '\0')
				) {
					fprintf(
						stderr,
						"%s: -t value must be equal or larger than %d\n",
						argv[0],
						MIN_TABLE_SIZE
					);
					fail = true;
				}
				break;
			case 'c':
				if (*hash_by_city) {
					*city = optarg;
					*hash_by_city = 1;
				} else {
					fprintf(stderr, "%s: Cannot query both a city and a state\n", argv[0]);
					fail = true;
				}
				break;
			case 's':
				if (*hash_by_city) {
					*state = optarg;
					*hash_by_city = 0;
				} else {
					fprintf(stderr, "%s: Cannot query both a city and a state\n", argv[0]);
					fail = true;
				}
				break;
			case '?':
				fprintf(stderr, "%s: unknown option -%c\n", argv[0], optopt);
				fail = true;
				break;
			default:
				fail = true;
				break;
		}
	}

	*filename = argv[optind];
	if (*filename == NULL) {
		fprintf(stderr, "%s: filename is required\n", argv[0]);
		fail = true;
	}
	if (*city == NULL && *state == NULL) {
		fprintf(stderr, "%s: -c city or -s state is required\n", argv[0]);
		fail = true;
	}
	if (fail) {
		fprintf(stderr, "Usage: %s [-i] [-t tablesize] [-c city]/[-s state] filename\n", argv[0]);
	}

	return !fail;
}

/*
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * hash
 *
 * Arguments: a null terminated string
 *
 * Operation: calculates a hash value for the string
 *
 * returns:   the hash value
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
unsigned long hash(char *str) {
	unsigned long hash = 0;
	unsigned int c;
	while ((c = (unsigned char) *str++) != '\0') {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

/*
 * node_lookup
 *
 * Arguments: hash chain pointer head; name of city, name of state, population
 *
 * Operation: walks the chain looking for a node that has the same city, state and population
 *            returns a pointer to the node in the chain that has the the same city, state and
 *            population
 * returns:    NULL if not found
 */
node *node_lookup(node *front, char *city, char *state, int pop) {
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) front;
	(void) city;
	(void) state;
	(void) pop;
	return NULL;
}

/*
 * add_front
 *
 * Arguments: hash chain pointer head, city, state, population
 *
 * Operation: inserts a new node with the given data at the front of the chain
 *
 * returns: a pointer to the new head of the chain and NULL if the insert fails
 */
node *add_front(node *front, char *city, char *state, int pop) {
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) front;
	(void) city;
	(void) state;
	(void) pop;
	return NULL;
}

/*
 * print_population
 *
 * Arguments: hash chain pointer head, str string, hash table size, hash by city or state
 *
 * Operation: walks the chain looking for a node that has the city/state name
 *            prints maximum, minimum and average population of the chain
 *            If no such node exists in the table, print an error message.
 */
void print_population(node **table, char *str, unsigned long size, bool hash_by_city) {
	// TODO: delete body below and implement function
	/*
	 * Use these format strings as given.
	 *
	 * printf("Unable to find any %s by the name of %s.\n", <arg1>, <arg2>);
	 * printf("Minimum: %d\tMaximum: %d\tAverage: %d\n", <arg1>, <arg2>, <arg3>);
	 */
	// suppresses warnings before implementation
	(void) table;
	(void) str;
	(void) size;
	(void) hash_by_city;
}

/*
 * load_table
 *
 * Arguments: pointer to hash table, hash table size, file name, hash by city or state
 *
 * Operation:  opens the csv file with "r",
 *             reads while getline() > 0, each line from the file, and stores city, states and
 *                 population
 *             hashes the city/state name to find the chain
 *             calls add_front() to insert it into the table
 *             if unable to allocate memory, fprintf to stderr
 *             closes the file frees the buffer created by getline()
 *             Returns 0 if all ok, 1 otherwise
 */
int load_table(node **table, unsigned long size, char *filename, bool hash_by_city) {
	// TODO: delete body below and implement function
	/*
	 * Use these format strings as given
	 *
	 * fprintf(stderr, "load_table duplicate entry: %s %s %d\n", <arg1>, <arg2>, <arg3>);
	 * fprintf(stderr, "load_table could not add %s\n", <arg>);
	 */
	// suppresses warnings before implementation
	(void) table;
	(void) size;
	(void) filename;
	(void) hash_by_city;
	return 1;
}

/*
 * print_info for debug
 *
 * Arguments: pointer to a hash table; number of elements
 *
 * Operation: Walks the hash table chain by chain
 * 	      1. Calculates the number of nodes in the table
 *	      2. The longest and shortest chains
 *	      3. prints this to stderr
 */
void print_info(node **table, unsigned long size) {
	// TODO: delete body below and implement function
	/*
	 * Use these format strings as given
	 *
	 * printf("Table size: %lu\n", <arg>);
	 * printf("Total entries: %lu\n", <arg>);
	 * printf("Longest chain: %lu\n", <arg>);
	 * printf("Shortest chain: %lu\n", <arg>);
	 * printf("Empty buckets: %lu\n", <arg>);
	 */
	// suppresses warnings before implementation
	(void) table;
	(void) size;
}

/*
 * delete_table
 *
 * Arguments: pointer to hash table, hash table array size
 *
 * Operation: frees all the memory allocated while creating linked lists for each entry in the hash
 *            table.  Finally, it frees the memory allocated for the hash table itself.
 *
 */
void delete_table(node **table, unsigned long size) {
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) table;
	(void) size;
}
