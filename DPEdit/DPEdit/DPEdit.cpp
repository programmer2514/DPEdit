/*--------------------------------------------------------------
 | Display Position Editor v1.2.1                               |
 | By Benjamin J. Pryor                                         |
 |--------------------------------------------------------------|
 | A simple command line utility to accurately set the relative |
 | position of monitors in a dual- or multi- monitor setup.     |
  --------------------------------------------------------------*/

/*
* Original code from here:
* https://what.thedailywtf.com/topic/26137/windows-10-display-arranging-sucks-so-i-fixed-it-by-setting-the-pixel-positions-manually
* Credit to LB_ for the basic methods used in this utility.
* Credit to GreenYun for the /L routine, and for correcting my mistaken understanding of display indices
*/

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void set_display_pos(int argc, char** argv);
void list_displays(void);
void show_help(void);
bool is_valid_int(string s);

int main(int argc, char** argv)
{
    if (argc > 1) {

        if ((!strcmp(argv[1], "/L")) || (!strcmp(argv[1], "/l")))
            list_displays();

        else if ((!strcmp(argv[1], "/H")) || (!strcmp(argv[1], "/h")) || (!strcmp(argv[1], "/?")))
            show_help();

        else set_display_pos(argc, argv);

    } else show_help();

    return 0;
}

void set_display_pos(int argc, char** argv) {
    DISPLAY_DEVICEW dmInfo{ sizeof(DISPLAY_DEVICEW) };
    DEVMODEW dmMode{ {}, {}, {}, sizeof(DEVMODEW), 0 };

    for (int i = 0; i < ((argc - 1) / 3); i++) {

        if (is_valid_int(argv[(3 * i) + 1]) && is_valid_int(argv[(3 * i) + 2]) && is_valid_int(argv[(3 * i) + 3])) {

            cout << endl << "Applying position {" << argv[(3 * i) + 2] << ", " << argv[(3 * i) + 3] << "} to Display #" << argv[(3 * i) + 1] << "..." << endl;

            if (EnumDisplayDevicesW(NULL, stoi(argv[(3 * i) + 1]) - 1, &dmInfo, EDD_GET_DEVICE_INTERFACE_NAME) != 0) {

                if (EnumDisplaySettingsExW(dmInfo.DeviceName, ENUM_CURRENT_SETTINGS, &dmMode, EDS_RAWMODE) != 0) {

                    dmMode.dmFields = DM_POSITION;
                    dmMode.dmPosition.x = stoi(argv[(3 * i) + 2]);
                    dmMode.dmPosition.y = stoi(argv[(3 * i) + 3]);

                    if (ChangeDisplaySettingsExW(dmInfo.DeviceName, &dmMode, NULL, CDS_GLOBAL | CDS_UPDATEREGISTRY, NULL) == DISP_CHANGE_SUCCESSFUL)
                        cout << "Done!" << endl << endl;
                    else cout << "Operation failed! Unable to write to display settings." << endl << "Skipping..." << endl << endl;

                }
                else cout << "Operation failed! Unable to read display settings." << endl << "Skipping..." << endl << endl;

            }
            else cout << "Operation failed! Unable to connect to display." << endl << "Skipping..." << endl << endl;
        }
        else {
            cout << "Invalid argument(s) detected!" << endl;
            cout << "Use 'dpedit.exe /?' for more info" << endl << endl;
        }
    }
}

void list_displays(void) {
    DISPLAY_DEVICE displayDevice{ sizeof displayDevice, };

    for (int i = 0; EnumDisplayDevices(nullptr, i, &displayDevice, EDD_GET_DEVICE_INTERFACE_NAME); i++) {
        cout << endl;
        cout << "Display #" << i + 1 << endl;
        wcout << "Device name: " << displayDevice.DeviceName << endl;
        wcout << "Device string: " << displayDevice.DeviceString << endl;
        cout << "Active: " << (displayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE) << endl;
        cout << "Mirroring: " << (displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) << endl;
        cout << "Modes pruned: " << (displayDevice.StateFlags & DISPLAY_DEVICE_MODESPRUNED) << endl;
        cout << "Primary: " << (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) << endl;
        cout << "Removable: " << (displayDevice.StateFlags & DISPLAY_DEVICE_REMOVABLE) << endl;
        cout << "VGA compatible: " << (displayDevice.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE) << endl;

        DEVMODE devMode{ {}, {}, {}, sizeof devMode, 0, };
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
        {
            cout << "Position: {" << devMode.dmPosition.x << ", " << devMode.dmPosition.y << "}" << endl;
        }
    }
}

void show_help(void) {
    cout << endl << "DPEdit 1.2.1" << endl;
    cout << "A command line utility to accurately position displays in a multi-monitor setup." << endl << endl;
    cout << "Usage: dpedit.exe [/H] [/?]" << endl;
    cout << "       dpedit.exe /L" << endl;
    cout << "       dpedit.exe <displayNum> <xPos> <yPos> [<displayNum2> <xPos2> <yPos2>] ..." << endl << endl;
    cout << "  Options:" << endl << endl;
    cout << "  /H, /?          Shows this help page" << endl;
    cout << "  /L              Lists all displays and their indices" << endl;
    cout << "  <displayNum>    The index of the display to position" << endl;
    cout << "  <xPos>          The X (horizontal) position of the top-left corner of display <displayNum>." << endl;
    cout << "  <YPos>          The Y (vertical) position of the top-left corner of display <displayNum>." << endl << endl;
    cout << "Example: dpedit.exe 1 0 0 2 -1920 21" << endl;
    cout << "         Moves Display #1 to coords {0, 0} and positions Display #2 to the left of" << endl;
    cout << "         and 21 pixels lower than Display #1 (coords {-1920, 21}). This example assumes" << endl;
    cout << "         Display #2 to be 1080p." << endl << endl;
    cout << "Notes: This utility should work for any number and any size(s) of monitors." << endl;
    cout << "       The display numbers do not need to be in order." << endl << endl;
    cout << "THIS UTILITY MODIFIES THE REGISTRY! USE AT YOUR OWN RISK!" << endl;
}

bool is_valid_int(string s) {
    return !s.empty() && (s.find_first_not_of("0123456789") == string::npos);
}