/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* show the ordered array in the screen */
    int tem_min = temp_min(array);
    printf("La Menor Temperatura Minima Historica Registrada es %d\n", tem_min);


    int temps_maxs[YEARS];
    temps_maxs_totales(array, temps_maxs);
    printf("Las Mayores Temperaturas Maximas de cada Año son\n");
    for (unsigned int i = 0; i < YEARS; i++) {
        printf("%u: %d\n", (i+1980), temps_maxs[i]);
    }

    month_t precips_maxs[YEARS];
    precips_maxs_mensuales(array, precips_maxs);
    printf("Los Meses con mas precipitaciones de cada Año son\n");
    for (unsigned int i = 0; i < YEARS; i++) {
        printf("%u: %u\n", (i+1980), (precips_maxs[i]+1));
    }



    /* show the ordered array in the screen */
    array_dump(array);

    return (EXIT_SUCCESS);
}
