/** @file route_manager.c
 *  @brief A program to analyze airline routes data.
 *  @author Your Name
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "list.h"
 
 #define MAX_LINE_LEN 100  // Adjusted based on input file constraints
 
 /**
  * @brief Structure representing an airline route.
  */
 typedef struct route_t {
     char airline[50];
     char source[50];
     char destination[50];
     int distance;
 } route_t;
 
 /**
  * @brief Reads airline routes from a file and stores them in a linked list.
  *
  * @param filename The name of the input file.
  * @return node_t* A pointer to the head of the linked list.
  */
 node_t* load_routes(const char *filename) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         fprintf(stderr, "Error: Cannot open file %s\n", filename);
         return NULL;
     }
 
     node_t *route_list = NULL;
     char line[MAX_LINE_LEN];
 
     while (fgets(line, sizeof(line), file)) {
         route_t *route = (route_t *)malloc(sizeof(route_t));
         if (!route) {
             fprintf(stderr, "Memory allocation error\n");
             exit(1);
         }
 
         sscanf(line, "%49s %49s %49s %d", route->airline, route->source, route->destination, &route->distance);
         route_list = add_inorder(route_list, new_node((char *)route)); // Using linked list functions
     }
 
     fclose(file);
     return route_list;
 }
 
 /**
  * @brief Prints all routes in the linked list.
  *
  * @param list The linked list containing routes.
  */
 void print_routes(node_t *list) {
     node_t *curr = list;
     while (curr) {
         route_t *route = (route_t *)curr->word;
         printf("Airline: %s, From: %s, To: %s, Distance: %d km\n",
                route->airline, route->source, route->destination, route->distance);
         curr = curr->next;
     }
 }
 
 /**
  * @brief Frees allocated memory for the route list.
  *
  * @param list The linked list to free.
  */
 void free_routes(node_t *list) {
     node_t *temp;
     while (list) {
         temp = list->next;
         free(list->word);
         free(list);
         list = temp;
     }
 }
 
 /**
  * @brief Main function to manage airline routes.
  *
  * @param argc The number of arguments.
  * @param argv The argument list.
  * @return int Program exit status.
  */
 int main(int argc, char *argv[]) {
     if (argc != 2) {
         fprintf(stderr, "Usage: %s <routes_file>\n", argv[0]);
         return 1;
     }
 
     node_t *routes = load_routes(argv[1]);
 
     if (routes) {
         printf("Loaded Airline Routes:\n");
         print_routes(routes);
         free_routes(routes);
     } else {
         printf("No routes loaded.\n");
     }
 
     return 0;
 }
 