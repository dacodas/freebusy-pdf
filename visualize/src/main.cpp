#include <cairo/cairo-pdf.h>

#include <libical/ical.h>
#include <libical/icalparser.h>
#include <libical/icalproperty.h>

#include <specification.h>
#include <settings.h>
#include <drawDays.h>
#include <busy.h>

#include <strokeHelper.c.in>

#include <cstdio>

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

int main(int argc, const char* argv[])
{
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
