#### Project
    mysql-c-ancestry
#### Description
    Console c program using mysql C api to Jarman family ancestors
#### Author
    Geoffrey Jarman
#### Started
    14-Jul-2021
#### References:
    https://qnaplus.com/how-to-access-mysql-database-from-c-program/
#### Prerequisites:
    None
#### Installation:
    Create a local repository and clone down
    Run ./mysql-c-ancestry from the local directory
#### Compliation:
    make, or
    gcc -g -o mysql-c-ancestry $(mysql_config --cflags) mysql-c-ancestry.c $(mysql_config --libs) cs50.c rf50.c
#### Log:
    14-Jul-2021 started
    15-Jul-2021 fix the age formula to account for months and days
    15-Jul-2021 add cohort table and listing option
    15-Jul-2021 create loop around printing person list options
    15-Jul-2021 enable options
    16-Jul-2021 add upcoming birthdays to the list functions
#### Enhancements: (0)
    add intelligent headings on listings
    send or show reminders of upcoming birthdays and events via emial
    remove the temporarily disabled password
