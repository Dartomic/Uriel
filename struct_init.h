#ifndef STRUCT_INIT_H
#define STRUCT_INIT_H

// section 1
extern struct st_node* to_study;                        // st_to_study
extern struct st_node* topics_list;                  // st_topic_model
extern struct st_node* topics;                       // st_topic_model

// The Globals struct can just be turned into global variables for the C language
// static Globals globals = new Globals();
extern struct st_creation_model creation_vars;
extern struct st_study_model study_vars;

/***********************************************/
//section 2
// Start of parts to predict date of last topic being studied
extern struct st_node* studied_simlist;                // st_sim_model
extern struct st_node* projected_simlist;              // st_sim_model
extern struct st_node* gensims_studied;                // st_sim_model
extern struct st_node* gensims_all;                    // st_sim_model
extern struct st_node* fstudy_dates;                // st_fstudy_dates
extern struct st_node* fstudy_counts;              // st_fstudy_counts
// For Ymax END

// For XmaxRepeats START
extern struct st_node* xrep_temp_dates;           // st_xrep_temp_dates
extern struct st_node* xrep_datecounts;          // st_xrep_datecounts
extern struct st_node* to_xmax;                        // st_sim_model
// For XmaxRepeats END

//ReduceNew START
extern struct st_node* reduced_projected;              // st_sim_model
//ReduceNew END
extern struct st_node* xmax_sortlist;                  // st_sim_model
extern struct st_node* studyrep_elements;      // st_studyrep_elements
extern struct st_predict_model predict_vars;
// End of parts to predict date of last topic being studied
/***********************************************/

/***********************************************/
//section 3
// Start of parts for Scheduler
extern struct st_week_model week_list;

// End parts of Scheduler
/***********************************************/


/*FIXME: HAVE THIS INITIALIZED IN MAIN FOR NOW*/
// For file stuff
// extern struct st_file_strings file_strings;


#endif /* STRUCT_INIT_H */
