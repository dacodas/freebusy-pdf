#pragma once

#include <specification.h>

void calculateMeasurements(
	DaysContext* daysContext,
	SeparatorsContext* separatorsContext,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext
);
