// includes and defines

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs50.h"
#include "rf50.h"
#include <ctype.h>
#include <stdbool.h>

#define SQL_LEN 5000

// function declarations

void fShowMainMenu(void);                                                                 // show the main console menu
void fGetPwdFromConsole(void);                                                       // get a password from the console
void fListPeople(char *, int *, char *, char *, char *);                                    // display a list of people

// global declarations

char *sgServer = "192.168.0.13";                                                               //mysqlServer IP address
char *sgUsername = "gjarman";                                                              // mysqlSerer logon username
char sgPassword[20] = {'\0'};                                                     // password to connect to mysqlserver
char *sgDatabase = "risingfast";                                                // default database name on mysqlserver

MYSQL *conn;

int main(int argc, char **argv)
{

// declarations

    char *sPrgNme = strcat(argv[0] + 2, " -- Library and reading log");                                 // program name
    bool bHelp = false;                                                                  // help flag to show help text
    bool bExitMain = false;                                                                 // flag to exit the program
    char cMainChoice = '0';                                                                         // main menu choice
    int  iDisplayPageLength = 83;                                                      // display page lines for paging
    char cDisplayPageWidth = 'W';                                                  // display page width wide or narrow
    char cDipslayPageFormat = 'T';                                                // display page format (T)ab or (C)SV
    char cDisplayOrder = 'A';                                                 // display order asc or desc on Person ID

// Search for input parameters

    for(int i = 1; i < argc; i++)
    {
        if(strcmp("--help", argv[i]) == 0 || strcmp("--h", argv[i]) == 0)
        {
            bHelp = true;
        }
    }

    if(bHelp == true)
    {
        printf("\n");
        printf("Command line switch --h or --help not specified so help suppressed");
        printf("\n");
    }

// get a password from the console and test the db connection

    fRetitleConsole(sPrgNme);
    fGetPwdFromConsole();
    if(strcmp("BadSoExit", sgPassword) == 0)
    {   
        printf("\n");
        return EXIT_FAILURE;
    }
    fRetitleConsole(sPrgNme);

// Initialize a connection and connect to the database$

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, sgServer, sgUsername, sgPassword, sgDatabase, 0, NULL, 0))
    {
        printf("\n");
        printf("Failed to connect to MySQL Server %s in module %s()", sgServer, __func__);
        printf("\n\n");
        printf("Error: %s\n", mysql_error(conn));
        printf("\n");
        fPressEnterToContinue();
        printf("\n");
        return  EXIT_FAILURE;
    }

// print the main menu and execute menu choices

    while(bExitMain == false)
    {
        while(cMainChoice == '0')
        {
            fRetitleConsole(sPrgNme);
            fShowMainMenu();
            cMainChoice = GetChar();
            if(strchr("1234567lLeEpPrRnNsSxX", cMainChoice) == NULL)
            {
                cMainChoice = '0';
                fRetitleConsole(sPrgNme);
                printf("\n");
            }
        }

        if(strchr("1lL", cMainChoice) != NULL)
        {
            printf("\n");
            fListPeople(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDipslayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
        }
        else if(strchr("2eE", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 2eE");
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
            fPressEnterToContinue();
        }
        else if(strchr("3pP", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 3pP");
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
            fPressEnterToContinue();
        }
        else if(strchr("4rR", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 4rR");
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
            fPressEnterToContinue();
        }
        else if(strchr("nN5", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 5nN");
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
            fPressEnterToContinue();
        }
        else if(strchr("sS6", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 6sS");
            printf("\n");
            cMainChoice = '0';
            bExitMain = false;
            fPressEnterToContinue();
        }
        else if(strchr("xX7", cMainChoice) != NULL)
        {
            bExitMain = true;
        }
    }

    mysql_close(conn);
    system("clear");
    return EXIT_SUCCESS;
}

void fShowMainMenu(void)                                                                                   // main menu
{
    printf("\n");
    printf("Main Menu");
    printf("\n\n");
    printf("1. (L)ist People");
    printf("\n");
    printf("2. List (E)vents");
    printf("\n");
    printf("3. (P)rofile Person");
    printf("\n");
    printf("4. Enter Pe(r)son");
    printf("\n");
    printf("5. E(n)ter Event");
    printf("\n");
    printf("6. Option(s)");
    printf("\n");
    printf("7. E(x)it");
    printf("\n\n");
    printf("Choice: ");

    return;
}

void fGetPwdFromConsole(void)
{
    char *sEnteredPwd = NULL;;
    char *sTempPwd = "Mpa4egu$";                                                         // Temporary disabled password

    printf("\n");
    do
    {
        printf("Password to connect to mysqlDB (or E(x)it): ");
//        sEnteredPwd = GetString();                                                     // Temporary disabled password
        sEnteredPwd = sTempPwd;                                                          // Temporary disabled password
        if((strlen(sEnteredPwd) == 1) && (strchr("xX", sEnteredPwd[0]) != NULL))
        {
            strcpy(sgPassword, "BadSoExit");
            break;
        }
        else
        {
            conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, sgServer, sgUsername, sEnteredPwd, sgDatabase, 0, NULL, 0))
            {
                printf("\n");
                printf("Failed to connect to MySQL server with entered password");
                printf("\n\n");
                fPressEnterToContinue();
                printf("\n");
            }
            else
            {
                strcpy(sgPassword, sEnteredPwd);
            }
        }
    } while(strcmp(sgPassword, sEnteredPwd) != 0);

    return;
}

void fListPeople(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDipslayPageFormat, char *pcDisplayOrder)
{
    int iColCount = 0;
    int *iLengths = NULL;
    int iRowCount = 0;
    char cQueryFilterchoice = '0';
    char caOrder[6] = {'D', 'E', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    bool bEndOfPrintBlock = false;

    MYSQL_RES *res;
    MYSQL_ROW row;

    if(*pcDisplayOrder == 'A')
    {
        strcpy(caOrder, "ASC");
    }
    else if(*pcDisplayOrder == 'D')
    {
        strcpy(caOrder, "DESC");
    }

    fRetitleConsole(sPrgNme);
    printf("\n");
    printf("Main Menu > List People > People names ...");
    printf("\n\n");
    printf("(A)ll, (M)ales, (F)emales, (L)iving, (D)eceased, (C)ohort or E(x)it");
    printf("\n\n");
    while(strchr("aAmMfFlLdDcCxX", cQueryFilterchoice) == NULL)
    {
        printf("Choice: ");
        cQueryFilterchoice = toupper(GetChar());
    }
    if(toupper(cQueryFilterchoice) == 'X')
    {
        return;
    }
    else if(cQueryFilterchoice == 'A')
    {
        sprintf(caSQL, "SELECT AP.`Person ID` "
                            ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                            ", AP.`Gender` "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            "  FROM risingfast.`Ancestry People` AP"
                            "  WHERE AP.`Person ID` != 10"
                            "  ORDER BY AP.`Person ID` %s", caOrder)
                            ;
    }
    else if(cQueryFilterchoice == 'M')
    {
        sprintf(caSQL, "SELECT AP.`Person ID` "
                            ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                            ", AP.`Gender` "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            "  FROM risingfast.`Ancestry People` AP"
                            "  WHERE AP.`Person ID` != 10"
                            "  AND AP.`Gender` = 'Male'"
                            "  ORDER BY AP.`Person ID` %s", caOrder)
                            ;
    }
    else if(cQueryFilterchoice == 'F')
    {
        sprintf(caSQL, "SELECT AP.`Person ID` "
                            ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                            ", AP.`Gender` "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            "  FROM risingfast.`Ancestry People` AP"
                            "  WHERE AP.`Person ID` != 10"
                            "  AND AP.`Gender` = 'Female'"
                            "  ORDER BY AP.`Person ID` %s", caOrder)
                            ;
    }
    else if(cQueryFilterchoice == 'L')
    {
        sprintf(caSQL, "SELECT AP.`Person ID` "
                            ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                            ", AP.`Gender` "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            "  FROM risingfast.`Ancestry People` AP"
                            "  WHERE AP.`Person ID` != 10"
                            "  AND AP.`Deceased` = 0"
                            "  ORDER BY AP.`Person ID` %s", caOrder)
                            ;
    }
    else if(cQueryFilterchoice == 'D')
    {
        sprintf(caSQL, "SELECT AP.`Person ID` "
                            ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                            ", AP.`Gender` "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            "  FROM risingfast.`Ancestry People` AP"
                            "  WHERE AP.`Person ID` != 10"
                            "  AND AP.`Deceased` = 1"
                            "  ORDER BY AP.`Person ID` %s", caOrder)
                            ;
    }
    else if(cQueryFilterchoice == 'C')
    {
        sprintf(caSQL, "select AP.`Person ID` as 'ID' "
                            ", AP.`First Name` as 'First' "
                            ", AP.`Middle Names` as 'Middle' "
                            ", AP.`Last Name` as 'Last' "
                            ", AP.`Born On` as 'Born' "
                            ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') as 'Status' "
                            ", AP.`Deceased On` as 'Deceased On' "
                            ", IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)) as 'Age' "
                            ", AC.Cohort "
                            "  from risingfast.`Ancestry People` AP "
                            "  left join risingfast.`Ancestry Cohorts` AC on (AP.`Born On` >= AC.`Start`) and (AP.`Born On` <= AC.`Finish`) ")
                            ;
    }

// execute the query and check for no result

    if(mysql_query(conn, caSQL) != 0)
    {
        printf("\n");
        printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
        printf("\n\n");
        fPressEnterToContinue();
        return;
    }

// store the result of the query

    res = mysql_store_result(conn);
    if(res == NULL)
    {
        printf("%s() -- no results returned", __func__);
        printf("\n");

        mysql_free_result(res);
        return;
    }

// fetch the number of fields in the result

    if(*pcDisplayPageWidth == 'W')
    {
        iColCount = mysql_num_fields(res);
    }
    else if(*pcDisplayPageWidth == 'N')
    {
        iColCount = mysql_num_fields(res) - 3;
    }

// fetch the max width of each column

    iLengths = (int *)calloc(iColCount, sizeof(int));

    while(row = mysql_fetch_row(res))
    {
        for (int k = 0; k < iColCount; k++)
        {
            if(row[k] != NULL)
            {
                if(strlen(row[k]) > iLengths[k])
                {
                     iLengths[k] = strlen(row[k]);
                }
            }
        }
    }

    mysql_data_seek(res, 0);

// print a heading nad print each row of results

    printf("\n");
    if(*pcDisplayPageWidth == 'W')
    {
        printf("   ID  Person                       Gender   Status       Age");
    }
    else if(*pcDisplayPageWidth == 'N')
    {
        printf("   ID  Person");
    }
    printf("\n\n");

    while(row = mysql_fetch_row(res))
    {
        if(*pcDipslayPageFormat == 'T')
        {
            bEndOfPrintBlock = false;
            iRowCount++;
            for(int i = 0; i < iColCount; i++)
            {
                if((i == 0) || (i == 4))
                {
                    printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                }
                else
                {
                    printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                }
            }
            printf("\n");
            if(iRowCount >= *piDisplayPageLength)
            {
                printf("\n");
                fPressEnterToContinue();
                printf("\n");
                iRowCount = 0;
            }
        }
        else
        {
            for(int i = 0; i < iColCount; i++)
            {
                if(i == 0)
                {
                    printf("     ");
                }
                else if(i == 3)
                {
                    continue;
                }
                else if(row[i])
                {
                    printf("%s, ", row[i]);
                }
                else
                {
                    printf("%s", "");
                }
            }
            printf("\n");
        }
    }

    printf("\n");
    if(bEndOfPrintBlock == false)
    {
        fPressEnterToContinue();
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}
