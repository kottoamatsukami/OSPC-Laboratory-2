#include <stdio.h>
#include "core/stuff.h"

int main()
{
    int menu_carrier;
    greeting();
    while (True)
    {
        main_menu();
        put_arrow();
        menu_carrier = get_choice(0, 2);

        switch (menu_carrier) {
            // Error
            case -1:
                continue;
            // Exit
            case 0:
                return 0;
            // Launch Satellite
            case 1:
                puts("Something");
                break;
            // Destroy Satellite
            case 2:
                puts("Something 2");
                break;
            default:
                puts("Undefined behaviour");
        }

    }
}