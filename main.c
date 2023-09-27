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

#define ZERO_CHAR "0"
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
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char buffer[11];
    strftime(buffer, 11, "%m/%d/%Y", local_time);
    globals.the_date = buffer;
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


/*FIXME*/
// void check_for_count()
// {
//     const int ZERO = 0;
//     const int ONE = 1;
//     const int OPTION_TWO = 2; // this is the initialization option needed to get the file path

//     // char *filename = "/CourseCount.txt";
//     // char *path;
//     struct st_string *c_course_count = malloc(sizeof(struct st_string));
//     int i_course_count = ZERO;

//     // Set up required variables, and allocate memory for the whole file name
//     // int len = strlen(globals.directory_path) + strlen(filename) + ONE;
//     // path = malloc(len);

//     // // Combine the parts into the filename
//     // sprintf(path, "%s%s", globals.directory_path, filename);
//     init_file_path(OPTION_TWO);
//     if (file_strings.course_countfile == NULL)
//     {
//         perror("malloc() error"); // REPLACE with code to make the file if it does not exist
//         return EXIT_FAILURE;
//     }

    

//     // try block
//     if ((c_course_count->string = read_all_text(file_strings.course_countfile)) != NULL)
//     {
//         i_course_count = atoi(c_course_count->string);
//         globals.course_count = i_course_count;
//     }
//     // catch block
//     else
//     {
//         write_all_text(file_strings.course_countfile, ZERO_CHAR);
//         c_course_count->string = read_all_text(file_strings.course_countfile);
//         i_course_count = atoi(c_course_count->string);
//         globals.course_count = i_course_count;
//     }

//     // Free up what's no longer needed
//     free(c_course_count);
// }


void main_menu()
{
    const int ZERO = 0;
    const int ONE = 1;

    // one if there are courses, zero if there are no courses
    if (globals.course_count > ZERO)
        available_options(ONE);
    else
        available_options(ZERO);
}
void available_options(int options)
{
    // constants
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int FIVE = 5;

    int selectionInt;
    char *selection_string;

    globals.made_select = false;
    while (globals.made_select == false)
    {
        selectionInt = ZERO; // To get rid of IDE warning.
        if (options == ZERO)
        {
            // Option set for no available courses
            selection_dialogs(ONE);

            selection_string = cs_read_line();

            // Check that the user's input is valid
            if (!isdigit(selection_string[0]))
                printf("\nInvalid Input. Try again:\n");
            else
            {
                selectionInt = atoi(selection_string);
                free(selection_string);
                if (selectionInt == ONE || selectionInt == TWO)
                    main_options(selectionInt);
            }
        }
        if (options == ONE)
        {
            // Option set if courses are available
            selection_dialogs(TWO);

            selection_string = cs_read_line();
            // Check that the user's input is valid
            if (!isdigit(selection_string[0]))
                printf("\nInvalid Input. Try again:\n");
            else
            {
                selectionInt = atoi(selection_string);
                free(selection_string);
                if (selectionInt >= ONE && selectionInt <= FIVE)
                    main_options(selectionInt);
            }
        }
    }
}
void main_options(int selection_int)
{
    const int ZERO = 0;
    switch (selection_int)
    {
    case 1:
        globals.made_select = true;
        cs_console_clear();
        printf("\nWeekly Schedule Selected.\n");
        weekly_schedule();
        break;
    case 2:
        globals.made_select = true;
        cs_console_clear();
        printf("\nCreate new course selected.\n");
        create_course();
        break;
    case 3:
        globals.made_select = true;
        cs_console_clear();
        printf("\nCOURSES:\n");
        study_incrementer();
        clear_lists();
        select_course();
        study_course();
        break;
    case 4:
        globals.made_select = true;
        cs_console_clear();
        printf("Current date set at: %s", globals.the_date);
        printf("\nEnter a date, in your region's formatting, to force program to use it:");
        printf("\nExample: If date under the 10nth in the month: \nIf in US (12/2/2021): \"mm/d/yyyy\"\nIf in Germany: (2/12/2021)\"d/mm/yyyy\"\n");
        printf("\nExample: If the date is the 10nth in the month, or greater, then:\nIf in US (12/13/2021): \"mm/dd/yyyy\"\nIf in Germany (13/12/2021): \"dd/mm/yyyy\"\n");
        printf("\n\nEnter a date to use: ");
        globals.the_date = cs_read_line();
        break;
    case 5:
        globals.made_select = true;
        cs_console_clear();
        printf("\nGood Bye");
        exit(ZERO);
        break;
    default:
        printf("\nDefault case");
        globals.made_select = false;
        break;
    }
}
void selection_dialogs(int dialog)
{
    const int ZERO = 0;
    switch (dialog)
    {
    case 1:
        // For AvailableOptions()
        //  Option 1 if no courses available
        cs_console_clear();
        printf("\n\n\n1: Exit the program");
        printf("\n2: Create a new course\n");
        printf("\n\n\n\nEnter an option from the menu: ");
        break;
    case 2:
        // For AvailableOptions()
        //  Option 2 if courses are available
        cs_console_clear();
        printf("\nDate: %s", globals.the_date);
        printf("\n\n\n1: Weekly Schedule");
        printf("\n2: Create a new course");
        printf("\n3: Study a course");
        printf("\n4: Force GlieCLI to use a different date");
        printf("\n5: Exit the program\n");
        printf("\n\n\n\nSelect an option from the menu: ");
        break;
    case 3:
        // For StudyCourse()
        cs_console_clear();
        printf("\n\n\n\nNothing left to study for current topic today.");
        printf("\nEnter m to quit back to menu, or any other key to exit.");
        globals.response = cs_read_line();
        if (globals.response == "m")
        {
            cs_console_clear();
            globals.made_select = false;
            globals.new_left = ZERO;
            globals.current_left = ZERO;
            globals.late_left = ZERO;
            return;
        }
        else
        {
            cs_console_clear();
            exit(ZERO);
        }
        break;
    case 4:
        // For CreateCourse()
        cs_console_clear();
        printf("\n\n\n\n\n\nWhat is the name of the course? ");
        globals.course_name = cs_read_line();
        printf("\n\n\n\n\n\nHow many chapters are in the text book? ");
        globals.course_chapters = cs_read_line();
        creation_vars.chapters_int = atoi(globals.course_chapters);
        break;
    case 5:
        // For SetupData()
        printf("\n\n\n\n\n\nHow many sub-sections are in chapter %d: ", creation_vars.current_chapter); // Chapters are used here to make it easier to set the course up.
        creation_vars.subsection_string = cs_read_line();
        creation_vars.subsection_counter = atoi(creation_vars.subsection_string);
        break;
    case 6:
        // For SetupData()
        printf("\n\n\n\n\n\nHow many topics are in section %d.%d: ", creation_vars.current_chapter, creation_vars.current_subsection); // Chapters are used here to make it easier to set the course up.
        creation_vars.topic_count_string = cs_read_line();
        break;
    case 7:
        // For SetupData()
        printf("\n\n\n\n\n\nEnter the quantity of questions for section %s: ", creation_vars.new_top_name);
        creation_vars.p_count_string = cs_read_line();
        break;
    case 8:
        // For UpdateCounts()
        cs_console_clear();
        printf("\nFinished updating CourseCount.txt");
        cs_read_line();
        cs_console_clear();
        break;
    case 9:
        // For SelectCourse()
        printf("\n\nEnter a Course ID: ");
        break;
    case 10:
        // For StudyCourse()
        study_hud();
        break;
    case 11:
        // For StudyCourse()
        printf("\n\n\nQuantity answered correctly, or option choice: ");
        break;
    case 12:
        // For StudyCourse()
        study_hud();
        printf("\nInvalid Input:");
        printf("\n\n\nvalue exceeds number of problems or questions, \nor it is less than zero.");
        printf("\n\n\nQuantity answered correctly, or option choice: ");
        break;
    case 13:
        // For WeeklySchedule()
        weekly_dialog();
        break;
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
    const int ZERO_INT = 0;
    const double ZERO_DOUBLE = 0;
    const  int ONE = 1;
    const int FIVE = 5;
    const int SIX = 6;
    const int SEVEN = 7;
    const char NONE = "none"; // FIXME: Set up test to make this work.

    // 1) Initialization
    // Initializing topic linked list
    // 1 of 5: Initialization
    // template piece START 1
        // At initialization, always set the node count to ZERO and call the
        // node initializer.
        struct st_node *topic = malloc(sizeof(struct st_node));
        topic->total_nodes = ZERO_INT;
        topic = cs_node_intializer(topic);
    // template piece END

    // For CreateCourse()
    while (creation_vars.chapter_loop < creation_vars.chapters_int)
    {
        creation_vars.current_chapter = creation_vars.chapter_loop + ONE;
        selection_dialogs(FIVE);
        while (creation_vars.sub_loop < creation_vars.subsection_counter)
        {
            creation_vars.current_subsection = creation_vars.sub_loop + ONE;
            selection_dialogs(SIX);
            creation_vars.topic_counter = atoi(creation_vars.topic_count_string);
            globals.topic_count = globals.topic_count + creation_vars.topic_counter;

            // Link protocols 2 of 5 AND 3 of 5: combined node adding and page adding
            // This loop is where all of the essential data are set up
            // int index = ZERO_INT; <----- I don't think I need this.
            while (creation_vars.topic_loop < creation_vars.topic_counter)
            {
                // From step 2.
	            topics = cs_add(topics); // Removes need for check of step 3, but step 3 depends a prepared chain.


                // From step 3.
                struct st_topic_model *new_topic = malloc(sizeof(struct st_topic_model));
                topics->page = new_topic;

                // Data manipulation can occur within the loop
                if (creation_vars.topic_loop == ZERO_INT)
                    ((struct st_topic_model*)topics->page)->top_id = ZERO_INT;
                creation_vars.problem_count = ZERO_INT;
                creation_vars.current_topic = creation_vars.topic_loop + ONE;
                creation_vars.check = ZERO_INT; // will be used to see if Top_ID should increment.
                sprintf(creation_vars.topic_string, "%d", creation_vars.current_topic);



                // FIXME: Build a test environment to fix this. START
                char *period = ".";
                
                // FIXME: Check this. I think I have some 'int' types being passed without
                // converting to char in this line.
                int len = strlen(creation_vars.current_chapter) + strlen(period) + strlen(creation_vars.current_subsection) + strlen(period) + strlen(creation_vars.topic_string) + ONE;
                
                ((struct st_topic_model*)topics->page)->top_name = malloc(len);

                // FIXME: Check this. I think I have some 'int' types being passed without
                // converting to char in this line.
                sprintf(((struct st_topic_model*)topics->page)->top_name, "%s%s%s%s%s", creation_vars.current_chapter, period, creation_vars.current_subsection, period, creation_vars.topic_string);
                
                
                creation_vars.new_top_name = ((struct st_topic_model*)topics->page)->top_name;
                // FIXME: Build a test environment to fix this. END


                selection_dialogs(SEVEN);
                creation_vars.problem_count = atof(creation_vars.p_count_string);
                ((struct st_topic_model*)topics->page)->course_id = globals.course_count + ONE;               // int
                ((struct st_topic_model*)topics->page)->top_studied = false;                                  // bool
                ((struct st_topic_model*)topics->page)->next_date = NONE;                                     // string
                ((struct st_topic_model*)topics->page)->first_date = NONE;                                    // string
                ((struct st_topic_model*)topics->page)->num_problems = creation_vars.problem_count;           // the rest are type double
                ((struct st_topic_model*)topics->page)->num_correct = ZERO_DOUBLE;
                ((struct st_topic_model*)topics->page)->top_difficulty = ZERO_DOUBLE;
                ((struct st_topic_model*)topics->page)->top_repetition = ZERO_INT;
                ((struct st_topic_model*)topics->page)->interval_remaining = ZERO_DOUBLE;
                ((struct st_topic_model*)topics->page)->interval_length = ZERO_DOUBLE;
                ((struct st_topic_model*)topics->page)->engram_stability = ZERO_DOUBLE;
                ((struct st_topic_model*)topics->page)->engram_retrievability = ZERO_DOUBLE;
                

                ++creation_vars.topic_loop;
                creation_vars.check = creation_vars.topic_loop;
                if (creation_vars.check <= creation_vars.topic_counter)
                {
                    // Top_ID must be incremented before next iteration of loop, if more topics exist.
                    ++creation_vars.topic_id;
                    ((struct st_topic_model*)topics->page)->top_id = creation_vars.topic_id;
                }
            }
            creation_vars.topic_counter = ZERO_INT;
            creation_vars.topic_loop = ZERO_INT;
            ++creation_vars.sub_loop;
        }
        creation_vars.subsection_counter = ZERO_INT;
        creation_vars.sub_loop = ZERO_INT;
        ++creation_vars.chapter_loop;
    }
}
void produce_course()
{
    // struct st_node temp_node; <-- FIXME: Dont know why I put this here.
    const int ZERO = 0;
    const int ONE = 1;


    // 1 of 5: Initialization
    struct st_node *output = malloc(sizeof(struct st_node));
    output->total_nodes = ZERO;
    output = cs_node_intializer(output);


    // 2 of 5: Build out the node chain
    int total_topics = topics->total_nodes;
    int node_quantity = total_topics - ONE; // Already a first node. This is the number to add to the list.
    int index = ZERO; // Start with zero
	while (index < node_quantity)
	{
		output = cs_add(output);
		++index;
	}
    output = cs_element_at(output, ZERO); // Get back to node zero.


    // 3 of 5: Add pages to nodes    
    index = ZERO;
    while (index < total_topics)
    {
        // These two lines are what is essential within the page adding loop.
        struct st_string *temp = malloc(sizeof(struct st_string));
        output->page = &temp;



        topics = cs_element_at(topics, index);
        char *comma = ",";

        // Prepare the information so it can be written as text to a file.
        char *str_top_id;                // 1 int
        char *str_course_id;             // 2 int
        char *str_top_name = ((struct st_topic_model*)topics->page)->top_name;           // 3 string
        char *str_top_studied;           // 4 bool        
        char *str_next_date = ((struct st_topic_model*)topics->page)->next_date;         // 5 string
        char *str_first_date = ((struct st_topic_model*)topics->page)->first_date;        // 6 string
        char *str_num_problems;           // 7 double
        char *str_num_correct;            // 8 double
        char *str_top_difficulty;         // 9 double
        char *str_top_repetition;         // 10 int
        char *str_interval_remaining;     // 11 double
        char *str_interval_length;        // 12 double
        char *str_engram_stability;       // 13 double
        char *str_engram_retrievability;  // 14 double


        sprintf(str_top_id, "%d", ((struct st_topic_model*)topics->page)->top_id);                                      // int       1
        sprintf(str_course_id, "%d", ((struct st_topic_model*)topics->page)->course_id);                                // int       2
        sprintf(str_top_studied, "%d", ((struct st_topic_model*)topics->page)->top_studied);                            // bool      4
        sprintf(str_num_problems, "%f", ((struct st_topic_model*)topics->page)->num_problems);                          // double    7
        sprintf(str_num_correct, "%f", ((struct st_topic_model*)topics->page)->num_correct);                            // double    8
        sprintf(str_top_difficulty, "%f", ((struct st_topic_model*)topics->page)->top_difficulty);                      // double    9
        sprintf(str_top_repetition, "%d", ((struct st_topic_model*)topics->page)->top_repetition);                      // int       10
        sprintf(str_interval_remaining, "%f", ((struct st_topic_model*)topics->page)->interval_remaining);              // double    11
        sprintf(str_interval_length, "%f", ((struct st_topic_model*)topics->page)->interval_length);                    // double    12 
        sprintf(str_engram_stability, "%f", ((struct st_topic_model*)topics->page)->engram_stability);                  // double    13
        sprintf(str_engram_retrievability, "%f", ((struct st_topic_model*)topics->page)->engram_retrievability);        // double    14

        // Data manipulation can occur within the loop
        // Allocate memory for each string
        int len = strlen(str_top_id) + strlen(comma) + strlen(str_course_id) + strlen(comma) + strlen(((struct st_topic_model*)topics->page)->top_name) + strlen(comma) + strlen(str_top_studied) + strlen(comma) + strlen(((struct st_topic_model*)topics->page)->next_date) + strlen(comma) + strlen(((struct st_topic_model*)topics->page)->first_date) + strlen(comma) + strlen(str_num_problems)  + strlen(comma) + strlen(str_num_correct)  + strlen(comma) + strlen(str_top_difficulty)  + strlen(comma) + strlen(str_top_repetition)  + strlen(comma) + strlen(str_interval_remaining)  + strlen(comma) + strlen(str_interval_length)  + strlen(comma) + strlen(str_engram_stability)  + strlen(comma) + strlen(str_engram_retrievability)  + ONE;
        ((struct st_string*)output->page)->string = malloc(len);
        sprintf(((struct st_string*)output->page)->string, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", str_top_id, comma, str_course_id, comma, str_top_name, comma, str_top_studied, comma, str_next_date, comma, str_first_date, comma, str_num_problems, comma, str_num_correct, comma, str_top_difficulty, comma, str_top_repetition, comma, str_interval_remaining, comma, str_interval_length, comma, str_engram_stability, comma, str_engram_retrievability );

        // Part 3: Make sure to go to the next node to add a new page.
        // In a loop that combines steps 2 and 3, this can simply be done by adding
        // a new node to the chain before a page is added to the node.
        ++index;
        if (index < output->total_nodes)
            output = cs_element_at(output, index);
    }
    index = 0;
    output = cs_element_at(output, index); // Probably want to go back to node zero

    /* Write to File START */
    // For Linux
    char *slash = "/";
    char *txt_format = ".txt";

    int len = strlen(globals.directory_path) + strlen(slash) + strlen(globals.course_name) + strlen(txt_format) + ONE;
    creation_vars.file_path = malloc(len);
    sprintf(creation_vars.file_path, "%s%s%s%s", globals.directory_path, slash, globals.course_name, txt_format);


    // File.WriteAllLines(creation_vars.filePath, output);
    cs_write_all_lines(creation_vars.file_path, output, output->total_nodes);

    // Now store the list file's path:
    char *file_name = "CourseList";
    len = strlen(globals.directory_path) + strlen(slash) + strlen(file_name) + strlen(txt_format) + ONE;
    creation_vars.list_file = malloc(len);
    sprintf(creation_vars.list_file, "%s%s%s%s", globals.directory_path, slash, file_name, txt_format);
    /* Write to file END */

    // 4 of 5: Free pages from the nodes
    index = ZERO;
    while (index < output->total_nodes)
    {
        output = cs_element_at(output, index);
        free((struct st_string*)output->page);
        ++index;
    }
    index = 0;
    output = cs_element_at(output, index); // Probably want to go back to node zero


    
    // 5 of 5: Destroy the node chain
    // Test to see if I need the '*' symbol later
    cs_clear_nodes(output);
    free(output);
    
    // I don't think I need this part anymore.
    // /* Now free the nodes */
    // index = ZERO;
    // int index_back = total_topics - ONE; // Have to work from last node to first to make sure I free all the nodes.
    // struct st_node *temp_node;
    // while (index < total_topics)
    // {
    //     temp_node = cs_element_at(output, (index_back - ONE));
    //     output = cs_element_at(output, index_back);
    //     free(output);
    //     output = &temp_node;
    //     ++index;
    //     --index_back;
    // }

    // STOPPED HERE
}


/*FIXME: Convert the int to a char in a way that the char could display the value of the
int, but as characters.

example: int var = 65; <-- I want printf to display 65, but from the char its converted to.
*/
// I dont think this one needs the 5 step protocols either.
void update_counts()
{ 
    const int ONE = 1;
    const int EIGHT = 8;
    int total_nodes = 0;
    int new_id = globals.course_count;
    char new_id_char = (char)
    char *path;
    char *course_count;
    char *list_contents;
    char *slash = "/";
    char *txt_format = ".txt";
    char *comma = ",";

    // List<string> contentList = new List<string>();
    struct st_node *content_list = malloc(sizeof(struct st_node));
    struct st_string *temp_string = malloc(sizeof(struct st_string));
    
    // Make a new ID, prepare the information for the file
    ++new_id;
    int len = strlen(new_id) + strlen(comma) + strlen(globals.course_name) + strlen(txt_format) + strlen(comma) + strlen(creation_vars.file_path) + ONE;
    list_contents = malloc(len);
    sprintf(list_contents, "%s%s%s%s%s%s", new_id, comma, globals.course_name, txt_format, comma, creation_vars.file_path);

    
    // Prepare the variable for use with the functions
    temp_string = &list_contents;
    content_list->page = &temp_string;
    content_list->index = 0;
    content_list->total_nodes = ONE;
    total_nodes = content_list->total_nodes;

    // If the file does not exist, then create it and save the course count to it.
    if (cs_file_exists(creation_vars.list_file))
        course_listpath();
    else
        cs_write_all_lines(creation_vars.list_file, content_list, total_nodes);

    // Store the Unix style path to the file
    char *count_filename = "CourseCount.txt";
    len = strlen(globals.directory_path) + strlen(slash) + strlen(count_filename) + ONE;
    path = malloc(len);
    sprintf(path, "%s%s%s", globals.directory_path, slash, count_filename);

    // Get the old count, and convert it to an int so it can be updated
    course_count = cs_read_all_text(path);
    globals.course_count = atoi(course_count);
    
    // Update the course count, then convert the updated count back to a string
    // for file processing.
    ++globals.course_count;
    course_count = cs_to_string(globals.course_count);

    // Write the new count to the file.
    // Free the allocated memory
    // Go to selection dialog #EIGHT
    cs_write_all_text(path, course_count);
    free(content_list);
    free(temp_string);
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
// void add_course_tolist(const char *file_path, const char *file_pathtwo, const char *course_filepath)
// {
//     const int ZERO = 0;
//     const int ONE = 1;
//     int course_id = globals.course_count;
//     ++course_id;
//     char *comma = ",";
//     char *txt_format = ".txt";
//     char *slash = "/";
//     // char *temp_string;


//     /* Not as many steps because it is using read all lines, or cs_ral_tolist */
//     // List<string> lines = new List<string>();
//     // 1 of 5: Initialization
//     // At initialization, always set the node count to ZERO and call the
//     // node initializer.
//     struct st_node *lines = malloc(sizeof(struct st_node));
//     lines->total_nodes = ZERO;
//     lines = cs_node_intializer(lines);



//     struct st_string *temp_string = malloc(sizeof(struct st_string));
    
//     if (cs_file_exists(file_path))
//         lines = cs_ral_tolist(file_path);

//     // lines.Add($"{course_id},{globals.coursename}.txt,{course_filepath}");
//     int len = strlen(course_id) + strlen(comma) + strlen(globals.course_name) + strlen(txt_format) + strlen(comma) + strlen(course_filepath) + ONE;
//     temp_string = malloc(len);
//     sprintf(temp_string, "%s%s%s%s%s%s", course_id, comma, globals.course_name, txt_format, comma, course_filepath);
    
//     int total_nodes = lines->total_nodes;
//     --total_nodes;
//     lines = cs_element_at(lines, total_nodes);
//     lines = cs_add(lines);
//     lines->page = &temp_string;
    
//     // Go back to the start of the linked list so I can write everything from it to a file
//     int index = ZERO;
//     lines = cs_element_at(lines, index);
//     cs_write_all_lines(file_pathtwo, lines, lines->total_nodes);
//     cs_write_all_lines(file_path, lines, lines->total_nodes);

//     /* First free the pages */
//     index = ZERO;
//     ++total_nodes;
//     while (index < total_nodes)
//     {
//         lines = cs_element_at(lines, index);
//         free((struct st_string*)lines->page);
//         ++index;
//     }

//     /* Now free the nodes */
//     cs_clear_nodes(lines);
// }


// 9-11-2023
// Continue from the next function. 
// Need to use other PC.
// This one is too slow while ffmpeg is being used

// Clean this function up.
// DOES NEED THE 5 PROTOCOLS
void select_course()
{
    // string filePath;
    // string selectionString;
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int NINE = 9;
    const int OPTION_FOUR = 4; // For the course name file path initialization
    // char *file_path;
    char *selection_string;


    int selection_int = ZERO;
    bool valid_input = false;

    // file_path = $"{globals.DirectoryPath}//CourseList.txt";
    // Make a string globally available to replace this
    // to reduce the risk of memory leaks <--- DONE
    // file_strings->txt_course_listfile;



    /* Temp file path storage START */
    // char *course_filepath;
    // char *slash = "/";
    // char *course_file = "CourseList";
    // char *txt_format = ".txt";

    // int len_one = strlen(globals.directory_path) + strlen(slash) + strlen(course_file) + strlen(txt_format) + 1;
    // file_path = malloc(len_one); // Free this since I called malloc
    // sprintf(file_path, "%s%s%s%s", globals.directory_path, slash, course_file, txt_format);
    /* Temp file path storage END */

    
    // Before 5 protocols
    // List<CourseListModel> completeList = new List<CourseListModel>();
    // struct st_node *complete_list = malloc(sizeof(struct st_node));

    // 1 of 5: Initialization
    // template piece START 1
    // At initialization, always set the node count to ZERO and call the
    // node initializer.
    struct st_node *complete_list = malloc(sizeof(struct st_node));
    complete_list->total_nodes = ZERO;
    complete_list = cs_node_intializer(complete_list);
    // template piece END
    
    // List<string> lines = new List<string>();
    struct st_node *lines = malloc(sizeof(struct st_node));


    // lines = File.ReadAllLines(filePath).ToList();
    lines = cs_ral_tolist(file_strings.txt_course_listfile);
    

    // 2 of 5: Build out the node chain
    // This can be within a data preparation loop that is for a new page to be added to a new link
    // template piece START 2
    // Link a list of nodes together
    int total_nodes = lines->total_nodes;
    int index = ZERO; // start index at zero.
    // node_quantity is the number of nodes to add.
    while (index < total_nodes)
    {
        complete_list = cs_add(complete_list);
        ++index;
    }
    index = ZERO;
    complete_list = cs_element_at(complete_list, index); // Probably want to go back to node zero
    // template piece END



    // 3 of 5: Add pages to nodes
    // This step can be combined with step 2.
    // template piece START 3
    // Add the links to the nodes
    complete_list = cs_element_at(complete_list, ZERO);
    index = ZERO; // Start with zero since we now need to iterate through the elements starting at zero
    while (index < complete_list->total_nodes)
    {

        // Part 1: These two lines are what is essential within the page adding loop.
        struct st_node *entries = malloc(sizeof(struct st_node));
        struct st_course_list_model *new_list = malloc(sizeof(struct st_course_list_model));
        char token[] = ',';

        lines = cs_element_at(lines, index);
        entries = cs_list_split(lines->page, token);
        complete_list->page = new_list;
        
        // Part 2: Data manipulation can occur within the loop
        // Prepare a page for a node in the list
        // ((struct st_course_list_model*)complete_list->page)->


        entries = cs_element_at(entries, ZERO);
        ((struct st_course_list_model*)complete_list->page)->course_id = atoi((struct st_string*)entries->page);
        entries = cs_element_at(entries, ONE);
        ((struct st_course_list_model*)complete_list->page)->course_name = (struct st_string*)entries->page;
        entries = cs_element_at(entries, TWO);
        ((struct st_course_list_model*)complete_list->page)->file_path = (struct st_string*)entries->page;

        // Add a page to a node of complete_list
        complete_list = cs_element_at(complete_list, index);
        complete_list->page = &new_list;




        // Part 3: Make sure to go to the next node to add a new page.
        // In a loop that combines steps 2 and 3, this can simply be done by adding
        // a new node to the chain before a page is added to the node.
        ++index;
        if (index < complete_list->total_nodes)
            complete_list = cs_element_at(complete_list, index);


        // Rest of code is for some kind of test I'll run later. uncomment when ready.
        /* TEST START */
        // entries = cs_element_at(entries, ZERO);
        // free((struct st_string*)entries->page);
        // entries = cs_element_at(entries, ONE);
        // free((struct st_string*)entries->page);
        // entries = cs_element_at(entries, TWO);

        // Might should keep these until complete_list is done with the pages.
        // STOPPED HERE 9-11-2023
        free((struct st_string*)entries->page);
        cs_clear_nodes(entries);


        printf("\n\nWrite some test code to check needed values of complete list, \n");
        printf("\nto make sure I didn't erase them after freeing the \"entries\" list after program is converted.");
        getchar();
        /* TEST END */
    }
    index = ZERO;
    complete_list = cs_element_at(complete_list, index); // Probably want to go back to node zero

    /* TEST START */
    if (total_nodes != complete_list->total_nodes)
    {
        printf("\n\nNODE COUNTS NOT EQUAL\n\n");
        printf("\ntotal_nodes = %d\ncomplete_list->total_nodes = %d\n", total_nodes, complete_list->total_nodes);
        getchar();
    }
    else
    {
        printf("\n\nNODE COUNTS EQUAL. DELETE THE TEST FROM CODE\n\n");
        printf("\ntotal_nodes = %d\ncomplete_list->total_nodes = %d\n", total_nodes, complete_list->total_nodes);
        getchar();
    }
    /* TEST END */

    
    
    // foreach (var course in completeList)
    //    Console.WriteLine($"Course ID: {course.Course_ID} - Course Name: {course.Course_Name}");
    index = ZERO;
    while (index < total_nodes)
    {
        complete_list = cs_element_at(complete_list, index);
        printf("\nCourse ID: %d - Course Name: %s\n", ((struct st_course_list_model*)complete_list->page)->course_id, ((struct st_course_list_model*)complete_list->page)->course_name);
        ++index;
    }

    
    while (valid_input == false)
    {
        // selection_dialogs(Constants.NINE_INT);
        // selection_string = cs_read_line();
        selection_dialogs(NINE);
        selection_string = cs_read_line();
        // selectionInt = Convert.ToInt32(selectionString);
        selection_int = cs_to_int(selection_string);

        if (selection_int != NULL)
        {
            valid_input = true;
        }
        else
        {
            printf("\nInvalid selection.\n");
            valid_input = false;
        }


        if (valid_input == true)
        {
            --selection_int;
            int test_var = selection_int + ONE;
            // Clear the console screen just because it's nice to do
            cs_console_clear();


            /* Verify that the couse the user selected is an available option */


            // Check that might be more efficient since I forgot what I wrote it the other way for
            //if (total_nodes <= complete_list->total_nodes)
            if((selection_int < complete_list->total_nodes) && (selection_int >= ZERO))
            {
                complete_list = cs_element_at(complete_list, selection_int);
                if (test_var == ((struct st_course_list_model*)complete_list->page)->course_id)
                {
                    globals.file_path = ((struct st_course_list_model*)complete_list->page)->file_path;
                    globals.course_name = ((struct st_course_list_model*)complete_list->page)->course_name;
                    
                    // First free anything that may be in this filepath.
                    free_file_path(OPTION_FOUR);
                    // Now initialize the filepath for the selected course
                    init_file_path(OPTION_FOUR);
                    
                    valid_input = true;
                }
                else
                {
                    valid_input = false;
                    printf("\nInvalid selection.\n");
                }
                
            }
            else
            {
                valid_input = false;
                printf("\nInvalid selection.\n");
            }


            // Check that may not be as good as the commented out code above
            // unless I need it to list out all of the courses here for some reason
            // DELETE this comment if this code is the one that is actually needed
            // index = ZERO;
            // while (index < total_nodes)
            // {
            //     complete_list = cs_element_at(complete_list, index);
            //     if (test_var == ((struct st_course_list_model*)complete_list->page)->course_id)
            //     {
            //         complete_list = cs_element_at(complete_list, selection_int);
            //         globals.file_path = ((struct st_course_list_model*)complete_list->page)->file_path;
            //         globals.course_name = ((struct st_course_list_model*)complete_list->page)->course_name;
                    
                    
            //         // initialize the global complete file path to the course file
            //         file_strings->txt_course_namefile;
                    
                    
                    
                    
                    
            //         valid_input = true;

            //         /* TEST IF LOOP NEEDED START */
            //         printf("\nWas this loop needed? Check if the job can be don with the\n");
            //         printf("simple if statment that is commented out above and check the ressults");
            //         getchar();
            //         /* TEST IF LOOP NEEDED END */
            //     }
            //     else
            //     {
            //         valid_input = false;
            //         printf("\nInvalid selection.\n");
            //     }
            //     ++index;
            // }
        }
    }


    // 4 of 5: Free pages from the nodes
    // template piece START 4
    // Clear links

    // lines 
    index = ZERO;
    while(index < lines->total_nodes)
    {
        lines = cs_element_at(lines, index);
        free((struct st_string*)lines->page);
        ++index;
    }
    index = ZERO;
    lines = cs_element_at(lines, index); // Probably want to go back to node zero

    // complete_list
    // 4 of 5: Free pages from the nodes
    // template piece START 4
    // Clear links
    index = ZERO;
    while(index < complete_list->total_nodes)
    {
        complete_list = cs_element_at(complete_list, index);
        free((struct st_course_list_model*)complete_list->page);
        ++index;
    }
    index = ZERO;
    complete_list = cs_element_at(complete_list, index); // Probably want to go back to node zero
    // template piece END
    // template piece END


    // FIXME: Check that cs_clear_nodes accepts these list types
    // 5 of 5: Destroy the node chain
    // Test to see if I need the '*' symbol later
    cs_clear_nodes(lines);
    cs_clear_nodes(complete_list);
    free(lines);
    free(complete_list);

    // Remove this last free() function once I have global strings
    // needed to reduce possible memory leaks
    // free(file_path);
    /* FREE THE MEMORY END */
}
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

                    if (study_vars.response == "m")
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
    
    /* REPLACE WHEN IM READY START */
    printf("\n\nReplace the DateTime code when finished converting the rest of the program\n\n");
    getchar();
    DateTime today = DateTime.Parse(globals.TheDate);
    DateTime next_date = today.AddDays(days);
    TopicsList.ElementAt(globals.TopicID).Next_Date = nextDate.ToString("d");
    /* REPLACE WHEN IM READY START */

    if (((struct st_topic_model*)topics_list->page)->top_studied = false)
        ((struct st_topic_model*)topics_list->page)->top_studied = true;
}
void save_progress()
{
    const  int ZERO = 0;
    const int ONE = 1;
    int total_topics = topics_list->total_nodes;
    int index = ZERO;

    // Make sure the linked list is at the required node
    topics_list = cs_element_at(topics_list, globals.topic_id);



    // List<string> output = new List<string>();
    struct st_node *output = malloc(sizeof(struct st_node));

    // Output already has a node from initialization, so the index is equal to 
    // one, so as not to receive an additional node in the loop.
    index = ONE;
    while (index < total_topics)
    {
        output = cs_add(output);
        ++index;
    }
    index = ZERO;
    output = cs_element_at(output, index);


    // add all the pages to the linked list
    int index = ZERO;
    while (index < total_topics)
    {
        // Make sure the each node of the linked list is iterated through
        topics = cs_element_at(topics, index);

        // Allocate the memory for the strings. There are four because sprintf() needs less arguments
        struct st_string *temp = malloc(sizeof(struct st_string));                           // temp does not get freed here because its used as the pages of the linked list
        struct st_string *temp_one = malloc(sizeof(struct st_string));                       // temp does not get freed here because its used as the pages of the linked list
        struct st_string *temp_two = malloc(sizeof(struct st_string));                       // temp does not get freed here because its used as the pages of the linked list
        struct st_string *temp_three = malloc(sizeof(struct st_string));                     // temp does not get freed here because its used as the pages of the linked list
        struct st_string *temp_four = malloc(sizeof(struct st_string));                      // temp does not get freed here because its used as the pages of the linked list
        
        
        struct st_string *str_top_id = malloc(sizeof(struct st_string));                 // 1 int
        struct st_string *str_course_id = malloc(sizeof(struct st_string));              // 2 int
        struct st_string *str_top_name = malloc(sizeof(struct st_string));               // 3 string
        struct st_string *str_top_studied = malloc(sizeof(struct st_string));            // 4 bool
        struct st_string *str_next_date = malloc(sizeof(struct st_string));              // 5 string
        struct st_string *str_first_date = malloc(sizeof(struct st_string));             // 6 string
        struct st_string *str_num_problems = malloc(sizeof(struct st_string));           // 7 double
        struct st_string *str_num_correct = malloc(sizeof(struct st_string));            // 8 double
        struct st_string *str_top_difficulty = malloc(sizeof(struct st_string));         // 9 double
        struct st_string *str_top_repetition = malloc(sizeof(struct st_string));         // 10 int
        struct st_string *str_interval_remaining = malloc(sizeof(struct st_string));     // 11 double
        struct st_string *str_interval_length = malloc(sizeof(struct st_string));        // 12 double
        struct st_string *str_engram_stability = malloc(sizeof(struct st_string));       // 13 double
        struct st_string *str_engram_retrievability = malloc(sizeof(struct st_string));  // 14 double

        // Store the information as strings of characters
        str_top_name = ((struct st_topic_model*)topics->page)->top_name;                                                // 3 string
        str_next_date = ((struct st_topic_model*)topics->page)->next_date;                                              // 5 string
        str_first_date = ((struct st_topic_model*)topics->page)->first_date;                                            // 6 string
        sprintf(str_top_id, "%d", ((struct st_topic_model*)topics->page)->top_id);                                      // int       1
        sprintf(str_course_id, "%d", ((struct st_topic_model*)topics->page)->course_id);                                // int       2
        sprintf(str_top_studied, "%d", ((struct st_topic_model*)topics->page)->top_studied);                            // bool      4
        sprintf(str_num_problems, "%f", ((struct st_topic_model*)topics->page)->num_problems);                          // double    7
        sprintf(str_num_correct, "%f", ((struct st_topic_model*)topics->page)->num_correct);                            // double    8
        sprintf(str_top_difficulty, "%f", ((struct st_topic_model*)topics->page)->top_difficulty);                      // double    9
        sprintf(str_top_repetition, "%d", ((struct st_topic_model*)topics->page)->top_repetition);                      // int       10
        sprintf(str_interval_remaining, "%f", ((struct st_topic_model*)topics->page)->interval_remaining);              // double    11
        sprintf(str_interval_length, "%f", ((struct st_topic_model*)topics->page)->interval_length);                    // double    12 
        sprintf(str_engram_stability, "%f", ((struct st_topic_model*)topics->page)->engram_stability);                  // double    13
        sprintf(str_engram_retrievability, "%f", ((struct st_topic_model*)topics->page)->engram_retrievability);        // double    14

        // Allocate memory for each string, then store a copy of the previously combined strings. 
        // There are four parts to this because sprintf() recieves too many arguments if I do it all at once.
        // My code editor still said sprintf() had too many arguments, but once I restarted intelliSense 
        // in my code editor, the warning for too many arguments went away. It's possible I did not have
        // to do it this way.

        // Leaving this here for now in case I missed something.
        // int len_two = strlen(str_top_id) + strlen(file_constants.comma) + strlen(str_course_id) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->top_name) + strlen(file_constants.comma) + strlen(str_top_studied) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->next_date) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->first_date) + strlen(file_constants.comma) + strlen(str_num_problems)  + strlen(file_constants.comma) + strlen(str_num_correct)  + strlen(file_constants.comma) + strlen(str_top_difficulty)  + strlen(file_constants.comma) + strlen(str_top_repetition)  + strlen(file_constants.comma) + strlen(str_interval_remaining)  + strlen(file_constants.comma) + strlen(str_interval_length)  + strlen(file_constants.comma) + strlen(str_engram_stability)  + strlen(file_constants.comma) + strlen(str_engram_retrievability)  + ONE;
        // int len_three = strlen(str_top_id) + strlen(file_constants.comma) + strlen(str_course_id) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->top_name) + strlen(file_constants.comma) + strlen(str_top_studied) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->next_date) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->first_date) + strlen(file_constants.comma) + strlen(str_num_problems)  + strlen(file_constants.comma) + strlen(str_num_correct)  + strlen(file_constants.comma) + strlen(str_top_difficulty)  + strlen(file_constants.comma) + strlen(str_top_repetition)  + strlen(file_constants.comma) + strlen(str_interval_remaining)  + strlen(file_constants.comma) + strlen(str_interval_length)  + strlen(file_constants.comma) + strlen(str_engram_stability)  + strlen(file_constants.comma) + strlen(str_engram_retrievability)  + ONE;
        // int len_four = strlen(str_top_id) + strlen(file_constants.comma) + strlen(str_course_id) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->top_name) + strlen(file_constants.comma) + strlen(str_top_studied) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->next_date) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->first_date) + strlen(file_constants.comma) + strlen(str_num_problems)  + strlen(file_constants.comma) + strlen(str_num_correct)  + strlen(file_constants.comma) + strlen(str_top_difficulty)  + strlen(file_constants.comma) + strlen(str_top_repetition)  + strlen(file_constants.comma) + strlen(str_interval_remaining)  + strlen(file_constants.comma) + strlen(str_interval_length)  + strlen(file_constants.comma) + strlen(str_engram_stability)  + strlen(file_constants.comma) + strlen(str_engram_retrievability)  + ONE;
        // temp_one->string = malloc(temp_one);
        // temp_two->string = malloc(temp_two);
        // temp_three->string = malloc(temp_three);
        // temp_four->string = malloc(len_four);
        // sprintf(temp_one->string, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", str_top_id, file_constants.comma, str_course_id, file_constants.comma, str_top_name, file_constants.comma, str_top_studied, file_constants.comma, str_next_date, file_constants.comma, str_first_date, file_constants.comma, str_num_problems, file_constants.comma, str_num_correct, file_constants.comma, str_top_difficulty, file_constants.comma, str_top_repetition, file_constants.comma, str_interval_remaining, file_constants.comma, str_interval_length, file_constants.comma, str_engram_stability, file_constants.comma, str_engram_retrievability );
        // sprintf(temp_two->string, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", str_top_id, file_constants.comma, str_course_id, file_constants.comma, str_top_name, file_constants.comma, str_top_studied, file_constants.comma, str_next_date, file_constants.comma, str_first_date, file_constants.comma, str_num_problems, file_constants.comma, str_num_correct, file_constants.comma, str_top_difficulty, file_constants.comma, str_top_repetition, file_constants.comma, str_interval_remaining, file_constants.comma, str_interval_length, file_constants.comma, str_engram_stability, file_constants.comma, str_engram_retrievability );
        // sprintf(temp_three->string, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", str_top_id, file_constants.comma, str_course_id, file_constants.comma, str_top_name, file_constants.comma, str_top_studied, file_constants.comma, str_next_date, file_constants.comma, str_first_date, file_constants.comma, str_num_problems, file_constants.comma, str_num_correct, file_constants.comma, str_top_difficulty, file_constants.comma, str_top_repetition, file_constants.comma, str_interval_remaining, file_constants.comma, str_interval_length, file_constants.comma, str_engram_stability, file_constants.comma, str_engram_retrievability );
        // sprintf(temp_four->string, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", str_top_id, file_constants.comma, str_course_id, file_constants.comma, str_top_name, file_constants.comma, str_top_studied, file_constants.comma, str_next_date, file_constants.comma, str_first_date, file_constants.comma, str_num_problems, file_constants.comma, str_num_correct, file_constants.comma, str_top_difficulty, file_constants.comma, str_top_repetition, file_constants.comma, str_interval_remaining, file_constants.comma, str_interval_length, file_constants.comma, str_engram_stability, file_constants.comma, str_engram_retrievability );


        // LENGTHS
        int len_one = strlen(str_top_id) + strlen(file_constants.comma) + strlen(str_course_id) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->top_name) + strlen(file_constants.comma) + ONE;
        int len_two = strlen(str_top_studied) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->next_date) + strlen(file_constants.comma) + strlen(((struct st_topic_model*)topics->page)->first_date) + strlen(file_constants.comma) + strlen(str_num_problems)  + ONE;
        int len_three = strlen(file_constants.comma) + strlen(str_num_correct)  + strlen(file_constants.comma) + strlen(str_top_difficulty)  + strlen(file_constants.comma) + strlen(str_top_repetition) + strlen(file_constants.comma) + ONE;
        int len_four = strlen(str_interval_remaining) + strlen(file_constants.comma) + strlen(str_interval_length) + strlen(file_constants.comma) + strlen(str_engram_stability)  + strlen(file_constants.comma) + strlen(str_engram_retrievability)  + ONE;


        // MEMORY ALLOCATIONS
        temp_one->string = malloc(len_one);
        temp_two->string = malloc(len_two);
        temp_three->string = malloc(len_three);
        temp_four->string = malloc(len_four);


        // TEMP STORAGE
        sprintf(temp_one->string, "%s%s%s%s%s%s", str_top_id, file_constants.comma, str_course_id, file_constants.comma, ((struct st_topic_model*)topics->page)->top_name, file_constants.comma);
        sprintf(temp_two->string, "%s%s%s%s%s%s%s", str_top_studied, file_constants.comma, ((struct st_topic_model*)topics->page)->next_date, file_constants.comma, ((struct st_topic_model*)topics->page)->first_date, file_constants.comma, str_num_problems);
        sprintf(temp_two->string, "%s%s%s%s%s%s%s", file_constants.comma, str_num_correct, file_constants.comma, str_top_difficulty, file_constants.comma, str_top_repetition, file_constants.comma);
        sprintf(temp_two->string, "%s%s%s%s%s%s%s", str_interval_remaining, file_constants.comma, str_interval_length, file_constants.comma, str_engram_stability, file_constants.comma, str_engram_retrievability);
        
        // final string
        int len = strlen(temp_one->string) + strlen(temp_two->string) + strlen(temp_three->string) + strlen(temp_four->string) + ONE;
        temp->string = malloc(len);
        sprintf(temp->string, "%s%s%s%s", temp_one->string, temp_two->string, temp_three->string, temp_four->string);
        

        // Store the string in a page linked to a node
        output = cs_element_at(output, index);
        output->page = &temp;

        // Free the allocated memory for the temporary strings
        free(str_top_id);
        free(str_course_id);
        free(str_top_name);
        free(str_top_studied);
        free(str_next_date);
        free(str_first_date);
        free(str_num_problems);
        free(str_num_correct);
        free(str_top_difficulty);
        free(str_top_repetition);
        free(str_interval_remaining);
        free(str_interval_length);
        free(str_engram_stability);
        free(str_engram_retrievability);

        // Free the four temp initializers
        free(temp_one);
        free(temp_two);
        free(temp_three);
        free(temp_four);
    }
    
    printf("\n\n\n\n\n\nSaving Work.\n");

    // Use Unix style directory structure and store the data in a text file
    cs_write_all_lines(file_strings->txt_course_namefile, output, output->total_nodes);
    cs_write_all_lines(file_strings->bak_course_namefile, output, output->total_nodes);

    printf("\nWork Saved.\n");
    getchar();

    // free the allocated memory for the pages of each node of the output linked list
    index = ZERO;
    while (index < total_topics)
    {
        output = cs_element_at(output, index);
        free((struct st_string*)output->page);
        ++index;
    }

    // Free the nodes
    cs_clear_nodes(output);
}
void change_topic_questions()
{
    const int ZERO = 0;
    const int OPTION_TEN = 10;

    char *num_total_string;
    double num_total_double = ZERO;
    bool test = false;
    int validator = ZERO; // to check if input from the user is a number.
    
    
    while (test == false)
    {
        cs_console_clear();
        printf("\nEnter new number of TOTAL questions:\n");
        num_total_string = cs_read_line();
        
        if (cs_check_double(num_total_string) == ZERO)
        {
            num_total_double = atof(num_total_string);
            test = true;
        }
        else
        {
            cs_console_clear();
            test = false;
            printf("\n\n\nInvalid Input\n\nPress Enter to Continue");
            getchar();
            SelectionDialogs(OPTION_TEN);
        }
    }

    // Store the new number of questions into the required variable
    topics_list = cs_element_at(topics_list, globals.topic_id);
    ((struct st_topic_model*)topics_list->page)->num_problems = num_total_double;
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
    // List<string> lines = new List<string>();
    struct st_node *lines = malloc(sizeof(struct st_node));


    // lines = File.ReadAllLines(study_vars.filePath).ToList();
    lines = cs_ral_tolist(study_vars.file_path);



    study_vars.line_count = total_nodes = lines->total_nodes;
    
    
    // First prepare the linked list nodes to add the pages in the next loop
    // Set index equal to one, because topics_list is already initialized with a node
    index = ONE;
    while (index < total_nodes)
    {
        topics_list = cs_add(topics_list);
        ++index;
    }
    
    

    // Now add the pages to the nodes of the list    
    index = ZERO;
    while (index < total_nodes)
    {
        // string[] entries = line.Split(',');
        // TopicModel new_list = new TopicModel();
        
        // Initialize
        struct st_node *entries = malloc(sizeof(struct st_node));
        struct st_topic_model new_list;
        const char TOKEN[] = ',';
        const char TRUE_CHAR[] = "TRUE";
        lines = cs_element_at(lines, index);
        entries = cs_list_split(lines->page, TOKEN);
        
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


        // Go to the necessary node of the linked list
        topics_list = cs_element_at(topics_list, index);
        topics_list->page = &new_list;
        ++index;
    }
}
void study_dates()
{
    //Called From study_course()
    // Retry Studied topic_id's section (these are study sessions that were missed)
    const int ZERO = 0;
    int total_nodes = ZERO;
    const int TODAY = ZERO;

    study_vars.index = ZERO;
    globals.late_left = ZERO;

    total_nodes = topics_list->total_nodes;
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            topics_list = cs_element_at(topics_list, study_vars.index);
            study_vars.date_as_string = ((struct st_topic_model*)topics_list->page)->next_date;

            // study_vars.topicDate = DateTime.Parse(study_vars.dateAsString);
            study_vars.topic_date = study_vars.date_as_string;

            // Detect if the topic date is the same, before, or after the current date for the user.
            study_vars.date_compare = cs_date_compare(study_vars.topic_date, study_vars.today);


            if (study_vars.date_compare < TODAY)
            {
                // Add a topic id to the list
                to_study = cs_add(to_study);
                ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;

                // to display number of late topics left to study
                ++globals.late_left;
            }
        }
        ++study_vars.index;
    }
    // Studied topic-id's scheduled for today section
    study_vars.index = ZERO;
    globals.current_left = ZERO;
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            topics_list = cs_element_at(topics_list, study_vars.index);
            study_vars.date_as_string = ((struct st_topic_model*)topics_list->page)->next_date;

            // study_vars.topicDate = DateTime.Parse(study_vars.dateAsString);
            study_vars.topic_date = study_vars.date_as_string;

            // Detect if the topic date is the same, before, or after the current date for the user.
            study_vars.date_compare = cs_date_compare(study_vars.topic_date, study_vars.today);
            if (study_vars.date_compare < TODAY)
            {
                // Add a topic id to the list
                to_study = cs_add(to_study);
                ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;

                // to display number of late topics left to study
                ++globals.current_left;
            }
        }
        ++study_vars.index;
    }
    // New Topic ID's section
    study_vars.index = ZERO;
    globals.new_left = ZERO;
    while (study_vars.index < total_nodes)
    {
        topics_list = cs_element_at(topics_list, study_vars.index);
        if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        {
            // Add a topic id to the list
            to_study = cs_add(to_study);
            ((struct st_to_study*)to_study->page)->topic_id = study_vars.index;

            // to display number of late topics left to study
            ++globals.new_left;
        }
        ++study_vars.index;
    }
}
void study_false()
{
    //From study_not_done()

    const int ZERO_INT = 0;
    const double ZERO_DOUBLE = 0;
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
                printf("\n\n\n\nEnter the quantity you answered correctly:\n");
                study_vars.response = cs_read_line();
                if(cs_check_double(study_vars.response) == ZERO_INT)
                    study_vars.num_correct_double = atof(study_vars.response);
                else
                {
                    cs_console_clear();
                    printf("\n\n\nInvalid Input\n\nPress Enter to Continue");
                    study_vars.response = "u";
                    cs_read_line();
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
        study_vars.response = cs_read_line();
        if(cs_check_double(study_vars.response) == ZERO_INT)
        {
            study_vars.num_correct_string = study_vars.response;
            study_vars.num_correct_double = atof(study_vars.num_correct_string);
            test = true;
        }
        else
        {
            cs_console_clear();
            printf("\n\n\nInvalid Input\n\nPress Enter to try again");
            getchar();
            selection_dialogs(TEN);
            test = false;
        }
        //Not an else since response expected to change if response == "u"
        if (test == true)
        {
            study_vars.num_correct_string = study_vars.response;

            if(cs_check_double(study_vars.response) == ZERO_INT)
            {
                study_vars.num_correct_double = atof(study_vars.num_correct_string);

                // TopicsList.ElementAt(globals.TopicID).Num_Problems;

                topics_list = cs_element_at(topics_list, globals.topic_id);
                while (study_vars.num_correct_double > ((struct st_topic_model*)topics_list->page)->num_problems || study_vars.num_correct_double < ZERO_DOUBLE)
                {
                    selection_dialogs(TWELVE);
                    study_vars.response = cs_read_line();
                    
                    if (strcmp(study_vars.response, "u") == ZERO_INT)
                    {
                        change_topic_questions();
                        cs_console_clear();
                        printf("\nRe-enter number of problems or questions you respoded to correctly");
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
                    
                    
                    study_vars.num_correct_string = study_vars.response;
                    if(cs_check_double(study_vars.response) == ZERO_INT)
                        study_vars.num_correct_double = atof(study_vars.num_correct_string);
                    else
                    {
                        cs_console_clear();
                        printf("\n\n\nInvalid Input\n\nPress Enter to try again");
                        getchar();
                    }
                }

                topics_list = cs_element_at(topics_list, globals.topic_id);
                ((struct st_topic_model*)topics_list->page)->num_correct = study_vars.num_correct_double;
                ((struct st_topic_model*)topics_list->page)->first_date = study_vars.today_date_string;
                
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
    topics_list = cs_element_at(topics_list, globals.topic_id);

    study_vars.date_as_string = ((struct st_topic_model*)topics_list->page)->next_date;
    study_vars.topic_date = study_vars.date_as_string;
    
    // study_vars.date_compare = DateTime.Compare(study_vars.topic_date, study_vars.today);
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
    const int ZERO_INT = 0;
    const double ZERO_DOUBLE = 0;
    const int TEN = 10;

    //From StudyCourse()
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
            study_true();
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
        globals.problems_done = true;
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
    const int ZERO = 0;

    cs_console_clear();

    topics_list = cs_element_at(topics_list, globals.topic_id);
    if (((struct st_topic_model*)topics_list->page)->top_studied == true)
        study_vars.top_stud_bool = TRUE_CHAR;
    else
        study_vars.top_stud_bool = FALSE_CHAR;

    printf("\nCourse Name: %s", globals.course_name);
    printf("\nToday is: %s", globals.the_date);

    if (predict_vars.enough_studied == true)
    {
        // Display Initial Goal Date IF End_Reached == FALSE AND Unlock_New_Date == FALSE
        if (predict_vars.end_reached == false && predict_vars.unlock_new_date == false)
        {
            // Display Number of topics left to reach Initial Goal Date
            // Initial_Prediction_Date
            printf("\nCurrent Repetition Goal: %d section(s)", predict_vars.until_new);
            topics_list = cs_element_at(topics_list, predict_vars.final_topic);
            printf("\nCURRENT COMPLETION GOAL: Last Section: %s | Completion Date: %s", ((struct st_topic_model*)topics_list->page)->top_name, predict_vars.prediction_date);
            printf("\nStudy more than %d section(s) to unlock next date calculation.\n(Completion requires 2 repetitions of Section Number %s)\n", predict_vars.until_new, ((struct st_topic_model*)topics_list->page)->top_name);
        }
        // Display New Goal Date IF End_Reached == FALSE AND Unlock_New_Date == TRUE
        if (predict_vars.end_reached == false && predict_vars.unlock_new_date == true)
        {
            // Display New Goal Date
            // New_Prediction_Date
            printf("\nStudy %d section(s) for this NEW COMPLETION GOAL:", predict_vars.until_new);
            topics_list = cs_element_at(topics_list, predict_vars.final_topic);
            printf("\nSection Number %s on Date of %s\n(Completion requires 2 repetitions of Section Number %s.)\n", ((struct st_topic_model*)topics_list->page)->top_name, predict_vars.prediction_date, ((struct st_topic_model*)topics_list->page)->top_name);
            predict_vars.unlock_new_date = false;
        }
        // Display No_Date IF End_Reached == TRUE
        if (predict_vars.end_reached == true)
            printf("\nMaintenance study session");

    }


    topics_list = cs_element_at(topics_list, globals.topic_id);
    printf("\nCurrent Section: %s", ((struct st_topic_model*)topics_list->page)->top_name);
    if (study_vars.top_stud_bool == true)
        printf("\nPreviously Studied: %s", TRUE_CHAR);
    else
        printf("\nPreviously Studied: %s", FALSE_CHAR);
    printf("\nNumber of LATE practice to review: %d", globals.late_left);
    printf("\nNumber of ON-TIME practice topics to review: %d", globals.current_left);
    printf("\nNumber of NEW topics left: %d", globals.new_left);
    printf("\n\n\nNumber of questions/problems: %d", ((struct st_topic_model*)topics_list->page)->num_problems);
    
    printf("\n\nOPTIONS:");
    printf("\n(m) = Main Menu.");


    if (globals.late_left > ZERO || globals.current_left > ZERO)
        printf("\n(enter key) = Process topic, and go to next");
    else
        printf("\n(u) = Update number of questions.");
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
    // TODO: initialize some structs variables of the dates and counts, so that I can 
    // use memory allocation and freeing in order to avoid memory leaks during the 
    // sorting process, in place of just storing new characters into ram that do not free.
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
    
    const int ZERO = 0;
    const int ONE = 1;
    int date_compare;
    int total_nodes = ZERO;
    int last_node = ZERO;
    date_time *temp_date_one;
    date_time *temp_date_two;


    // studiedSimList.ElementAt(predict_vars.loop_index).First_Date
    studied_simlist = cs_element_at(studied_simlist, predict_vars.loop_index);

    ((struct st_sim_model*)studied_simlist->page)->first_date;
    
    
    if (predict_vars.first_check == true)
    {
        // Add a node to the fstudy lists
        // copy the values into the list pages
        
        // fstudy_dates
        // fstudy_dates.Add($"{studiedSimList.ElementAt(predict_vars.loop_index).First_Date}");

        total_nodes = fstudy_dates->total_nodes;
        last_node = total_nodes - ONE;
        fstudy_dates = cs_element_at(fstudy_dates, last_node);
        fstudy_dates = cs_add(fstudy_dates);
        ((struct st_fstudy_dates*)fstudy_dates->page)->dates = ((struct st_topic_model*)studied_simlist->page)->first_date;

        // fstudy_counts
        //fstudy_counts.Add(Constants.ONE_INT);
        total_nodes = fstudy_counts->total_nodes;
        last_node = total_nodes - ONE;
        fstudy_counts = cs_element_at(fstudy_counts, last_node);
        fstudy_counts = cs_add(fstudy_counts);
        ((struct st_fstudy_counts*)fstudy_counts->page)->counts = ONE;



        predict_vars.first_check = false;
    }
    else
    {
        // temp_date_one = DateTime.Parse(fstudy_dates[predict_vars.Find_Yhigh_Index]);
        
        fstudy_dates = cs_element_at(fstudy_dates, predict_vars.find_y_high_index);
        temp_date_one = ((struct st_fstudy_dates*)fstudy_dates->page)->dates;

        // temp_date_two = DateTime.Parse(studiedSimList.ElementAt(predict_vars.loop_index).First_Date);
        studied_simlist = cs_element_at(studied_simlist, predict_vars.loop_index);
        temp_date_one = ((struct st_sim_model*)studied_simlist->page)->first_date;
        
        // dateCompare = DateTime.Compare(temp_date_one, temp_date_two);
        date_compare = cs_date_compare(temp_date_one, temp_date_two);

        if (date_compare == ZERO)
        {
            // ++fstudy_counts[predict_vars.Find_Yhigh_Index];
            fstudy_counts = cs_element_at(fstudy_counts, predict_vars.find_y_high_index);
            ++((struct st_fstudy_counts*)fstudy_counts->page)->counts;
        }
        else
        {
            // ++predict_vars.Find_Yhigh_Index;
            ++predict_vars.find_y_high_index;
           
            // fstudy_dates
            // fstudy_dates.Add($"{studiedSimList.ElementAt(predict_vars.loop_index).First_Date}");

            total_nodes = fstudy_dates->total_nodes;
            last_node = total_nodes - ONE;
            fstudy_dates = cs_element_at(fstudy_dates, last_node);
            fstudy_dates = cs_add(fstudy_dates);
            ((struct st_fstudy_dates*)fstudy_dates->page)->dates = ((struct st_sim_model*)studied_simlist->page)->first_date;

            // fstudy_counts
            //fstudy_counts.Add(Constants.ONE_INT);
            total_nodes = fstudy_counts->total_nodes;
            last_node = total_nodes - ONE;
            fstudy_counts = cs_element_at(fstudy_counts, last_node);
            fstudy_counts = cs_add(fstudy_counts);
            ((struct st_fstudy_counts*)fstudy_counts->page)->counts = ONE;
        }
    }
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

    //SimModel listKey = new SimModel();
    /*
    // For all lists
	int top_number;        // The line number here is used instead of topic id
	
	char *first_date;
	char *simulated_date;  // Simulated date of the simulateed repetition.
	char *next_date;
	
	int real_repetition;
	int sim_repetition;        

	double top_difficulty;
	double interval_length;
    */
    struct st_sim_model list_key;


    for (predict_vars.j = TWO; predict_vars.j < xmax_sortlist->total_nodes; predict_vars.j++)
    {
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.j);
        list_key.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
        list_key.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
        list_key.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
        list_key.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
        list_key.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
        list_key.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;
        list_key.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
        list_key.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;
        //list_key.top_number = xmax_sortlist[predict_vars.j];

        // Insert xmax_sortlist[j] into sorted sequence xmax_sortlist[1...j-1]
        predict_vars.i = predict_vars.j - ONE;
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
        predict_vars.date_check = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, list_key.simulated_date);
        while (predict_vars.i > ZERO && predict_vars.date_check > ZERO)
        {
            struct st_sim_model xmax_temp;
            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
            xmax_temp.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
            xmax_temp.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
            xmax_temp.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
            xmax_temp.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
            xmax_temp.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
            xmax_temp.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;
            xmax_temp.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
            xmax_temp.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;

            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i + ONE);
            xmax_sortlist = &xmax_temp;
            predict_vars.i = predict_vars.i - ONE;
            xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i);
            predict_vars.date_check = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, list_key.simulated_date);
        }
        xmax_sortlist = cs_element_at(xmax_sortlist, predict_vars.i + ONE);
        xmax_sortlist = &list_key;
    }

    /* 
    this is here to get the first element sorted into 
    the rest of the array on the second run of the loop
    */
    struct st_sim_model xmax_temp;
    xmax_sortlist = cs_element_at(xmax_sortlist, ONE);
    xmax_temp.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
    xmax_temp.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
    xmax_temp.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
    xmax_temp.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
    xmax_temp.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
    xmax_temp.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;
    xmax_temp.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
    xmax_temp.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;
    xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);

    int toFixSort = cs_date_compare(((struct st_sim_model*)xmax_sortlist->page)->simulated_date, xmax_temp.simulated_date);
    if (toFixSort > ZERO)
    {
        //key = A[ZERO];
        xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);
        list_key.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
        list_key.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
        list_key.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
        list_key.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
        list_key.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
        list_key.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;
        list_key.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
        list_key.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;
        //A[ZERO] = A[ONE];
        xmax_sortlist = cs_element_at(xmax_sortlist, ONE);
        xmax_temp.top_number = ((struct st_sim_model*)xmax_sortlist->page)->top_number;
        xmax_temp.first_date = ((struct st_sim_model*)xmax_sortlist->page)->first_date;
        xmax_temp.simulated_date = ((struct st_sim_model*)xmax_sortlist->page)->simulated_date;
        xmax_temp.next_date = ((struct st_sim_model*)xmax_sortlist->page)->next_date;
        xmax_temp.real_repetition = ((struct st_sim_model*)xmax_sortlist->page)->real_repetition;
        xmax_temp.sim_repetition = ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition;
        xmax_temp.top_difficulty = ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty;
        xmax_temp.interval_length = ((struct st_sim_model*)xmax_sortlist->page)->interval_length;

        xmax_sortlist = cs_element_at(xmax_sortlist, ZERO);
        ((struct st_sim_model*)xmax_sortlist->page)->top_number = xmax_temp.top_number;
        ((struct st_sim_model*)xmax_sortlist->page)->first_date = xmax_temp.first_date;
        ((struct st_sim_model*)xmax_sortlist->page)->simulated_date = xmax_temp.simulated_date;
        ((struct st_sim_model*)xmax_sortlist->page)->next_date = xmax_temp.next_date;
        ((struct st_sim_model*)xmax_sortlist->page)->real_repetition = xmax_temp.real_repetition;
        ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition = xmax_temp.sim_repetition;
        ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty = xmax_temp.top_difficulty;
        ((struct st_sim_model*)xmax_sortlist->page)->interval_length = xmax_temp.interval_length;
        //A[ONE] = key;
        xmax_sortlist = cs_element_at(xmax_sortlist, ONE);
        ((struct st_sim_model*)xmax_sortlist->page)->top_number = list_key.top_number;
        ((struct st_sim_model*)xmax_sortlist->page)->first_date = list_key.first_date;
        ((struct st_sim_model*)xmax_sortlist->page)->simulated_date = list_key.simulated_date;
        ((struct st_sim_model*)xmax_sortlist->page)->next_date = list_key.next_date;
        ((struct st_sim_model*)xmax_sortlist->page)->real_repetition = list_key.real_repetition;
        ((struct st_sim_model*)xmax_sortlist->page)->sim_repetition = list_key.sim_repetition;
        ((struct st_sim_model*)xmax_sortlist->page)->top_difficulty = list_key.top_difficulty;
        ((struct st_sim_model*)xmax_sortlist->page)->interval_length = list_key.interval_length;
    }
    else
        xsort_correct = false;
    return xsort_correct;
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
    const int ZERO = 0;
    const int TWO = 2;
    int index;

    index = ZERO;
    if (predict_vars.process_prediction == true)
    {
        
        while (index < topics_list->total_nodes)
        {
            gensims_all_getter(index);
            ++index;
        }
        predict_vars.process_prediction = false;
    }
    
    collect_study_x();
    // Might just have to skip the following 3 functions for an off day HERE
    date_time *simDate, *previousDate;
    bool skipDay = false;

    previousDate = predict_vars.sim_date_use;
    simDate = cs_add_days(previousDate, TWO);
    
    skipDay = skip_checker(simDate);
    if (skipDay == false)
    {
        find_y_at_x();
        collect_study_y();
        reduce_new();
    }


    index = ZERO;
    

    while (index < studyrep_elements->total_nodes)
    {
        studyrep_elements = cs_element_at(studyrep_elements, index);

        predict_vars.gen_projected_index = ((struct st_studyrep_elements*)studyrep_elements->page)->studyrep_elements;
        sim_calculate_learning();
        ++index;
    }


    // clear
    index = ZERO;
    while (index < studyrep_elements->total_nodes)
    {
        studyrep_elements = cs_element_at(studyrep_elements, index);

        free((struct st_studyrep_elements*)studyrep_elements->page);
        ++index;
    }
    // st_studyrep_elements
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
    const int ZERO = 0;
    const int ONE = 1;
    const double SINGLE_DAY = 1440;
    double interval_length;
    double days_double;
    int days_int = ZERO;
    date_time *fake_today;
    date_time *next_date;
    char *next_date_string;

    if (predict_vars.process_gen_sims_studied == true)
    {
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_studied_index);

        // interval_length = gensims_studied.ElementAt(predict_vars.Gen_Studied_Index).Interval_Length;
        // days_double = interval_length / SINGLE_DAY; 
        // days_int = (int)days_double; //Necessary to cut off fractional portion without rounding, so cant convert to Int32 yet.
        // fake_today = DateTime.Parse(gensims_studied[predict_vars.Gen_Studied_Index].Simulated_Date);
        interval_length = ((struct st_sim_model*)gensims_studied->page)->interval_length = interval_length;
        days_double = interval_length / SINGLE_DAY;
        days_int = (int)days_double; // Necessary to cut off fractional portion without rounding, so cant convert to Int32 yet.
        fake_today = ((struct st_sim_model*)gensims_studied->page)->simulated_date;
    }
    else
    {
        // Continue here
        // interval_length = gensims_all[predict_vars.Gen_Projected_Index].Interval_Length;
        // days_double = interval_length / SINGLE_DAY;  
        // days_int = (int)days_double; //Necessary to cut off fractional portion without rounding, so cant convert to Int32 yet.
        // fake_today = DateTime.Parse(predict_vars.Sim_Date_Use);

        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_projected_index);
        interval_length = ((struct st_sim_model*)gensims_studied->page)->interval_length;
        days_double = interval_length / SINGLE_DAY;  
        days_int = (int)days_double; //Necessary to cut off fractional portion without rounding, so cant convert to Int32 yet.
        fake_today = predict_vars.sim_date_use;
    }
    //next_date = fake_today.AddDays(days_double);
    
    // next_date = fake_today.AddDays(days_int);
    // next_date_string = next_date.ToString("d");
    next_date_string = cs_add_days(fake_today, days_int);


    int index_future = ZERO;
    int topic_future = ZERO;
    if (predict_vars.process_gen_sims_studied == true)
    {
        index_future = predict_vars.gen_studied_index + ONE;

        gensims_studied = cs_element_at(gensims_studied, index_future);
        topic_future = ((struct st_sim_model*)gensims_studied->page)->top_number;
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_studied_index);
        ((struct st_sim_model*)gensims_studied->page)->next_date = next_date_string;
        
        if (index_future < gensims_studied->total_nodes)
            if (((struct st_sim_model*)gensims_studied->page)->top_number == topic_future)
            {
                // gensims_studied[index_future].Simulated_Date = next_date_string;
                gensims_studied = cs_element_at(gensims_studied, index_future);
                ((struct st_sim_model*)gensims_studied->page)->simulated_date = next_date_string;
            }
    }
    else
    {
        // gensims_all[predict_vars.Gen_Projected_Index].Simulated_Date = predict_vars.Sim_Date_Use;
        // gensims_all[predict_vars.Gen_Projected_Index].Next_Date = next_date_string;
        gensims_studied = cs_element_at(gensims_studied, predict_vars.gen_projected_index);
        ((struct st_sim_model*)gensims_studied->page)->simulated_date = predict_vars.sim_date_use;
        ((struct st_sim_model*)gensims_studied->page)->next_date = next_date_string;
    }
}
/***********************************PREDICTION END*********************************************/
/*******************************WEEKLY SCHEDULE START******************************************/
void check_for_week()
{
    const int ZERO = 0;
    const int THREE = 3;
    // char *file_name, *file_path;
    // if (globals.osSwitch == true)
    //     file_name = "//week.sc";
    // else
    //     file_name = "\\week.sc";
    
    // file_name = "//week.sc";
    // file_path = $"{globals.DirectoryPath}{file_name}";
    init_file_path(THREE);

    // List<string> weekfile_contents = new List<string>();
    // st_week_model
    // 
    // struct st_week_model weekfile_contents;

    if (cs_file_exists(file_strings.week_file))
    {
        

        // weekfile_contents = File.ReadAllLines(file_path).ToList();
        // file_strings->week_file
        // ((struct st_sim_model*)week_list->page)->top_difficulty;
        struct st_node* week_lines;
        
        // fix file_strings so that it works. It is messing up the intellisense for code that 
        // comes after its use here is why I commented it out for right now.
        
        // week_lines = cs_ral_tolist(file_strings->week_file);
        

        int index = ZERO;
        while (index < week_lines->total_nodes)
        {
            //((struct st_sim_model*)week_list->page)->top_difficulty;
            week_lines = cs_element_at(week_lines, index);
            struct st_node* week_entries;
            //string[] entries = line.Split(',');
            week_entries = cs_list_split((struct st_string*)week_lines->page, ',');

            // weekList.monday = Convert.ToInt32(entries[Constants.ZERO_INT]);
            // weekList.tuesday = Convert.ToInt32(entries[Constants.ONE_INT]);
            // weekList.wednesday = Convert.ToInt32(entries[Constants.TWO_INT]);
            // weekList.thursday = Convert.ToInt32(entries[Constants.THREE_INT]);
            // weekList.friday = Convert.ToInt32(entries[Constants.FOUR_INT]);
            // weekList.saturday = Convert.ToInt32(entries[Constants.FIVE_INT]);
            // weekList.sunday = Convert.ToInt32(entries[Constants.SIX_INT]);

            week_list.monday = ZERO;
            week_list.tuesday = ZERO;
            week_list.wednesday = ZERO;
            week_list.thursday = ZERO;
            week_list.friday = ZERO;
            week_list.saturday = ZERO;
            week_list.sunday = ZERO;
            
        }
        
    }
    else
    {
        char file_contents = "0,0,0,0,0,0,0";

        // File.WriteAllText(file_path,fileContents);
        cs_write_all_text(file_strings.week_file, file_contents);
        
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
    simDate
        if (simDate.DayOfWeek == DayOfWeek.Monday)
            skip = true;
    if (weekList.Tuesday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Tuesday)
            skip = true;
    if (weekList.Wednesday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Wednesday)
            skip = true;
    if (weekList.Thursday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Thursday)
            skip = true;
    if (weekList.Friday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Friday)
            skip = true;
    if (weekList.Saturday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Saturday)
            skip = true;
    if (weekList.Sunday == Constants.ONE_INT)
        if (simDate.DayOfWeek == DayOfWeek.Sunday)
            skip = true;
    
    return skip;
}
void weekly_schedule()
{
    const int ZERO = 0;
    const int SIX = 6;
    const int THIRTEEN = 13;
    const char MENU = 'm';
    bool menuBool = false;
    char *userInput;
    int dayOption = ZERO;
    char *endptr;
    int dayOption;
    long int converted;
    
    while (menuBool == false)
    {
        selection_dialogs(THIRTEEN);
        userInput = cs_read_line();
        if (userInput != MENU)
        {
            converted = strtol(userInput, &endptr, 10);
            if (*endptr == '\0' && ((int)converted <= SIX || (int)converted >= ZERO))
            {
                dayOption = (int)converted;
                // Conversion to int was successful
                // You can proceed with the logic involving dayOption here
                
                cs_console_clear();
                toggle_day_function(dayOption);
            }
            else
            {
                // Conversion to int failed
                // Handle the case where userInput is not a valid integer

                cs_console_clear();
                // Console.WriteLine("Invalid input.\nPress Enter to try again.");
                cs_read_line();
                cs_console_clear();
            }
        }
        else
        {
            menuBool = true;
        }
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
    const int SEVEN = 7;
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
            printf("\n%d    ---   %s\n", days[index], state[STUDY_DAY]);
        else
            printf("\n%d    ---   %s\n", days[index], state[OFF_DAY]);
        ++index;
    }
    printf("\n\n\n\n\nOPTIONS:\nEnter a number from 1 to 7 to alter the schedule.\n\nOr enter m to go back to the main menu:\n");
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

    

    switch (dayOption)
    {
        case 0:
            if (week_list.monday == ZERO)
                week_list.monday = ONE;
            else
                week_list.monday = ZERO;
            break;
        case 1:
            if (week_list.tuesday == ZERO)
                week_list.tuesday = ONE;
            else
                week_list.tuesday = ZERO;
            break;
        case 2:
            if (week_list.wednesday == ZERO)
                week_list.wednesday = ONE;
            else
                week_list.wednesday = ZERO;
            break;
        case 3:
            if (week_list.thursday == ZERO)
                week_list.thursday = ONE;
            else
                week_list.thursday = ZERO;
            break;
        case 4:
            if (week_list.friday == ZERO)
                week_list.friday = ONE;
            else
                week_list.friday = ZERO;
            break;
        case 5:
            if (week_list.saturday == ZERO)
                week_list.saturday = ONE;
            else
                week_list.saturday = ZERO;
            break;
        case 6:
            if (week_list.sunday == ZERO)
                week_list.sunday = ONE;
            else
                week_list.sunday = ZERO;
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
/********************************WEEKLY SCHEDULE END*******************************************/

// COMPILE A COPY IN VM, not out of VM!!!!!!!!!!!!

/********************************FILE PATHS START**********************************************/
void init_file_path(int choice)
{
    const int ZERO = 0;
    int len = ZERO;
    int len_one = ZERO;
    int len_two = ZERO;
    int len_three = ZERO;
    switch (choice) 
    {
        case 1:
            // file_strings->txt_course_listfile;
            // file_strings->bak_course_listfile
            file_constants.course_file;
            // FILE: CourseList
            
            len_one = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(file_constants.course_file) + strlen(file_constants.txt_format) + 1;
            len_two = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(file_constants.course_file) + strlen(file_constants.bak_format) + 1;
            file_strings->txt_course_listfile = malloc(len_one);
            file_strings->bak_course_listfile = malloc(len_two);
            sprintf(file_strings->txt_course_listfile, "%s%s%s%s", globals.directory_path, file_constants.slash, file_constants.course_file, file_constants.txt_format);     
            sprintf(file_strings->bak_course_listfile, "%s%s%s%s", globals.directory_path, file_constants.slash, file_constants.course_file, file_constants.bak_format);
            break;
        case 2:
            // file_strings->course_countfile
            // file_constants.course_count
            // FILE: CourseCount
            len = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(file_constants.course_count) + strlen(file_constants.txt_format) + 1;
            file_strings->course_countfile = malloc(len);
            sprintf(file_strings->course_countfile, "%s%s%s%s", globals.directory_path, file_constants.slash, file_constants.course_count, file_constants.txt_format);     
            break;
        case 3:
            // file_strings->week_file
            // file_constants.week_sc
            // FILE: week.sc
            len = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(file_constants.week_sc) + 1;
            file_strings->week_file = malloc(len);
            sprintf(file_strings->week_file, "%s%s%s", globals.directory_path, file_constants.slash, file_constants.week_sc);     
            break;
        case 4:
            // file_strings->txt_course_namefile
            // globals.course_name
            // FILE: CourseName
            len_one = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(globals.course_name) + strlen(file_constants.txt_format) + 1;
            len_two = strlen(globals.directory_path) + strlen(file_constants.slash) + strlen(globals.course_name) + strlen(file_constants.bak_format) + 1;
            file_strings->txt_course_namefile = malloc(len);
            file_strings->bak_course_namefile = malloc(len);
            sprintf(file_strings->txt_course_namefile, "%s%s%s%s", globals.directory_path, file_constants.slash, globals.course_name, file_constants.txt_format);     
            sprintf(file_strings->bak_course_namefile, "%s%s%s%s", globals.directory_path, file_constants.slash, globals.course_name, file_constants.txt_format);     
            break;
        default:
            printf("The number is not 1, 2, or 3\n");
            break;
    }
}


void free_file_path(int choice)
{
    switch (choice) 
    {
        case 1:
            // file_strings->txt_course_listfile
            // file_strings->bak_course_listfile
            free(file_strings->txt_course_listfile);
            free(file_strings->bak_course_listfile);
            break;
        case 2:
            // file_strings->course_countfile
            free(file_strings->course_countfile);
            break;
        case 3:
            // file_strings->week_file
            free(file_strings->week_file);
            break;
        case 4:
            // Free this one right before initializing it, and at program exit with the others.
            // file_strings->txt_course_namefile
            free(file_strings->txt_course_namefile);
            break;
        default:
            printf("The number is not 1, 2, or 3\n");
            break;
    }
}
/********************************FILE PATHS END************************************************/
