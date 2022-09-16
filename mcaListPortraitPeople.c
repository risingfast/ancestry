//  mcaListPortraitPeople.c -- list People who have portraits and list the portrait count as a cgi
//  Author: Geoffrey Jarman
//  Started: 02-Sep-2022
//  References:
//  Log:
//      02-Sep-2022 started and tested
//      15-Sep-2022 add Access-Control-Allow-Origin: * CORS http header
//  Enhancements:
//

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define SQL_LEN 5000
#define HDG_LEN 1000

// global declarations

char *sgServer = "192.168.0.13";                                                               //mysqlServer IP address
char *sgUsername = "gjarman";                                                              // mysqlSerer logon username
char *sgPassword = "Mpa4egu$";                                                    // password to connect to mysqlserver
char *sgDatabase = "risingfast";                                                // default database name on mysqlserver

MYSQL *conn;

int main(int argc, char** argv) {

    int iColCount = 0;
    char caOrder[] = {'A', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    long lPersonID = 0;
    char *data = NULL;

    MYSQL_RES *res;
    MYSQL_ROW row;

// print HTTP headers for content-type and CORS

    printf("Content-type: text/html\n");
    printf("Access-Control-Allow-Origin: *\n\n");

// define SQL to query the database for portraits in JSON

    sprintf(caSQL, "SELECT JSON_OBJECT('Person ID', APE.`Person ID` "
                   ", 'Name', CONCAT(APE.`First Name`, ' ', APE.`Last Name`)"
                   ", 'Count', COUNT(APO.`Person ID`))"
                   "  FROM `Ancestry People` APE "
                   "  LEFT JOIN `Ancestry Portraits` APO ON APE.`Person ID` = APO.`Person ID`"
                   "  GROUP BY APE.`Person ID`"
                   "  HAVING COUNT(APO.`Person ID`) > 0"
                   "  ORDER BY APE.`Person ID` ASC")
                   ;

// Initialize a connection and connect to the database

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, sgServer, sgUsername, sgPassword, sgDatabase, 0, NULL, 0))
    {
        printf("\n");
        printf("Failed to connect to MySQL Server %s in module %s()", sgServer, __func__);
        printf("\n\n");
        printf("Error: %s\n", mysql_error(conn));
        printf("\n");
        return  EXIT_FAILURE;
    }

// execute the query and check for no result
    
    if(mysql_query(conn, caSQL) != 0)
    {
        printf("\n");
        printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
        printf("\n\n");
        return EXIT_FAILURE;
    }

// store the result of the query

    res = mysql_store_result(conn);
    if(res == NULL)
    {
        printf("%s() -- no results returned", __func__);
        printf("\n");

        mysql_free_result(res);
        return EXIT_FAILURE;
    }
    
// fetch the number of fields in the result
    
    iColCount = mysql_num_fields(res);
    
    mysql_data_seek(res, 0);
    
// print each row of results

    while(row = mysql_fetch_row(res))
    {
        for(int i = 0; i < iColCount; i++)
        {
            if(i == 0)
            {
                printf("%s ", row[i]);
            }
            else if (i == iColCount - 1)
            {
                printf("%s", row[i]);
            }
            else
            {
                printf("%s|", row[i]);
            }
        }
        printf("\n");
    }

    mysql_free_result(res);

    return 0;
}
