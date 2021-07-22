// includes and defines

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs50.h"
#include "rf50.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SQL_LEN 5000
#define HDG_LEN 1000

// function declarations

void fShowMainMenu(void);                                                                 // show the main console menu
void fGetPwdFromConsole(void);                                                       // get a password from the console
void fListPeople(char *, int *, char *, char *, char *);                                    // display a list of people
void fListMarriages(char *, int *, char *, char *, char *);                              // display a list of marriages
void fPrintListHeading(char *, char*);                                          // print the heading for a console list
void fSetOptions(char *, int *, char *, char *, char *);                                    // main menu to set options
void fShowPersonProfile(char *, int *, char *, char *, char *);                              // show a person's profile
int  fGetTableLength(char *);                                                              // count the rows in a table
int  fGetPersonMaxID(void);                                                       // get the max ID in the person table
bool fValidatePersonID(int);                                                  // validate an entered int as a Person ID
void fPrintPersonProfile(char *, int);                                       // print a person's profile to the console
void fPrintPersonSearch(char *, int *);                                    // print a person search list to the console
void fPrintParents(char *, int);                                                            // print a person's parents
void fPrintSiblings(char *, int);                                                           // print a person's parents
void fPrintChildren(char *, int);                                                          // print a person's children
void fPrintMarriages(char *, int);                                                        // print a person's marriages
void fPrintDivorces(char *, int);                                                          // print a person's divorces
void fPrintAddresses(char *, int);                                                         // print a person's divorces
void fPrintReferences(char *, int);                                                      // print a person's references

// global declarations

char *sgServer = "192.168.0.13";                                                               //mysqlServer IP address
char *sgUsername = "gjarman";                                                              // mysqlSerer logon username
char sgPassword[20] = {'\0'};                                                     // password to connect to mysqlserver
char *sgDatabase = "risingfast";                                                // default database name on mysqlserver

MYSQL *conn;

int main(int argc, char **argv)
{

// declarations

    char *sPrgNme = strcat(argv[0] + 2, " -- Jarman family and relatives");                             // program name
    bool bHelp = false;                                                                  // help flag to show help text
    bool bExitMainMenu = false;                                                             // flag to exit the program
    char cMainChoice = '0';                                                                         // main menu choice
    int  iDisplayPageLength = 40;                                                      // display page lines for paging
    char cDisplayPageWidth = 'W';                                                  // display page width wide or narrow
    char cDisplayPageFormat = 'T';                                                // display page format (T)ab or (C)SV
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

    while(bExitMainMenu == false)
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
            fListPeople(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("2eE", cMainChoice) != NULL)
        {
            printf("\n");
            fListMarriages(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("3pP", cMainChoice) != NULL)
        {
            printf("\n");
            fShowPersonProfile(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("4rR", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 4rR");
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
            fPressEnterToContinue();
        }
        else if(strchr("nN5", cMainChoice) != NULL)
        {
            printf("\n");
            printf("You chose: 5nN");
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
            fPressEnterToContinue();
        }
        else if(strchr("sS6", cMainChoice) != NULL)
        {
            printf("\n");
            fSetOptions(sPrgNme, &iDisplayPageLength, &cDisplayPageWidth, &cDisplayPageFormat, &cDisplayOrder);
            printf("\n");
            cMainChoice = '0';
            bExitMainMenu = false;
        }
        else if(strchr("xX7", cMainChoice) != NULL)
        {
            bExitMainMenu = true;
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
    printf("5. E(n)ter Marriages");
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

void fListPeople(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    int iColCount = 0;
    int *iLengths = NULL;
    int iRowCount = 0;
    char cQueryFilterchoice = '0';
    char caOrder[6] = {'D', 'E', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    bool bEndOfPrintBlock = false;
    bool bExitListMenu = false;
    char caListHeading[HDG_LEN] = {'\0'};

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
    
    while(bExitListMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > List People > People names ...");
        printf("\n\n");
        printf("(A)ll, (M)ales, (F)emales, (L)iving, (D)eceased, (C)ohort, (B)irthdays or E(x)it");
        printf("\n\n");
        while(strchr("aAmMfFlLdDcCbBxX", cQueryFilterchoice) == NULL)
        {
            printf("Choice: ");
            cQueryFilterchoice = toupper(GetChar());
        }
        if(toupper(cQueryFilterchoice) == 'X')
        {
            bExitListMenu = true;
            return;
        }
        else if(cQueryFilterchoice == 'A')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Actual`= TRUE"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'M')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Actual`= TRUE"
                                "  AND AP.`Gender` = 'Male'"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'F')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Actual`= TRUE"
                                "  AND AP.`Gender` = 'Female'"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'L')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Actual`= TRUE"
                                "  AND AP.`Deceased` = 0"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age");
        }
        else if(cQueryFilterchoice == 'D')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status'"
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') as 'Age' "
                                "  FROM risingfast.`Ancestry People` AP"
                                "  WHERE AP.`Actual`= TRUE"
                                "  AND AP.`Deceased` = 1"
                                "  ORDER BY AP.`Person ID` %s", caOrder)
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/AgeAtDeath");
        }
        else if(cQueryFilterchoice == 'C')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') as 'ID' "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') AS 'Age' "
                                ", AC.Cohort "
                                "  FROM risingfast.`Ancestry People` AP "
                                "  LEFT JOIN risingfast.`Ancestry Cohorts` AC on (AP.`Born On` >= AC.`Start`) "
                                "  and (AP.`Born On` <= AC.`Finish`) "
                                "  WHERE AP.`Actual`= TRUE" )
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age/Cohort");
        }
        else if(cQueryFilterchoice == 'B')
        {
            sprintf(caSQL, "SELECT LPAD(AP.`Person ID`, 4, ' ') as 'ID' "
                                ", CONCAT(AP.`First Name`, ' ', AP.`Last Name`) AS `Person` "
                                ", AP.`Gender` "
                                ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                                ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 0), "
                                "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 0)), '') AS 'Current Age' "
                                ", AP.`Born On` "
                                ", IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 "
                                "  - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) 'Mths Away' "
                                "  FROM risingfast.`Ancestry People` AP "
                                "  WHERE IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 "
                                "  - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) < 12 "
                                "  AND AP.`Deceased` = 0 "
                                "  AND AP.`Actual`= TRUE"
                                "  ORDER BY IF(MONTH(AP.`Born On`) - MONTH(CURRENT_DATE()) < 0, MONTH(AP.`Born On`) + 12 "
                                "  - MONTH(CURRENT_DATE()) , MONTH(AP.`Born On`) - MONTH(CURRENT_DATE())) asc ")
                                ;
            cQueryFilterchoice = '0';
            strcpy(caListHeading, "ID/Person/Gender/Status/Age/Birthday/MonthsAway");
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
    
// print a heading 
    
        fPrintListHeading(pcDisplayPageWidth, caListHeading);
   
// print each row of results

        iRowCount = 0;
        while(row = mysql_fetch_row(res))
        {
            if(*pcDisplayPageFormat == 'T')
            {
//                bEndOfPrintBlock = false;
                for(int i = 0; i < iColCount; i++)
                {
                    if(i == 0)
                    {
                        printf("%s", row[i]);
                    }
                    else if((i == 4) || (i == 6))
                    {
                        printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                    else
                    {
                        printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                }
                iRowCount++;
                printf("\n");
                if(iRowCount >= *piDisplayPageLength)
                {
                    printf("\n");
                    fPressEnterToContinue();
                    fRetitleConsole(sPrgNme);
                    printf("\n");
                    printf("Main Menu > List People > People names ...");
                    printf("\n\n");
                    printf("(A)ll, (M)ales, (F)emales, (L)iving, (D)eceased, (C)ohort, (B)irthdays or E(x)it");
                    printf("\n\n");
                    printf("Choice: ");
                    printf("\n");
                    fPrintListHeading(pcDisplayPageWidth, caListHeading);
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
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}

void fPrintListHeading(char *pcDisplayPageWidth, char caListHeading[])
{
    printf("\n");
    if(*pcDisplayPageWidth == 'W')
    {
        printf("%s", caListHeading);
    }
    else if(*pcDisplayPageWidth == 'N')
    {
        printf("   ID  Person");
    }
    printf("\n\n");
}
void fSetOptions(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDispayPageFormat, char *pcDisplayOrder)
{

    int  iOptionChoice = '0';
    bool bExitOptions = false;
    bool bValidOptionChoice = false;

    fRetitleConsole(sPrgNme);

    while(bExitOptions == false)
    {
        while(iOptionChoice == '0')
        {
            printf("\n");
            printf("Main Menu > Set Options");
            printf("\n");
            printf("\n");
            printf("1. Display (L)ength: %9d", *piDisplayPageLength);
            printf("\n");
            printf("2. Display (W)idth: %10s", (*pcDisplayPageWidth == 'N') ? "Narrow" : "Wide");
            printf("\n");
            printf("3. List (F)ormat: %12s", (*pcDispayPageFormat == 'T') ? "Tab" : "CSV");
            printf("\n");
            printf("4. List (O)rder: %13s", (*pcDisplayOrder == 'A') ? "Ascending" : "Descending");
            printf("\n");
            printf("5. (P)rint Options");
            printf("\n");
            printf("6. (R)eset Options");
            printf("\n");
            printf("7. E(x)it");
            printf("\n\n");
            printf("Choice: ");
            iOptionChoice = GetChar();
            if(strchr("1234567LloOpPrRxX", iOptionChoice) == NULL)
            {
                iOptionChoice = '0';
            }
        }
        if(strchr("1lL", iOptionChoice) != NULL)
        {
            printf("\n");
            printf("Display Length: ");
            *piDisplayPageLength = GetInt();
            printf("\n");
            iOptionChoice = '0';
        }
        else if(strchr("2wW", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Width ((W)ide or (N)arrow) or E(x)it: ");
                *pcDisplayPageWidth = toupper(GetChar());
                if(*pcDisplayPageWidth == 'W')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayPageWidth == 'N')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayPageWidth == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("3fF", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Format ((T)ab or (C)SV) or E(x)it: ");
                *pcDispayPageFormat = toupper(GetChar());
                if(*pcDispayPageFormat == 'T')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDispayPageFormat == 'C')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDispayPageFormat == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("4oO", iOptionChoice) != NULL)
        {
            printf("\n");
            while(bValidOptionChoice == false)
            {
                printf("Display Order ((A)sc or (D)esc or E(x)it): ");
                *pcDisplayOrder = toupper(GetChar());
                if(*pcDisplayOrder == 'A')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayOrder == 'D')
                {
                    bValidOptionChoice = true;
                }
                else if(*pcDisplayOrder == 'X')
                {
                    bValidOptionChoice = true;
                }
                else
                {
                    bValidOptionChoice = false;
                }
            }
            printf("\n");
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("5pP", iOptionChoice) != NULL)
        {
            *pcDispayPageFormat = 'C';
            *pcDisplayOrder = 'A';
            *piDisplayPageLength = 1000;
            *pcDisplayPageWidth = 'W';
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("6rR", iOptionChoice) != NULL)
        {
            *pcDispayPageFormat = 'T';
            *pcDisplayOrder = 'A';
            *piDisplayPageLength = 80;
            *pcDisplayPageWidth = 'N';
            bValidOptionChoice = false;
            iOptionChoice = '0';
        }
        else if(strchr("7xX", iOptionChoice) != NULL)
        {
            bExitOptions = true;
        }
        fRetitleConsole(sPrgNme);
    }

    return;
}

void fListMarriages(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    int iColCount = 0;
    int *iLengths = NULL;
    int iRowCount = 0;
    char cQueryFilterchoice = '0';
    char caOrder[6] = {'D', 'E', 'S', 'C', '\0'};
    char caSQL[SQL_LEN] = {'\0'};
    bool bEndOfPrintBlock = false;
    bool bExitListMenu = false;
    char caListHeading[HDG_LEN] = {'\0'};

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
    
    while(bExitListMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > List Marriages ...");
        printf("\n\n");
        printf("(A)ll, (U)pcoming or E(x)it");
        printf("\n\n");
        while(strchr("aAuUxX", cQueryFilterchoice) == NULL)
        {
            printf("Choice: ");
            cQueryFilterchoice = toupper(GetChar());
        }
        if(toupper(cQueryFilterchoice) == 'X')
        {
            bExitListMenu = true;
            return;
        }
        else if(cQueryFilterchoice == 'A')
        {
            sprintf(caSQL, "SELECT AM.`Marriage ID` "
                                ", AM.`Marriage Type` "
                                ", CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`) AS `First Person` "
                                ", CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`) AS `First Person` "
                                ", AM.`Marriage Date` "
                                ", AM.`Marriage Place` "
                                ", AC.`Country Abbreviation` "
                                "  FROM risingfast.`Ancestry Marriages` AM "
                                "  LEFT JOIN risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Marriage Country ID` = AC.`Country ID`")
                                ;

            cQueryFilterchoice = '0';
            strcpy(caListHeading, "MarriageID/Type/Husband/Wife/Date/Place/Country");
        }
        else if(cQueryFilterchoice == 'U')
        {
            sprintf(caSQL, "SELECT AM.`Marriage ID` "
                                ", AM.`Marriage Type` "
                                ", CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`) AS `First Person` "
                                ", CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`) AS `First Person` "
                                ", AM.`Marriage Date` "
                                ", AM.`Marriage Place` "
                                ", AC.`Country Abbreviation` "
                                ", IF(MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AM.`Marriage Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE())) AS 'Mths Away' "
                                "  FROM risingfast.`Ancestry Marriages` AM "
                                "  LEFT JOIN risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                                "  LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Marriage Country ID` = AC.`Country ID` "
                                "  WHERE IF(MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AM.`Marriage Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE())) < 12 "
                                "  ORDER BY IF(MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE()) < 0, MONTH(AM.`Marriage Date`) + 12 - MONTH(CURRENT_DATE()) , MONTH(AM.`Marriage Date`) - MONTH(CURRENT_DATE())) asc ")
                                ;

            cQueryFilterchoice = '0';
            strcpy(caListHeading, "MarriageID/Marriage/FirstPerson/SecondPerson/Date/Place/Country/MthsAway");
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
    
// print a heading 
    
        fPrintListHeading(pcDisplayPageWidth, caListHeading);
   
// print each row of results

        iRowCount = 0;
        while(row = mysql_fetch_row(res))
        {
            if(*pcDisplayPageFormat == 'T')
            {
                for(int i = 0; i < iColCount; i++)
                {
                    if((i == 0) || (i == 4) || (i == 7))
                    {
                        printf("  %*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                    else
                    {
                        printf("  %-*s", iLengths[i] + 1, row[i] ? row[i] : "");
                    }
                }
                iRowCount++;
                printf("\n");
                if(iRowCount >= *piDisplayPageLength)
                {
                    printf("\n");
                    fPressEnterToContinue();
                    fRetitleConsole(sPrgNme);
                    printf("\n");
                    printf("Main Menu > List People > People names ...");
                    printf("\n\n");
                    printf("(A)ll, (U)pcoming or E(x)it");
                    printf("\n\n");
                    printf("Choice: ");
                    printf("\n");
                    fPrintListHeading(pcDisplayPageWidth, caListHeading);
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
        fPressEnterToContinue();
    }

    fRetitleConsole(sPrgNme);
    free(iLengths);
    mysql_free_result(res);
    return;
}

void fShowPersonProfile(char *sPrgNme, int *piDisplayPageLength, char *pcDisplayPageWidth, char *pcDisplayPageFormat, char *pcDisplayOrder)
{
    char cProfileMenuChoice = 'O';
    bool bExitProfileMenu  = false;
    char caSQL[SQL_LEN] = {'\0'};
    char *sSingleSpace = " ";
    int  iRowCount = 0;
    int  iColCount = 0;
    int  iPersonID = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    while(bExitProfileMenu == false)
    {
        fRetitleConsole(sPrgNme);
        printf("\n");
        printf("Main Menu > Person Profile ...");
        printf("\n\n");
        printf("(S)how, Sea(r)ch or E(x)it");
        printf("\n\n");
        while(strchr("sSrRxX", cProfileMenuChoice) == NULL)
        {
            printf("Choice: ");
            cProfileMenuChoice = toupper(GetChar());
        }
        if(toupper(cProfileMenuChoice) == 'X')
        {
            bExitProfileMenu = true;
            return;
        }
        else if(cProfileMenuChoice == 'S')
        {
            cProfileMenuChoice = '0';
            printf("\n");

            do {
                printf("Person ID (1 - %d): ", fGetPersonMaxID());
                iPersonID = GetInt();
                printf("\n");
                if (fValidatePersonID(iPersonID) == false)
                {
                    printf("Not a valid Person ID");
                    printf("\n\n");
                    iPersonID = 0;
                    fPressEnterToContinue();
                    printf("\n");
                }
            } while(iPersonID < 1 || iPersonID > fGetPersonMaxID());

            fPrintPersonProfile(sPrgNme, iPersonID);
            fPrintParents(sPrgNme, iPersonID);
            fPrintSiblings(sPrgNme, iPersonID);
            fPrintMarriages(sPrgNme, iPersonID);
            fPrintDivorces(sPrgNme, iPersonID);
            fPrintChildren(sPrgNme, iPersonID);
            fPrintAddresses(sPrgNme, iPersonID);
            fPrintReferences(sPrgNme, iPersonID);
            fPressEnterToContinue();
            fRetitleConsole(sPrgNme);
        }

        else if(cProfileMenuChoice == 'R')
        {
            cProfileMenuChoice = '0';
            fPrintPersonSearch(sPrgNme, piDisplayPageLength);
            printf("\n");
            fPressEnterToContinue();
            fRetitleConsole(sPrgNme);
        }
    }
    return;
}


int fGetTableLength(char *sTblNme)
{
    char caSQL[SQL_LEN] = {'\0'};
    char *ptr;

    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL, "SELECT COUNT(*) FROM risingfast.`%s`", sTblNme);

// execute the query and check for no result
    
        if(mysql_query(conn, caSQL) != 0)
        {
            printf("\n");
            printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
            printf("\n\n");
            fPressEnterToContinue();
            return -1;
        }

// store the result of the query

        res = mysql_store_result(conn);
        if(res == NULL)
        {
            printf("%s() -- no results returned", __func__);
            printf("\n");
    
            mysql_free_result(res);
            return -1;
        }
    
// print each row of results

    row = mysql_fetch_row(res);

    mysql_free_result(res);
    return (int) strtol(row[0], &ptr, 10);
}

int fGetPersonMaxID(void)
{
    char caSQL[SQL_LEN] = {'\0'};
    char *ptr;

    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL, "SELECT MAX(`Person ID`) FROM risingfast.`Ancestry People`");

// execute the query and check for no result
    
        if(mysql_query(conn, caSQL) != 0)
        {
            printf("\n");
            printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
            printf("\n\n");
            fPressEnterToContinue();
            return -1;
        }

// store the result of the query

        res = mysql_store_result(conn);
        if(res == NULL)
        {
            printf("%s() -- no results returned", __func__);
            printf("\n");
    
            mysql_free_result(res);
            return -1;
        }
    
// print each row of results

    row = mysql_fetch_row(res);

    mysql_free_result(res);
    return (int) strtol(row[0], &ptr, 10);
}

void fPrintPersonProfile(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    char *sSingleSpace = " ";

    MYSQL_RES *res;
    MYSQL_ROW row;

    fRetitleConsole(sPrgNme);
    printf("\n");
    printf("Main Menu > Person Profile > Show ...");
    printf("\n\n");

    sprintf(caSQL, "select AP.`Person ID` as 'ID' "
                        ", AP.`First Name` as 'First' "
                        ", AP.`Middle Names` as 'Middle' "
                        ", AP.`Last Name` as 'Last' "
                        ", AP.`Birth Last Name` as 'Née' "
                        ", AP.`Born On` as 'Born' "
                        ", AP.`Birth Place` as 'Born In' "
                        ", IF(AP.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                        ", AP.`Deceased On` AS 'Deceased On' "
                        ", AP.`Deceased Place` AS 'Deceased Place' "
                        ", AP.`Cause of Death` AS 'Cause of Death' "
                        ", COALESCE(IF(AP.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AP.`Born On`)/365, 1), "
                        "  ROUND(DATEDIFF(AP.`Deceased On`, AP.`Born On`)/365, 1)), '') AS 'Age' "
                        ", AP.`Profile` "
                        ", AP.`Education` "
                        " FROM risingfast.`Ancestry People` AP "
                        " WHERE AP.`Actual`= TRUE"
                        " AND AP.`Person ID` = %d", iPersonID);

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

// print the profile

    row = mysql_fetch_row(res);
    printf("Profile:");
    printf("\n\n");
    printf("  Person ID:      %s", (row[0] == NULL) ? sSingleSpace : row[0]);
    printf("\n");
    printf("  First Name:     %s", (row[1] == NULL) ? sSingleSpace : row[1]);
    printf("\n");
    printf("  Middle Name:    %s", (row[2] == NULL) ? sSingleSpace : row[2]);
    printf("\n");
    printf("  Last Name:      %s", (row[3] == NULL) ? sSingleSpace : row[3]);
    printf("\n");
    printf("  Née:            %s", (row[4] == NULL) ? sSingleSpace : row[4]);
    printf("\n");
    printf("  Born on:        %s", (row[5] == NULL) ? sSingleSpace : row[5]);
    printf("\n");
    printf("  Birth Place:    %s", (row[6] == NULL) ? sSingleSpace : row[6]);
    printf("\n");
    printf("  Status:         %s", (row[7] == NULL) ? sSingleSpace : row[7]);
    printf("\n");
    printf("  Deceased On:    %s", (row[8] == NULL) ? sSingleSpace : row[8]);
    printf("\n");
    printf("  Deceased At:    %s", (row[9] == NULL) ? sSingleSpace : row[9]);
    printf("\n");
    printf("  Cause of Death: %s", (row[10] == NULL) ? sSingleSpace : row[10]);
    printf("\n");
    printf("  Age:            %s", (row[11] == NULL) ? sSingleSpace : row[11]);
    printf("\n");
    printf("  Profile:        %s", (row[12] == NULL) ? sSingleSpace : row[12]);
    printf("\n");
    printf("  Education:      %s", (row[13] == NULL) ? sSingleSpace : row[13]);
    printf("\n\n");
    mysql_free_result(res);
    
    return;
}

void fPrintPersonSearch(char *sPrgNme, int *piDisplayPageLength)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    fRetitleConsole(sPrgNme);
    printf("\n");
    printf("Main Menu > Person Profile > Search ...");
    printf("\n\n");

    sprintf(caSQL,"SELECT LPAD(AP.`Person ID`, 4, ' ') "
                ", REPLACE(CONCAT(COALESCE(AP.`First Name`, ''), ' ', COALESCE(AP.`Middle Names`, ''), ' ',"
                " COALESCE(AP.`Last Name`, '')), '  ', ' ')"
                " FROM risingfast.`Ancestry People` AP "
                " ORDER BY AP.`Person ID` ASC" );

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        printf("  %s", row[0]);
        printf("  %s", row[1]);

        iRowCount++;
        printf("\n");
    }
    if (iRowCount < *piDisplayPageLength)
    {
        printf("\n");
    }
    mysql_free_result(res);
    return;
}

void fPrintParents(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Parents:");
    printf("\n\n");

    sprintf(caSQL, "SELECT LPAD(AM.`Person ID`, 4, ' ') AS 'Parent ID' "
                      " , 'Mother:' as 'Relation' "
                      " , AM.`First Name` AS 'First' "
                      " , COALESCE(AM.`Middle Names`, '') AS 'Middle' "
                      " , CONCAT(AM.`Last Name`, ' (née ', AM.`Birth Last Name`, ')') AS 'Last' "
                      " , IF(AM.`Deceased` = 1, 'Deceased', 'Living') as 'Status' "
                      " , COALESCE(IF(AM.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AM.`Born On`)/365, 1), "
                      "   ROUND(DATEDIFF(AM.`Deceased On`, AM.`Born On`)/365, 1)), '') as 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT join risingfast.`Ancestry People` AM ON AP.`Mother ID` = AM.`Person ID` "
                   "WHERE  AP.`Person ID` = %d "
                   "AND AM.`Actual` = TRUE "
                   "UNION DISTINCT "
                   "SELECT LPAD(AF.`Person ID`, 4, ' ') AS 'Parent ID' "
                      ", 'Father:' AS 'Relation' "
                      ", AF.`First Name` AS 'First' "
                      ", COALESCE(AF.`Middle Names`, '') AS 'Middle' "
                      ", AF.`Last Name` AS 'Last' "
                      ", IF(AF.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      ", COALESCE(IF(AF.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AF.`Born On`)/365, 1), "
                      "  ROUND(DATEDIFF(AF.`Deceased On`, AF.`Born On`)/365, 1)), '') AS 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT JOIN risingfast.`Ancestry People` AF ON AP.`Father ID` = AF.`Person ID` "
                   "WHERE  AP.`Person ID` = %d "
                   "AND AF.`Actual` = TRUE ", iPersonID, iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            printf(" %s", row[5]);
            printf(" %s", row[6]);
            iRowCount++;
            printf("\n");
        }
    }
    mysql_free_result(res);
    printf("\n");
    return;
}

void fPrintSiblings(char *sPrgNme, int iPersonID )
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Siblings:");
    printf("\n\n");

    sprintf(caSQL, "SELECT LPAD(AC.`Person ID`, 4, ' ') AS 'Sibling ID' "
                       ", 'Sibling:' AS 'Relation' "
                       " , AC.`First Name` AS 'First' "
                       " , AC.`Middle Names` AS 'Middle' "
                       " , IF(AC.`Gender` = 'Female', (CONCAT(AC.`Last Name`, ' (née ', AC.`Birth Last Name`, ')')), AC.`Last Name`) AS 'Last' "
                       " , IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                       " , COALESCE(IF(AC.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365, 1), "
                       "   ROUND(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365, 1)), '') as 'Age' "
                   "FROM risingfast.`Ancestry People` AP "
                   "LEFT JOIN risingfast.`Ancestry People` AC on AP.`Mother ID` = AC.`Mother ID` AND AP.`Father ID` = AC.`Father ID` "
                   "LEFT JOIN risingfast.`Ancestry People` AM on AP.`Mother ID` = AM.`Person ID` "
                   "LEFT JOIN risingfast.`Ancestry People` AF on AP.`Father ID` = AF.`Person ID` "
                   "WHERE  AP.`Person ID` in (%d) "
                   "AND AC.`Actual` = TRUE "
                   "AND AM.`Actual` = TRUE "
                   "AND AF.`Actual` = TRUE "
                   "AND AP.`Person ID` != AC.`Person ID`", iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            printf(" %s", row[5]);
            printf(" %s", row[6]);
        }
        iRowCount++;
        printf("\n");
    }
    printf("\n");
    mysql_free_result(res);
    return;
}

void fPrintChildren(char *sprgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Children:");
    printf("\n\n");

    sprintf(caSQL, "SELECT LPAD(AC.`Person ID`, 4, ' ') AS AP"
                      " , 'Child:' AS 'Relation' "
                      " , AC.`First Name` AS 'First' "
                      " , COALESCE(AC.`Middle Names`, '') AS 'Middle' "
                      " , IF(AC.`Gender` = 'Female', (CONCAT(AC.`Last Name`, ' (née ', AC.`Birth Last Name`, ')')), AC.`Last Name`) AS 'Last' "
                      ",  IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      ",  COALESCE(IF(AC.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365, 1), "
                      "   ROUND(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365, 1)), '') AS 'Age' "
                   " FROM risingfast.`Ancestry People` AP "
                   " LEFT JOIN risingfast.`Ancestry People` AC ON AP.`Person ID` = AC.`Father ID` "
                   " WHERE AP.`Person ID` = %d "
                   " AND AC.`Actual` = TRUE "
                   " UNION ALL "
                   "SELECT LPAD(AC.`Person ID`, 4, ' ') AS AP"
                      " , 'Child:' AS 'Relation' "
                      " , AC.`First Name` AS 'First' "
                      " , COALESCE(AC.`Middle Names`, '') AS 'Middle' "
                      " , IF(AC.`Gender` = 'Female', (CONCAT(AC.`Last Name`, ' (née ', AC.`Birth Last Name`, ')')), AC.`Last Name`) AS 'Last' "
                      ",  IF(AC.`Deceased` = 1, 'Deceased', 'Living') AS 'Status' "
                      ",  COALESCE(IF(AC.`Deceased` = 0, ROUND(DATEDIFF(CURRENT_DATE(), AC.`Born On`)/365, 1), "
                      "   ROUND(DATEDIFF(AC.`Deceased On`, AC.`Born On`)/365, 1)), '') AS 'Age' "
                   " FROM risingfast.`Ancestry People` AP "
                   " LEFT JOIN risingfast.`Ancestry People` AC ON AP.`Person ID` = AC.`Mother ID` "
                   " WHERE AP.`Person ID` = %d"
                   " AND AC.`Actual` = TRUE ", iPersonID, iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            printf(" %s", row[5]);
            printf(" %s", row[6]);
            iRowCount++;
            printf("\n");
        }
    }
    printf("\n");
    mysql_free_result(res);
    return;
}

bool fValidatePersonID(int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    char *ptr;
    int  iRowsReturned = 0;
    bool bRetVal;

    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(caSQL, "SELECT AP.`Person ID` FROM risingfast.`Ancestry People` AP "
                   "WHERE AP.`Actual` = TRUE AND AP.`Person ID` = %d", iPersonID);

// execute the query and check for no result
    
        if(mysql_query(conn, caSQL) != 0)
        {
            printf("\n");
            printf("mysql_query() error in function %s():\n\n%s", __func__, mysql_error(conn));
            printf("\n\n");
            fPressEnterToContinue();
            return -1;
        }

// store the result of the query

        res = mysql_store_result(conn);
        if(res == NULL)
        {
            printf("%s() -- no results returned", __func__);
            printf("\n");
    
            mysql_free_result(res);
            return -1;
        }

//  count the number of rows returned ... should be 1

        iRowsReturned = mysql_num_rows(res);
        if(iRowsReturned > 0)
        {
            bRetVal = true;
        }
        else
        {
            bRetVal = false;
        }

// print each row of results

    row = mysql_fetch_row(res);
    mysql_free_result(res);

    return bRetVal;
}

void fPrintMarriages(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Marriages: ");
    printf("\n\n");

    sprintf(caSQL, "select LPAD(AM.`Marriage ID`, 4, ' ') "
                        " , CONCAT(AM.`Marriage Type`, ':') AS 'Marriage Type' "
                        " , CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`, ' and') AS `Husband` "
                        " , CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`, COALESCE(CONCAT(' (née ', AP2.`Birth Last Name`, ')'))) AS `Wife` "
                        " , COALESCE(AM.`Marriage Date`, '') "
                        " , AM.`Marriage Place` "
                        " , AC.`Country Abbreviation` "
                    " FROM risingfast.`Ancestry Marriages` AM "
                    " left join risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                    " left join risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                    " LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Marriage Country ID` = AC.`Country ID` "
                    " WHERE AM.`Husband ID` = %d OR AM.`Wife ID` = %d "
                    " AND AM.`Marriage Type` in ('Marriage', 'Divorce')", iPersonID, iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            printf(" %s", row[5]);
            printf(" %s", row[6]);
            iRowCount++;
            printf("\n");
        }
    }
    printf("\n");
    mysql_free_result(res);
    return;
}

void fPrintDivorces(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Divorces: ");
    printf("\n\n");

    sprintf(caSQL, "select LPAD(AM.`Marriage ID`, 4, ' ') "
                        " , 'Divorce' AS 'Marriage Type' "
                        " , CONCAT(AP1.`First Name`, ' ', AP1.`Last Name`, ' and') AS `Husband` "
                        " , CONCAT(AP2.`First Name`, ' ', AP2.`Last Name`, COALESCE(CONCAT(' (née ', AP2.`Birth Last Name`, ')'))) AS `Wife` "
                        " , COALESCE(AM.`Divorce Date`, '') "
                        " , AM.`Divorce Place` "
                        " , AC.`Country Abbreviation` "
                    " FROM risingfast.`Ancestry Marriages` AM "
                    " left join risingfast.`Ancestry People` AP1 on AM.`Husband ID` = AP1.`Person ID` "
                    " left join risingfast.`Ancestry People` AP2 on AM.`Wife ID` = AP2.`Person ID` "
                    " LEFT JOIN risingfast.`Ancestry Countries` AC on AM.`Divorce Country ID` = AC.`Country ID` "
                    " WHERE AM.`Husband ID` = %d OR AM.`Wife ID` = %d "
                    " AND AM.`Divorce date` != NULL", iPersonID, iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            printf(" %s", row[5]);
            printf(" %s", row[6]);
            iRowCount++;
            printf("\n");
        }
    }
    printf("\n");
    mysql_free_result(res);
    return;
}

void fPrintReferences(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("References: ");
    printf("\n\n");

    sprintf(caSQL, "SELECT LPAD(AR.`Reference ID`, 4, ' ') "
                      "  , AR.`Reference Name` "
                      "  , AR.`Reference Link` "
                      " FROM risingfast.`Ancestry References` AR "
                      " WHERE AR.`Person ID` = %d", iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", " ... ");
            printf(" %s", row[2]);
            iRowCount++;
            printf("\n");
        }
    }
    printf("\n");
    mysql_free_result(res);
    return;

}

void fPrintAddresses(char *sPrgNme, int iPersonID)
{
    char caSQL[SQL_LEN] = {'\0'};
    int  iRowCount = 0;
    int  iColCount = 0;

    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Addresses: ");
    printf("\n\n");

    sprintf(caSQL, " SELECT LPAD(AA.`Address ID`, 4, ' ') "
                   ", CONCAT(AA.`Address Line 1`, COALESCE(CONCAT(' ', AA.`Address Line 2`), ' ') "
                   ", COALESCE(CONCAT(' ', AA.`Address Line 3`), ' ')) AS Street "
                   ", AA.`Address City` "
                   ", AA.`Address State` "
                   ", AC.`Country Abbreviation` "
                   "  FROM risingfast.`Ancestry Addresses` AA "
                   "  LEFT JOIN risingfast.`Ancestry Residents` AR on AR.`Address ID` = AA.`Address ID` "
                   "  LEFT JOIN risingfast.`Ancestry Countries` AC on AA.`Address Country ID` = AC.`Country ID` "
                   "  WHERE AR.`Person ID` = %d", iPersonID);

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

// print each row of results

    iRowCount = 0;
    while(row = mysql_fetch_row(res))
    {
        if(row[0] != NULL)
        {
            printf("%s", row[0]);
            printf(" %s", row[1]);
            printf(" %s", row[2]);
            printf(" %s", row[3]);
            printf(" %s", row[4]);
            iRowCount++;
            printf("\n");
        }
    }
    printf("\n");
    mysql_free_result(res);
    return;
}
