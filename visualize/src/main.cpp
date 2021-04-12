#include <cairo/cairo-pdf.h>
#include <specification.h>

int main(int argc, const char* argv[])
{
	PaperSize paperSize = AMERICAN_LETTER;

	cairo_surface_t* surface = 
		cairo_pdf_surface_create(
			"/tmp/freebusy.pdf", 
			paperSizeSpecifications[paperSize].width_in_points,
			paperSizeSpecifications[paperSize].height_in_points
		);

	cairo_t *cr = cairo_create(surface);

	cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 32.0);
	cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
	cairo_move_to (cr, 10.0, 50.0);
	cairo_show_text (cr, "Hello, world");

	cairo_surface_finish(surface);
	cairo_surface_flush(surface);

	cairo_destroy (cr);
}
