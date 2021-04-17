#include <config.h>

#include <busy.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <cairo/cairo.h>

#include <libical/ical.h>
#include <libical/icalparser.h>
#include <libical/icalproperty.h>

#include <measurements.h>

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

void* cheap_malloc(size_t size)
{
	void* allocatedMemory = malloc( size );

	if ( allocatedMemory == NULL )
		abort();

	return allocatedMemory;
}

BusyContext* get_draw_busy_context(
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext,
	const struct tm* startDate
)
{
	struct tm* copiedStartDate = (struct tm*) cheap_malloc( sizeof(struct tm) );
	HoursContext* copiedHoursContext = (HoursContext*) cheap_malloc( sizeof(HoursContext) );
	DaysContext* daysContext = (DaysContext*) cheap_malloc( sizeof(DaysContext) );
	SeparatorsContext* separatorsContext = (SeparatorsContext*) cheap_malloc( sizeof(SeparatorsContext) );
	_BusyContext* busyContext  = (_BusyContext*) cheap_malloc( sizeof(_BusyContext) );

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

void processFreeBusy(
	cairo_t* cr,
	BusyContext* busyContext,
	icalproperty* property
)
{	
	struct icalperiodtype period = icalproperty_get_freebusy(property);

	// icaltimezone* timezone = icaltimezone_get_builtin_timezone("America/Los_Angeles");
	// time_t time = icaltime_as_timet_with_zone(period.start, timezone);

	time_t startTime = icaltime_as_timet(period.start);
	time_t endTime = icaltime_as_timet(period.end);

	Busy busy;

	localtime_r(&startTime, &busy.start);
	localtime_r(&endTime, &busy.end);

	draw_single_busy_from_context(
		cr,
		busyContext,
		&busy
	);
	
	return;
}

void processVFreeBusy(
	cairo_t* cr,
	BusyContext* busyContext,
	icalcomponent* component
)
{
	icalproperty* property;

	for (
		property = 
			icalcomponent_get_first_property(component, ICAL_FREEBUSY_PROPERTY);
		property != 0;
		property = 
			icalcomponent_get_next_property(component, ICAL_FREEBUSY_PROPERTY)
	)
	{
		processFreeBusy(cr, busyContext, property);
	}
}

void processVCalendar(
	cairo_t* cr,
	BusyContext* busyContext,
	icalcomponent* component
)
{
	icalcomponent* subcomponent;

	for (
		subcomponent = 
			icalcomponent_get_first_component(component, ICAL_VFREEBUSY_COMPONENT);
		subcomponent != 0;
		subcomponent = 
			icalcomponent_get_next_component(component, ICAL_VFREEBUSY_COMPONENT)
	)
	{
		processVFreeBusy(cr, busyContext, subcomponent);
	}
}

char* readFreeBusyStream(char *s, size_t size, void *d)
{
    return fgets(s, size, (FILE*) d);
}

void readFreeBusy(
	cairo_t* cr,
	BusyContext* busyContext,
	const char* filename
)
{
	char *line;
	icalcomponent *component;
	icalparser *parser = icalparser_new();

	FILE* stream = fopen(filename, "r");

	icalparser_set_gen_data(parser, stream);

	do {
		line = icalparser_get_line(parser, readFreeBusyStream);
		component = icalparser_add_line(parser, line);

		if (component != 0) {
			processVCalendar(cr, busyContext, component);
			icalparser_clean(parser);

			icalcomponent_free(component);
		}
	} while (line != 0);
}
