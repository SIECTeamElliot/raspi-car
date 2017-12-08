#ifndef LISTEN_H
#define LISTEN_H

#include <stdio.h>
#include <pthread.h>
#include "can_var.h"
#define DEBUG 1

#define TH_NAME "[Listen]"



/***********************  Listen   **********************
 * Réception/traitement des messages provenant du CAN
 * INPUTS : socketCAN : socket can 
 *********************************************************/
void * listenCAN (void * socketCAN);


#endif