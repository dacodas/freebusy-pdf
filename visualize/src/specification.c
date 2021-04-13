#include <specification.h>

PaperSizeSpecification paperSizeSpecifications[NUMBER_OF_PAPER_SIZES] = {
	[AMERICAN_LETTER] = 
		{
			8.5d * 72.0d,
			11.0d * 72.0d
		}
};

PaperSizeSpecification getPaperSizeSpecification(PaperSize size, Orientation orientation) {
	switch ( orientation ) 
	{
	case PORTRAIT:
		return paperSizeSpecifications[size]; 
	case LANDSCAPE:
	{
		PaperSizeSpecification specification = paperSizeSpecifications[size];
		return 
			(PaperSizeSpecification) 
			{ specification.height_in_points, specification.width_in_points };
	}
	default:
		return 
			(PaperSizeSpecification) 
			{ 0, 0 };
	}
}
