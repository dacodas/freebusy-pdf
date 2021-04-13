#include <stddef.h>
#include <time.h>

#include <cairo/cairo.h>

#include <specification.h>
#include <measurements.h>
#include <text.h>

void enact_stroke_context(cairo_t* cr, const StrokeContext* context) {
	cairo_set_line_width(cr, context->lineWidth);
	cairo_set_line_cap(cr, context->lineCap);

	const CairoDash* dash = &context->cairoDash;
	cairo_set_dash(cr, dash->dashes, dash->numberOfDashes, dash->offset);
}

void draw_days_bounding_box(cairo_t* cr, const DaysContext* context) {
	cairo_rectangle(
		cr, context->startingHorizontalPosition, context->startingVerticalPosition,
		context->endingHorizontalPosition - context->startingHorizontalPosition,
		context->endingVerticalPosition - context->startingVerticalPosition
	);
	cairo_stroke(cr);
}

void draw_days_separators(cairo_t* cr, const DaysContext* context, const SeparatorsContext* separatorsContext) {
	for ( size_t day = 1 ; day < 7; ++day )
	{
		double horizontalPosition = 
			context->startingHorizontalPosition 
				+ ((double) day) * separatorsContext->deltaHorizontalPosition;

		cairo_move_to(cr, horizontalPosition, context->startingVerticalPosition);
		cairo_line_to(
			cr, 
			horizontalPosition,
			context->endingVerticalPosition
		);

		cairo_stroke(cr);
	}
}

// A curious question:
// Is pushing the following arguments onto the stack optimized away?
// Perhaps some clarification here: 
// https://stackoverflow.com/questions/27596160/do-c-compilers-optimize-away-functions-in-assembly-so-they-minimize-use-of-the-s
void draw_days_hour_separators_bulk(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext,
	double startingVerticalPosition
) {
	for ( size_t hour = 0 ; hour < separatorsContext->numberOfHours ; ++hour )
	{
		double verticalPosition =
			startingVerticalPosition 
				+ ((double) hour) * separatorsContext->deltaVerticalPosition;

		cairo_move_to(cr, daysContext->startingHorizontalPosition, verticalPosition);
		cairo_line_to(
			cr, 
			daysContext->endingHorizontalPosition,
			verticalPosition
		);

		cairo_stroke(cr);
	}
}

void draw_days_hour_separators(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext
) {
	draw_days_hour_separators_bulk(cr, daysContext, hoursContext, separatorsContext, daysContext->startingVerticalPosition);
}

void draw_days_half_hour_separators(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext
) {
	draw_days_hour_separators_bulk(
		cr,
		daysContext,
		hoursContext,
		separatorsContext,
		daysContext->startingVerticalPosition + separatorsContext->deltaVerticalPosition / 2.0d
	);
}

void draw_days_quarter_hour_separators(
	cairo_t* cr,
	const DaysContext* daysContext,
	const HoursContext* hoursContext,
	const SeparatorsContext* separatorsContext
) {
	double firstStartingPosition = 
		daysContext->startingVerticalPosition + separatorsContext->deltaVerticalPosition / 4.0d;
	double secondStartingPosition = 
		firstStartingPosition + separatorsContext->deltaVerticalPosition / 2.0d;

	draw_days_hour_separators_bulk(cr, daysContext, hoursContext, separatorsContext, firstStartingPosition);
	draw_days_hour_separators_bulk(cr, daysContext, hoursContext, separatorsContext, secondStartingPosition);
}

void draw_days(
	cairo_t* cr,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const StrokeContexts* strokeContexts,
	const HoursContext* hoursContext,
	const struct tm* startDate
) {
	DaysContext daysContext; 
	SeparatorsContext separatorsContext;

	calculateMeasurements(
		&daysContext,
		&separatorsContext,
		margins,
		paperSize,
		hoursContext
	);

	// Set strokes here...
	enact_stroke_context(cr, *strokeContexts + DAY_STROKE_CONTEXT);
	draw_days_bounding_box(cr, &daysContext);
	draw_days_separators(cr, &daysContext, &separatorsContext);

	enact_stroke_context(cr, *strokeContexts + HOUR_STROKE_CONTEXT);
	draw_days_hour_separators(
		cr, 
		&daysContext, 
		hoursContext,
		&separatorsContext
	);

	enact_stroke_context(cr, *strokeContexts + HALF_HOUR_STROKE_CONTEXT);
	draw_days_half_hour_separators(
		cr, 
		&daysContext, 
		hoursContext,
		&separatorsContext
	);

	enact_stroke_context(cr, *strokeContexts + QUARTER_HOUR_STROKE_CONTEXT);
	draw_days_quarter_hour_separators(
		cr, 
		&daysContext, 
		hoursContext,
		&separatorsContext
	);

	draw_hours(
		cr,
		&daysContext, 
		hoursContext,
		&separatorsContext
	);

	draw_days_text(
		cr,
		&daysContext,
		startDate
	);
}
