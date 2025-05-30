/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "person.h"
#include "list.h"
#include "tcp_client.h"
#include <unistd.h>




int person_cmd(int commSock,char cmd, person_t* person)
{
    char request_buffer[MAX_LEN+1];
    request_buffer[0] = cmd;

    int len = person_to_csv_string(person,&request_buffer[2]);
    request_buffer[1] = (unsigned char)len;
    printf("person_cmd: &request_buffer[2]=%s, len+2=%d\n",&request_buffer[2], len+2);
    sendRequest(commSock, request_buffer, len+2);
    char retval = 0; 
    receiveResponse(commSock,&retval, 1);
    return retval;
}

void list_show_cmd(int commSock)
{
    char list_show_cmd = 'S';
	 
    sendRequest(commSock, &list_show_cmd,1);

	 char noOfRecords = 0;

	 receiveResponse(commSock, &noOfRecords, 1);
	 printf("list_show_cmd: noOfRecords=%d\n",noOfRecords);
	 for(char i = 1;i<=noOfRecords;i++)
	 {
		char noOfBytes =0;
		const unsigned char buflen =255;
		char buffer[buflen];
	   	int r1 = receiveResponse(commSock, &noOfBytes, 1);
	   	int r2 = receiveResponse(commSock, buffer    , noOfBytes);
		person_t person;
		person_from_csv_string(&person,buffer);
		printf("%20s %20s %u\n", person.name, person.first_name, person.age);
	 }
}

void list_clear_cmd(int commSock)
{
    char list_clear_cmd = 'C';
    sendRequest(commSock, &list_clear_cmd,1);
}
void server_terminate_cmd(int commSock)
{
    char list_clear_cmd = 'T';
    sendRequest(commSock, &list_clear_cmd,1);
}
/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */

int main(int argc, char* argv[])
{
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <Server> <Port>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char* serverName = argv[1];
    const char* port = argv[2];
    char choice;
    while(1) {
        printf("Enter command (I)nsert, (R)emove, (S)how, (C)lear, (T)erminate, (Q)uit: ");
        if(scanf(" %c", &choice) != 1) break;
        choice = toupper(choice);
        if(choice == 'Q') break;
        int commSock = client_connect(serverName, port);
        switch(choice) {
            case 'I':
            case 'R': {
                person_t person;
                if(!person_read(&person)) {
                    printf("Invalid input\n");
                } else {
                    int retval = person_cmd(commSock, choice, &person);
                    if(retval == 0) printf("Ok\n");
                    else if(retval == 1) printf("Not found\n");
                    else if(retval == 2) printf("Invalid data\n");
                }
            } break;
            case 'S':
                list_show_cmd(commSock);
                break;
            case 'C':
                list_clear_cmd(commSock);
                printf("Cleared\n");
                break;
            case 'T':
                server_terminate_cmd(commSock);
                printf("Server terminating\n");
                break;
            default:
                printf("Unknown command\n");
                break;
        }
        close(commSock);
    }
    return EXIT_SUCCESS;
}
