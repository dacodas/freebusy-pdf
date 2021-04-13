#pragma once

#include <cairo/cairo.h>

#include <specification.h>

typedef struct _BusyContext BusyContext;

#ifdef __cplusplus
extern "C" {
#endif
BusyContext* get_draw_busy_context(
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext,
	const struct tm* startDate
);

void draw_single_busy_from_context(
	cairo_t* cr,
	BusyContext* context,
	const Busy* busy
);
#ifdef __cplusplus
}
#endif
