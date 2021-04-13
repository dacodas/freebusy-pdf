#include <cairo/cairo-pdf.h>

#include <specification.h>
#include <settings.h>

#include <strokeHelper.c.in>
#include <margins.cpp.in>

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

	cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 24.0);
	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "April 11 to April 17, 2021");

	draw_days(cr, &calendarDayMargins, &paperSize, &strokeContexts);

	cairo_surface_finish(surface);
	cairo_surface_flush(surface);

	cairo_destroy (cr);
}
