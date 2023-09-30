#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h> 
#include <stdbool.h>
#include <math.h>
#include "struct_init.h"
#include "struct_file.h"
#include "cs_tools.h"

// Constants
#define ZERO_CHAR "0"
#define ZERO_INT 0
#define ZERO 0
#define ONE_INT 1
#define FIVE_INT 5
#define SIX_INT 6
#define SEVEN_INT 7
#define ZERO_DOUBLE 0.0
#define NONE "none"
#define TRUE_CHAR "true"
#define FALSE_CHAR "false"




/* CORE FUNTIONS */
void get_date();
void linux_path();
void start_up();
void check_for_count();
void main_menu();
void available_options(int options);
void main_options(int selection_int);
void selection_dialogs(int dialog);
void create_course();
void setup_data();
void produce_course();
void update_counts();
void course_listpath();
void add_course_tolist(const char *file_path, const char *file_pathtwo, const char *course_filepath);
void select_course();
void study_course();
void calculate_learning();
void add_repetition();
void spacing_multiplier();
void interval_time();
void engram_stability();
void engram_retrievability();
void process_date();
void save_progress();
void change_topic_questions();
void study_incrementer();
void study_decrementer();
void clear_lists();
void study_lines();
void study_dates();
void study_false();
void study_true();
void study_not_done();
void study_not_zero();
void study_hud();

/* PREDICTION FUNCTIONS */
void predict_main();
void avg_diff();
void collect_first_studies();
int add_firsts_collect(int topic_number, int index);
void y_max_firsts();
void y_max_sort_firsts();
void find_high_y();
void prepare_past_studies();
void initialize_one_past_study(int index, int repetition);
int past_study_initialization(int index, int repetition);
void simulate_past_studies();
void x_max_repeats();
bool sort_xrep_counts(bool repsort_correct);
void x_max_to_sort();
void add_to_xmax();
void x_max_count_reps();
void x_max_repeat_sort();
bool x_insert_sort(bool xsort_correct);
void collect_non_studied();
int non_study_getter(int topicNumber, int loopIndex);
void generate_projected_studies();
void prediction_lists_clear();
void predict_studies();
void collect_study_x();
void gensims_all_getter(int index);
void find_y_at_x();
void rep_setter();
void goal_setter();
void collect_study_y();
void y_to_gen_sims_all(int index);
void reduce_new();
void get_reduced_new(int count);
void get_reduced_projected(int count);
void sim_calculate_learning();
void sim_interval_time();
void sim_add_repetition();
void sim_process_date();

/* WEEKLY SCHEDULE FUNCTIONS */
void check_for_week();
bool skip_checker(date_time *simDate);
void weekly_schedule();
void weekly_dialog();
void toggle_day_function(int dayOption);

/* FILE PATHS FUNCTIONS */
void init_file_path(int choice);
void free_file_path(int choice);


// NOTE: the make a checklist struct that is set to true once a linked list
//       recieves its firts page for a node.
//      
//       it will be set to false upon clearing each element, except for the
//       first node.
//
//      This will make it easy to ensure that there will not be too many nodes added.
//      Once program parts converted, then go through the parts that have cs_add, and
//      make it check before adding.
//
//      Then go through the parts where the lists are cleared, and set the corresponding
//      element in the struct checklist to false, but make sure to leave at least one node.


// NOTE 2: To make the logic of the program potentially a bit more difficult for a program to match
//         this source code to the C# version I wrote, I could make the function calls recursive,
//         instead of calling them one after the other exits. But if I do this, then do it after
//         I have the program working with the current logical design.



// Memory Leaks:
// Once done converting, go through and collect the list of string pointers 
// that I can to put into a global variable list, to decrease the number 
// of memory leaks.
// All unfreed "char *var" strings are memory leaks. must free them after not being used.

// Initialize some lists
// const int ZERO = 0;
// struct st_fstudy_counts first_page;
// fstudy_counts->page = &first_page;
// ((struct st_fstudy_counts*)fstudy_counts->page)->counts = ZERO;



// Figure out if I can even use this in a separate file like I want.
struct st_file_strings
{
	// comment a done after each variable once I
	// have the code store that string into this 
	// struct. That way I can reduce the amount of
	// code by checking off a list using 1 as a check. 
	// mark. Once all have been done, remove the check
	// mark comments from here.


	// These must be initialized after the 
	// username is obtained. 
	// They must be freed upon exit of the program.
	// These are all full file paths.

	/* In course_list_path() */
	// struct choice 1 along with it's bak file
	char *txt_course_listfile; //1

	// Back up file made in case power outage while file being written, but doesnt complete. It can happen.
	char *bak_course_listfile;  

	/* In check_for_count() */
	// struct choice 2
	char *course_countfile;
	


	/* In check_for_week() */
	// struct choice 3
	char *week_file; // I use sc extension for schedule

	// This one must get initialized at the same time as
	// globals.course_name
	// It must be freed upon exit of the course, and the program.
	/* I think it is in select_course */
	// struct choice 4
	char *txt_course_namefile;

	// Back up file made in case power outage while file being written, but doesnt complete. It can happen.
	char *bak_course_namefile;
};
extern struct st_file_strings file_strings;


// 36 functions complete
/********************** Core program **********************************/
int main(void)
{
    get_date();
    linux_path();
    start_up();
}
void get_date()
{
/*
Remember to free(globals.the_date); when you're done using it to prevent memory leaks.
*/
    
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    globals.the_date = malloc(11 * sizeof(char));  // Allocate memory
    if (globals.the_date != NULL) {
        strftime(globals.the_date, 11, "%m/%d/%Y", local_time);
    }
    // Add error handling for malloc failure if you want
}


void linux_path()
{
    const int ONE = 1;
    bool skip_all = false;

    // Get the username, then store it locally
    char *username = getenv("USER");
    if (username == NULL)
    {
        perror("getenv() error");
        // return EXIT_FAILURE;
        skip_all = true;
    }
    
    char *local_username = malloc(strlen(username) + 1);

    if (skip_all != true)
    {
        if (local_username == NULL)
        {
            perror("malloc() error");
            // return EXIT_FAILURE;
        }
        strcpy(local_username, username);

        // Set up required variables, and allocate memory for the whole file name
        char *filename1 = "/home/";
        char *filename2 = "/Documents/GlideCLI";
        char *path_string;
        int len = strlen(filename1) + strlen(local_username) + strlen(filename2) + ONE;
        path_string = malloc(len);
        if (path_string == NULL)
        {
            perror("malloc() error");
            free(local_username);
            // return EXIT_FAILURE;
        }

        // Combine the parts into the filename
        sprintf(path_string, "%s%s%s", filename1, local_username, filename2);

        // Make the directory if it does not exist
        struct stat st = {0};
        if (stat(path_string, &st) == -1)
        {
            mkdir(path_string, 0700);
        }

        // Store the path into the global struct
        globals.directory_path = path_string;
        globals.os_switch = true;
    }
    free(local_username);
}
void start_up()
{
    while (true)
    {
        study_decrementer();
        check_for_count();
        check_for_week();
        main_menu();
        study_incrementer();
        clear_lists();
    }
}


void check_for_count()
{
    const int ZERO = 0;
    const int OPTION_TWO = 2; // this is the initialization option needed to get the file path

    struct st_string *c_course_count = malloc(sizeof(struct st_string));
    if (c_course_count == NULL)
    {
        perror("malloc() error");
        exit(EXIT_FAILURE);
    }
    
    int i_course_count = ZERO;

    // Initialize the file path
    init_file_path(OPTION_TWO);
    if (file_strings.course_countfile == NULL)
    {
        perror("No path for course_countfile"); // You might want to handle this error differently
        free(c_course_count);
        exit(EXIT_FAILURE);
    }
    
    // Try to read the text from the file
    if ((c_course_count->string = read_all_text(file_strings.course_countfile)) != NULL)
    {
        i_course_count = atoi(c_course_count->string);
        globals.course_count = i_course_count;
    }
    else
    {
        // If reading fails, initialize the file and try again
        write_all_text(file_strings.course_countfile, "0");
        free(c_course_count->string); // Ensure the previous string is deallocated
        c_course_count->string = read_all_text(file_strings.course_countfile);
        
        if (c_course_count->string == NULL)
        {
            perror("Failed to read course_countfile after initializing it");
            free(c_course_count);
            exit(EXIT_FAILURE);
        }
        
        i_course_count = atoi(c_course_count->string);
        globals.course_count = i_course_count;
    }

    // Free up what's no longer needed
    free(c_course_count->string);
    free(c_course_count);
}



void main_menu()
{
    available_options(globals.course_count > 0);
}
void available_options(int options)
{
    int selectionInt;
    char *selection_string;

    globals.made_select = false;

    do
    {
        if (options == 0)
        {
            selection_dialogs(1);
        }
        else if (options == 1)
        {
            selection_dialogs(2);
        }

        selection_string = cs_read_line();

        // Check that the user's input is valid
        if (!isdigit(selection_string[0]))
        {
            printf("\nInvalid Input. Try again:\n");
            continue;
        }

        selectionInt = atoi(selection_string);
        free(selection_string);

        if ((options == 0 && (selectionInt == 1 || selectionInt == 2)) ||
            (options == 1 && (selectionInt >= 1 && selectionInt <= 5)))
        {
            main_options(selectionInt);
            globals.made_select = true;
        }
        else
        {
            printf("\nInvalid Selection. Try again:\n");
        }

    } while (globals.made_select == false);
}

void main_options(int selection_int)
{
    // Clear console and set flag for selected option for cases 1-5
    if (selection_int >= 1 && selection_int <= 5)
    {
        cs_console_clear();
        globals.made_select = true;
    }

    switch (selection_int)
    {
    case 1:
        printf("\nWeekly Schedule Selected.\n");
        weekly_schedule();
        break;
    case 2:
        printf("\nCreate new course selected.\n");
        create_course();
        break;
    case 3:
        printf("\nCOURSES:\n");
        study_incrementer();
        clear_lists();
        select_course();
        study_course();
        break;
    case 4:
        printf("Current date set at: %s", globals.the_date);
        printf("\nEnter a date, in your region's formatting, to force the program to use it:");
        printf("\nExample formatting provided...\n"); // You could continue your example here
        globals.the_date = cs_read_line();
        break;
    case 5:
        printf("\nGood Bye");
        exit(0);
        break;
    default:
        printf("\nInvalid option selected.\n");
        globals.made_select = false;
        break;
    }
} 

void print_line_breaks(int n) {
    for (int i = 0; i < n; ++i) {
        printf("\n");
    }
}

void clear_and_print_date() {
    cs_console_clear();
    printf("\nDate: %s", globals.the_date);
}

void selection_dialogs(int dialog)
{
    // FIXME: ChatGPT cut many of the options out of the switch
    const int ZERO = 0;

    switch (dialog)
    {
    case 1:
        cs_console_clear();
        print_line_breaks(3);
        printf("1: Exit the program\n2: Create a new course\n");
        print_line_breaks(4);
        printf("Enter an option from the menu: ");
        break;
    case 2:
        clear_and_print_date();
        print_line_breaks(3);
        printf("1: Weekly Schedule\n2: Create a new course\n3: Study a course\n4: Force GlieCLI to use a different date\n5: Exit the program\n");
        print_line_breaks(4);
        printf("Select an option from the menu: ");
        break;
    // Other case statements remain the same
    }
} 

void create_course()
{
    const int ZERO_INT = 0;
    const char ZERO_CH = '0';
    const int FOUR = 4;
    // increment the course count after the course file containing the topic names
    // is created AND/OR updated.
    creation_vars.chapter_loop = ZERO_INT;
    creation_vars.current_chapter = ZERO_INT;
    creation_vars.chapters_int = ZERO_INT;
    creation_vars.topic_counter = ZERO_INT;
    creation_vars.topic_count_string = ZERO_CH;
    creation_vars.topic_loop = ZERO_INT;
    creation_vars.subsection_counter = ZERO_INT;
    creation_vars.subsection_string = ZERO_CH;
    creation_vars.sub_loop = ZERO_INT;
    creation_vars.topic_id = ZERO_INT;
    globals.topic_count = ZERO_INT;
    creation_vars.current_subsection = ZERO_INT;
    selection_dialogs(FOUR);
    setup_data();
    produce_course();
    update_counts();
} 
void setup_data()
{
    // Constants
    const int ZERO_INT = 0;
    const int ONE_INT = 1;
    const int FIVE_INT = 5;
    const int SIX_INT = 6;
    const int SEVEN_INT = 7;
    const double ZERO_DOUBLE = 0.0;

    // Initialization
    struct st_node *topics = malloc(sizeof(struct st_node));
    topics->total_nodes = ZERO_INT;
    topics = cs_node_initializer(topics);

    // For CreateCourse()
    while (creation_vars.chapter_loop < creation_vars.chapters_int)
    {
        creation_vars.current_chapter = creation_vars.chapter_loop + ONE_INT;
        selection_dialogs(FIVE_INT);

        while (creation_vars.sub_loop < creation_vars.subsection_counter)
        {
            creation_vars.current_subsection = creation_vars.sub_loop + ONE_INT;
            selection_dialogs(SIX_INT);
            creation_vars.topic_counter = atoi(creation_vars.topic_count_string);
            globals.topic_count += creation_vars.topic_counter;

            while (creation_vars.topic_loop < creation_vars.topic_counter)
            {
                // Add a new topic node and initialize its page
                topics = cs_add(topics);
                struct st_topic_model *new_topic = malloc(sizeof(struct st_topic_model));
                topics->page = new_topic;

                // Setup essential data
                if (creation_vars.topic_loop == ZERO_INT)
                    new_topic->top_id = ZERO_INT;

                creation_vars.current_topic = creation_vars.topic_loop + ONE_INT;
                sprintf(creation_vars.topic_string, "%d", creation_vars.current_topic);
                
                // Create Top_Name string
                char top_name[256]; // Ensure that the size is appropriate
                snprintf(top_name, sizeof(top_name), "%d.%d.%s",
                         creation_vars.current_chapter, 
                         creation_vars.current_subsection, 
                         creation_vars.topic_string);
                
                new_topic->top_name = strdup(top_name);
                selection_dialogs(SEVEN_INT);

                creation_vars.problem_count = atof(creation_vars.p_count_string);
                new_topic->course_id = globals.course_count + ONE_INT;
                new_topic->top_studied = false;
                new_topic->next_date = strdup("NONE");
                new_topic->first_date = strdup("NONE");
                new_topic->num_problems = creation_vars.problem_count;
                new_topic->num_correct = ZERO_DOUBLE;
                new_topic->top_difficulty = ZERO_DOUBLE;
                new_topic->top_repetition = ZERO_INT;
                new_topic->interval_remaining = ZERO_DOUBLE;
                new_topic->interval_length = ZERO_DOUBLE;
                new_topic->engram_stability = ZERO_DOUBLE;
                new_topic->engram_retrievability = ZERO_DOUBLE;

                // Loop management
                ++creation_vars.topic_loop;
                creation_vars.check = creation_vars.topic_loop;
                if (creation_vars.check <= creation_vars.topic_counter)
                {
                    ++creation_vars.topic_id;
                    new_topic->top_id = creation_vars.topic_id;
                }
            }

            // Reset topic-related variables
            creation_vars.topic_counter = ZERO_INT;
            creation_vars.topic_loop = ZERO_INT;
            ++creation_vars.sub_loop;
        }

        // Reset subsection-related variables
        creation_vars.subsection_counter = ZERO_INT;
        creation_vars.sub_loop = ZERO_INT;
        ++creation_vars.chapter_loop;
    }
} 

void produce_course()
{
    const int ZERO = 0;
    const int ONE = 1;

    struct st_node *output = malloc(sizeof(struct st_node));
    output->total_nodes = ZERO;
    output = cs_node_intializer(output);

    int total_topics = topics->total_nodes;
    int node_quantity = total_topics - ONE;
    int index = ZERO;

    // Build out the node chain
    while (index < node_quantity)
    {
        output = cs_add(output);
        ++index;
    }
    output = cs_element_at(output, ZERO);

    // Add pages to nodes
    index = ZERO;
    while (index < total_topics)
    {
        struct st_string *temp = malloc(sizeof(struct st_string));
        output->page = temp;

        topics = cs_element_at(topics, index);

        char *comma = ",";
        char str_top_id[32], str_course_id[32], str_top_studied[32], str_num_problems[64], str_num_correct[64],
             str_top_difficulty[64], str_top_repetition[32], str_interval_remaining[64], str_interval_length[64],
             str_engram_stability[64], str_engram_retrievability[64];

        // Convert to string
        sprintf(str_top_id, "%d", ((struct st_topic_model*)topics->page)->top_id);
        sprintf(str_course_id, "%d", ((struct st_topic_model*)topics->page)->course_id);
        sprintf(str_top_studied, "%d", ((struct st_topic_model*)topics->page)->top_studied);
        sprintf(str_num_problems, "%f", ((struct st_topic_model*)topics->page)->num_problems);
        sprintf(str_num_correct, "%f", ((struct st_topic_model*)topics->page)->num_correct);
        sprintf(str_top_difficulty, "%f", ((struct st_topic_model*)topics->page)->top_difficulty);
        sprintf(str_top_repetition, "%d", ((struct st_topic_model*)topics->page)->top_repetition);
        sprintf(str_interval_remaining, "%f", ((struct st_topic_model*)topics->page)->interval_remaining);
        sprintf(str_interval_length, "%f", ((struct st_topic_model*)topics->page)->interval_length);
        sprintf(str_engram_stability, "%f", ((struct st_topic_model*)topics->page)->engram_stability);
        sprintf(str_engram_retrievability, "%f", ((struct st_topic_model*)topics->page)->engram_retrievability);

        // Concatenate
        int len = 1280;  // Estimated buffer size, adjust if needed
        char *result = malloc(len);
        snprintf(result, len, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                 str_top_id, str_course_id, ((struct st_topic_model*)topics->page)->top_name,
                 str_top_studied, ((struct st_topic_model*)topics->page)->next_date,
                 ((struct st_topic_model*)topics->page)->first_date, str_num_problems,
                 str_num_correct, str_top_difficulty, str_top_repetition,
                 str_interval_remaining, str_interval_length, str_engram_stability,
                 str_engram_retrievability);

        temp->string = result;

        ++index;
        if (index < output->total_nodes)
        {
            output = cs_element_at(output, index);
        }
    }

    output = cs_element_at(output, ZERO);

    // Write to File
    char *file_path;
    int len = strlen(globals.directory_path) + strlen("/") + strlen(globals.course_name) + strlen(".txt") + ONE;
    file_path = malloc(len);
    sprintf(file_path, "%s/%s.txt", globals.directory_path, globals.course_name);

    cs_write_all_lines(file_path, output, output->total_nodes);

    char *list_file;
    len = strlen(globals.directory_path) + strlen("/CourseList.txt") + ONE;
    list_file = malloc(len);
    sprintf(list_file, "%s/CourseList.txt", globals.directory_path);

    // Free memory
    index = ZERO;
    while (index < output->total_nodes)
    {
        output = cs_element_at(output, index);
        free(((struct st_string*)output->page)->string);
        free(output->page);
        ++index;
    }

    cs_clear_nodes(output);
    free(output);
}
void update_counts()
{
    const int ONE = 1;
    const int EIGHT = 8;
    
    // Declare and initialize variables
    int new_id = globals.course_count;
    ++new_id;

    char new_id_str[12];  // Max string length for int32 is 11 chars + null terminator
    sprintf(new_id_str, "%d", new_id);

    char *path;
    char *course_count_str;
    char *list_contents;

    // Create the new list entry
    int len = strlen(new_id_str) + 1 + strlen(globals.course_name) + strlen(".txt") + 1 + strlen(creation_vars.file_path) + 1;
    list_contents = malloc(len);
    snprintf(list_contents, len, "%s,%s.txt,%s", new_id_str, globals.course_name, creation_vars.file_path);

    struct st_node *content_list = malloc(sizeof(struct st_node));
    struct st_string *temp_string = malloc(sizeof(struct st_string));
    temp_string->string = list_contents;

    content_list->page = temp_string;
    content_list->index = 0;
    content_list->total_nodes = ONE;

    // Check for file existence and write accordingly
    if (cs_file_exists(creation_vars.list_file))
        course_listpath();
    else
        cs_write_all_lines(creation_vars.list_file, content_list, ONE);

    // Create the path to the CourseCount.txt file
    len = strlen(globals.directory_path) + 1 + strlen("CourseCount.txt") + 1;
    path = malloc(len);
    snprintf(path, len, "%s/%s", globals.directory_path, "CourseCount.txt");

    // Update course count
    course_count_str = cs_read_all_text(path);
    globals.course_count = atoi(course_count_str);
    free(course_count_str);  // Don't forget to free memory if cs_read_all_text allocates memory

    ++globals.course_count;
    len = snprintf(NULL, 0, "%d", globals.course_count);  // Find out the length of the string
    course_count_str = malloc(len + 1);
    snprintf(course_count_str, len + 1, "%d", globals.course_count);

    cs_write_all_text(path, course_count_str);

    // Cleanup
    free(path);
    free(list_contents);
    free(temp_string);
    free(content_list);
    free(course_count_str);

    // Go to the selection dialog
    selection_dialogs(EIGHT);
}
void course_listpath()
{
    const int OPTION_ONE = 1; // this is the initialization option needed to get the file path

    init_file_path(OPTION_ONE);
    add_course_tolist(file_strings->txt_course_listfile, file_strings->bak_course_listfile, file_strings->txt_course_namefile);
}

// This one may need to be redesigned, because it looks like it just re-writes the info
// back to the file that it already had.
// Just double check later. It's probably fine.
void add_course_tolist(const char *file_path, const char *file_pathtwo, const char *course_filepath)
{
    const int ZERO = 0;
    const int ONE = 1;
    int course_id = globals.course_count;
    ++course_id;

    // Initialize linked list and temporary string
    struct st_node *lines = malloc(sizeof(struct st_node));
    lines->total_nodes = ZERO;
    lines = cs_node_intializer(lines);  // Initialize the linked list

    struct st_string *temp_string;

    // Read existing lines from the file if it exists
    if (cs_file_exists(file_path)) {
        lines = cs_ral_tolist(file_path);
    }

    // Prepare the string to be added to the list
    char course_id_str[20]; // Assuming course_id would not exceed this length
    snprintf(course_id_str, sizeof(course_id_str), "%d", course_id);
    int len = strlen(course_id_str) + strlen(globals.course_name) + strlen(course_filepath) + 5; // Additional 5 characters for two commas, ".txt", and a null terminator
    temp_string = malloc(len);
    snprintf(temp_string, len, "%d,%s.txt,%s", course_id, globals.course_name, course_filepath);

    // Add the new line to the linked list
    lines = cs_element_at(lines, lines->total_nodes - 1);  // Move to the last element
    lines = cs_add(lines); // Add a new element at the end
    lines->page = temp_string;
    
    // Write to files
    lines = cs_element_at(lines, ZERO); // Move to the first element
    cs_write_all_lines(file_pathtwo, lines, lines->total_nodes);
    cs_write_all_lines(file_path, lines, lines->total_nodes);

    // Free memory
    int index = ZERO;
    while (index < lines->total_nodes)
    {
        lines = cs_element_at(lines, index);
        free(lines->page);  // Free the string
        ++index;
    }
    cs_clear_nodes(lines);  // Clear all nodes
}


// 9-11-2023
// Continue from the next function. 
// Need to use other PC.
// This one is too slow while ffmpeg is being used

// Clean this function up.
// DOES NEED THE 5 PROTOCOLS
void select_course() {
    // Constants
    const int ZERO = 0;
    const int ONE = 1;
    const int NINE = 9;
    const int OPTION_FOUR = 4;

    // Variables
    int selection_int = ZERO;
    bool valid_input = false;
    char *selection_string;

    // Initialize complete_list
    struct st_node *complete_list = malloc(sizeof(struct st_node));
    complete_list->total_nodes = ZERO;
    complete_list = cs_node_intializer(complete_list);

    // Read all lines and convert to list
    struct st_node *lines = cs_ral_tolist(file_strings.txt_course_listfile);

    // Build out the node chain and add pages to nodes
    int total_nodes = lines->total_nodes;
    int index = ZERO;
    while (index < total_nodes) {
        complete_list = cs_add(complete_list);
        lines = cs_element_at(lines, index);
        struct st_node *entries = cs_list_split(lines->page, ",");
        struct st_course_list_model *new_list = malloc(sizeof(struct st_course_list_model));
        complete_list->page = new_list;

        // Populate new_list with data from entries
        entries = cs_element_at(entries, ZERO);
        new_list->course_id = atoi(entries->page);
        entries = cs_element_at(entries, ONE);
        new_list->course_name = entries->page;
        entries = cs_element_at(entries, TWO);
        new_list->file_path = entries->page;

        complete_list = cs_element_at(complete_list, ++index);
    }

    // Display the courses
    index = ZERO;
    complete_list = cs_element_at(complete_list, ZERO);
    while (index < total_nodes) {
        printf("Course ID: %d - Course Name: %s\n",
               ((struct st_course_list_model*)complete_list->page)->course_id,
               ((struct st_course_list_model*)complete_list->page)->course_name);
        complete_list = cs_element_at(complete_list, ++index);
    }

    // Selection Loop
    while (!valid_input) {
        selection_dialogs(NINE);
        selection_string = cs_read_line();
        selection_int = cs_to_int(selection_string);

        valid_input = (selection_int != NULL);

        if (valid_input) {
            --selection_int;
            int test_var = selection_int + ONE;
            if (test_var >= ONE && test_var <= total_nodes) {
                complete_list = cs_element_at(complete_list, selection_int);
                if (test_var == ((struct st_course_list_model*)complete_list->page)->course_id) {
                    globals.file_path = ((struct st_course_list_model*)complete_list->page)->file_path;
                    globals.course_name = ((struct st_course_list_model*)complete_list->page)->course_name;
                    free_file_path(OPTION_FOUR);
                    init_file_path(OPTION_FOUR);
                } else {
                    printf("Invalid selection.\n");
                    valid_input = false;
                }
            } else {
                printf("Invalid selection.\n");
                valid_input = false;
            }
        } else {
            printf("Invalid selection.\n");
        }
    }

    // Clean-up
    index = ZERO;

    // Free memory for entries and new_list within the loop
    while (index < complete_list->total_nodes) {
        complete_list = cs_element_at(complete_list, index);
        free((struct st_course_list_model*)complete_list->page); // Free new_list
        free(entries); // Free entries
        ++index;
    }

    // Free memory for lines
    index = ZERO;
    while (index < lines->total_nodes) {
        lines = cs_element_at(lines, index);
        free((struct st_string*)lines->page);
        ++index;
    }

    // Free memory for complete_list and lines
    free(complete_list);
    free(lines);
} 

// Take note of the functions in c# source for locations of clearing of lists, and
// which lists are cleared.

void study_course()
{
    const int ZERO = 0;
    const int THREE = 3;

    predict_vars.lock_goals = false;
    predict_vars.until_new = ZERO;
    study_vars.index = ZERO;
    study_vars.today = globals.the_date;
    study_vars.file_path = globals.file_path;
    study_vars.line_count = ZERO;
    study_lines();
    if (study_vars.line_count > ZERO)
    {
        if (topics_list->total_nodes > ZERO)
        {
            study_dates();
            if (to_study->total_nodes != ZERO)
            {
                study_not_zero();
                while (globals.problems_done != true)
                {
                    if (globals.new_left > ZERO)
                    {
                        predict_vars.end_reached = false;
                        predict_main();
                    }
                    else
                        predict_vars.end_reached = true;
                    study_not_done();

                    if (strcmp(study_vars.response, "m") == 0)
                        return;
                }
            }
        }
        selection_dialogs(THREE);
    }
    else
        selection_dialogs(THREE);
}

void calculate_learning()
{
    const int ONE = 1;
    add_repetition();
    topics_list = cs_element_at(topics_list, globals.topic_id);
    int ith_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;
    if (ith_repetition == ONE)
        spacing_multiplier();
    interval_time();
    engram_stability();
    engram_retrievability();
    process_date();
}
void add_repetition()
{
    const int ONE = 1;
    int updated_rep = ((struct st_topic_model*)topics_list->page)->top_repetition + ONE;
    ((struct st_topic_model*)topics_list->page)->top_repetition = updated_rep;
}
void spacing_multiplier()
{
    /*
        The calculation of difficulty performed here is different than the formula given by the
        research article named "Optimization of repetition spacing in the practice of learning."
        That research article is the basis for the calculation of difficulty for the article named
        "Two components of long-term memory." Both articles are included with the source code.
        The calculation is different due to an inaccuracy in the results of the researchers proposed calculation. 
        In the research article, engrams that have a difficulty calculation below 1.3, which means they are very 
        difficult, are just given a value of 1.3, even though engram difficulties that actually calculate to 1.3 
        are easier than the ones that are less then 1.3. Engrams that have a difficulty calculated at greater 
        than 2.5, which is the value found best to represent the easiest engrams, which I call "topics in my 
        software, are just given a value of 2.5, even though the topics that actually calculated to 2.5 are harder 
        than those that are just assigned a value of 2.5, even though they are easier than the topics that were 
        actually calculated at 2.5.

        I therefore use a different formula to calculate difficulty within the constraints of the values 1.3, being
        the hardest for the brain to form connections that allow for understanding of information, and 2.5 being the
        easiest for the brain to form connections that allow for understanding of information.

        The slope-intercept formula is much simpler than that proposed by the researchers, and is very accurate from
        my own experience with calculating difficulty of information. I currently do not have the funds to do the proper
        experiments with subjects to determine the validity of this portion of the software, as well as the assertion in which
        I am making. But it currently appears to me to be the most logical way of calculating this variable.

        If there exists a more accurate way of calculating difficulty, then I hope I, or someone else that will publish the
        research, finds this formula. If that ever happens, and I become aware of it, or if I find it in a study I hope to conduct in
        the future, then I will change this formula to the more accurate one. But far as I can tell, it is currently the best 
        way to calculate difficulty, and I currently have no reason to think the formula itself can be improved. However, 
        I do think the endpoints of the linear equations have the possibility of having more accurate values than 1.3 and 2.5,
        but I can not know that without running a proper experiment.

        Other software that I have seen that has similar functionality to this software uses the inacurate calculation
        from the research article I mentioned. On top of that, the users of those software packages are forced to
        use their intuition about how difficult a piece of information was to retrieve from memory. Intuition is
        not the basis on which this software aims to calculate anything, though I am currently forced to use some intuition
        myself, due to me having no current way of running proper experiments, and the fact that a piece of information is omitted
        from the research articles, such as the length of time of the initial interval. I used my intuition to make the initial 
        interval 24 hours. It seems logical that it is 24 hours, seeing as how a study session can be several hours long, so I suppose
        it may be better than using a "feeling," that intuition is using as a foundation. But a more optimal interval length 
        may in fact be much shorter. I currently have no way of knowing this for certain. But hopefuly
        these two pieces that I was only able to hypothesize will have experimental results that will allow me to improve the 
        software, or be satisfied with what I have already implemented as far as those two pieces are concerned. The point is that
        intuition without logic is meaningless to me, and logic without proper experiment is still not good enough. The aim of this
        software is to be eventually be based entirely on solid theoretical work. Right now it still does better calculations, and
        leaves nothing to the intuition of the users of the software, but I'm still not satisfied.

        Having said that, here is the formula for difficulty which I assert to be correct on the basis of logic, and not proper
        experiment yet. It's a simple slope-intercept formula, and I'm calling it "Spacing Multiplier," because it's result is
        used to multiply the spacing of the lengths of intervals between study sessions of information that connections in the brain
        used for a piece of information need to be reactivated in order to be more strongly learned.
    */


    // Make sure the linked list is at the required node
    topics_list = cs_element_at(topics_list, globals.topic_id);

    // Since interval_time multiplies against difficulty, and difficulty is set only once
    // then a topic could be scheduled every day for a long time if too close to 1.0, and too 
    // far apart if above 2.5
    const double LOW_DIFFICULTY = 2.5;
    const double HIGH_DIFFICULTY = 1.3;
    double rise = LOW_DIFFICULTY - HIGH_DIFFICULTY;
    double total_problems = ((struct st_topic_model*)topics_list->page)->num_problems;
    double correct_problems = ((struct st_topic_model*)topics_list->page)->num_correct;
    double run = total_problems;
    double slope = rise / run;
    double difficulty = (slope * correct_problems) + HIGH_DIFFICULTY;           // Slope-Intercept formula y = mx + b
    ((struct st_topic_model*)topics_list->page)->top_difficulty = difficulty;   // Write difficulty to student record file Difficulty column
}
void interval_time()
{
    // Make sure the linked list is at the required node
    topics_list = cs_element_at(topics_list, globals.topic_id);

    // 1440 is the quantity in minutes of a day. I'm using minutes, instead of whole days, to be more precise, incase more precision is needed for future updates.
    const double SINGLE_DAY = 1440; 
    double difficulty = ((struct st_topic_model*)topics_list->page)->top_difficulty;
    int ith_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;
    double interval_remaining = ((struct st_topic_model*)topics_list->page)->interval_remaining;
    double interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;
    const int ONE = 1;

    //     Second repetition will occur the next day. 
    //	   Although, the research document does not precisely
    //	   state a time frame until the second repetition. The 
    //	   values of the two variables may need to be changed, 
    //	   if the spacing is too far apart. So far it appears to be ok, 
    //     but I need to do experimental validation when I can afford it to be sure.
    if (ith_repetition == ONE)
    {
        // The researech document says that s == r @ 1st repetition
        interval_remaining = SINGLE_DAY;
        interval_length = SINGLE_DAY;
    }
    else
        interval_length = interval_length * difficulty;
    interval_remaining = interval_length;
    ((struct st_topic_model*)topics_list->page)->interval_length = interval_length;         // Write intervalLength to student record Interval.
    ((struct st_topic_model*)topics_list->page)->interval_remaining = interval_remaining;   // Write remainingTime to student record file RTime column
}
void engram_stability()
{
    // Make sure the linked list is at the required node
    topics_list = cs_element_at(topics_list, globals.topic_id);

    // It is important to note that these values require the reading of the research paper named
    // "Two components of long-term memory", which is available with the source code, in order to
    // understand the values of some of the variables better. At the very least, you will know the source
    // of what determines the values in this function, which is the research article.
    
    // KNOWLEDGE_LINK is the natural logarithm of K, which itself is equal to 0.95 from the research. I just didn't want to name it 'K'
    const double KNOWLEDGE_LINK = -0.0512932943875506;
    const double NEGATIVE_ONE = -1;
    // remaining_time and interval_length represent the variables r and s, respectively, from the research document.
    double interval_remaining = ((struct st_topic_model*)topics_list->page)->interval_remaining;
    double interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;
    double engram_stability;
    engram_stability = (NEGATIVE_ONE * interval_length) / KNOWLEDGE_LINK;              // S = -s/ln(K), where K = 0.95, and the natural logarithm of K equals KNOWLEDGE_LINK.            
    ((struct st_topic_model*)topics_list->page)->engram_stability = engram_stability;  // Write Stability to student record file Stability column
}
void engram_retrievability()
{
    // Make sure the linked list is at the required node
    topics_list = cs_element_at(topics_list, globals.topic_id);

    // This function calculates engram retrievability in accordance with the included research paper
    // named "Two components of long-term memory"

    const double NEGATIVE_ONE = -1;
    double interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;
    double interval_remaining = ((struct st_topic_model*)topics_list->page)->interval_remaining;
    double engram_stability = ((struct st_topic_model*)topics_list->page)->engram_stability;
    double power = NEGATIVE_ONE * (interval_length - interval_remaining) / engram_stability;
    double retrievability = exp(power);
    ((struct st_topic_model*)topics_list->page)->engram_retrievability = retrievability;
}
void process_date()
{
    // This function calculates the date of the next repetition for a topic

    // I use the value of 1440 in case a future update requires more precision than 24 hours. 1440 is the number of minutes in a day.
    const double SINGLE_DAY = 1440;


    double interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;
    double days = (interval_length / SINGLE_DAY); // The truncation is fine, because anything less than a day, which is after the decimal, is still part of the day that is calculated for the day to study the information.
    
    // date format is mm/dd/yyyy
    char *today = globals.the_date;
    char *next_date = cs_add_days(today, days);
    
    topics_list = element_at(topics_list, globals.topic_id);
    ((struct st_topic_model*)topics_list->page)->next_date = next_date;

    if (((struct st_topic_model*)topics_list->page)->top_studied = false)
        ((struct st_topic_model*)topics_list->page)->top_studied = true;
}
void save_progress()
{
    int total_topics = topics_list->total_nodes;
    int index = 0;

    // Initialize output list
    struct st_node *output = malloc(sizeof(struct st_node));
    for(index = 1; index < total_topics; ++index)
    {
        output = cs_add(output);
    }

    // Loop through each topic and save progress
    for(index = 0; index < total_topics; ++index)
    {
        struct st_topic_model *current_topic = (struct st_topic_model*)cs_element_at(topics_list, index)->page;
        char temp[2048]; // Make sure the size is enough to hold all data.

        // Format the string (equivalent to your String.Format or string interpolation in C#)
        snprintf(temp, sizeof(temp), "%d,%d,%s,%d,%s,%s,%.2f,%.2f,%.2f,%d,%.2f,%.2f,%.2f,%.2f",
            current_topic->top_id,
            current_topic->course_id,
            current_topic->top_name,
            current_topic->top_studied,
            current_topic->next_date,
            current_topic->first_date,
            current_topic->num_problems,
            current_topic->num_correct,
            current_topic->top_difficulty,
            current_topic->top_repetition,
            current_topic->interval_remaining,
            current_topic->interval_length,
            current_topic->engram_stability,
            current_topic->engram_retrievability);

        struct st_string *temp_str = malloc(sizeof(struct st_string));
        temp_str->string = strdup(temp);

        struct st_node *current_node = cs_element_at(output, index);
        current_node->page = temp_str;
    }

    printf("\n\n\n\n\n\nSaving Work.\n");

    // Saving to file (use your own file-writing functions here)
    cs_write_all_lines(file_strings->txt_course_namefile, output, total_topics);
    cs_write_all_lines(file_strings->bak_course_namefile, output, total_topics);

    printf("\nWork Saved.\n");
    getchar();

    // Cleanup
    for(index = 0; index < total_topics; ++index)
    {
        struct st_node *current_node = cs_element_at(output, index);
        free(((struct st_string*)current_node->page)->string);
        free(current_node->page);
    }
    cs_clear_nodes(output);
}
void change_topic_questions()
{
    const double ZERO_DOUBLE = 0.0;
    const int TEN_INT = 10;
    
    char *num_total_string = NULL;
    double num_total_double = ZERO_DOUBLE;
    bool test = false;
    
    while (!test)
    {
        cs_console_clear();
        printf("\nEnter new number of TOTAL questions:\n");
        num_total_string = cs_read_line();
        
        if (cs_check_double(num_total_string) == 0)
        {
            num_total_double = atof(num_total_string);
            test = true;
        }
        else
        {
            cs_console_clear();
            printf("\n\n\nInvalid Input\n\nPress Enter to Continue");
            getchar();
            SelectionDialogs(TEN_INT);
        }
        
        // Free the allocated memory for num_total_string
        if (num_total_string != NULL)
        {
            free(num_total_string);
            num_total_string = NULL;
        }
    }
    
    // Update the topic's problem count
    struct st_topic_model *selected_topic = (struct st_topic_model*) cs_element_at(topics_list, globals.topic_id)->page;
    selected_topic->num_problems = num_total_double;
}
void study_incrementer()
{
    ++globals.study_tracker;
}
void study_decrementer()
{
    const int ZERO = 0;
    if (globals.study_tracker > ZERO)
        --globals.study_tracker;
}
void clear_lists()
{
    const int ZERO = 0;
    const int ONE = 1;
    int index = ZERO;
    int total_nodes = ZERO;
    if (globals.study_tracker > ONE)
    {
        // First free the pages of the 3 lists needed to be cleared here.
        // Then free the nodes of the linked lists.
    
    
        // 1
        // free the pages
        index = ZERO;
        total_nodes = topics_list->total_nodes;
        while (index < total_nodes)
        {
            topics_list = cs_element_at(topics_list, index);
            free((struct st_topic_model*)topics_list->page);
        }
        // free the nodes
        cs_clear_nodes(topics_list);


        //2
        // free the pages
        index = ZERO;
        total_nodes = topics->total_nodes;
        while (index < total_nodes)
        {
            topics = cs_element_at(topics, index);
            free((struct st_course_list_model*)topics->page);
        }
        // free the nodes
        cs_clear_nodes(topics);


        // 3
        // free the pages
        index = ZERO;
        total_nodes = to_study->total_nodes;
        while (index < total_nodes)
        {
            to_study = cs_element_at(to_study, index);
            free((struct st_to_study*)to_study->page);
        }
        // free the nodes
        cs_clear_nodes(to_study);
    }
}
void study_lines()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;
    const int SEVEN = 7;
    const int EIGHT = 8;
    const int NINE = 9;
    const int TEN = 10;
    const int ELEVEN = 11;
    const int TWELVE = 12;
    const int THIRTEEN = 13;
    
    int index = ZERO;
    int total_nodes = ZERO;

    // Initialization for 'lines' list
    struct st_node *lines = malloc(sizeof(struct st_node));
    lines->total_nodes = 0;
    lines = cs_node_initializer(lines);

    // Read all lines and build the 'lines' list
    lines = cs_ral_tolist(study_vars.file_path);
    study_vars.line_count = total_nodes = lines->total_nodes;

    // Build the Node Chain for topics_list
    index = ONE;
    while (index < total_nodes)
    {
        topics_list = cs_add(topics_list);
        ++index;
    }
    index = ZERO; // Reset index
    
    // Add Pages to Nodes for topics_list
    while (index < total_nodes)
    {
        // Initialization for 'entries' list
        struct st_node *entries = malloc(sizeof(struct st_node));
        entries->total_nodes = 0;
        entries = cs_node_initializer(entries);

        // Initialize other variables
        struct st_topic_model new_list;
        const char TOKEN[] = ",";
        const char TRUE_CHAR[] = "TRUE";

        // Get the specific line from lines
        lines = cs_element_at(lines, index);
        
        // Build the Node Chain and Add Pages for 'entries'
        entries = cs_list_split(((struct st_string*)lines->page)->string, TOKEN);

        
        // Transfer the data from the character strings into their necessary
        // data types.
        entries = cs_element_at(entries, ZERO);
        new_list.top_id = atoi(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, ONE);
        new_list.course_id = atoi(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, TWO);
        new_list.top_name = ((struct st_string*)entries->page)->string;
        entries = cs_element_at(entries, THREE);

        // I only transfer this character to improve readability of the code.
        study_vars.top_stud_string = ((struct st_string*)entries->page)->string;
        if (strcmp(study_vars.top_stud_string, TRUE_CHAR) == ZERO)
            new_list.top_studied = true;
        else
            new_list.top_studied = false;
        
        entries = cs_element_at(entries, FOUR);
        new_list.next_date = ((struct st_string*)entries->page)->string;
        entries = cs_element_at(entries, FIVE);
        new_list.first_date = ((struct st_string*)entries->page)->string;
        entries = cs_element_at(entries, SIX);
        new_list.num_problems = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, SEVEN);
        new_list.num_correct = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, EIGHT);
        new_list.top_difficulty = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, NINE);
        new_list.top_repetition = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, TEN);
        new_list.interval_remaining = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, ELEVEN);
        new_list.interval_length = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, TWELVE);
        new_list.engram_stability = atof(((struct st_string*)entries->page)->string);
        entries = cs_element_at(entries, THIRTEEN);
        new_list.engram_retrievability = atof(((struct st_string*)entries->page)->string);


         // Go to the necessary node of the topics_list
        topics_list = cs_element_at(topics_list, index);
        topics_list->page = &new_list;

        // Free Pages from entries
        for (int j = 0; j < entries->total_nodes; ++j)
        {
            entries = cs_element_at(entries, j);
            free((struct st_string*)entries->page); // Assuming page data is dynamically allocated
        }
        // Destroy the Node Chain for entries
        cs_clear_nodes(entries);
        free(entries);

        ++index;
    }

    // Reset to the first node if needed for lines and topics_list
    index = ZERO;
    lines = cs_element_at(lines, index);
    topics_list = cs_element_at(topics_list, index);
}
void study_dates()
{
    // Constants
    const int ZERO = 0;
    const int TODAY = 0;
    
    // Initialize variables
    study_vars.index = ZERO;
    int total_nodes = topics_list->total_nodes;
    
    // Clear late topics counter
    globals.late_left = ZERO;

    // Retry studied TopicIDs (late topics)
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            study_vars.date_as_string = ((struct st_topic_model*)topics_list->page)->next_date;
            study_vars.date_compare = cs_date_compare(study_vars.date_as_string, study_vars.today);
            
            if (study_vars.date_compare < TODAY)
            {
                to_study = cs_add(to_study);
                ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;
                ++globals.late_left;
            }
        }
        ++study_vars.index;
    }

    // Initialize variables for on-time topics
    study_vars.index = ZERO;
    globals.current_left = ZERO;

    // Study TopicIDs scheduled for today
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            study_vars.date_as_string = ((struct st_topic_model*)topics_list->page)->next_date;
            study_vars.date_compare = cs_date_compare(study_vars.date_as_string, study_vars.today);
            
            if (study_vars.date_compare == TODAY)
            {
                to_study = cs_add(to_study);
                ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;
                ++globals.current_left;
            }
        }
        ++study_vars.index;
    }

    // Initialize variables for new topics
    study_vars.index = ZERO;
    globals.new_left = ZERO;

    // New Topic IDs
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == false)
        {
            to_study = cs_add(to_study);
            ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;
            ++globals.new_left;
        }
        ++study_vars.index;
    }
}
void study_false()
{
    // Constants
    const int ZERO_INT = 0;
    const double ZERO_DOUBLE = 0.0;
    const int ONE = 1;
    const int TEN = 10;
    const int ELLEVEN = 11;
    const int TWELVE = 12;

    bool test = false;
    study_vars.studied = true;

    while (test == false) 
    {
        selection_dialogs(ELLEVEN);
        study_vars.response = cs_read_line();

        if (strcmp(study_vars.response, "m") == ZERO_INT || strcmp(study_vars.response, "u") == ZERO_INT) 
        {
            while (strcmp(study_vars.response, "u") == ZERO_INT)
            {
                change_topic_questions();
                printf("\n\n\nEnter the quantity you answered correctly:\n");
                study_vars.response = cs_read_line();
                
                if (cs_check_double(study_vars.response) == ZERO_INT)
                {
                    study_vars.num_correct_double = atof(study_vars.response);
                }
                else
                {
                    cs_console_clear();
                    printf("\n\nInvalid Input\n\nPress Enter to Continue");
                    study_vars.response = "u";
                    getchar();
                    selection_dialogs(TEN);
                }
            }
            
            if (strcmp(study_vars.response, "m") == ZERO_INT)
            {
                cs_console_clear();
                globals.made_select = false;
                globals.new_left = ZERO_INT;
                globals.current_left = ZERO_INT;
                globals.late_left = ZERO_INT;
                study_vars.studied = false;
                return;
            }
        }
        
        // The corresponding part from C#
        if (cs_check_double(study_vars.response) == ZERO_INT)
        {
            study_vars.num_correct_string = study_vars.response;
            study_vars.num_correct_double = atof(study_vars.num_correct_string);
            test = true;
        }
        else
        {
            cs_console_clear();
            printf("\n\nInvalid Input\n\nPress Enter to try again");
            getchar();
            selection_dialogs(TEN);
            test = false;
        }

        if (test == true)
        {
            struct st_topic_model *current_topic = cs_element_at(topics_list, globals.topic_id)->page;
            
            while (study_vars.num_correct_double > current_topic->num_problems || study_vars.num_correct_double < ZERO_DOUBLE)
            {
                selection_dialogs(TWELVE);
                study_vars.response = cs_read_line();
                
                if (strcmp(study_vars.response, "u") == ZERO_INT)
                {
                    change_topic_questions();
                    cs_console_clear();
                    printf("\nRe-enter number of problems or questions you responded to correctly\n");
                }
                if (strcmp(study_vars.response, "m") == ZERO_INT)
                {
                    cs_console_clear();
                    globals.made_select = false;
                    globals.new_left = ZERO_INT;
                    globals.current_left = ZERO_INT;
                    globals.late_left = ZERO_INT;
                    study_vars.studied = false;
                    return;
                }
                
                if (cs_check_double(study_vars.response) == ZERO_INT)
                {
                    study_vars.num_correct_double = atof(study_vars.response);
                }
                else
                {
                    cs_console_clear();
                    printf("\n\nInvalid Input\n\nPress Enter to try again");
                    getchar();
                }
            }
            
            current_topic->num_correct = study_vars.num_correct_double;
            current_topic->first_date = study_vars.today_date_string;

            if (globals.new_left >= ONE)
                --globals.new_left;
            if (predict_vars.until_new > ZERO_INT)
                --predict_vars.until_new;
            if (predict_vars.until_new == ZERO_INT)
                predict_vars.lock_goals = false;

            cs_console_clear();
        }
    }
}
void study_true()
{
    const int ZERO = 0;
    const int TODAY = ZERO;

    printf("\n\n\n\nOption: ");

    study_vars.studied = true;
    study_vars.response = cs_read_line();

    if (strcmp(study_vars.response, "m") == ZERO)
    {
        globals.made_select = false;
        cs_console_clear();
        globals.new_left = ZERO;
        globals.current_left = ZERO;
        globals.late_left = ZERO;
        study_vars.studied = false;
        return;
    }

    struct st_topic_model *current_topic = cs_element_at(topics_list, globals.topic_id)->page;

    study_vars.date_as_string = current_topic->next_date;
    study_vars.topic_date = study_vars.date_as_string;

    // Assuming cs_date_compare mimics DateTime.Compare in functionality
    study_vars.date_compare = cs_date_compare(study_vars.topic_date, study_vars.today);

    if (study_vars.date_compare < TODAY)
        --globals.late_left;
    else if (study_vars.date_compare == TODAY)
        --globals.current_left;
    
    if (predict_vars.until_new > TODAY)
        --predict_vars.until_new;
    if (predict_vars.until_new == TODAY)
        predict_vars.lock_goals = false;
    
    cs_console_clear();
}
void study_not_done()
{
    int ZERO_INT = 0;
    const double ZERO_DOUBLE = 0;
    const int TEN = 10;


    // From StudyCourse()
    study_vars.studied = false;

    if (globals.topic_index < study_vars.to_study_count)
    {
        selection_dialogs(TEN);

        topics_list = cs_element_at(topics_list, globals.topic_id);
        
        if (((struct st_topic_model*)topics_list->page)->top_studied == false)
        {
            study_false();
            
            if (strcmp(study_vars.response, "m") == ZERO_INT)
                return;
        }
        else
        {
            study_true();
        }

        if (study_vars.studied == true)
        {
            study_vars.num_correct_double = ZERO_DOUBLE;
            calculate_learning();
            save_progress();

            ++globals.topic_index;
            
            if (globals.topic_index < study_vars.to_study_count)
            {
                to_study = cs_element_at(to_study, globals.topic_index);
                globals.topic_id = ((struct st_to_study*)to_study->page)->topic_id;
            }
        }
    }
    else
    {
        globals.problems_done = true;
    }
}
void study_not_zero()
{
    const int ZERO = 0;
    const double ZERO_DOUBLE = 0;
    //From StudyCourse()
    to_study = cs_element_at(to_study, ZERO);
    globals.topic_id = ((struct st_to_study*)to_study->page)->topic_id;
    globals.topic_index = ZERO;
    study_vars.to_study_count = to_study->total_nodes;

    study_vars.today_date_string = study_vars.today;
    if (study_vars.to_study_count > ZERO)
        globals.problems_done = false;
    else
        globals.problems_done = true;
    study_vars.response = ZERO_CHAR; //Just added this to give option to go back to Ready Menu
    study_vars.num_correct_double = ZERO_DOUBLE;
}
void study_hud()
{
    struct st_topic_model* current_topic;
    struct st_topic_model* final_topic;

    cs_console_clear();

    topics_list = cs_element_at(topics_list, globals.topic_id);
    current_topic = (struct st_topic_model*)topics_list->page;
    
    if (current_topic->top_studied)
        study_vars.top_stud_bool = TRUE_CHAR;
    else
        study_vars.top_stud_bool = FALSE_CHAR;

    printf("Course Name: %s\n", globals.course_name);
    printf("Today is: %s\n", globals.the_date);

    if (predict_vars.enough_studied)
    {
        topics_list = cs_element_at(topics_list, predict_vars.final_topic);
        final_topic = (struct st_topic_model*)topics_list->page;

        if (!predict_vars.end_reached && !predict_vars.unlock_new_date)
        {
            printf("Current Repetition Goal: %d section(s)\n", predict_vars.until_new);
            printf("CURRENT COMPLETION GOAL: Last Section: %s | Completion Date: %s\n", final_topic->top_name, predict_vars.prediction_date);
            printf("Study more than %d section(s) to unlock next date calculation.\n", predict_vars.until_new);
        }
        else if (!predict_vars.end_reached && predict_vars.unlock_new_date)
        {
            printf("Study %d section(s) for this NEW COMPLETION GOAL:\n", predict_vars.until_new);
            printf("Section Number %s on Date of %s\n", final_topic->top_name, predict_vars.prediction_date);
            predict_vars.unlock_new_date = false;
        }
        else if (predict_vars.end_reached)
        {
            printf("Maintenance study session\n");
        }
    }

    printf("Current Section: %s\n", current_topic->top_name);
    printf("Previously Studied: %s\n", study_vars.top_stud_bool);
    printf("Number of LATE practice to review: %d\n", globals.late_left);
    printf("Number of ON-TIME practice topics to review: %d\n", globals.current_left);
    printf("Number of NEW topics left: %d\n", globals.new_left);
    printf("\n\nNumber of questions/problems: %d\n", current_topic->num_problems);
    printf("\nOPTIONS:\n");
    printf("(m) = Main Menu.\n");

    if (globals.late_left > ZERO || globals.current_left > ZERO)
        printf("(enter key) = Process topic, and go to next\n");
    else
        printf("(u) = Update number of questions.\n");
}

// 23 function complete
/***********************************PREDICTION START*********************************************/
void predict_main()
{
    const int ZERO = 0;
    bool enough_studied = false;
    int total_count = ZERO;

    avg_diff();
    
    // Point Ymax is (x1 , y1)
    // For point (x1 , y1), where y1 is maximum first studies performed
    // x1 is number of repeat studies performed at max first studies
    collect_first_studies();      // Get first study dates of studied topics
    total_count = studied_simlist->total_nodes;
    if (total_count > ZERO)
    {
        y_max_firsts();            // Get y1: max Y First Studies for point Ymax
        if (predict_vars.only_one == true)
        {
            predict_vars.enough_studied = enough_studied;
            predict_vars.only_one = false;

            //Clear Lists here too
            prediction_lists_clear();
            return;
        }
        enough_studied = true;
        prepare_past_studies();
        simulate_past_studies();
        x_max_repeats();
        collect_non_studied();
        predict_vars.process_prediction = true;
        generate_projected_studies();
    }
    predict_vars.enough_studied = enough_studied;
}
void avg_diff()
{
    const double ZERO_DOUBLE = 0;
    const int ZERO_INT = 0;
    int total_topics = ZERO_INT;
    // Apply average of difficulty to simulation of 
    // calculating non-studied topics learning dates.
    double num_difficults = ZERO_DOUBLE;
    double difficults_added = ZERO_DOUBLE;

    predict_vars.avg_difficulty = ZERO_DOUBLE;

    total_topics = topics_list->total_nodes;
    int index = ZERO_INT;
    int count = ZERO_INT;

    while(index < total_topics)
    {
        topics_list = cs_element_at(topics_list, index);

        if(((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            ((struct st_topic_model*)topics_list->page)->top_difficulty;
            ++count;
        }
        ++index;
    }

    num_difficults = atof(count);
    predict_vars.avg_difficulty = difficults_added / num_difficults;
}
void collect_first_studies()
{
    const int ZERO = 0;
    int topic_number = ZERO;
    int tracker = ZERO;
    int index = ZERO;
    int total_topics = topics_list->total_nodes;

    total_topics = topics_list->total_nodes;
    while (index < total_topics)
    {
        tracker = add_firsts_collect(topic_number, index);
        topic_number = tracker;
        ++index;
        if (index < total_topics)
            studied_simlist = cs_add(studied_simlist);
    }
}
int add_firsts_collect(int topic_number, int index)
{
    const int ZERO = 0;
    const int ONE = 1;
    int total_nodes = ZERO;
    int last_node = ZERO;




    struct st_sim_model new_sims; // if I have a problem, then allocate this memory to it: = malloc(sizeof(struct st_sim_model));
    topics_list = cs_element_at(topics_list, index);
    if (((struct st_topic_model*)topics_list->page)->top_studied == true)
    {
        // newSims.First_Date = TopicsList.ElementAt(index).First_Date;
        // newSims.Real_Repetition = TopicsList.ElementAt(index).Top_Repetition;
        // newSims.Sim_Repetition = Constants.ONE_INT;
        // newSims.Top_Difficulty = TopicsList.ElementAt(index).Top_Difficulty;
        // newSims.Interval_Length = TopicsList.ElementAt(index).Interval_Length;
        // newSims.Top_Number = topic_number;
        // newSims.Next_Date = TopicsList.ElementAt(index).Next_Date;

        new_sims.first_date = ((struct st_topic_model*)topics_list->page)->first_date;
        new_sims.real_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;
        new_sims.sim_repetition = ONE;
        new_sims.top_difficulty = ((struct st_topic_model*)topics_list->page)->top_difficulty;
        new_sims.interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;
        new_sims.top_number = topic_number;
        new_sims.next_date = ((struct st_topic_model*)topics_list->page)->next_date;
        
        
        // Give a page to the node of studied_simlist        
        total_nodes = studied_simlist->total_nodes;
        last_node = total_nodes - ONE;
        studied_simlist = cs_element_at(studied_simlist, last_node);
        studied_simlist->page = &new_sims;

        ++topic_number;
    }
    return topic_number;
}
void y_max_firsts()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    int firsts_count = ZERO;
    int highest_index = ZERO;
    int total_nodes = ZERO;
    predict_vars.loop_index = ZERO;
    predict_vars.find_y_high_index = ZERO;
    predict_vars.first_check = true;


    total_nodes = studied_simlist->total_nodes;
    while (predict_vars.loop_index < total_nodes)
    {
        find_high_y();
        ++predict_vars.loop_index;
    }

    predict_vars.loop_index = ZERO;
    predict_vars.find_y_high_index = ZERO;
    firsts_count = fstudy_counts->total_nodes;
    if (firsts_count > TWO)
    {
        y_max_sort_firsts();
        predict_vars.only_one = false;
    }
    else
    {
        predict_vars.only_one = true;
        return;
    }

    highest_index = firsts_count - ONE;
    fstudy_counts = cs_element_at(fstudy_counts, highest_index);
    predict_vars.y_high_y_count = ((struct st_fstudy_counts*)fstudy_counts->page)->counts;
}
void y_max_sort_firsts()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    int count = ONE;
    int j, i, keyOne;
    char *keyTwo;
    char *temp_date;
    int fcount_total, fdate_total, temp_count;

    fcount_total = fstudy_counts->total_nodes;
    fdate_total = fstudy_dates->total_nodes;

    count = temp_count = ZERO;
    while (count < TWO)
    {

        for (j = TWO; j < fcount_total; ++j)
        {
            fstudy_counts = cs_element_at(fstudy_counts, j);
            fstudy_dates = cs_element_at(fstudy_dates, j);

            keyOne = ((struct st_fstudy_counts*)fstudy_counts->page)->counts;
            keyTwo = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;

            // Insert fStudyCounts[j] into sorted sequence fStudyCounts[1...j-1]
            // Insert fStudyDates[j] into sorted sequence fStudyDates[1...j-1]
            i = j - ONE;
            fstudy_counts = cs_element_at(fstudy_counts, i);
            while (i > ZERO && ((struct st_fstudy_counts*)fstudy_counts->page)->counts > keyOne)
            {
                temp_count = ((struct st_fstudy_counts*)fstudy_counts->page)->counts;
                fstudy_counts = cs_element_at(fstudy_counts, i + ONE);
                ((struct st_fstudy_counts*)fstudy_counts->page)->counts = temp_count;

                fstudy_dates = cs_element_at(fstudy_dates, i);
                temp_date = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;
                fstudy_dates = cs_element_at(fstudy_dates, i + ONE);
                ((struct st_fstudy_dates*)fstudy_dates->page)->dates = temp_date;
                i = i - ONE;
            }

            fstudy_counts = cs_element_at(fstudy_counts, i + ONE);
            fstudy_dates = cs_element_at(fstudy_dates, i + ONE);
            ((struct st_fstudy_counts*)fstudy_counts->page)->counts = keyOne;
            ((struct st_fstudy_dates*)fstudy_dates->page)->dates = keyTwo;
        }

        /* 
        this is here to get the first element sorted into 
        the rest of the array on the second run of the loop
        */
        if (count == ZERO)
        {
            //key = A[ZERO];
            fstudy_counts = cs_element_at(fstudy_counts, ZERO);
            fstudy_dates = cs_element_at(fstudy_dates, ZERO);
            keyOne = ((struct st_fstudy_counts*)fstudy_counts->page)->counts;
            keyTwo = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;
            //A[ZERO] = A[ONE];

            fstudy_counts = cs_element_at(fstudy_counts, ONE);
            fstudy_dates = cs_element_at(fstudy_dates, ONE);
            temp_count = ((struct st_fstudy_counts*)fstudy_counts->page)->counts;
            temp_date = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;
            
            fstudy_counts = cs_element_at(fstudy_counts, ZERO);
            fstudy_dates = cs_element_at(fstudy_dates, ZERO);
            ((struct st_fstudy_counts*)fstudy_counts->page)->counts = temp_count;
            ((struct st_fstudy_dates*)fstudy_dates->page)->dates = temp_date;
            //A[ONE] = key;

            fstudy_counts = cs_element_at(fstudy_counts, ZERO);
            fstudy_dates = cs_element_at(fstudy_dates, ZERO);
            ((struct st_fstudy_counts*)fstudy_counts->page)->counts = keyOne;
            ((struct st_fstudy_dates*)fstudy_dates->page)->dates = keyTwo;
        }
        ++count;
    }
}
void find_high_y()
{
    int date_compare;
    int total_nodes = 0;
    int last_node = 0;
    date_time *temp_date_one;
    date_time *temp_date_two;

    studied_simlist = cs_element_at(studied_simlist, predict_vars.loop_index);
    temp_date_two = ((struct st_sim_model*)studied_simlist->page)->first_date;

    if (predict_vars.first_check == true)
    {
        add_fstudy_node(temp_date_two, 1);
        predict_vars.first_check = false;
    }
    else
    {
        fstudy_dates = cs_element_at(fstudy_dates, predict_vars.find_y_high_index);
        temp_date_one = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;

        date_compare = cs_date_compare(temp_date_one, temp_date_two);

        if (date_compare == 0)
        {
            increment_fstudy_count(predict_vars.find_y_high_index);
        }
        else
        {
            ++predict_vars.find_y_high_index;
            add_fstudy_node(temp_date_two, 1);
        }
    }
}

void add_fstudy_node(date_time *new_date, int new_count)
{
    // For find_high_y

    // Add new_date to fstudy_dates
    total_nodes = fstudy_dates->total_nodes;
    last_node = total_nodes - 1;
    fstudy_dates = cs_element_at(fstudy_dates, last_node);
    fstudy_dates = cs_add(fstudy_dates);
    ((struct st_fstudy_dates*)fstudy_dates->page)->dates = new_date;

    // Add new_count to fstudy_counts
    total_nodes = fstudy_counts->total_nodes;
    last_node = total_nodes - 1;
    fstudy_counts = cs_element_at(fstudy_counts, last_node);
    fstudy_counts = cs_add(fstudy_counts);
    ((struct st_fstudy_counts*)fstudy_counts->page)->counts = new_count;
}

void increment_fstudy_count(int index)
{
    // For find_high_y

    fstudy_counts = cs_element_at(fstudy_counts, index);
    ++((struct st_fstudy_counts*)fstudy_counts->page)->counts;
}

void prepare_past_studies()
{
    const int ZERO = 0;
    const int ONE = 1;
    int index = ZERO;
    int repetition = ONE;

    

    while (index < studied_simlist->total_nodes) //Replace Foreach foreach
    {
        // repetition = studiedSimList.ElementAt(index).Sim_Repetition;
        studied_simlist = cs_element_at(studied_simlist, index);
        repetition = ((struct st_sim_model*)studied_simlist->page)->sim_repetition;

        initialize_one_past_study(index, repetition);
        ++index;
    }
}
void initialize_one_past_study(int index, int repetition)
{
    const int ZERO = 0;
    int next_rep = ZERO;
    int last_rep = ZERO;

    studied_simlist = cs_element_at(studied_simlist, index);
    last_rep = ((struct st_sim_model*)studied_simlist->page)->real_repetition;
    
    while (repetition <= last_rep)
    {
        next_rep = past_study_initialization(index, repetition);
        repetition = next_rep;
    }
}
int past_study_initialization(int index, int repetition)
{
    const int ONE = 1;
    const int ZERO = 0;
    // struct st_node *output = malloc(sizeof(struct st_node));
    struct st_sim_model *studied_sims =  malloc(sizeof(struct st_sim_model));

    studied_simlist = cs_element_at(studied_simlist, index);

    studied_sims->first_date = ((struct st_sim_model*)studied_simlist->page)->first_date;
    studied_sims->real_repetition = ((struct st_sim_model*)studied_simlist->page)->real_repetition;
    studied_sims->sim_repetition = repetition;
    studied_sims->top_difficulty = ((struct st_sim_model*)studied_simlist->page)->top_difficulty;
    studied_sims->interval_length = ZERO; // Be sure that this is updated for each rep!
    studied_sims->top_number = ((struct st_sim_model*)studied_simlist->page)->top_number;
    
    if (repetition == ONE)
        studied_sims->simulated_date = ((struct st_sim_model*)studied_simlist->page)->first_date;

    //genSimsStudied.Add(studied_sims);
    gensims_studied = cs_add(gensims_studied);
    gensims_studied->page = &studied_sims;

    ++repetition;
    return repetition;
}
void simulate_past_studies()
{
    const int ZERO = 0;
    predict_vars.gen_studied_index = ZERO;

    while (predict_vars.gen_studied_index < gensims_studied->total_nodes)
    {
        predict_vars.process_gen_sims_studied = true;
        sim_calculate_learning();
        predict_vars.process_gen_sims_studied = false;
        ++predict_vars.gen_studied_index;
    }
    predict_vars.gen_studied_index = ZERO;
}
void x_max_repeats()
{
    const int ZERO = 0;
    const int ONE = 1;
    //xMaxList

    predict_vars.loop_index = ZERO;
    while (predict_vars.loop_index < gensims_studied->total_nodes)
    {
        x_max_to_sort();
        ++predict_vars.loop_index;
    }
    x_max_repeat_sort();

    predict_vars.loop_index = ZERO;
    while (predict_vars.loop_index < xmax_sortlist->total_nodes)
    {
        add_to_xmax();
        ++predict_vars.loop_index;
    }
    predict_vars.loop_index = ZERO;


    // xmax_sortlist.Clear();
    int index = ZERO;
    int total_nodes = xmax_sortlist->total_nodes;
    while(index < total_nodes)    
    {
        xmax_sortlist = cs_element_at(xmax_sortlist, index);
        free((struct st_sim_model*)xmax_sortlist->page);
        ++index;
    }
    cs_clear_nodes(xmax_sortlist);


    //Get X
    // int32 something = DateTime.Compare(t1 , t2);
    // if something < zero, then t1 is earlier than t2
    // if something == zero, then same day
    // if something > zero, then t1 is later than t2

    predict_vars.x_rep_index = ZERO;
    predict_vars.first_check = true;
    predict_vars.loop_index = ZERO;
    while (predict_vars.loop_index < to_xmax->total_nodes)
    {
        x_max_count_reps();
        ++predict_vars.loop_index;
    }
    predict_vars.x_rep_index = ZERO;

    bool repsort_correct, repsort_check;
    predict_vars.loop_index = ZERO;
    repsort_correct = repsort_check = true;
    while (repsort_correct == true)
    {
        repsort_check = sort_xrep_counts(repsort_correct);
        repsort_correct = repsort_check;
        ++predict_vars.loop_index;
    }
    predict_vars.loop_index = ZERO;
    int highest_element = xrep_datecounts->total_nodes - ONE;
    xrep_datecounts = cs_element_at(xrep_datecounts, highest_element);
    predict_vars.x_high_x_count = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;
}
bool sort_xrep_counts(bool repsort_correct)
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;

    int list_key = ZERO;

    for (predict_vars.j = TWO; predict_vars.j < xrep_datecounts->total_nodes; predict_vars.j++)
    {
        xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.j);
        list_key = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;

        // Insert xRepDateCounts[j] into sorted sequence xRepDateCounts[1...j-1]
        predict_vars.i = predict_vars.j - ONE;
        xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.i);
        //list_key = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;

        while (predict_vars.i > ZERO && ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts > list_key)
        {
            int temp_one = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;
            
            xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.i + ONE);
            ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = temp_one;
            
            predict_vars.i = predict_vars.i - ONE;
            xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.i);
        }
        xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.i + ONE);
        ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = list_key;
    }

    /* 
    this is here to get the first element sorted into 
    the rest of the array on the second run of the loop
    */

    xrep_datecounts = cs_element_at(xrep_datecounts, ONE);
    int temp = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;

    xrep_datecounts = cs_element_at(xrep_datecounts, ZERO);
    if (((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts > temp)
    {
        //key = A[ZERO];
        list_key = ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;
        //A[ZERO] = A[ONE];
        ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = temp;
        //A[ONE] = key;

        xrep_datecounts = cs_element_at(xrep_datecounts, ONE);
        ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = list_key;
    }
    else
    {
        repsort_correct = false;
    }

    return repsort_correct;
}
void x_max_to_sort()
{
    // SimModel sim = new SimModel();
    struct st_sim_model sim;

    gensims_studied = cs_element_at(gensims_studied, predict_vars.loop_index);
    sim.first_date = ((struct st_sim_model*)gensims_studied->page)->first_date;
    sim.real_repetition = ((struct st_sim_model*)gensims_studied->page)->real_repetition;
    sim.top_difficulty = ((struct st_sim_model*)gensims_studied->page)->top_difficulty;
    sim.interval_length = ((struct st_sim_model*)gensims_studied->page)->interval_length;
    sim.top_number = ((struct st_sim_model*)gensims_studied->page)->top_number;
    sim.next_date = ((struct st_sim_model*)gensims_studied->page)->next_date;
    sim.simulated_date = ((struct st_sim_model*)gensims_studied->page)->simulated_date;
    sim.sim_repetition = ((struct st_sim_model*)gensims_studied->page)->sim_repetition;

    xmax_sortlist = cs_add(xmax_sortlist);
    xmax_sortlist->page = &sim;
}
void add_to_xmax()
{
    // SimModel sim = new SimModel();
    struct st_sim_model sim;

    xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.loop_index);

    sim.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
    sim.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
    sim.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
    sim.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;
    sim.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
    sim.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
    sim.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
    sim.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;


    to_xmax = cs_add(to_xmax);
    to_xmax->page = &sim;
}
void x_max_count_reps()
{
    const int ZERO = 0;
    const int ONE = 1;    
    int firstRep = ONE;

    to_xmax = cs_element_at(to_xmax, predict_vars.loop_index);

    if (predict_vars.first_check == true)
    {
        if (firstRep != ((struct st_sim_model*)to_xmax->page)->sim_repetition)
        {
            // xrep_datecounts.Add(ZERO);
            xrep_datecounts = cs_add(xrep_datecounts);
            ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = ZERO;


            xrep_temp_dates = cs_add(xrep_temp_dates);
            to_xmax = cs_element_at(to_xmax, predict_vars.loop_index);
            ((struct st_xrep_temp_dates*)xrep_temp_dates->page)->xrep_tempdates = ((struct st_sim_model*)to_xmax->page)->simulated_date;
            
            predict_vars.first_check = false;
        }
    }
    if (predict_vars.first_check == false) // Must not be an else for logic to work
    {
        if (firstRep != ((struct st_sim_model*)to_xmax->page)->sim_repetition)
        {
            xrep_temp_dates = cs_element_at(xrep_temp_dates, predict_vars.x_rep_index);
            if (((struct st_xrep_temp_dates*)xrep_temp_dates->page)->xrep_tempdates == ((struct st_sim_model*)to_xmax->page)->simulated_date)
            {
                xrep_datecounts = cs_element_at(xrep_datecounts, predict_vars.x_rep_index);
                ++((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts;
            }
            else
            {
                ++predict_vars.x_rep_index;

                xrep_temp_dates = cs_add(xrep_temp_dates);
                to_xmax = cs_element_at(to_xmax, predict_vars.loop_index);
                ((struct st_xrep_temp_dates*)xrep_temp_dates->page)->xrep_tempdates = ((struct st_sim_model*)to_xmax->page)->simulated_date;
                
                xrep_datecounts = cs_add(xrep_datecounts);
                ((struct st_xrep_datecounts*)xrep_datecounts->page)->xrep_datecounts = ONE;
            }
        }
    }

}
void x_max_repeat_sort()
{
    const int ZERO = 0;

    predict_vars.j = ZERO;
    predict_vars.i = ZERO;
    predict_vars.date_check = ZERO;

    bool xsort_correct, xsort_check;
    xsort_check = xsort_correct = true;
    while (xsort_check == true)
    {
        xsort_check = x_insert_sort(xsort_correct);
        xsort_correct = xsort_check;
    }

    predict_vars.j = ZERO;
    predict_vars.i = ZERO;
    predict_vars.date_check = ZERO;
}
/*
    stopped updating a lot of variable names after here to speed things up.
    change them one functions are converted.
*/

bool x_insert_sort(bool xsort_correct)
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    struct st_sim_model list_key, xmax_temp;

    for (predict_vars.j = TWO; predict_vars.j < xmax_sortlist->total_nodes; predict_vars.j++)
    {
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.j);
        copy_model(&list_key, (struct st_sim_model*)xmax_sortlist->page);

        predict_vars.i = predict_vars.j - ONE;
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
        predict_vars.date_check = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, list_key.simulated_date);

        while (predict_vars.i > ZERO && predict_vars.date_check > ZERO)
        {
            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
            copy_model(&xmax_temp, (struct st_sim_model*)xmax_sortlist->page);

            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i + ONE);
            copy_model((struct st_sim_model*)xmax_sortlist->page, &xmax_temp);

            predict_vars.i = predict_vars.i - ONE;
            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
            predict_vars.date_check = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, list_key.simulated_date);
        }
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i + ONE);
        copy_model((struct st_sim_model*)xmax_sortlist->page, &list_key);
    }

    // Extra logic to handle the first element
    xmax_sortlist = cs_element_at(xmax_sortlist, ONE);
    copy_model(&xmax_temp, (struct st_sim_model*)xmax_sortlist->page);
    xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);

    int toFixSort = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, xmax_temp.simulated_date);

    if (toFixSort > ZERO)
    {
        xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);
        copy_model(&list_key, (struct st_sim_model*)xmax_sortlist->page);
        xmax_sortlist = cs_element_at(xmax_sortlist, ONE);
        copy_model((struct st_sim_model*)xmax_sortlist->page, &xmax_temp);
        xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);
        copy_model((struct st_sim_model*)xmax_sortlist->page, &list_key);
    }
    else
    {
        xsort_correct = false;
    }
    return xsort_correct;
}
bool copy_model(struct st_sim_model *dest, struct st_sim_model *src)
{
    // For x_insert_sort
    dest->top_number = src->top_number;
    dest->first_date = src->first_date;
    dest->simulated_date = src->simulated_date;
    dest->next_date = src->next_date;
    dest->real_repetition = src->real_repetition;
    dest->sim_repetition = src->sim_repetition;
    dest->top_difficulty = src->top_difficulty;
    dest->interval_length = src->interval_length;
    return true;
}

void collect_non_studied()
{
    const int ZERO = 0;
    const int ONE = 1;
    int index = studied_simlist->total_nodes - ONE;
    studied_simlist = cs_element_at(studied_simlist, index);
    int topicNumber = ((struct st_sim_model*)studied_simlist->page)->top_number + ONE;
    int tracker = ZERO;

    int loopIndex = ZERO;
    // ((struct st_topic_model*)topics_list->page)->top_repetition
    while (loopIndex < topics_list->total_nodes)
    {
        tracker = NonStudyGetter(topicNumber, loopIndex);
        topicNumber = tracker;
        ++loopIndex;
    }
    loopIndex = ZERO;
}
int non_study_getter(int topicNumber, int loopIndex)
{
    const int ZERO = 0;
    // SimModel newSims = new SimModel();
    struct st_sim_model newSims;

    topics_list = cs_element_at(topics_list, loopIndex);
    if(((struct st_topic_model*)topics_list->page)->top_studied == false)
    {
        newSims.first_date = ((struct st_topic_model*)topics_list->page)->first_date;
        newSims.real_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;
        newSims.sim_repetition = ZERO;
        newSims.top_difficulty = predict_vars.avg_difficulty;
        newSims.interval_length = ZERO;
        newSims.top_number = topicNumber;

        projected_simlist = cs_add(projected_simlist);
        projected_simlist = &newSims;
        ++topicNumber;
    }
    return topicNumber;
}
void generate_projected_studies()
{
    const int ZERO = 0;
    const int ONE = 1;

    date_time *previousDate, *simDate;
    int totalNewTopics, count;
    bool skipDay = false;
    predict_vars.sim_date_use = globals.the_date;
    totalNewTopics = projected_simlist->total_nodes; //This reduces in value as new topics are transfered
    count = ZERO; //This stays ZERO

    if (predict_vars.until_new == ZERO)
        predict_vars.lock_prediction = false;

    while (count < totalNewTopics)
    {
        printf("\nTEST");
        previousDate = predict_vars.sim_date_use;
        simDate = cs_add_days(previousDate, ONE);
        skipDay = skip_checker(simDate);
        if (skipDay == false)
            predict_studies(); // I think if I add another if statement here to make sure there is not a day off the day after the new study.
        predict_vars.sim_date_use = simDate;
        totalNewTopics = projected_simlist->total_nodes;
    }

    if (predict_vars.lock_prediction == false)
    {
        goal_setter();
        predict_vars.lock_prediction = true;
    }
    prediction_lists_clear();
}
void prediction_lists_clear()
{
    const int ZERO = 0;
    int index = ZERO;
    int total_nodes = ZERO;
    
    // studied_simlist.Clear();
    index = ZERO;
    total_nodes = studied_simlist->total_nodes;
    while(index < total_nodes)    
    {
        studied_simlist = cs_element_at(studied_simlist, index);
        free((struct st_sim_model*)studied_simlist->page);
        ++index;
    }
    cs_clear_nodes(studied_simlist);
    
    // gensims_all.Clear();
    index = ZERO;
    total_nodes = gensims_all->total_nodes;
    while(index < total_nodes)    
    {
        gensims_all = cs_element_at(gensims_all, index);
        free((struct st_sim_model*)gensims_all->page);
        ++index;
    }
    cs_clear_nodes(gensims_all);
    
    // gensims_studied.Clear();
    index = ZERO;
    total_nodes = gensims_studied->total_nodes;
    while(index < total_nodes)    
    {
        gensims_studied = cs_element_at(gensims_studied, index);
        free((struct st_sim_model*)gensims_studied->page);
        ++index;
    }
    cs_clear_nodes(gensims_studied);
    
    // projected_simlist.Clear();
    index = ZERO;
    total_nodes = projected_simlist->total_nodes;
    while(index < total_nodes)    
    {
        projected_simlist = cs_element_at(projected_simlist, index);
        free((struct st_sim_model*)projected_simlist->page);
        ++index;
    }
    cs_clear_nodes(projected_simlist);

    // fstudy_dates.Clear();
    index = ZERO;
    total_nodes = fstudy_dates->total_nodes;
    while(index < total_nodes)    
    {
        fstudy_dates = cs_element_at(fstudy_dates, index);
        free((struct st_fstudy_dates*)fstudy_dates->page);
        ++index;
    }
    cs_clear_nodes(fstudy_dates);

    // fstudy_counts.Clear();
    index = ZERO;
    total_nodes = fstudy_counts->total_nodes;
    while(index < total_nodes)    
    {
        fstudy_counts = cs_element_at(fstudy_counts, index);
        free((struct st_fstudy_counts*)fstudy_counts->page);
        ++index;
    }
    cs_clear_nodes(fstudy_counts);

    // xrep_temp_dates.Clear();
    index = ZERO;
    total_nodes = xrep_temp_dates->total_nodes;
    while(index < total_nodes)    
    {
        xrep_temp_dates = cs_element_at(xrep_temp_dates, index);
        free((struct st_xrep_temp_dates*)xrep_temp_dates->page);
        ++index;
    }
    cs_clear_nodes(xrep_temp_dates);
    
    // xrep_datecounts.Clear();
    index = ZERO;
    total_nodes = xrep_datecounts->total_nodes;
    while(index < total_nodes)    
    {
        xrep_datecounts = cs_element_at(xrep_datecounts, index);
        free((struct st_xrep_datecounts*)xrep_datecounts->page);
        ++index;
    }
    cs_clear_nodes(xrep_datecounts);


    // to_xmax.Clear();
    index = ZERO;
    total_nodes = to_xmax->total_nodes;
    while(index < total_nodes)    
    {
        to_xmax = cs_element_at(to_xmax, index);
        free((struct st_sim_model*)to_xmax->page);
        ++index;
    }
    cs_clear_nodes(to_xmax);
}
































void predict_studies()
{
    const int INITIAL_INDEX = 0;
    const int DAYS_TO_ADD = 2;

    // Initialize index and process predictions if required
    int index = INITIAL_INDEX;
    if (predict_vars.process_prediction)
    {
        while (index < topics_list->total_nodes)
        {
            gensims_all_getter(index);
            ++index;
        }
        predict_vars.process_prediction = false;
    }

    // Collect studies based on x-axis data
    collect_study_x();

    // Date and skip check
    date_time *simDate, *previousDate;
    bool skipDay = false;
    previousDate = predict_vars.sim_date_use;
    simDate = cs_add_days(previousDate, DAYS_TO_ADD);
    skipDay = skip_checker(simDate);

    // If not a skip day, proceed with further calculations
    if (!skipDay)
    {
        find_y_at_x();
        collect_study_y();
        reduce_new();
    }

    // Simulation and learning calculations
    index = INITIAL_INDEX;
    while (index < studyrep_elements->total_nodes)
    {
        studyrep_elements = cs_element_at(studyrep_elements, index);
        predict_vars.gen_projected_index = ((struct st_studyrep_elements*)studyrep_elements->page)->studyrep_elements;
        sim_calculate_learning();
        ++index;
    }

    // Clear the elements
    index = INITIAL_INDEX;
    while (index < studyrep_elements->total_nodes)
    {
        studyrep_elements = cs_element_at(studyrep_elements, index);
        free((struct st_studyrep_elements*)studyrep_elements->page);
        ++index;
    }
    cs_clear_nodes(studyrep_elements);
}

void collect_study_x()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;

    date_time *useDate, *nextDate;
    int dateCompare;
    useDate = predict_vars.sim_date_use;

    // Get 2nd rep studies
    int index, repCheck, last_node;
    index = repCheck = last_node = ZERO;
    
    while (index < gensims_all->total_nodes)
    {
        // st_sim_model
        gensims_all = cs_element_at(gensims_all, index);
        nextDate = ((struct st_sim_model*)gensims_all->page)->next_date;
        dateCompare = cs_date_compare(nextDate, useDate);

        if (dateCompare <= ZERO && ((struct st_sim_model*)gensims_all->page)->real_repetition == TWO)
            if (repCheck < predict_vars.x_high_x_count)
            {
                // (struct st_studyrep_elements*)studyrep_elements->page
                studyrep_elements = cs_add(studyrep_elements);
                last_node = studyrep_elements->total_nodes - ONE;
                studyrep_elements = cs_element_at(studyrep_elements, last_node);
                ((struct st_studyrep_elements*)studyrep_elements->page)->studyrep_elements = index;
                ++repCheck;
            }
        ++index;
    }

    // Get Late
    index = ZERO;
    while (index < gensims_all->total_nodes)
    {
        // st_sim_model
        gensims_all = cs_element_at(gensims_all, index);
        nextDate = ((struct st_sim_model*)gensims_all->page)->next_date;
        dateCompare = cs_date_compare(nextDate, useDate);

        if (dateCompare < ZERO && ((struct st_sim_model*)gensims_all->page)->real_repetition != TWO)
            if (repCheck < predict_vars.x_high_x_count)
            {
                // (struct st_studyrep_elements*)studyrep_elements->page
                studyrep_elements = cs_add(studyrep_elements);
                last_node = studyrep_elements->total_nodes - ONE;
                studyrep_elements = cs_element_at(studyrep_elements, last_node);
                ((struct st_studyrep_elements*)studyrep_elements->page)->studyrep_elements = index;
                ++repCheck;
            }
        ++index;
    }

    //Get On-Time
    index = ZERO;
    while (index < gensims_all->total_nodes)
    {
        gensims_all = cs_element_at(gensims_all, index);
        nextDate = ((struct st_sim_model*)gensims_all->page)->next_date;
        dateCompare = cs_date_compare(nextDate, useDate);

        if (dateCompare < ZERO && ((struct st_sim_model*)gensims_all->page)->real_repetition != TWO)
            if (repCheck < predict_vars.x_high_x_count)
            {
                // (struct st_studyrep_elements*)studyrep_elements->page
                studyrep_elements = cs_add(studyrep_elements);
                last_node = studyrep_elements->total_nodes - ONE;
                studyrep_elements = cs_element_at(studyrep_elements, last_node);
                ((struct st_studyrep_elements*)studyrep_elements->page)->studyrep_elements = index;
                ++repCheck;
            }
        ++index;
    }
    predict_vars.current_x = repCheck;
}

void gensims_all_getter(int index)
{
   const int ZERO = 0;
   const int ONE = 1;
   int last_node = ZERO;

    // st_sim_model
    struct st_sim_model *newSims =  malloc(sizeof(struct st_sim_model));

    topics_list = cs_element_at(topics_list, index);    
    if (((struct st_topic_model*)topics_list->page)->top_studied == true)
    {
        newSims->top_number = ((struct st_topic_model*)topics_list->page)->top_id - ONE;
        newSims->first_date = ((struct st_topic_model*)topics_list->page)->first_date;
        newSims->simulated_date = ((struct st_topic_model*)topics_list->page)->next_date;
        newSims->next_date = ((struct st_topic_model*)topics_list->page)->next_date;
        newSims->real_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;
        newSims->sim_repetition = ((struct st_topic_model*)topics_list->page)->top_repetition;  //Some of these are not matching Real_Repetition. They should increment to that value in simulation of previous study sessions.
        newSims->top_difficulty = ((struct st_topic_model*)topics_list->page)->top_difficulty;
        newSims->interval_length = ((struct st_topic_model*)topics_list->page)->interval_length;

        // (struct st_studyrep_elements*)studyrep_elements->page
        gensims_all = cs_add(gensims_all);
        last_node = gensims_all->total_nodes - ONE;
        gensims_all = cs_element_at(gensims_all, last_node);

        gensims_all->page = &newSims;
    }
}
void find_y_at_x()
{
    const double ZERO = 0;
    double lowY, highY, run;
    double curReps, rise, slope, value_b, yCurrent;

    highY = value_b = predict_vars.y_high_y_count;
    run = predict_vars.x_high_x_count;
    lowY = ZERO;
    rise = lowY - highY;
    slope = rise / run;
    curReps = predict_vars.current_x;
    yCurrent = (slope * curReps) + value_b;
    predict_vars.current_y = (int)yCurrent;

    if (predict_vars.lock_goals == false)
    {
        predict_vars.lock_goals = true;
        rep_setter();
    }
}
void rep_setter()
{
    const int ZERO = 0;

    int currentX = (int)predict_vars.current_x;
    int currentY = predict_vars.current_y;
    int countDown = ZERO;

    if (currentY > globals.new_left)
        currentY = globals.new_left;
    countDown = currentX + currentY;

    predict_vars.until_new = countDown;
}
void goal_setter()
{
    gensims_all = cs_element_at(gensims_all, predict_vars.gen_projected_index);
    ((struct st_sim_model*)gensims_all->page)->next_date;
    predict_vars.prediction_date = ((struct st_sim_model*)gensims_all->page)->next_date;
    predict_vars.final_topic = ((struct st_sim_model*)gensims_all->page)->top_number;
}
void collect_study_y()
{
    const int ZERO = 0;
    const int ONE = 1;

    int yToStudied = gensims_all->total_nodes - ONE;
    int index = ZERO;
    int last_node = ZERO;

    while (index < predict_vars.current_y)
    {
        if (index < projected_simlist->total_nodes)
        {
            ++yToStudied;

            //st_studyrep_elements
            last_node = studyrep_elements->total_nodes - ONE;
            studyrep_elements = cs_add(studyrep_elements);

            ((struct st_studyrep_elements*)gensims_all->page)->studyrep_elements = yToStudied;
        }
        ++index;
    }
    index = ZERO;
    int indexTwo = ZERO;
    while (index < predict_vars.current_y)
    {
        if (projected_simlist->total_nodes >= predict_vars.current_y)
        {
            y_to_gen_sims_all(index);
        }
        else if (projected_simlist->total_nodes > ZERO)
        {
            while (indexTwo < projected_simlist->total_nodes)
            {
                y_to_gen_sims_all(indexTwo);
                ++indexTwo;
            }
        }
        ++index;
    }
}
void y_to_gen_sims_all(int index)
{
    const int ZERO = 0;
    struct st_sim_model new_sims; // if I have a problem, then allocate this memory to it: = malloc(sizeof(struct st_sim_model));


    new_sims.top_number = ((struct st_sim_model*)projected_simlist->page)->top_number;
    new_sims.first_date = predict_vars.sim_date_use;
    new_sims.simulated_date = predict_vars.sim_date_use;
    new_sims.next_date = predict_vars.sim_date_use;
    new_sims.real_repetition = ZERO;
    new_sims.sim_repetition = ZERO;
    new_sims.top_difficulty = ((struct st_sim_model*)projected_simlist->page)->top_difficulty;
    new_sims.interval_length = ((struct st_sim_model*)projected_simlist->page)->interval_length;
    
    gensims_all = cs_add(gensims_all);
    gensims_all->page = &new_sims;
}
void reduce_new()
{
    const int ZERO = 0;
    int count = ZERO;
    if (projected_simlist->total_nodes > ZERO && count < predict_vars.current_y)
    {
        while (count < projected_simlist->total_nodes)
        {
            get_reduced_new(count);
            ++count;
        }
        
        // st_sim_model
        // clear projected_simlist
        int index = ZERO;
        while (index < projected_simlist->total_nodes)
        {
            projected_simlist = cs_element_at(projected_simlist, index);

            free((struct st_sim_model*)projected_simlist->page);
            ++index;
        }
        // st_sim_model
        cs_clear_nodes(projected_simlist);


        count = ZERO;
        while (count < reduced_projected->total_nodes)
        {
            get_reduced_projected(count);
            ++count;
        }
        
        // st_sim_model
        // clear reduced_projected
        index = ZERO;
        while (index < reduced_projected->total_nodes)
        {
            reduced_projected = cs_element_at(reduced_projected, index);

            free((struct st_sim_model*)reduced_projected->page);
            ++index;
        }
        // st_sim_model
        cs_clear_nodes(reduced_projected);
    }
}
void get_reduced_new(int count)
{
    // SimModel newSims = new SimModel();
    struct st_sim_model new_sims; // if I have a problem, then allocate this memory to it: = malloc(sizeof(struct st_sim_model));


    if (count >= predict_vars.current_y)
    {
        // newSims = projected_simlist[count];
        projected_simlist = cs_element_at(projected_simlist, count);

        // For all lists
        // int top_number;        // The line number here is used instead of topic id
        
        // char *first_date;
        // char *simulated_date;  // Simulated date of the simulateed repetition.
        // char *next_date;
        
        // int real_repetition;
        // int sim_repetition;        

        // double top_difficulty;
        // double interval_length;
        new_sims.top_number = ((struct st_sim_model*)projected_simlist->page)->top_number;

        new_sims.first_date = ((struct st_sim_model*)projected_simlist->page)->first_date;
        new_sims.simulated_date = ((struct st_sim_model*)projected_simlist->page)->simulated_date;
        new_sims.next_date = ((struct st_sim_model*)projected_simlist->page)->next_date;

        new_sims.real_repetition = ((struct st_sim_model*)projected_simlist->page)->real_repetition;
        new_sims.sim_repetition = ((struct st_sim_model*)projected_simlist->page)->sim_repetition;

        new_sims.top_difficulty = ((struct st_sim_model*)projected_simlist->page)->top_difficulty;
        new_sims.interval_length = ((struct st_sim_model*)projected_simlist->page)->interval_length;
    

        // remember to update the parts that add, with a check to see
        // if there is one element whose page is empty (using a checklist struct)
        // if there is only one element with an empty page, then add to the page, 
        // and mark it as non-empty.

        // reducedProjected.Add(new_sims);
        reduced_projected = cs_add(reduced_projected);
        reduced_projected->page = &new_sims;
    }
}
void get_reduced_projected(int count)
{
    // SimModel newSims = new SimModel();
    struct st_sim_model new_sims; // if I have a problem, then allocate this memory to it: = malloc(sizeof(struct st_sim_model));

    
    
    // newSims = reducedProjected[count];
    reduced_projected = cs_add(count);
    new_sims.top_number = ((struct st_sim_model*)reduced_projected->page)->top_number;

    new_sims.first_date = ((struct st_sim_model*)reduced_projected->page)->first_date;
    new_sims.simulated_date = ((struct st_sim_model*)reduced_projected->page)->simulated_date;
    new_sims.next_date = ((struct st_sim_model*)reduced_projected->page)->next_date;

    new_sims.real_repetition = ((struct st_sim_model*)reduced_projected->page)->real_repetition;
    new_sims.sim_repetition = ((struct st_sim_model*)reduced_projected->page)->sim_repetition;

    new_sims.top_difficulty = ((struct st_sim_model*)reduced_projected->page)->top_difficulty;
    new_sims.interval_length = ((struct st_sim_model*)reduced_projected->page)->interval_length;

    // remember to update the parts that add, with a check to see
    // if there is one element whose page is empty (using a checklist struct)
    // if there is only one element with an empty page, then add to the page, 
    // and mark it as non-empty.

    // projectedSimList.Add(newSims);
    projected_simlist = cs_add(projected_simlist);
    projected_simlist->page = &new_sims;
}
void sim_calculate_learning()
{
    sim_interval_time();
    if (predict_vars.process_gen_sims_studied == false)
        sim_add_repetition();
    sim_process_date();
}
void sim_interval_time()
{
    const int ONE = 1;
    const double SINGLE_DAY = 1440; // 1440 is the quatity in minutes of a day. I'm using minutes, instead of whole days, to be more precise.
    double difficulty;
    int ith_repetition;
    double interval_length;

    if (predict_vars.process_gen_sims_studied == true)
    {
        // gensims_studied
        // st_sim_model
        // genSimsStudied.ElementAt(predict_vars.Gen_Studied_Index).Top_Difficulty;
        // ((struct st_sim_model*)gensims_studied->page)->interval_length
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_studied_index);

        // difficulty = gensims_studied.ElementAt(predict_vars.Gen_Studied_Index).Top_Difficulty;
        // ith_repetition = gensims_studied.ElementAt(predict_vars.Gen_Studied_Index).Sim_Repetition;
        // interval_length = gensims_studied.ElementAt(predict_vars.Gen_Studied_Index).Interval_Length;

        difficulty = ((struct st_sim_model*)gensims_studied->page)->top_difficulty;
        ith_repetition = ((struct st_sim_model*)gensims_studied->page)->sim_repetition;
        interval_length = ((struct st_sim_model*)gensims_studied->page)->interval_length;




        if (ith_repetition == ONE)
            interval_length = SINGLE_DAY;
        else
            interval_length = interval_length * difficulty;

        ((struct st_sim_model*)gensims_studied->page)->interval_length = interval_length;

        int indexFuture = predict_vars.gen_studied_index + ONE;
        // Get needed values from future index, then change back to studied index
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_studied_index);
        int f_topic_num = ((struct st_sim_model*)gensims_studied->page)->top_number;
        // int f_interval_len = ((struct st_sim_model*)gensims_studied->page)->interval_length;
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_studied_index);


        if (indexFuture < gensims_studied->total_nodes)
            if (((struct st_sim_model*)gensims_studied->page)->top_number == f_topic_num)
            {
                // gensims_studied[indexFuture].Interval_Length = interval_length;
                // int f_interval_len = ((struct st_sim_model*)gensims_studied->page)->interval_length;
                gensims_studied = cs_element_at(gensims_studied, indexFuture);
                ((struct st_sim_model*)gensims_studied->page)->interval_length = interval_length;
            }
    }
    else
    {
        // difficulty = genSimsAll.ElementAt(predict_vars.Gen_Projected_Index).Top_Difficulty;
        // ith_repetition = genSimsAll.ElementAt(predict_vars.Gen_Projected_Index).Sim_Repetition;
        // interval_length = genSimsAll.ElementAt(predict_vars.Gen_Projected_Index).Interval_Length;
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_projected_index);
        difficulty = ((struct st_sim_model*)gensims_studied->page)->top_difficulty;
        ith_repetition = ((struct st_sim_model*)gensims_studied->page)->sim_repetition;
        interval_length = ((struct st_sim_model*)gensims_studied->page)->interval_length;


        if (ith_repetition == ONE)
            interval_length = SINGLE_DAY;
        else
            interval_length = interval_length * difficulty;

        // genSimsAll[predict_vars.gen_projected_index].Interval_Length = interval_length;
        gensims_all = cs_element_at(gensims_all, predict_vars.gen_projected_index);
        ((struct st_sim_model*)gensims_all->page)->interval_length = interval_length;
    }
}
void sim_add_repetition()
{
    // ++genSimsAll[predict_vars.Gen_Projected_Index].Sim_Repetition;
    gensims_all = cs_element_at(gensims_all, predict_vars.gen_projected_index);
    ++((struct st_sim_model*)gensims_all->page)->sim_repetition;
}
void sim_process_date()
{
    const int ONE = 1;
    const double SINGLE_DAY = 1440.0;
    double interval_length;
    double days_double;
    int days_int = 0;
    char *fake_today;
    char *next_date_string;
    int index_future = 0;
    int topic_future = 0;

    // Choose the data source based on the condition
    struct st_sim_model *current_studied;
    if (predict_vars.process_gen_sims_studied)
    {
        current_studied = (struct st_sim_model*)cs_element_at(gensims_studied, predict_vars.gen_studied_index)->page;
        fake_today = current_studied->simulated_date;
    }
    else
    {
        current_studied = (struct st_sim_model*)cs_element_at(gensims_studied, predict_vars.gen_projected_index)->page;
        fake_today = predict_vars.sim_date_use;
    }

    // Extract common calculations
    interval_length = current_studied->interval_length;
    days_double = interval_length / SINGLE_DAY;
    days_int = (int)days_double;

    // Calculate the next date
    next_date_string = cs_add_days(fake_today, days_int);

    // Logic for processing 'genSimsStudied' or 'genSimsAll'
    if (predict_vars.process_gen_sims_studied)
    {
        index_future = predict_vars.gen_studied_index + ONE;
        struct st_sim_model *next_studied = (struct st_sim_model*)cs_element_at(gensims_studied, index_future)->page;
        topic_future = next_studied->top_number;

        current_studied->next_date = next_date_string;

        if (index_future < gensims_studied->total_nodes && current_studied->top_number == topic_future)
        {
            next_studied->simulated_date = next_date_string;
        }
    }
    else
    {
        current_studied->simulated_date = predict_vars.sim_date_use;
        current_studied->next_date = next_date_string;
    }

    // Remember to free next_date_string when done, to prevent memory leak.
    free(next_date_string);
}

/***********************************PREDICTION END*********************************************/
/*******************************WEEKLY SCHEDULE START******************************************/
void check_for_week()
{
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;

    // Initialize the file path
    init_file_path(THREE);  // Assuming 3 is a code for determining the correct file path for week.sc

    // Check if the file exists
    if (cs_file_exists(file_strings.week_file))
    {
        // Read all lines from the file into a list
        struct st_node* week_lines = cs_ral_tolist(file_strings.week_file);

        // Since the C# version reads all lines but actually only processes the first, 
        // we will do the same here for a 1-to-1 mapping.
        if (week_lines->total_nodes > ZERO) 
        {
            struct st_string* current_line = (struct st_string*)cs_element_at(week_lines, ZERO)->page;
            
            // Split the line by commas
            struct st_node* week_entries = cs_list_split(current_line, ',');

            // Convert these st_string objects to integers and store them in week_list
            week_list.monday    = atoi(((struct st_string*)cs_element_at(week_entries, ZERO)->page)->string);
            week_list.tuesday   = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
            week_list.wednesday = atoi(((struct st_string*)cs_element_at(week_entries, TWO)->page)->string);
            week_list.thursday  = atoi(((struct st_string*)cs_element_at(week_entries, THREE)->page)->string);
            week_list.friday    = atoi(((struct st_string*)cs_element_at(week_entries, FOUR)->page)->string);
            week_list.saturday  = atoi(((struct st_string*)cs_element_at(week_entries, FIVE)->page)->string);
            week_list.sunday    = atoi(((struct st_string*)cs_element_at(week_entries, SIX)->page)->string);
            
            // Don't forget to free week_entries if necessary

        }
        
        // Don't forget to free week_lines if necessary
        // Free Pages from Nodes
        index = 0;
        while (index < week_lines->total_nodes) {
            week_lines = cs_element_at(week_lines, index);
            free((struct st_node*)week_lines->page); // Free page data
            ++index;
        }
        index = 0;
        week_lines = cs_element_at(week_lines, index); // Reset to the first node if needed.
        cs_clear_nodes(week_lines); // Clear the nodes
    }
    else
    {
        // File doesn't exist, so write default values to it
        char file_contents[] = "0,0,0,0,0,0,0";
        cs_write_all_text(file_strings.week_file, file_contents);

        // Set all fields in week_list to zero
        week_list.monday = ZERO;
        week_list.tuesday = ZERO;
        week_list.wednesday = ZERO;
        week_list.thursday = ZERO;
        week_list.friday = ZERO;
        week_list.saturday = ZERO;
        week_list.sunday = ZERO;
    }
}

bool skip_checker(date_time *simDate)
{
    const int ONE = 1;
    bool skip = false;
    
    if (weekList.monday == ONE)
        if (simDate->DayOfWeek == DayOfWeek.Monday)
            skip = true;
    if (weekList->Tuesday == ONE)
        if (simDate->DayOfWeek == DayOfWeek.Tuesday)
            skip = true;
    if (weekList->Wednesday ==  ONE)
        if (simDate->DayOfWeek == DayOfWeek.Wednesday)
            skip = true;
    if (weekList->Thursday ==  ONE)
        if (simDate->DayOfWeek == DayOfWeek.Thursday)
            skip = true;
    if (weekList->Friday ==  ONE)
        if (simDate->DayOfWeek == DayOfWeek.Friday)
            skip = true;
    if (weekList->Saturday ==  ONE)
        if (simDate->DayOfWeek == DayOfWeek.Saturday)
            skip = true;
    if (weekList.Sunday ==  ONE)
        if (simDate->DayOfWeek == DayOfWeek.Sunday)
            skip = true;
    
    return skip;
}
void weekly_schedule()
{
    const int ZERO = 0;
    const int SIX = 6;
    const int THIRTEEN = 13;
    bool menuBool = false;
    char *userInput = NULL;
    int dayOption = ZERO;
    char *endptr;
    long int converted;

    while (menuBool == false)
    {
        selection_dialogs(THIRTEEN);
        userInput = cs_read_line(); // Assuming cs_read_line allocates memory for userInput
        if (strcmp(userInput, "m") != 0)
        {
            converted = strtol(userInput, &endptr, 10);
            if (*endptr == '\0' && converted <= SIX && converted >= ZERO)
            {
                dayOption = (int)converted;
                cs_console_clear();
                toggle_day_function(dayOption);
            }
            else
            {
                cs_console_clear();
                // Show "Invalid input" message and wait for Enter
                cs_read_line();
                cs_console_clear();
            }
        }
        else
        {
            menuBool = true;
        }

        // Free the allocated memory for userInput
        free(userInput);
        userInput = NULL;
    }
}
void weekly_dialog()
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;
    const int SEVEN = 7; // Or use (SIX + 1)
    const int STUDY_DAY = 0;
    const int OFF_DAY = 1;
    
    char* days[] = {"0) Monday", "1) Tuesday", "2) Wednesday", "3) Thursday", "4) Friday", "5) Saturday", "6) Sunday"};
    char* state[] = {"Study Day", "Off Day"};
    
    int dayState[SEVEN];

    dayState[ZERO] = weekList.Monday;
    dayState[ONE] = weekList.Tuesday;
    dayState[TWO] = weekList.Wednesday;
    dayState[THREE] = weekList.Thursday;
    dayState[FOUR] = weekList.Friday;
    dayState[FIVE] = weekList.Saturday;
    dayState[SIX] = weekList.Sunday;

    int index = ZERO;
    while (index <= SIX)
    {
        if (dayState[index] == ZERO)
            printf("%s    ---   %s\n", days[index], state[STUDY_DAY]);
        else
            printf("%s    ---   %s\n", days[index], state[OFF_DAY]);
        ++index;
    }
    printf("\n\n\nOPTIONS:\nEnter a number from 1 to 7 to alter the schedule.\n\nOr enter m to go back to the main menu: ");
}
void toggle_day_function(int dayOption)
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;

    // List<string> weekFileContents = new List<string>();
    // struct st_node* week_lines;
    // struct st_node* week_entries;
    // string filePath;
    // if (globals.osSwitch == true)
    //     filePath = $"{globals.DirectoryPath}//week.sc";
    // else
    //     filePath = $"{globals.DirectoryPath}\\week.sc";
    init_file_path(THREE);
    struct st_node* week_lines;

    // weekFileContents = File.ReadAllLines(filePath).ToList();
    week_lines = cs_read_line(file_strings.week_file);

    // int index = ZERO;
    // while (index < week_lines->total_nodes)
    // {
    // string[] entries = line.Split(',');
    //((struct st_sim_model*)week_list->page)->top_difficulty;
    week_lines = cs_element_at(week_lines, ZERO); // <--- may not need to set this, but I'll figure it out later
    struct st_node* week_entries;
    //string[] entries = line.Split(',');
    week_entries = cs_list_split((struct st_string*)week_lines->page, ',');



    // weekList.Monday = Convert.ToInt32(entries[Constants.ZERO_INT]);
    // weekList.Tuesday = Convert.ToInt32(entries[Constants.ONE_INT]);
    // weekList.Wednesday = Convert.ToInt32(entries[Constants.TWO_INT]);
    // weekList.Thursday = Convert.ToInt32(entries[Constants.THREE_INT]);
    // weekList.Friday = Convert.ToInt32(entries[Constants.FOUR_INT]);
    // weekList.Saturday = Convert.ToInt32(entries[Constants.FIVE_INT]);
    // weekList.Sunday = Convert.ToInt32(entries[Constants.SIX_INT]);
    week_entries = cs_element_at(week_lines, ZERO);
    week_list.monday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, ONE);
    week_list.tuesday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, TWO);
    week_list.wednesday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, THREE);
    week_list.thursday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, FOUR);
    week_list.friday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, FIVE);
    week_list.saturday = atoi(((struct st_string*)week_entries->page)->string);

    week_entries = cs_element_at(week_lines, SIX);
    week_list.sunday = atoi(((struct st_string*)week_entries->page)->string);
    //}

    week_list.monday = atoi(((struct st_string*)cs_element_at(week_entries, ZERO)->page)->string);
    week_list.tuesday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.wednesday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.thursday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.friday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.saturday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.sunday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);


    // Toggle the day based on the option
    switch (dayOption)
    {
        case 0:
            week_list.monday = (week_list.monday == ZERO) ? ONE : ZERO;
            break;
        case 1:
            week_list.monday = (week_list.tuesday == ZERO) ? ONE : ZERO;
            break;
        case 2:
            week_list.monday = (week_list.wednesday == ZERO) ? ONE : ZERO;
            break;
        case 3:
            week_list.monday = (week_list.thursday == ZERO) ? ONE : ZERO;
            break;
        case 4:
            week_list.monday = (week_list.friday == ZERO) ? ONE : ZERO;
            break;
        case 5:
            week_list.monday = (week_list.saturday == ZERO) ? ONE : ZERO;
            break;
        case 6:
            week_list.monday = (week_list.sunday == ZERO) ? ONE : ZERO;
            break;
    }

    // Allocate the memory for the strings. There are four because sprintf() needs less arguments
    struct st_string *temp = malloc(sizeof(struct st_string));
    
    
        // List<string> output = new List<string>();
    struct st_string *monday = malloc(sizeof(struct st_string));
    struct st_string *tuesday = malloc(sizeof(struct st_string));
    struct st_string *wednesday = malloc(sizeof(struct st_string));
    struct st_string *thursday = malloc(sizeof(struct st_string));
    struct st_string *friday = malloc(sizeof(struct st_string));
    struct st_string *saturday = malloc(sizeof(struct st_string));
    struct st_string *sunday = malloc(sizeof(struct st_string));

    const char *COMMA = ",";
    // Store the information as strings of characters
    // days
    sprintf(monday, "%d%s", week_list.monday, COMMA);                                      // int       1
    sprintf(tuesday, "%d%s", week_list.tuesday, COMMA);                                      // int       1
    sprintf(wednesday, "%d%s", week_list.wednesday, COMMA);                                      // int       1
    sprintf(thursday, "%d%s", week_list.thursday, COMMA);                                      // int       1
    sprintf(friday, "%d%s", week_list.friday, COMMA);                                      // int       1
    sprintf(saturday, "%d%s", week_list.saturday, COMMA);                                      // int       1
    sprintf(sunday, "%d", week_list.sunday);                                      // int       1


    // LENGTHS
    int len = strlen(monday) + strlen(tuesday) + strlen(wednesday) + strlen(thursday) + strlen(friday) + strlen(saturday) + strlen(sunday) + ONE;

    // MEMORY ALLOCATIONS
    temp->string = malloc(len);

    // final string
    sprintf(temp->string, "%s%s%s%s%s%s%s", monday, tuesday, wednesday, thursday, friday, saturday, sunday);
    

    // Free the allocated memory for the temporary strings
    free(monday);
    free(tuesday);
    free(wednesday);
    free(thursday);
    free(friday);
    free(saturday);
    free(sunday);

    struct st_node *output = malloc(sizeof(struct st_node));
    output = cs_add(output); // TODO: Check if it already has a node
    output= cs_element_at(output, ZERO);
    output->page = &temp;
    
    // Use Unix style directory structure and store the data in a text file
    cs_write_all_lines(file_strings.week_file, output, output->total_nodes);

    free(temp);
    cs_clear_nodes(output);
}
void toggle_day_function(int dayOption)
{
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;
    
    // Initialize file path
    init_file_path(THREE);
    char *file_content = cs_read_all_text(file_strings.week_file);
    if (file_content == NULL) 
    {
        // Handle error, e.g., file not found or read failure
        fprintf(stderr, "Error: Unable to read from file %s.\n", file_strings.week_file);
        return;
    }


struct st_node *week_entries = cs_list_split(file_content, "\n");
if (week_entries == NULL)
{
    // Handle error, e.g., memory allocation failure
    fprintf(stderr, "Error: Failed to create linked list from file content.\n");
    // Optionally, clean up any previously allocated resources, if necessary
    if (file_content != NULL) {
        free(file_content);
    }
    return;
}


    // Update week_list from the file
    week_list.monday = atoi(((struct st_string*)cs_element_at(week_entries, ZERO)->page)->string);
    week_list.tuesday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.wednesday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.thursday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.friday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.saturday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);
    week_list.sunday = atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string);


    // Toggle the day based on the option
    switch (dayOption)
    {
        case 0:
            week_list.monday = (week_list.monday == ZERO) ? ONE : ZERO;
            break;
        case 1:
            week_list.tuesday = (week_list.tuesday == ZERO) ? ONE : ZERO;
            break;
        case 2:
            week_list.wednesday = (week_list.wednesday == ZERO) ? ONE : ZERO;
            break;
        case 3:
            week_list.thursday = (week_list.thursday == ZERO) ? ONE : ZERO;
            break;
        case 4:
            week_list.friday = (week_list.friday == ZERO) ? ONE : ZERO;
            break;
        case 5:
            week_list.saturday = (week_list.saturday == ZERO) ? ONE : ZERO;
            break;
        case 6:
            week_list.sunday = (week_list.sunday == ZERO) ? ONE : ZERO;
            break;
    }

    
    // Prepare to write the output
    char *output_str = NULL;
    size_t total_size = 0;
    total_size += snprintf(NULL, 0, "%d,", week_list.monday);
    total_size += snprintf(NULL, 0, "%d,", week_list.tuesday);
    total_size += snprintf(NULL, 0, "%d,", week_list.wednesday);
    total_size += snprintf(NULL, 0, "%d,", week_list.thursday);
    total_size += snprintf(NULL, 0, "%d,", week_list.friday);
    total_size += snprintf(NULL, 0, "%d,", week_list.saturday);
    total_size += snprintf(NULL, 0, "%d,", week_list.sunday);
    
    output_str = malloc(total_size + 1);
    snprintf(output_str, total_size + 1, "%d,%d,%d,%d,%d,%d,%d", 
                week_list.monday, week_list.tuesday, week_list.wednesday,
                week_list.thursday, week_list.friday, week_list.saturday,
                week_list.sunday);

    // struct st_node *output = malloc(sizeof(struct st_node));
    //... Initialize the output node properly
    cs_write_all_lines(file_strings.week_file, output_str);

    // Clean up
    free(output_str);
    free(output);
    //... any other cleanup you may need
}
void toggle_day_function(int dayOption)
{
    // Initialize file path
    init_file_path(THREE);
    char *file_content = cs_read_all_text(file_strings.week_file);
    if (file_content == NULL) 
    {
        fprintf(stderr, "Error: Unable to read from file %s.\n", file_strings.week_file);
        return;
    }

    struct st_node *week_entries = cs_list_split(file_content, "\n");
    if (week_entries == NULL)
    {
        fprintf(stderr, "Error: Failed to create linked list from file content.\n");
        free(file_content);
        return;
    }

    int days[] = {
        atoi(((struct st_string*)cs_element_at(week_entries, ZERO)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, ONE)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, TWO)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, THREE)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, FOUR)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, FIVE)->page)->string),
        atoi(((struct st_string*)cs_element_at(week_entries, SIX)->page)->string)
    };

    // Toggle the day based on the option
    days[dayOption] = (days[dayOption] == ZERO) ? ONE : ZERO

    // Prepare to write the output
    char *output = NULL;
    size_t total_size = 0;
    total_size += snprintf(NULL, 0, "%d,", days[ZERO]);
    total_size += snprintf(NULL, 0, "%d,", days[ONE]);
    total_size += snprintf(NULL, 0, "%d,", days[TWO]);
    total_size += snprintf(NULL, 0, "%d,", days[THREE]);
    total_size += snprintf(NULL, 0, "%d,", days[FOUR]);
    total_size += snprintf(NULL, 0, "%d,", days[FIVE]);
    total_size += snprintf(NULL, 0, "%d,", days[SIX]);

    // Prepare to write the output
    output = malloc(total_size + 1); // Adjust the size as necessary
    snprintf(output, sizeof(total_size + 1), "%d,%d,%d,%d,%d,%d,%d", 
            days[ZERO], days[ONE], days[TWO], days[THREE], days[FOUR], days[FIVE], days[SIX]);

    cs_write_all_lines(file_strings.week_file, output);

    // Clean up
    free(file_content);
    free(output);
    // Free any other allocated resources

    // Free Pages from Nodes
    int index = ZERO;
    while (index < week_entries->total_nodes) 
    {
        week_entries = cs_element_at(week_entries, index);
        free((struct st_number*)week_entries->page); // Free page data
        ++index;
    }
    index = ZERO;
    week_entries = cs_element_at(week_entries, index); // Reset to the first node if needed.

    cs_clear_nodes(week_entries); // Clear the nodes
    free(week_entries); // Optionally free the main list structure
}
/********************************WEEKLY SCHEDULE END*******************************************/

// COMPILE A COPY IN VM, not out of VM!!!!!!!!!!!!

/********************************FILE PATHS START**********************************************/
void init_file_path(int choice)
{
    switch (choice)
    {
        case 1:
            file_strings->txt_course_listfile = concat_filepath(globals.directory_path, file_constants.slash, file_constants.course_file, file_constants.txt_format);
            file_strings->bak_course_listfile = concat_filepath(globals.directory_path, file_constants.slash, file_constants.course_file, file_constants.bak_format);
            break;
        case 2:
            file_strings->course_countfile = concat_filepath(globals.directory_path, file_constants.slash, file_constants.course_count, file_constants.txt_format);
            break;
        case 3:
            file_strings->week_file = concat_filepath(globals.directory_path, file_constants.slash, file_constants.week_sc, "");
            break;
        case 4:
            file_strings->txt_course_namefile = concat_filepath(globals.directory_path, file_constants.slash, globals.course_name, file_constants.txt_format);
            file_strings->bak_course_namefile = concat_filepath(globals.directory_path, file_constants.slash, globals.course_name, file_constants.bak_format);
            break;
        default:
            printf("The number is not 1, 2, 3, or 4\n");
            break;
    }
}
char* concat_filepath(const char* directory, const char* slash, const char* filename, const char* ext)
{
    int len = strlen(directory) + strlen(slash) + strlen(filename) + strlen(ext) + 1;
    char *result = malloc(len);
    if (result != NULL) {
        snprintf(result, len, "%s%s%s%s", directory, slash, filename, ext);
    }
    return result;
}
void free_file_path(int choice)
{
    switch (choice) 
    {
        case 1:
            if (file_strings->txt_course_listfile) {
                free(file_strings->txt_course_listfile);
                file_strings->txt_course_listfile = NULL;
            }
            if (file_strings->bak_course_listfile) {
                free(file_strings->bak_course_listfile);
                file_strings->bak_course_listfile = NULL;
            }
            break;
        case 2:
            if (file_strings->course_countfile) {
                free(file_strings->course_countfile);
                file_strings->course_countfile = NULL;
            }
            break;
        case 3:
            if (file_strings->week_file) {
                free(file_strings->week_file);
                file_strings->week_file = NULL;
            }
            break;
        case 4:
            if (file_strings->txt_course_namefile) {
                free(file_strings->txt_course_namefile);
                file_strings->txt_course_namefile = NULL;
            }
            break;
        default:
            printf("Invalid choice. The number must be 1, 2, 3, or 4.\n");
            break;
    }
}
/********************************FILE PATHS END************************************************/

