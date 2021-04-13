#pragma once

#include <cairo/cairo.h>
#include <specification.h>

void draw_hours(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext
);

void draw_days_text(
	cairo_t* cr,
	const DaysContext* daysContext,
	const struct tm* startDate
);
