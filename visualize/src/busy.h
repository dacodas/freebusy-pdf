#pragma once

#include <cairo/cairo.h>

#include <specification.h>


#ifdef __cplusplus
extern "C" {
#endif
void draw_busy(
	cairo_t* cr,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext,
	const struct tm* startDate,
	const Busy* busy,
	size_t busyLength
);
#ifdef __cplusplus
}
#endif
