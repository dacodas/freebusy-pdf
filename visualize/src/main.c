#include <stdio.h>
#include <stdlib.h>

#include <cairo/cairo-pdf.h>

#include <gnulib/time.h>
#include <gnulib/parse-datetime.h>

#include <specification.h>
#include <settings.h>
#include <drawDays.h>
#include <busy.h>

#include <strokeHelper.c.in>

// Excuse me? How to localize this?
// - I would prefer to have a single string "%B %d to %B %d, %Y" which could be localized
// - Need a function that takes in:
// 	void formatString(char* buffer, size_t length, const char* format, const struct tm* startDate, const struct tm* endDate);
// - I would need a way to differentiate between %B for the start and end date
void createTitle(char* title, size_t length)
{
	struct tm endDate = startDate;
	endDate.tm_mday += 7;
	mktime(&endDate);

	size_t offset = strftime(title, length, "%B %d to ", &startDate);
	offset += strftime(title + offset, length - offset, "%B %d", &endDate);
	strftime(title + offset, length - offset, ", %Y", &startDate);
}

void set_start_date(const char* date)
{
	struct timespec when;

	unsigned int parse_datetime_flags = 0;
	const char* timezone_string = NULL;

	timezone_t timezone = tzalloc(timezone_string);

	if ( ! parse_datetime2(
			&when,
			date,
			NULL,
			parse_datetime_flags,
			timezone,
			timezone_string ) )
	{
		fprintf(stderr, "Invalid date '%s'\n", date);
		exit(1);
	}

	localtime_r(&when.tv_sec, &startDate);

	return;
}

int main(int argc, const char* argv[])
{
	set_start_date(argv[1]);

	PaperSizeSpecification paperSize = 
		getPaperSizeSpecification(AMERICAN_LETTER, LANDSCAPE);

	fixStrokeContexts();

	cairo_surface_t* surface = 
		cairo_pdf_surface_create(
			"../build/freebusy.pdf", 
			paperSize.width_in_points,
			paperSize.height_in_points
		);

	cairo_t *cr = cairo_create(surface);

	cairo_select_font_face(cr, globalFont, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 24.0);
	cairo_move_to(cr, 10.0, 50.0);

	char title[128];
	createTitle(title, sizeof(title));
	cairo_show_text(cr, title);

	cairo_set_font_size(cr, 12.0);
	draw_days(
		cr,
		&calendarDayMargins,
		&paperSize,
		&strokeContexts,
		&hoursContext,
		&startDate
	);
		
	BusyContext* busyContext = get_draw_busy_context(
		&calendarDayMargins,
		&paperSize,
		&hoursContext,
		&startDate
	);

	// TODO: Take these from arguments instead
	readFreeBusy(cr, busyContext, "../build/freebusy-5bbc952a-e4c2-1618096321256-374021.ics");
	readFreeBusy(cr, busyContext, "../build/freebusy-Default.ics");

	cairo_surface_finish(surface);
	cairo_surface_flush(surface);

	cairo_destroy (cr);
}
