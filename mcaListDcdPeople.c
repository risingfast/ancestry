//  mcaListDcdPeople.c -- list deceased people in the mysql ancestry database as a cgi
//  Author: Geoffrey Jarman
//  Started: 10-Aug-2021
//  References:
//  Log:
//      10-Aug-2021 started
//      15-Sep-2022 add Access-Control-Allow-Origin: * to http headers
//  Enhancements:
///

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

    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') as 'ID' "
                   ", REPLACE(REPLACE(CONCAT(AP.`First Name`, COALESCE(CONCAT(' ''', AP.`Nick Name`, ''' '), ' '), "
                   "  COALESCE(AP.`Middle Names`, ' '),' ', AP.`Last Name`, COALESCE(CONCAT(' ', AP.`Suffix`), '')), '  ', ''), '''''', '') AS `Person` "
                   ", AP.`Gender` "
                   ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                   ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                   "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                   ", COALESCE(CONCAT('b. ', `Born On`), '') as 'Born On' "
                   ", COALESCE(`Birth Place`, '') "
                   "  FROM risingfast.`Ancestry People` AP"
                   "  WHERE AP.`Actual`= TRUE"
                   "  AND AP.`Deceased` = 1 "
                   "  ORDER BY AP.`Person ID` %s", caOrder)
   ;

// print http headers for content-type and CORS

    printf("Content-type: text/html\n");
    printf("Access-Control-Allow-Origin: *\n\n");

// Initialize a connection and connect to the database$$

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
