/*
 * Filter.h
 *
 * Created: 2021-07-29 7:32:03 AM
 *  Author: mwatson
 */

#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

typedef struct {
    double *coefficients;
    double *dataBuffer;
    uint8_t length;
    uint8_t putIndex;
} Filter;

/**
*  \brief Initializes a digital filter.
*
*  \param filter A pointer to the Filter structure.
*  \param coefficients A pointer to an array of the filter coefficients.
*  \param dataBuffer A pointer to the circular data buffer.
*  \param length The length of the data buffer (i.e. the number of samples).
*/
void FilterInit(Filter *filter, double *coefficients, double *dataBuffer, const uint8_t length);

/**
*  \brief Implements the digital filter.
*
*  \param filter A pointer to the Filter structure.
*  \param input The newest data input to be added to the circular buffer and processed with the filter.
*
*  \returns The filtered output at current time.
*/
double FilterImplementation(Filter *filter, double input);

/**
*  \brief Clears the data buffer for digital filter.
*
*  \param filter A pointer to the Filter structure.
*  \param dataBuffer A pointer to the data buffer to be cleared.
*  \param length The length of the data buffer.
*/
void ClearFilterDataBuffer(Filter *filter, double *dataBuffer, const uint8_t length);

#endif
