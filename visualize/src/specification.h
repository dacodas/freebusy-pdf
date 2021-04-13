#pragma once

#include <stdint.h>
#include <cairo/cairo.h>

typedef enum _PaperSize {
	AMERICAN_LETTER = 0
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

typedef struct _DaysContext {
	double startingHorizontalPosition;
	double endingHorizontalPosition;
	double startingVerticalPosition;
	double endingVerticalPosition;
} DaysContext;

// 24-hour clock, please
typedef struct _HoursContext {
	uint8_t startingHour;
	uint8_t endingHour;
} HoursContext;

// INTERNAL
typedef struct _SeparatorsContext {
	uint8_t numberOfHours;
	double deltaVerticalPosition;
} SeparatorsContext;

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

// Is this a bad idea?
typedef struct _Calendar {
	PaperSizeSpecification paperSize;
	StrokeContexts strokeContexts;
	CalendarDayMargins calendarDayMargins;
} Calendar;

extern PaperSizeSpecification paperSizeSpecifications[10]; 

#ifdef __cplusplus
extern "C" {
#endif
	PaperSizeSpecification getPaperSizeSpecification(PaperSize, Orientation);
#ifdef __cplusplus
}
#endif
