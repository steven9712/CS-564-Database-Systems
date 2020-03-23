//
// File: wl.h
// 
//  Description: Program 1
//  Student Name: Steven Choi 
//  UW Campus ID: 9074018194
//  enamil: schoi243@wisc.edu

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>


using namespace std;

/// @brief enumeration for the specific commands in this program
typedef enum command {
	LOAD, 
	LOCATE,
	NEW,
	END,
	ERROR
} command;

