#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "struct_file.h"
#include "cs_tools.h"


// Note:
// File.ReadAllLines(filePath).ToList();
// Will be written as cs_ral_tolist() // To mean ReadAllLines().ToList();
// Is the same as reading all text into a variable
// Counting the number of "\n" symbols + 1 for the first line
// Sending the string to


/* C Sharp inspired file and IO utilities  */

int cs_file_exists(const char *filename)
{
    return access(filename, F_OK) != -1;
}
struct st_node* cs_ral_tolist(const char* path)
{
    struct st_node* current = malloc(sizeof(struct st_node));
    char *string = cs_read_all_text(path);
    char *token = "\n";
    current = cs_list_split(string, token);
    
    return current;
}
char* cs_read_all_text(char* path) 
{
    FILE* file = fopen(path, "r");
    char* buffer = NULL;
    size_t length = 0;
    ssize_t read = 0;
    
    if (file == NULL) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);
    buffer = (char*) malloc((length + 1) * sizeof(char));
    read = fread(buffer, sizeof(char), length, file);
    buffer[length] = '\0';
    fclose(file);
    
    if (read != length) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}
// char* cs_read_all_lines (char* path)
// {
//     // empty function
//     // I just made this function because I forgot the name of the function called here.
//     cs_ral_tolist(path);
// }
char* cs_read_line()
{
    char* line = NULL;
    size_t bufferSize = 0;
    ssize_t lineSize = getline(&line, &bufferSize, stdin);

    if (lineSize == -1) {
        printf("Failed to read input\n");
        return NULL;
    }

    // remove newline character from end of input
    if (line[lineSize - 1] == '\n') {
        line[lineSize - 1] = '\0';
    }

    return line;
}
int cs_write_all_lines(char* path, struct st_node *output, int total_nodes) 
{
    const int ZERO = 0;
    const int ONE = 1;

    FILE* file = fopen(path, "w");

    printf("\nBuild the file if it does not exist\n");
    getchar();
    if (file == NULL) 
    {
        // Don't leave any of this code once I change the inside of this function.
        printf("TODO: Change this to build the file if it does not exist.");
        getchar(); 

        return -1;  // TODO: Change this to build the file if it does not exist.
    }

    for (int index = ZERO; index < (total_nodes - ONE); index++) 
    {
        output = cs_element_at(output, index);
        fprintf(file, "%s\n", ((struct st_string*)output->page)->string);
    }

    fclose(file);    
    return 0;
}
int cs_write_all_text(const char *filename, const char *text)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) 
    {
        return -1;
    }
    fputs(text, fp);
    fclose(fp);
    return 0;
}


/* C Sharp inspired conversion tools */
int cs_to_int(const char *str)
{
    const int ZERO = 0;
    const int ONE = 1;
    int temp = ZERO;
    int check = ZERO;

    check = cs_check_int(str);
    if (check != ONE)
        return NULL;
    else
    {
        temp = atoi(str);
        return temp;
    }

}
int cs_check_int(const char *str) // This is just to check that the cs_to_int function recieves valid input
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}
// double cs_to_double(const char *str) // Pointless since I cannot return NULL, and input can be any double value.
// {
    
// }
int cs_check_double(const char *char_var)
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWENTY = 20; // 20 is small enough that it doesn't matter that it would be too high of a number of digits.
    const char null = '\0';
    const char decimal = '.';

    char num_total_string[TWENTY];
    double num_total_double;

    // printf("Enter a number: ");
    fgets(num_total_string, TWENTY, stdin);

    // Validate input
    int i = ZERO;
    int decimal_point_count = ZERO;
    while (num_total_string[i] != null) 
    {
        if (!isdigit(num_total_string[i]))
        {
            if (num_total_string[i] == decimal)
            {
                decimal_point_count++;
                if (decimal_point_count > ONE) 
                {
                    printf("\nInvalid: too many decimal points\n");
                    return ONE;
                }
                if (i == ZERO || !isdigit(num_total_string[i-ONE])) 
                {
                    printf("\nInvalid: decimal point in wrong position\n");
                    return ONE;
                }
            }
            else 
            {
                printf("\nInvalid: non-numeric character detected\n");
                return ONE;
            }
        }
        i++;
    }

    return ZERO;
}
char* cs_to_string(int value)
{
    char *str = malloc(12);  // allocate enough memory for an int in string form
    sprintf(str, "%d", value);
    return str;
}

/* C Sharp inspired linked list tools  */
struct st_node* cs_list_split(const char* string, const char* token_in)
{
    const int ZERO = 0;
    const int ONE = 1;
    struct st_node *current = malloc(sizeof(struct st_node));
    char *initial_token = strtok(string, token_in);
    char token[2];

    strcpy(token, initial_token);
    
    // count the number of times a token occurs
    int count = 0;
    for (int index = 0; index < strlen(string); index++) 
        if (string[index] == token) 
            count++;

    // Use the number counted to generate a linked list
    count -= ONE; // Decremented by one because there is already one element in the linked list
    while (count > ZERO)
    {
        current = cs_add(current);        
        --count;
    }


    // Fill the pages of the nodes of the linked list with the necessary values.
    int index = ZERO;
    while (initial_token != NULL) 
    {
        struct st_string* temp =  malloc(sizeof(struct st_string));

        strcpy(temp, initial_token); // copy the token string into the part array
        
        // store the split string into the linked list
        current = cs_element_at(current, index);
        current->page = &temp;

        // prepare the token for the next loop check
        initial_token = strtok(NULL, initial_token);
    }

    return current;
}
void cs_console_clear()
{
    system("clear");
}
void cs_clear_nodes(struct st_node* working_node)
{
    printf("\n\n\nMake sure that one node is left in the list\n\n");
    getchar();

	const int ONE = 1;
	int total_nodes = working_node->total_nodes;
	int last_index = total_nodes - ONE;
	
	while (working_node->index < last_index)
		working_node = working_node->next;
	
	while (working_node->b_previous == true)
	{
		working_node = working_node->previous;
		free(working_node->next);
	}
	
	free(working_node);
}
// This will give the node at whatever index value that is required
// This will not return a node at an index that is greater than the known
// quantity of nodes.
struct st_node* cs_element_at(struct st_node *working_node, int index)
{
    struct st_node *current = working_node;

    if ((index != current->index) && (index < current->total_nodes))
    {
        if(index > current->index)
        {
            while(index > current->index)
                current = current->next;
        }
        else if (index < current->index)
        {
            while(index < current->index)
                current = current->previous;
        }
    }

    return current;
}
// Function definition to link nodes together. 
// A second node parameter will be added once I have the current parts working
// in order to link a page to the node.
struct st_node* cs_add(struct st_node* first)
{
    const int ZERO = 0;
    const int ONE = 1;
    int first_index = first->index;
    int last_index = first->total_nodes - ONE;

    // Just incase a node is added to a linked list that is not on
    // the last node.
    if (first->index != last_index)
        first = cs_element_at(first, last_index);


	// struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct st_node* new_node = malloc(sizeof(struct st_node));
    new_node->total_nodes = first->total_nodes + ONE; // To bypass something in the next call since there are previous nodes.
    new_node = cs_node_intializer(new_node);

   	// Link first & second together
    first->b_next = true;
    first->next = new_node;

    new_node->index = (first->index + 1);    
    new_node->b_previous = true;
    new_node->previous = first;
    
    new_node = cs_add_total(new_node);
    printf("\nleft cs_add_node\n"); // delete line
    
    return new_node;    
}
struct st_node* cs_node_intializer(struct st_node* current)
{
    const int ZERO = 0;
    const int ONE = 1;

    if (current->total_nodes == ZERO)
    {
        printf("\nindex == 0\nfirst->b_previous = false\n"); // delete line
        getchar(); // delete line
        current->b_previous = false;
        current->previous = NULL;
        current->index = ZERO;
        current->total_nodes = ONE;
    }
    current->b_next = false;
    current->next = NULL;
    current->page = NULL;

    return current;
}
// This funtion is called from cs_add in order to know how many nodes 
// exist within the linked list from any node.
struct st_node*  cs_add_total(struct st_node* current)
{
	const int ZERO = 0;
	const int ONE = 1;
	const int TWO = 2;
	int index = ZERO;
	// struct st_node *previous = current->previous;
    // int total_nodes = ONE; // Set it to 1 because of the way I iterate through the list
    int current_index = ZERO;
    int total_nodes = ZERO;
    
    // First get the current index so that I can come back to it:
    current_index = current->index;

    // Get to the first node of the linked list.
    // Count from the first to the last to get the total number of nodes.
    while (current->b_previous != false)
    {
        current = current->previous;
    }
    while (current->b_next != false)
    {
        total_nodes += ONE;
        current = current->next;
    }
    total_nodes += ONE;

    // Get to the first node of the linked list.
    // Store the total number of nodes into each node.
    while (current->b_previous != false)
    {
        current = current->previous;
    }
    while (current->b_next != false)
    {
        current->total_nodes = total_nodes;
        current = current->next;
    }
    current->total_nodes = total_nodes;

    // Get to the first node of the linked list.
    // Get back to the node that was current when the function was entered.
    while (current->b_previous != false)
    {
        current = current->previous;
    }
    while (current->index != current_index)
    {
        current = current->next;
    }


    return current;
}


/* C Sharp inspired Date tools */
int cs_date_compare(const char *date_one, const char *date_two)
{
    // Return values.
    const int NEG_ONE = -1;
    const int ZERO = 0;
    const int ONE = 1;
    const int LESS = NEG_ONE;   // LESS is returned if date_one is earlier than date_two
    const int EQUAL = ZERO;     // EQUAL is returned if date_one is the same as date_two
    const int GREATER = ONE;    // GREATER is returned if date_one is after date_two

    // Split the date strings into month, day, and year components
    // int month1, day1, year1;
    // int month2, day2, year2;


    int month_one, day_one, year_one;
    int month_two, day_two, year_two;

    sscanf(date_one, "%d/%d/%d", &month_one, &day_one, &year_one);
    sscanf(date_two, "%d/%d/%d", &month_two, &day_two, &year_two);

    // Compare the year
    if (year_one > year_two) 
    {
        return GREATER;
    }
    else if (year_one < year_two)
    {
        return LESS;
    }

    // Compare the month
    if (month_one > month_two)
    {
        return GREATER;
    }
    else if (month_one < month_two)
    {
        return LESS;
    }

    // Compare the day
    if (day_one > day_two)
    {
        return GREATER;
    }
    else if (day_one < day_two)
    {
        return LESS;
    }

    // If the days are the same, the dates are equal
    return EQUAL;
}
char* cs_add_days(const char* date_str, int days)
{
    // parse date string into struct tm
    struct tm date = {0};
    if (strptime(date_str, "%m/%d/%Y", &date) == NULL)
    {
        fprintf(stderr, "Error parsing date string: %s\n", date_str);
        return NULL;
    }

    // add number of days to date
    time_t timestamp = mktime(&date);
    timestamp += (time_t)days * 24 * 60 * 60;

    // convert timestamp to new date string
    struct tm new_date = *localtime(&timestamp);
    char* new_date_str = (char*)malloc(11 * sizeof(char));
    strftime(new_date_str, 11, "%m/%d/%Y", &new_date);

    return new_date_str;
}
/*
int main() {
    char date1[] = "3/28/2023";
    char date2[] = "3/27/2023";

    int result = cs_date_compare(date1, date2);
    if (result > 0) {
        printf("%s is later than %s\n", date1, date2);
    } else if (result < 0) {
        printf("%s is earlier than %s\n", date1, date2);
    } else {
        printf("%s is the same as %s\n", date1, date2);
    }

    return 0;
}
*/



