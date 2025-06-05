//
// Created by louai on 6/2/2025.
//

#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include <stdint.h>

// Initializes the edge detector (configures PA5 as input)
void EdgeDetector_Init(void);

// Checks if a falling edge is detected on PA5
uint8_t EdgeDetector_DetectedFallingEdge(void);

#endif // EDGE_DETECTOR_H
