#pragma once

typedef enum _PaperSize {
	AMERICAN_LETTER = 1
} PaperSize;

typedef struct _PaperSizeSpecification {
	double width_in_points;
	double height_in_points;
} PaperSizeSpecification;

extern PaperSizeSpecification paperSizeSpecifications[10]; 
