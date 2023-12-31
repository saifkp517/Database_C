#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//read a line of input

typedef struct {
    char* buffer;
    size_t buffer_length;
    size_t input_length;
} InputBuffer;

//enums for checking success status
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_COMMAND,
} PrepareResult;

//enum and struct for checking commands
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct {
    StatementType type;
} Statement;

//declaring buffer
InputBuffer* new_input_buffer() { 
    InputBuffer* input_buffer = (InputBuffer* )malloc(sizeof(InputBuffer)); input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

//function that checks success status
MetaCommandResult do_meta_command (InputBuffer* input_buffer) {
    if(strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

//used in execute_statement, returns state of the input instruction
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if(strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_COMMAND;
}

//function to determine command

void print_prompt() {printf("db > "); }

void read_input(InputBuffer* input_buffer) {
   size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
   if (bytes_read <= 0) {
       printf("Error reading input\n");
       exit(EXIT_FAILURE);
   }

   //ignoring trailing new lines, cuz we dont want new lines as part of data
   input_buffer->input_length = bytes_read - 1;
   input_buffer->buffer[bytes_read - 1] = 0;
}

//function that frees the memory after work is done to prevent memory leaks
void close_input_buffer (InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

//fetches result from PrepareResult
void execute_statement(Statement* statement) {
    switch (statement->type) {
        case(STATEMENT_INSERT):
            printf("insert statement executed!\n");
            break;
        case(STATEMENT_SELECT):
            printf("select statement executed!\n");
            break;
    }
}

int main(int argc, char* argv[]) {
   InputBuffer* input_buffer = new_input_buffer();
   while (1) {
       print_prompt();
       read_input(input_buffer);

       if(input_buffer->buffer[0] == '.') {
           switch (do_meta_command(input_buffer)) {
               case(META_COMMAND_SUCCESS):
                   continue; //by default we break a case statement but since we need to continue our loop we use continue
               case(META_COMMAND_UNRECOGNIZED_COMMAND):
                   printf("Unrecognized command '%s'\n", input_buffer->buffer);
                   continue;
           }
       }
       Statement statement;
       switch(prepare_statement(input_buffer, &statement)) {
           case(PREPARE_SUCCESS):
               break;
           case(PREPARE_UNRECOGNIZED_COMMAND):
               printf("Unrecognized command '%s'\n", input_buffer->buffer);
               continue;
       }
       execute_statement(&statement);
       printf("Executed!\n");
   }
}
