/*--------------------------------------------------------------
 | Display Position Editor v1.0.0                               |
 | By Benjamin J. Pryor                                         |
 |--------------------------------------------------------------|
 | A simple command line utility to accurately set the relative |
 | position of monitors in a dual- or multi- monitor setup.     |
  --------------------------------------------------------------*/

/* 
* Original code from here:
* https://what.thedailywtf.com/topic/26137/windows-10-display-arranging-sucks-so-i-fixed-it-by-setting-the-pixel-positions-manually
* Credit to LB_ for the basic methods used in this utility.
*/

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main(int argc, char** argv)
{
    if (argc > 1) {

        DISPLAY_DEVICEW dmInfo{ sizeof(DISPLAY_DEVICEW) };
        DEVMODEW dmMode{ {}, {}, {}, sizeof(DEVMODEW), 0 };

        for (int i = 0; i < ((argc - 1) / 3); i++) {

            cout << endl << "Applying position {" << argv[(3 * i) + 2] << ", " << argv[(3 * i) + 3] << "} to monitor " << argv[(3 * i) + 1] << "..." << endl;

            if (EnumDisplayDevicesW(NULL, stoi(argv[(3 * i) + 1]) - 1, &dmInfo, EDD_GET_DEVICE_INTERFACE_NAME) != 0) {

                if (EnumDisplaySettingsExW(dmInfo.DeviceName, ENUM_CURRENT_SETTINGS, &dmMode, EDS_RAWMODE) != 0) {

                    dmMode.dmFields = DM_POSITION;
                    dmMode.dmPosition.x = stoi(argv[(3 * i) + 2]);
                    dmMode.dmPosition.y = stoi(argv[(3 * i) + 3]);

                    if (ChangeDisplaySettingsExW(dmInfo.DeviceName, &dmMode, NULL, CDS_GLOBAL | CDS_UPDATEREGISTRY, NULL) == DISP_CHANGE_SUCCESSFUL) {
                        cout << "Done!" << endl << endl;
                    }
                    else {
                        cout << "Operation failed! Unable to write to display settings." << endl << "Skipping..." << endl << endl;
                    }
                }
                else {
                    cout << "Operation failed! Unable to read display settings." << endl << "Skipping..." << endl << endl;
                }
            }
            else {
                cout << "Operation failed! Unable to connect to display." << endl << "Skipping..." << endl << endl;
            }
        }
    }
    else {

        cout << endl << "DPEdit 1.0.0" << endl;
        cout << "A command line utility to accurately position monitors in a multi-monitor setup." << endl << endl;
        cout << "Usage: dpedit.exe" << endl;
        cout << "       dpedit.exe <monitorNum> <xPos> <yPos> [<monitorNum2> <xPos2> <yPos2>] ..." << endl << endl;
        cout << "  Options:" << endl << endl;
        cout << "  <monitorNum>    The index of the monitor to position, where 1 = Main, 2 = Secondary, etc." << endl;
        cout << "  <xPos>          The X (horizontal) position of the top-left corner of monitor <monitorNum>." << endl;
        cout << "  <YPos>          The Y (vertical) position of the top-left corner of monitor <monitorNum>." << endl << endl;
        cout << "Example: dpedit.exe 1 0 0 2 -1920 21" << endl;
        cout << "         Moves the main monitor to coords {0, 0} and positions the secondary monitor to the left of" << endl;
        cout << "         and 21 pixels lower than the main monitor (coords {-1920, 21}). This example assumes the" << endl;
        cout << "         secondary monitor to be 1080p." << endl << endl;
        cout << "Notes: This utility should work for any number and any size(s) of monitors." << endl;
        cout << "       The monitor numbers do not need to be in order." << endl << endl;
        cout << "THIS UTILITY MODIFIES THE REGISTRY! USE AT YOUR OWN RISK!" << endl;

    }

    return 0;
}