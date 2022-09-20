/*--------------------------------------------------------------
 | Display Position Editor v1.1.0                               |
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

#define MAX_SIZE 400

using namespace std;

int main(int argc, char** argv)
{
    if (argc > 1) {

        if (strcmp(argv[1], "/L")) {

            DISPLAY_DEVICEW dmInfo{ sizeof(DISPLAY_DEVICEW) };
            DEVMODEW dmMode{ {}, {}, {}, sizeof(DEVMODEW), 0 };

            for (int i = 0; i < ((argc - 1) / 3); i++) {

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
        } else {
            DISPLAY_DEVICE displayDevice{sizeof displayDevice,};

            for (auto i = 0; EnumDisplayDevices(nullptr, i, &displayDevice, EDD_GET_DEVICE_INTERFACE_NAME); i++) {
                WCHAR buf[MAX_SIZE]{};
                wsprintf(buf,
                    L"\r\n"
                    L"Display #%d\r\n"
                    L"Device name: %s\r\n"
                    L"Device string: %s\r\n"
                    L"Active: %d\r\n"
                    L"Mirroring: %d\r\n"
                    L"Modes pruned: %d\r\n"
                    L"Primary: %d\r\n"
                    L"Removable: %d\r\n"
                    L"VGA compatible: %d\r\n",
                    i,
                    displayDevice.DeviceName,
                    displayDevice.DeviceString,
                    displayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE,
                    displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER,
                    displayDevice.StateFlags & DISPLAY_DEVICE_MODESPRUNED,
                    displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE,
                    displayDevice.StateFlags & DISPLAY_DEVICE_REMOVABLE,
                    displayDevice.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE);

                DWORD dwSize{ 0 };
                WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, lstrlen(buf), &dwSize, nullptr);

                DEVMODE devMode{ {}, {}, {}, sizeof devMode, 0, };
                if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
                {
                    wsprintf(buf, L"Position: {%ld, %ld}\r\n", devMode.dmPosition.x, devMode.dmPosition.y);
                    dwSize = 0;
                    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, lstrlen(buf), &dwSize, nullptr);
                }
            }
        }
    } else {

        cout << endl << "DPEdit 1.1.0" << endl;
        cout << "A command line utility to accurately position displays in a multi-monitor setup." << endl << endl;
        cout << "Usage: dpedit.exe" << endl;
        cout << "       dpedit.exe /L" << endl;
        cout << "       dpedit.exe <displayNum> <xPos> <yPos> [<displayNum2> <xPos2> <yPos2>] ..." << endl << endl;
        cout << "  Options:" << endl << endl;
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

    return 0;
}
