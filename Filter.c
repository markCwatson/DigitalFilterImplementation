/*
 * Filter.c
 *
 * Created: 2021-07-29 7:33:01 AM
 *  Author: mwatson
 */

#include "Filter.h"
#include <stdlib.h>

void FilterInit(Filter *filter, double *coefficients, double *dataBuffer, const uint8_t length)
{
    if ((filter != NULL) && (coefficients != NULL) && (dataBuffer != NULL) && (length > 0)) {

        filter->coefficients = coefficients;
        filter->dataBuffer = dataBuffer;
        filter->length = length;
        filter->putIndex = 0;

        for (uint8_t n = 0; n < length; n++)
            filter->dataBuffer[n] = 0.0;
    }
}

double FilterImplementation(Filter *filter, double input)
{
    double result;
    uint8_t getIndex = filter->putIndex;

    filter->dataBuffer[getIndex] = input;

    // Compute convolution of dataBuffer with impulse response of filter defined by coefficients.
    result = 0.0;

    for (uint8_t n = 0; n < filter->length; n++) {
        result += filter->coefficients[n] * filter->dataBuffer[getIndex];

        if (getIndex == 0)
            getIndex = filter->length - 1; // wrap around circular buffer
        else
            getIndex--;
    }

    filter->putIndex++;

    if (filter->putIndex == filter->length)
        filter->putIndex = 0; // wrap around circular buffer

    return result; // Return filtered output at current time
}

void ClearFilterDataBuffer(Filter *filter, double *dataBuffer, const uint8_t length)
{
    for (uint8_t n = 0; n < length; n++)
        filter->dataBuffer[n] = 0.0;
}
