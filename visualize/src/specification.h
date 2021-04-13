#pragma once

#include <stdint.h>
#include <time.h>

#include <cairo/cairo.h>

typedef enum _PaperSize {
	AMERICAN_LETTER = 0,
	NUMBER_OF_PAPER_SIZES = 1
} PaperSize;

typedef enum _Orientation {
	PORTRAIT = 0,
	LANDSCAPE = 1
} Orientation;

typedef enum _CalendarStrokeContexts {
	HOUR_STROKE_CONTEXT = 0,
	HALF_HOUR_STROKE_CONTEXT = 1,
	QUARTER_HOUR_STROKE_CONTEXT = 2,
	DAY_STROKE_CONTEXT = 3,
	NUMBER_OF_STROKE_CONTEXTS = 4
} CalendarStrokeContexts;

typedef struct _PaperSizeSpecification {
	double width_in_points;
	double height_in_points;
} PaperSizeSpecification;

typedef struct _CalendarDayMargins {
	double leftMargin;
	double rightMargin;
	double topMargin;
	double bottomMargin;
} CalendarDayMargins;

// 24-hour clock, please
typedef struct _HoursContext {
	uint8_t startingHour;
	uint8_t endingHour;
} HoursContext;

typedef struct _CairoDashSimple {
	double dashes[256];
	double offset;
} CairoDashSimple;

typedef struct _CairoDash {
	double* dashes;
	int numberOfDashes;
	double offset;
} CairoDash;

typedef struct _StrokeContext {
	double lineWidth;
	cairo_line_cap_t lineCap;
	CairoDash cairoDash;
} StrokeContext;

typedef StrokeContext StrokeContexts[NUMBER_OF_STROKE_CONTEXTS] ;

extern PaperSizeSpecification paperSizeSpecifications[NUMBER_OF_PAPER_SIZES]; 

typedef struct _Busy {
	struct tm start;
	struct tm end;
} Busy;

#ifdef __cplusplus
extern "C" {
#endif
	PaperSizeSpecification getPaperSizeSpecification(PaperSize, Orientation);
#ifdef __cplusplus
}
#endif

// INTERNAL
typedef struct _DaysContext {
	double startingHorizontalPosition;
	double endingHorizontalPosition;
	double startingVerticalPosition;
	double endingVerticalPosition;
} DaysContext;

typedef struct _SeparatorsContext {
	uint8_t numberOfHours;
	double deltaVerticalPosition;
	double deltaHorizontalPosition;
} SeparatorsContext;
