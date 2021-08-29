# -*- makefile -*-
# makefile for mysql-c-ancestry project
# Created: 14-Jul-2021
# Geoffrey Jarman
# $@ Target file
# $^ Dependency files
# $(CC) Compiler executable
# $(CFLAGS) Compiler options
# $@ Souce file
# $^ Dependent files (dependencies)

# Variables

CC=gcc
CFLAGS=-g -o
SQL1FLAGS=-I/usr/include/mysql
SQL2FLAGS=-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl -lresolv

all: mysql-c-ancestry mcaListPeople mcaListProfile mcaListCohorts mcaListBirthdays mcaListMarriages mcaListReferences mcaListResidents mcaListProfRefLinks mcaShowTree

mysql-c-ancestry: mysql-c-ancestry.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListPeople: mcaListPeople.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListProfile: mcaListProfile.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListCohorts: mcaListCohorts.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListBirthdays: mcaListBirthdays.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListResidents: mcaListResidents.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListReferences: mcaListReferences.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListMarriages: mcaListMarriages.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaListProfRefLinks: mcaListProfRefLinks.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

mcaShowTree: mcaShowTree.c ../shared/rf50.c ../shared/cs50.c
	$(CC) $(CFLAGS) $@ $(SQL1FLAGS) $^ $(SQL2FLAGS)

clean:
	rm -f *.o *.s *.i mysql-c-ancestry mcaListPeople mcaListProfile mcaListCohorts mcaListBirthdays mcaListProfRefLinks mcaShowTree
