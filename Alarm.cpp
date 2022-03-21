#include <iostream>
#include <chrono>
#include <Windows.h>
#include <string>


using namespace std;
using namespace std::chrono;

void Alarm();
void PaswordGenerator();

void DissableCloseButton();
void EnableCloseButton();

int main()

{
    Alarm();

    return 0;
}

void EnableCloseButton()
{
    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    EnableMenuItem(hmenu, SC_CLOSE, MF_ENABLED);
}

void DissableCloseButton()
{
    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}

void Alarm()
{
    int m, hour;
    cout << "input the hour of alarm:" << "\n";
    cin >> hour;
    cout << "input the min of alarm:" << "\n";
    cin >> m;

    while (1)
    {
        auto start = system_clock::now();

        auto Current_time = system_clock::to_time_t(start);
        auto Time_local = localtime(&Current_time);

        auto midnight_local = Time_local;

        midnight_local->tm_hour = 0;
        midnight_local->tm_min = 0;
        midnight_local->tm_sec = 0;

        auto midnight_timet = mktime(midnight_local);
        auto midnight = chrono::system_clock::from_time_t(midnight_timet);

        auto diff_h = duration_cast<hours>(start - midnight);
        auto diff_min = duration_cast<minutes>(start - midnight);
        auto diff_sec = duration_cast<seconds>(start - midnight);

        int min = diff_min.count() - diff_h.count() * 60;


        if (hour == diff_h.count())
        {
            if (m == min)
            {
                DissableCloseButton();
                PaswordGenerator();
                break;
            }
        }
    }

}

void PaswordGenerator()
{
    bool music = PlaySound(TEXT("C:/Users/Ghost/source/repos/Mad - Timer/Alarm/Assets/Music.owo.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // put musics files locations it must be a wav file

    string Input = "", password = "";

    while (1)
    {
        for (int i = 1; i <= 6; i++)
        {
            int N = rand() % 9;
            password += to_string(N);
        }

        cout << "Input this password to stop alarm: " << "\n" << password << "\n";
        cin >> Input;

        if (Input == password)
        {

            cout << "GoodWork owo";
            PlaySound(NULL, 0, 0);
            EnableCloseButton();
            break;
        }

        else
        {
            cout << "Try again you noob xD";
            continue; 
        }
    }
}

