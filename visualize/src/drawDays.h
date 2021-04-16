#pragma once

#include <cairo/cairo.h>
#include <specification.h>

#ifdef __cplusplus
extern "C" {
#endif
void draw_days(
	cairo_t* cr,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const StrokeContexts* strokeContexts,
	const HoursContext* hoursContext,
	const struct tm* startDate
);
#ifdef __cplusplus
}
#endif
