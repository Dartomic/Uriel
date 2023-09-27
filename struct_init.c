#include "struct_init.h"
#include "struct_file.h"
#include <stdlib.h>

#define ZERO 0

// This for the file path strings.
extern struct st_file_const file_constants = 
{
	.slash = "/",
	.comma = ",",
    .course_file = "CourseList",
    .course_count = "CourseCount",
    .week_sc = "week.sc",
    .txt_format = ".txt",
    .bak_format = ".bak"
};
// extern struct st_file_strings *file_strings;
// extern struct st_file_str_name* file_coursename = malloc(sizeof(struct st_file_str_name));




// section 1
extern struct st_node* to_study = (struct st_node*) malloc(sizeof(struct st_node));                     // st_to_study
extern struct st_node* topics_list = (struct st_node*) malloc(sizeof(struct st_node));                  // st_topic_model
extern struct st_node* topics = (struct st_node*) malloc(sizeof(struct st_node));                       // st_topic_model

// The Globals struct can just be turned into global variables for the C language
// static Globals globals = new Globals();
extern struct st_creation_model creation_vars;
extern struct st_study_model study_vars;

/***********************************************/
//section 2
// Start of parts to predict date of last topic being studied
extern struct st_node* studied_simlist = (struct st_node*) malloc(sizeof(struct st_node));              // st_sim_model
extern struct st_node* projected_simlist = (struct st_node*) malloc(sizeof(struct st_node));            // st_sim_model
extern struct st_node* gensims_studied = (struct st_node*) malloc(sizeof(struct st_node));              // st_sim_model
extern struct st_node* gensims_all = (struct st_node*) malloc(sizeof(struct st_node));                  // st_sim_model
extern struct st_node* fstudy_dates = (struct st_node*) malloc(sizeof(struct st_node));                 // st_fstudy_dates
extern struct st_node* fstudy_counts = (struct st_node*) malloc(sizeof(struct st_node));                // st_fstudy_counts
// For Ymax END

// For XmaxRepeats START
extern struct st_node* xrep_temp_dates = (struct st_node*) malloc(sizeof(struct st_node));              // st_xrep_temp_dates
extern struct st_node* xrep_datecounts = (struct st_node*) malloc(sizeof(struct st_node));             // st_xrep_datecounts
extern struct st_node* to_xmax = (struct st_node*) malloc(sizeof(struct st_node));                     // st_sim_model
// For XmaxRepeats END

//ReduceNew START
extern struct st_node* reduced_projected = (struct st_node*) malloc(sizeof(struct st_node));            // st_sim_model
//ReduceNew END
extern struct st_node* xmax_sortlist = (struct st_node*) malloc(sizeof(struct st_node));                // st_sim_model
extern struct st_node* studyrep_elements = (struct st_node*) malloc(sizeof(struct st_node));            // st_studyrep_elements
extern struct st_predict_model predict_vars;
// End of parts to predict date of last topic being studied
/***********************************************/

/***********************************************/
//section 3
// Start of parts for Scheduler
extern struct st_week_model week_list;

// End parts of Scheduler
/***********************************************/



