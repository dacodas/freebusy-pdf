#include <time.h>
#include <stdlib.h>

#include <cairo/cairo.h>

#include <specification.h>
#include <measurements.h>

void draw_single_busy(
	cairo_t* cr,
	const HoursContext* hoursContext,
	const DaysContext* daysContext,
	const SeparatorsContext* separatorsContext,
	const struct tm* startDate,
	const Busy* busy
) {
	struct tm 
		myStartDate = *startDate,
		startOfDay = busy->start
		;

	startOfDay.tm_hour = hoursContext->startingHour;
	startOfDay.tm_min = 0;

	Busy myBusy = *busy;

	// TODO: Is it in the calendar? 
	time_t difference = difftime(mktime(&myBusy.start), mktime(&myStartDate));
	if ( difference < 0 )
		abort();

	int day = (int) difference / ( 24 * 3600 );

	difference = difftime(mktime(&myBusy.start), mktime(&startOfDay));
	if ( difference < 0 )
		abort();

	double hour = (double) difference / 3600.0d;

	difference = difftime(mktime(&myBusy.end), mktime(&myBusy.start));
	if ( difference < 0 )
		abort();

	double duration = difference / 3600.0d;

	double x = 
		daysContext->startingHorizontalPosition
			+ day * separatorsContext->deltaHorizontalPosition;
	double y = 
		daysContext->startingVerticalPosition
			+ hour * separatorsContext->deltaVerticalPosition;

	double width = separatorsContext->deltaHorizontalPosition;
	double height = duration * separatorsContext->deltaVerticalPosition;

	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 0.5);
	cairo_rectangle(
		cr,
		x,
		y,
		width,
		height	
	);	
	cairo_fill(cr);

	return;
}

void draw_busy(
	cairo_t* cr,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext,
	const struct tm* startDate,
	const Busy* busy,
	size_t busyLength
)
{
	DaysContext daysContext; 
	SeparatorsContext separatorsContext;

	calculateMeasurements(
		&daysContext,
		&separatorsContext,
		margins,
		paperSize,
		hoursContext
	);

	for ( size_t index = 0 ; index < busyLength ; ++index )
	{
		draw_single_busy(
			cr,
			hoursContext,
			&daysContext,
			&separatorsContext,
			startDate,
			&busy[index]
		);
	}
}
