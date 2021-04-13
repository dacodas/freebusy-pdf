#include <specification.h>

void calculateSeparatorsContext(
	SeparatorsContext* separatorsContext,
	const DaysContext* daysContext,
	const HoursContext* hoursContext
) {
	uint8_t numberOfHours = 
		hoursContext->endingHour - hoursContext->startingHour;

	double deltaVerticalPosition = 
		( daysContext->endingVerticalPosition - daysContext->startingVerticalPosition ) / ((double) numberOfHours);

	double deltaHorizontalPosition = 
		( daysContext->endingHorizontalPosition - daysContext->startingHorizontalPosition ) / 7.0d;

	*separatorsContext = (SeparatorsContext) {numberOfHours, deltaVerticalPosition, deltaHorizontalPosition};
}

void calculateDaysContext(
	DaysContext* context,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize
)
{
	double startingHorizontalPosition = margins->leftMargin;
	double endingHorizontalPosition = paperSize->width_in_points - margins->rightMargin;
	double startingVerticalPosition = margins->topMargin;
	double endingVerticalPosition = paperSize->height_in_points - margins->bottomMargin;

	*context = (DaysContext) {
		startingHorizontalPosition,
		endingHorizontalPosition,
		startingVerticalPosition,
		endingVerticalPosition
	};
}

void calculateMeasurements(
	DaysContext* daysContext,
	SeparatorsContext* separatorsContext,
	const CalendarDayMargins* margins,
	const PaperSizeSpecification* paperSize,
	const HoursContext* hoursContext
)
{
	calculateDaysContext(daysContext, margins, paperSize);
	calculateSeparatorsContext(
		separatorsContext,
		daysContext,
		hoursContext
	);
}
