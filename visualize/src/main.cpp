#include <cairo/cairo-pdf.h>

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

int main(int argc, const char* argv[])
{
	PaperSizeSpecification paperSize = 
		getPaperSizeSpecification(AMERICAN_LETTER, LANDSCAPE);

	fixStrokeContexts();

	cairo_surface_t* surface = 
		cairo_pdf_surface_create(
			"/tmp/freebusy.pdf", 
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
	draw_days(cr, &calendarDayMargins, &paperSize, &strokeContexts, &hoursContext, &startDate);
	draw_busy(
		cr,
		&calendarDayMargins,
		&paperSize,
		&hoursContext,
		&startDate,
		busy,
		sizeof(busy) / sizeof(Busy)
	);

	cairo_surface_finish(surface);
	cairo_surface_flush(surface);

	cairo_destroy (cr);
}
