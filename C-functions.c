//
// To view/edit the script, click the Develop Script button
//
// This file defines the data and functions that will be used by EvalC
// steps in the script
//
// Note: this file is mandatory, do not delete it.

#include "lrun.h"
#include <stdlib.h>
#include <time.h>

int getRandomArticleIndex(void) {
    const char* countStr;
    int count;
    int randomIndex;
    char result[10];

    // Get article count from parameter
    countStr = lr_eval_string("{articleCount}");
    count = atoi(countStr);

    if (count <= 0) {
        lr_error_message("Invalid article count: %s", countStr);
        return -1;
    }

    // Seed random and generate index
    srand((unsigned int)time(NULL));
    randomIndex = rand() % count;

    // Convert to string and save to LR param
    sprintf(result, "%d", randomIndex);
    lr_save_string(result, "randomIndex");

    lr_output_message("Random article index (from C): %s", result);
    return randomIndex;
}
