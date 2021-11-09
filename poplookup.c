/*
 * CSE30 FA21 HW6
 * CSE30 username: cs30fa21cXX (TODO: Fill in)
 */

#include "poplookup.h"

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
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
 * Returns:   EXIT_SUCCESS if all ok, EXIT_FAILURE otherwise
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
int main(int argc, char *argv[]) {
	node** table;
	unsigned long size = TABLE_SIZE;
	// name of csv file
	char* filename;
	int info = 0;
	char* city;
	char* state;
	// indicates if the hash is to be done by city or state
	int hash_by_city = -1;

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
 * returns:   1 if success and 0 otherwise
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
int parse_opts(
	int argc,
	char* argv[],
	char** filename,
	unsigned long* size,
	int* info,
	char** city,
	char** state,
	int *hash_by_city
) {
	int opt;
	char *endptr;
	int fail = 0;
	extern int errno;

	opterr = 0;
	*filename = NULL;
	*city = NULL;
	*state = NULL;
	while ((opt = getopt(argc, argv, "it:c:s:")) != -1) {
		switch (opt) {
			case 'i':
				*info = 1;
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
					fail = 1;
				}
				break;
			case 'c':
				if (*hash_by_city == -1) {
					*city = optarg;
					*hash_by_city = 1;
				} else {
					fprintf(stderr, "%s: Cannot query both a city and a state\n", argv[0]);
					fail = 1;
				}
				break;
			case 's':
				if (*hash_by_city == -1) {
					*state = optarg;
					*hash_by_city = 0;
				} else {
					fprintf(stderr, "%s: Cannot query both a city and a state\n", argv[0]);
					fail = 1;
				}
				break;
			case '?':
				fprintf(stderr, "%s: unknown option -%c\n", argv[0], optopt);
				fail = 1;
				break;
			default:
				fail = 1;
				break;
		}
	}

	*filename = argv[optind];
	if (*filename == NULL) {
		fprintf(stderr, "%s: filename is required\n", argv[0]);
		fail = 1;
	}
	if (*city == NULL && *state == NULL) {
		fprintf(stderr, "%s: -c city or -s state is required\n", argv[0]);
		fail = 1;
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
 * Arguments: linked list chain pointer head, name of city, name of state, population
 */
node* node_lookup(node* front, char* city, char* state, int pop) {
	// TODO: delete body below and implement function
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
 * Arguments: linked list pointer head, city, state, population
 */
node* add_front(node* front, char* city, char* state, int pop) {
	// TODO: delete body below and implement function
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
 * Arguments: pointer to hash table, str string, hash table size, hash by city or state
 */
void print_population(node** table, char* str, unsigned long size, int hash_by_city) {
	// TODO: delete body below and implement function
	/*
	 * Use these format strings as given.
	 *
	 * printf("Unable to find any %s by the name of %s.\n", <arg1>, <arg2>);
	 * printf("Minimum: %d\tMaximum: %d\tAverage: %d\n", <arg1>, <arg2>, <arg3>);
	 */
	// TODO: delete suppression below and implement function
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
 */
int load_table(node** table, unsigned long size, char* filename, int hash_by_city) {
	// TODO: delete body below and implement function
	/*
	 * Use these format strings as given
	 *
	 * perror("load_table filename open");
	 * perror("load_table malloc");
	 * fprintf(stderr, "load_table duplicate entry: %s %s %d\n", <arg1>, <arg2>, <arg3>);
	 * fprintf(stderr, "load_table could not add %s\n", <arg>);
	 */
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) table;
	(void) size;
	(void) filename;
	(void) hash_by_city;
	return 0;
}

/*
 * print_info for debug
 *
 * Arguments: pointer to a hash table, number of elements
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
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) table;
	(void) size;
}

/*
 * delete_table
 *
 * Arguments: pointer to hash table, hash table array size
 */
void delete_table(node **table, unsigned long size) {
	// TODO: delete suppression below and implement function
	// suppresses warnings before implementation
	(void) table;
	(void) size;
}
