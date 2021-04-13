#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <cairo/cairo.h>

#include <specification.h>

void draw_hour(
	cairo_t* cr,
	const char* string,
	double x, 
	double y
)
{
	cairo_text_extents_t extents;
	cairo_text_extents(cr, string, &extents);

	x = x - ( extents.width + extents.x_bearing );
	y = y - ( extents.height / 2 + extents.y_bearing );

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, string);
}

void draw_hours(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext
) {
	for ( size_t hour = hoursContext->startingHour ; hour <= hoursContext->endingHour ; ++hour )
	{
		double verticalPosition =
			daysContext->startingVerticalPosition 
				+ ((double) hour - hoursContext->startingHour) * separatorsContext->deltaVerticalPosition;

		char hourString[128];
		snprintf(hourString, sizeof(hourString), "%d:00", hour);
		draw_hour(
			cr, 
			hourString,
			daysContext->startingHorizontalPosition - 10, 
			verticalPosition
		);
	}
}

void draw_day(
	cairo_t* cr,
	const char* string,
	double x, 
	double y
)
{
	cairo_text_extents_t extents;
	cairo_text_extents(cr, string, &extents);

	x = x - ( extents.width / 2 + extents.x_bearing );
	y = y - ( extents.height + extents.y_bearing );

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, string);
}

void draw_days_text(
	cairo_t* cr,
	const DaysContext* daysContext,
	const struct tm* startDate
) {
	struct tm datetime = *startDate;
	mktime(&datetime);

	double deltaHorizontalPosition = 
		( daysContext->endingHorizontalPosition - daysContext->startingHorizontalPosition ) / 7.0d;

	for ( 
		size_t day = 0 ; 
		day < 7; 
			++day, 
			++datetime.tm_mday, 
			mktime(&datetime)
	)
	{
		double horizontalPosition =
			daysContext->startingHorizontalPosition
				+ ((double) day ) * deltaHorizontalPosition 
				+ deltaHorizontalPosition * 0.5d;

		char dayString[128];
		strftime(dayString, sizeof(dayString), "%A %d", &datetime);
		draw_day(
			cr, 
			dayString,
			horizontalPosition,
			daysContext->startingVerticalPosition - 10
		);
	}
}
