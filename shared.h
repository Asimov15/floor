#ifndef SHARED_INCLUDES_HEADER
#define SHARED_INCLUDES_HEADER


// Open GL libraries.
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

#include "audax.h"
#include "color.h"
#include "body.h"
#include "spatium.h"

int main(int argc, char** args);

void initialize(vector<body>&, spatium *);
#endif


