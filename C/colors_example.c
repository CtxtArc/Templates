#include <stdio.h>


#define COLORS_IMPLEMENTATION
#include "colors.h"

int main() {
    // Using macros directly
    printf(BOLD RED "Error!" RESET "\n");
    printf(ITALIC BLU "Information" RESET "\n");
    
    // Using fixed utility macro
    COLOR_PRINTF(GRN, "Success! Value: %d\n", 42);
    
    // Using helper functions
    print_warning("This is a warning message");
    printf("\n");  // newline after warning
    
    return 0;
}
