#ifndef CSUTILS_H
#define CSUTILS_H

// File utilities
char* cs_read_all_text(char* path);
int cs_write_all_lines(char* path, struct st_node* output, int total_nodes);
int cs_write_all_text(const char *filename, const char *text);
char* cs_read_line();
// char* cs_read_all_lines (char* path);
int cs_file_exists(const char *filename);

// Conversion tools
char* cs_to_string(int value);
struct st_node* cs_ral_tolist(const char* path);
int cs_check_double(const char *char_var);

// Function declaration for void function to link nodes together
struct st_node* cs_add(struct st_node* first);
struct st_node* cs_add_total(struct st_node* current);
struct st_node* cs_node_intializer(struct st_node* first);
struct st_node* cs_element_at(struct st_node *working_node, int index);
void cs_clear_nodes(struct st_node* working_node);
void cs_console_clear();
struct st_node* cs_list_split(const char* string, const char* token_in);

// C Sharp inspired date time functions
int cs_date_compare(const char *date_one, const char *date_two);
char* cs_add_days(const char* date_str, int days);

// Other tools
int cs_check_int(const char *str);
#endif // CSUTILS_H

