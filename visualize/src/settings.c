#include <math.h>
#include <settings.h>

CalendarDayMargins calendarDayMargins = {
	100, 20, 100, 20
};

CairoDashSimple dashes[] = {
	[DAY_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[HOUR_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[HALF_HOUR_STROKE_CONTEXT] = { {NAN}, 0.0d },
	[QUARTER_HOUR_STROKE_CONTEXT] = { {5, 2, 2, 2, NAN}, 0.0d },
};
	
StrokeContexts strokeContexts = {
	[DAY_STROKE_CONTEXT] = { 1, CAIRO_LINE_CAP_BUTT, {} },
	[HOUR_STROKE_CONTEXT] = { 1, CAIRO_LINE_CAP_BUTT, {} },
	[HALF_HOUR_STROKE_CONTEXT] = { 0.25, CAIRO_LINE_CAP_BUTT, {} },
	[QUARTER_HOUR_STROKE_CONTEXT] = { 0.25, CAIRO_LINE_CAP_BUTT, {} },
};

const struct tm startDate = {
	.tm_mday = 11,
	.tm_mon = 3,
	.tm_year = 121,
};

const HoursContext hoursContext = {
	8, 18
};

const char* globalFont = "sans-serif";

const Busy busy[] = {
{
	{
		.tm_year = 121, 
		.tm_mon =  03, 
		.tm_mday = 12, 
		.tm_hour = 9, 
		.tm_min =  25
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =12,
		.tm_hour =9,
		.tm_min = 40
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 12, 
		.tm_hour = 10, 
		.tm_min = 15
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =12,
		.tm_hour =10,
		.tm_min = 30
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 12, 
		.tm_hour = 15, 
		.tm_min = 00
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =12,
		.tm_hour =16,
		.tm_min = 00
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 13, 
		.tm_hour = 9, 
		.tm_min = 25
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =13,
		.tm_hour =9,
		.tm_min = 40
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 13, 
		.tm_hour = 10, 
		.tm_min = 15
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =13,
		.tm_hour =10,
		.tm_min = 30
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 13, 
		.tm_hour = 16, 
		.tm_min = 00
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =13,
		.tm_hour =17,
		.tm_min = 00
	}
},
// {
// 	{
// 		.tm_year = 121, 
// 		.tm_mon = 03, 
// 		.tm_mday = 14, 
// 		.tm_hour = 02, 
// 		.tm_min = 00
// 	},
// 	{
// 		.tm_year =121,
// 		.tm_mon = 03,
// 		.tm_mday =14,
// 		.tm_hour =02,
// 		.tm_min = 30
// 	}
// },
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 14, 
		.tm_hour = 9, 
		.tm_min = 25
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =14,
		.tm_hour =9,
		.tm_min = 40
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 14, 
		.tm_hour = 10, 
		.tm_min = 15
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =14,
		.tm_hour =10,
		.tm_min = 45
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 14, 
		.tm_hour = 11, 
		.tm_min = 00
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =14,
		.tm_hour =12,
		.tm_min = 00
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 14, 
		.tm_hour = 13, 
		.tm_min = 30
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =14,
		.tm_hour =14,
		.tm_min = 00
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 14, 
		.tm_hour = 15, 
		.tm_min = 30
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =14,
		.tm_hour =16,
		.tm_min = 00
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 15, 
		.tm_hour = 9, 
		.tm_min = 25
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =15,
		.tm_hour =9,
		.tm_min = 40
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 15, 
		.tm_hour = 10, 
		.tm_min = 15
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =15,
		.tm_hour =10,
		.tm_min = 30
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 15, 
		.tm_hour = 13, 
		.tm_min = 30
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =15,
		.tm_hour =14,
		.tm_min = 30
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 16, 
		.tm_hour = 9, 
		.tm_min = 25
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =16,
		.tm_hour =9,
		.tm_min = 40
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 16, 
		.tm_hour = 10, 
		.tm_min = 15
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =16,
		.tm_hour =10,
		.tm_min = 45
	}
},
{
	{
		.tm_year = 121, 
		.tm_mon = 03, 
		.tm_mday = 16, 
		.tm_hour = 11, 
		.tm_min = 55
	},
	{
		.tm_year =121,
		.tm_mon = 03,
		.tm_mday =16,
		.tm_hour =12,
		.tm_min = 00
	}
}
};
