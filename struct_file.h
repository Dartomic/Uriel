#ifndef STRUCT_FILE_H
#define STRUCT_FILE_H

#include <stdbool.h>

typedef char date_time;   // This is used in some stucts

//TODO: Put the model structs into a separate header file


// I could have just made some global variables in another file for some file 
// strings, instead of this struct to use. It just seemed cleaner to me if I
// use a struct.
// I am using this so that I do not have memory leaks all over the place in a lot
// of the code that requires these file path parts.

// This struct is separate from the below one because these should not be freed.
struct st_file_const
{
    const char *slash;
    const char *comma;
    const char *course_file;
	const char *course_count;
	const char *week_sc;
    const char *txt_format;
    const char *bak_format;
};

// struct st_file_strings 
// {
// 	// comment a done after each variable once I
// 	// have the code store that string into this 
// 	// struct. That way I can reduce the amount of
// 	// code by checking off a list using 1 as a check. 
// 	// mark. Once all have been done, remove the check
// 	// mark comments from here.


// 	// These must be initialized after the 
// 	// username is obtained. 
// 	// They must be freed upon exit of the program.
// 	// These are all full file paths.

// 	/* In course_list_path() */
// 	// struct choice 1 along with it's bak file
// 	char *txt_course_listfile; //1

// 	// Back up file made in case power outage while file being written, but doesnt complete. It can happen.
// 	char *bak_course_listfile;  

// 	/* In check_for_count() */
// 	// struct choice 2
// 	char *course_countfile;
	


// 	/* In check_for_week() */
// 	// struct choice 3
// 	char *week_file; // I use sc extension for schedule

// 	// This one must get initialized at the same time as
// 	// globals.course_name
// 	// It must be freed upon exit of the course, and the program.
// 	/* I think it is in select_course */
// 	// struct choice 4
// 	char *txt_course_namefile;

// 	// Back up file made in case power outage while file being written, but doesnt complete. It can happen.
// 	char *bak_course_namefile;
// };

// This is the linked list node structure. I made a generalized linked list so
// I can use it in any software that I write in which using linked lists
// makes doing a lot of tasks for me easier.
struct st_node 
{
    int total_nodes;          /* Total number of elements in the linked list */
    int index;                /* Current node of the linked list */
    bool b_previous;          /* true if there is an element before the current. */
    bool b_next;              /* true if there is another element after this one. */
    struct st_node* next;        /* next entry in chain */
    struct st_node* previous;    /* previous entry in chain */
    void *page;               /* this is the page that is linked to the node of the linked list. */
};


// I use this in order to hopefully reduce potential memory leaks, by freeing 
// variables I have allocated memory of this struct type
struct st_string
{
	char *string;
};

// Section 1
struct st_to_study
{
    int topic_id;
};
struct st_topic_model
{
	int top_id;
    int course_id; // If more than one course, then it may be best to not start the TopicID at ZERO for the first topic, so that less of the program needs modifying to allow multiple courses.
    char *top_name; // This is only used to make things easier for building a course. I can't think of why this would be needed, other than for that purpose.
    bool top_studied;

    char *next_date;
    char *first_date;  // I might have a feature that displays the progress of topics since their first study dates.

    double num_problems;
    double num_correct;

    double top_difficulty;
    int top_repetition;
    double interval_remaining; // This variable will be used later in the GUI

    double interval_length;
    double engram_stability;
    double engram_retrievability;
};
struct st_global_variables // Variable declared for this here
{
	//used to check if list needs to be cleared
	int study_tracker;

	/* Schedule variables */
	char *schedule_path;
	int schedule_count;
	bool schedule_exists;
	bool days_off_bool;

    /* File Path variables */
	bool os_switch; // True if Linux, false if Windows. This is needed to store files correctly, so this app can be used in both operating systems.
	char *directory_path;
	char *file_path;


	/* Course files variables */
	char *course_name;
	char *course_chapters;
	int course_count;
	int topic_count;
	int topic_index; // Needed for course study session
	int topic_id;
	bool problems_done;
	
	// Date from time program initializes
	char *the_date;
	
	//This is for AvailableOptions() and MainOptions()
	bool made_select;

	// These three are just used to display
	// topics left to study for the user
	// to see.
	int new_left;
	int current_left;
	int late_left;

	//For SelectionDialogs(option three)
	char *response;
} globals;
struct st_creation_model  // Variable declared for this here
{
	int chapter_loop;
	int current_chapter;
	int chapters_int;
	int topic_counter;
	char *topic_count_string;
	int topic_loop;
	int subsection_counter;
	char *subsection_string;
	int sub_loop;
	char *file_path;
	int topic_id;
	int current_subsection;

	//These are for the data loops
	double problem_count;
	char *p_count_string;
	int current_topic;
	int check;
	char *topic_string;
	char *new_top_name;
	char *list_file;
} creation_vars;



struct st_study_model
{
	// date_times
	// TODO: replace datetime variables once I know how to work with date and time
	date_time *today;
	date_time *topic_date;

	// ints
	int date_compare;
	int line_count;
	int index;
	int to_study_count;

	// doubles
	double num_correct_double;

	// strings
	char *date_as_string;
	char *file_path;
	char *top_stud_string;
	char *top_stud_bool;
	char *num_correct_string;
	char *today_date_string;
	char *response;

	// bools
	bool studied;
};

// Section 2
struct st_sim_model
{
	// For all lists
	int top_number;        // The line number here is used instead of topic id
	
	char *first_date;
	char *simulated_date;  // Simulated date of the simulateed repetition.
	char *next_date;
	
	int real_repetition;
	int sim_repetition;        

	double top_difficulty;
	double interval_length;
};
struct st_fstudy_dates
{
    char *dates;
};
struct st_fstudy_counts
{
    int counts;
};
struct st_xrep_temp_dates
{
    char *xrep_tempdates;
};
struct st_xrep_datecounts
{
    int xrep_datecounts;
};
struct st_studyrep_elements
{
    int studyrep_elements;
};

// Section 3
struct st_course_list_model
{
    int course_id;
    char *course_name;
    char *file_path;
};
struct st_predict_model
{
	// Date for StudyHud()
	date_time *prediction_date;
	int final_topic;
	int until_new;                              // Counts down number of topics studied, if topics were scheduled to study        
	bool lock_goals;                            // Required so that Initial_Prediction_Date is set only once.
	bool lock_prediction;                       // Needed to allow date new date to be won repetition goal met.
	bool unlock_new_date;                       // Display a newer date if Until_New reaches ZERO
	bool end_reached;                           // No expected date shown if == false
	
	// Indices
	int gen_studied_index;
	int gen_projected_index;
	int loop_index;
	int x_rep_index;
	
	// Bools
	bool process_prediction;                   // Use to get actual info from topics one time
	bool process_gen_sims_studied;
	bool first_check;
	bool only_one;
	bool enough_studied;                       // For StudyHUD decision

	//Doubles
	double avg_difficulty;

	//Strings
	char *sim_date_use;                       // The date being simulated
	double y_high_y_count;
	double x_high_x_count;

	//Limits
	double current_x;                          // needs to be type double
	int current_y;                             // needs to be type int


	//YmaxFirsts
	//bool Loop_Entered;                       // To know if a date was stored.
	int find_y_high_index;

	//XmaxRepeatSort
	int j;
	int i;
	int date_check;
};
struct st_week_model
{
	int monday;
	int tuesday;
	int wednesday;
	int thursday;
	int friday;
	int saturday;
	int sunday;
};

// Might not need this last one after all.
struct st_single_day // replace code that needs a value to store int st_week_model from string to this.
{
	int day;
};

#endif /* STRUCT_FILE_H */

