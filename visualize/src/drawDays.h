#pragma once

#include <cairo/cairo.h>
#include <specification.h>

extern "C" {
void draw_days(
	cairo_t* cr,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const StrokeContexts* strokeContexts
);
}
