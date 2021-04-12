#pragma once

typedef enum _PaperSize {
	AMERICAN_LETTER = 1
} PaperSize;

typedef enum _Orientation {
	PORTRAIT = 1,
	LANDSCAPE = 2
} Orientation;

typedef struct _PaperSizeSpecification {
	double width_in_points;
	double height_in_points;
} PaperSizeSpecification;

extern PaperSizeSpecification paperSizeSpecifications[10]; 

#ifdef __cplusplus
extern "C" {
#endif
	PaperSizeSpecification getPaperSizeSpecification(PaperSize, Orientation);
#ifdef __cplusplus
}
#endif
