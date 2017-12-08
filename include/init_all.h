#ifndef INIT_ALL
#define INIT_ALL
#include <pthread.h>
#include "can_var.h"
#include "listen.h"
#include "communicationSTM.h"

/***********************  init_socket   *******************
 * Initialise et configure un socket conformément aux variables
 * qu'on veut recevoir
 * INPUTS : s : socket à initialiser
 *********************************************************/
void init_socket(int *s);
#endif