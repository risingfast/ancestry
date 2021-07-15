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
#### Enhancements: (0)
    create loop around printing person list options
    enable options
    add generational logic for baby boomers, millenials, gen-X'ers etc
    remove the temporarily disabled password
    send or show reminders of upcoming birthdays and events via emial
