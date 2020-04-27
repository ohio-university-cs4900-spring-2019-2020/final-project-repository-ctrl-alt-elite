//***************************************************************************
//
// This file contains preprosses definitions for portions of the code that
// may be considered optional or extraneous in certain situations. Comment
// out the preprocessor definition for the corresponding code if you do not
// need it.
//
// Do NOT re-commit this file unless all of the definitions are uncommented.
//
//***************************************************************************
#pragma once

//comment out to disable time diagnostic gathering for a slight (measurement to be conducted later) efficiency boost, no module will need this in an official release
#define TIME_DIAGNOSTIC

//number of "slots" for the time marker/retriever
#define NUM_TIME_MARKERS 20

