#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <config.h>

#include <cairo/cairo-pdf.h>

#include <time.h>
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

static struct option long_options[] = {
        {"output"              , required_argument, 0, 'o'},
        {"ics-files-directory" , required_argument, 0, 'd'},
        {0                     , 0                , 0,  0 },
};

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

int main(int argc, char* const argv[])
{
	char
		*output = (char*) NULL,
		*ics_files_directory = (char*) NULL;

	{
		int getopt_return = -1;

		for (;;) {
			int this_option_optind = optind ? optind : 1;
			int option_index = 0;

			getopt_return = getopt_long(argc, argv, "od:", long_options, &option_index);

			if ( getopt_return == -1 ) break;

			switch ( getopt_return )
			{
			case 'o':
				output = optarg;
				break;
			case 'd':
				ics_files_directory = optarg;
				break;
			case '?':
			{
				char error[256];
				snprintf(error, sizeof(error), "Unknown flag %s", argv[this_option_optind]);
				fprintf(stderr, "%s\n", error);
				exit(1);
			}
			}
		}
	}

	if ( output == NULL )
	{
		fprintf(stderr, "Specify the output file\n");
		exit(1);
	}

	if ( ics_files_directory == NULL )
	{
		fprintf(stderr, "Specify the directory containing the ICS files\n");
		exit(1);
	}

	if ( optind == argc )
	{
		fprintf(stderr, "Specify the start date\n");
		exit(1);
	}

	set_start_date(argv[optind++]);

	PaperSizeSpecification paperSize =
		getPaperSizeSpecification(AMERICAN_LETTER, LANDSCAPE);

	fixStrokeContexts();

	cairo_surface_t* surface =
		cairo_pdf_surface_create(
			output,
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

	if ( optind == argc )
	{
		fprintf(stderr, "Specify the calendars you would like to show\n");
		exit(1);
	}

	for ( ; optind < argc ; ++optind )
	{
		const char* calendar = argv[optind];
		char freebusyFile[256];

		snprintf(freebusyFile, sizeof(freebusyFile), "%s/freebusy-%s.ics", ics_files_directory, calendar);
		readFreeBusy(cr, busyContext, freebusyFile);
	}

	cairo_surface_finish(surface);
	cairo_surface_flush(surface);

	cairo_destroy (cr);
}
