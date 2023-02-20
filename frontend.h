#ifndef frontend_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define frontend_h

/**
 * Max username characters.
 */
#define COLUMN_USERNAME_SIZE 32

/**
 * Max email characters.
 */
#define COLUMN_EMAIL_SIZE 255

/**
* Max number of table pages.
*/
#define TABLE_MAX_PAGES 100

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

/**
 * An input buffer to hold input.
 */
struct InputBuffer {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

/**
 * Table of rows.
 */
struct Table {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
};

/**
 * A single row of a table.
 */
struct Row {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
};

/**
 * Available commands.
 */
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

/**
 * A command.
 */
typedef struct {
    StatementType type;
    struct Row row_to_insert;
} Statement;

/**
 * Was a statement successfully executed.
 */
typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteResult;

/**
 * Meta command results.
 */
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

/**
 * Does the parsed command exist.
 */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

/**
 * Serialize a row.
 */
void serialize_row(struct Row* source, void* destination);

/**
 * Deserialize a row.
 */
void deserialize_row(void *source, struct Row* destination);

/**
 * Insert a table row.
 */
void* row_slot(struct Table* table, uint32_t row_num);

/**
 * Init a table.
 */
struct Table* new_table(void);

/**
 * Deinit a table.
 */
void free_table(struct Table* table);

/**
 * Output a table row.
 */
void print_row(struct Row* row);

/**
 * Run a meta command (statements that begin with a dot '.' ).
 */
MetaCommandResult do_meta_command(struct InputBuffer* input_buffer, struct Table *table);

/**
 * Determines the statement to execute.
 */
PrepareResult process_statement(struct InputBuffer* input_buffer, Statement* statement);

/**
 * Executes an 'insert' statement.
 */
ExecuteResult execute_insert(Statement* statement, struct Table* table);

/**
 * Executes a 'select' statement.
 */
ExecuteResult execute_select(Statement* statement, struct Table* table);

/**
 * Executes a statement.
 */
ExecuteResult execute_statement(Statement* statement, struct Table *table);

/**
 * Opens an input buffer.
 */
struct InputBuffer* new_input_buffer (void);

/**
 * Reads the input buffer.
 */
void read_input_buffer (struct InputBuffer* input_buffer);

/**
 * Closes the input buffer.
 */
void close_input_buffer (struct InputBuffer* input_buffer);

/**
 * Outputs the REPL prompt.
 */
char* get_prompt (void);

/**
 * Start.
 */
int run (void);

#endif

