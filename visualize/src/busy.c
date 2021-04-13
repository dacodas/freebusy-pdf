#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <cairo/cairo.h>

#include <specification.h>
#include <measurements.h>

#include <busy.h>

struct _BusyContext {
	DaysContext* daysContext;
	SeparatorsContext* separatorsContext;
	HoursContext* hoursContext;
	struct tm* startDate;
};

typedef struct _BusyContext _BusyContext;

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
	{
		fprintf(stderr, "Busy start is before start date\n");
		goto incorrect_times;
	}

	int day = (int) difference / ( 24 * 3600 );

	difference = difftime(mktime(&myBusy.start), mktime(&startOfDay));
	if ( difference < 0 )
	{
		fprintf(stderr, "Busy start is before start of day\n");
		goto incorrect_times;
	}

	double hour = (double) difference / 3600.0d;

	difference = difftime(mktime(&myBusy.end), mktime(&myBusy.start));
	if ( difference < 0 )
	{
		fprintf(stderr, "Busy end is before busy start\n");
		goto incorrect_times;
	}

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

incorrect_times:

	return;
}

BusyContext* get_draw_busy_context(
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext,
	const struct tm* startDate
)
{
	struct tm* copiedStartDate = (struct tm*) malloc( sizeof(struct tm) ); 
	HoursContext* copiedHoursContext = (HoursContext*) malloc( sizeof(HoursContext) ); 
	DaysContext* daysContext = (DaysContext*) malloc( sizeof(DaysContext) ); 
	SeparatorsContext* separatorsContext = (SeparatorsContext*) malloc( sizeof(SeparatorsContext) ); 
	_BusyContext* busyContext  = (_BusyContext*) malloc( sizeof(_BusyContext) );

	calculateMeasurements(
		daysContext,
		separatorsContext,
		margins,
		paperSize,
		hoursContext
	);

	*busyContext = (_BusyContext) {
		daysContext,
		separatorsContext,
		copiedHoursContext,
		copiedStartDate
	};

	*busyContext->hoursContext = *hoursContext;
	*busyContext->startDate = *startDate;

	return busyContext;
}

void draw_single_busy_from_context(
	cairo_t* cr,
	BusyContext* context,
	const Busy* busy
)
{
	draw_single_busy(
		cr,
		context->hoursContext,
		context->daysContext,
		context->separatorsContext,
		context->startDate,
		busy
	);
}
