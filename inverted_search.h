#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

#define SUCCESS 0
#define FAILURE -1
#define FILE_EMPTY -3
#define DATA_NOT_FOUND -2

#define MAX_SIZE_FILENAME 25
#define MAX_SIZE_WORD 25

typedef int Status;

//file name structure
typedef struct file_arg
{
    char file[MAX_SIZE_FILENAME];
    struct file_arg *f_arg_link;
}f_arg;

//file list
typedef struct file_name
{
    int word_count;
    char file_name[MAX_SIZE_FILENAME];
    struct file_name *file_link;
}f_name;

//word structurei
typedef struct word_list
{
    int file_count;
    char word_name[MAX_SIZE_WORD];
    struct file_name *f_link;
    struct word_list *word_link;
}word_l;

//read and validate
Status read_and_validate(char **argv,f_arg **head_fname);

//create database function
Status create_DB(word_l *word[26], f_arg *head_fname);

//open file function
Status open_file_and_validate(f_arg *head_fname, FILE **fptr);

//create word node
void create_word_node(word_l **new,char *word);

//create file node
void create_file_node(f_name **new,char *file);

//display database
Status display_DB(word_l *word[26]);

//search word in database
Status search_DB(word_l *word[26],char *search_w);

//update database
Status update_DB(word_l *word[26],char *update_fname,f_arg **head_fname);

//read and validate for update
Status validate_and_open_update(char *update_fname,FILE **fptr);

//save database to file
Status save_DB(word_l *word[26],char *fname);

//read and validate for save
Status validate_and_open_save(char *update_fname,FILE **fptr);


#endif
