#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_struct.h"
#include "experiment.h"
#include "xmlReader.h"

enum STATE {IDLE,DEBUT, NOM};

/* Retourne une file contenant l'heure de début de chaque expérience */
QueueS* scheduleStart(char* filename);
/* Affiche le début et la fin de chaque expérience dans l'ordre chronologique */
void completeSchedule(char * filename);
