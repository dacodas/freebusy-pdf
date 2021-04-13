#include <math.h>
#include <settings.h>

CalendarDayMargins calendarDayMargins = {
	65, 20, 100, 20
};

CairoDashSimple dashes[] = {
	[DAY_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[HOUR_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[HALF_HOUR_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[QUARTER_HOUR_STROKE_CONTEXT] = { {5, 2, 2, 2, NAN}, 0.0d },
};
	
StrokeContexts strokeContexts = {
	[DAY_STROKE_CONTEXT] = { 1, CAIRO_LINE_CAP_BUTT, {} },
	[HOUR_STROKE_CONTEXT] = { 1, CAIRO_LINE_CAP_BUTT, {} },
	[HALF_HOUR_STROKE_CONTEXT] = { 0.25, CAIRO_LINE_CAP_BUTT, {} },
	[QUARTER_HOUR_STROKE_CONTEXT] = { 0.25, CAIRO_LINE_CAP_BUTT, {} },
};

const struct tm startDate = {
	.tm_year = 121,
	.tm_mon = 3,
	// .tm_mday = 11,
	.tm_mday = 18,
	.tm_isdst = -1
};

const HoursContext hoursContext = {
	8, 18
};

const char* globalFont = "sans-serif";
