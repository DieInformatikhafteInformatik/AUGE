#include <iostream>
#include <chrono>

#include "mouse.h"

void LoopThread::threadFunction(long timeout)
{
    while(shouldRun())
    {
        lFunc(this);

        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
}

/**
 * @param lFunc Funktion, die bei jedem Durchlauf ausgeführt werden soll
 * @param cFunc Bedingungsfunktion, die bestimmt, ob die Schleife weiterlaufen soll; true, wenn ja.
 * @param timeout Timeout nach jedem Schleifendurchlauf in Millisekunden
 */
LoopThread::LoopThread(LoopFunc lFunc, ConditionFunc cFunc, long timeout) :
    lFunc(std::move(lFunc)), cFunc(std::move(cFunc)), timeout(timeout) {}

/**
 * @brief Startet den Thread.
 */
void LoopThread::start()
{
    running = true;
    thread = std::thread(&threadFunction, this);
}

/**
 * @brief Stoppt die Schleife und somit den Thread.
 */
void LoopThread::stop()
{
    running = false;
}

/**
 * @brief 
 * 
 * Diese Methode darf nicht vor Verwendung von LoopThread#start() verwendet werden.
 */
void LoopThread::join()
{
    thread.join();
}

/**
 * @brief Macht diesen Thread zu einem Daemon-Thread.
 * 
 * Das Programm muss bei Vollendung des main-Threads nicht auf diesen Thread warten (Daemon Thread wird beendet).
 * 
 * Diese Methode darf nicht vor Verwendung von LoopThread#start() verwendet werden.
 */
void LoopThread::setDaemon()
{
    thread.detach();
}

/**
 * @brief Bestimmt, ob die Schleife in dem Thread weiterlaufen soll.
 * 
 * @return true Soll weiter laufen
 * @return false Soll gestoppt werden
 */
bool LoopThread::shouldRun()
{
    return running && cFunc();
}

/**
 * @brief Erstellt einen Thread, der die Mausposition ermittelt und an eine vom Nutzer definierte Funktion weitergibt.
 * 
 * Wird ein Window-Handle für hWindow übergeben, so läuft der Thread nur, solange der Handle gültig ist bzw.
 * das Fenster geöffnet ist (ist nicht ganz sicher). Zudem wird die Mausposition relativ zum Window berechnet.
 * Befindet sich der Cursor außerhalb des Window, wird INVALID_WINDOW_MOUSE_POS übergeben.
 * 
 * Wird NULL für den ersten Parameter übergeben, ist die Beendung der Schleife (des Threads) von der LoopThread#stop()-Methode abhängig.
 * Die Mausposition ist nicht relativ.
 * 
 * @param hWindow Window-Handle, mit dem die Mausposition verglichen werden soll; kann NULL sein.
 * @param command Funktion, an die die Mausposition übergeben werden soll.
 * @param timeout Timeout nach jedem Durch (muss > 0 sein!)
 * @return LoopThread 
 */
LoopThread createMousePositionThread(HWND hWindow, std::function<void(POINT)> command, long timeout)
{ 
    // TODO 2025-11-07_22:55 Prüfen, ob das Fenster noch geöffnet ist
    std::function<bool()> cFunc = [&hWindow]()
    {
        return hWindow == nullptr;
    };


    return LoopThread{[hWindow, command](LoopThread* unused) {
        POINT p, result;

        RECT r;

        GetCursorPos(&p);
        if(hWindow != nullptr)
        {
            GetWindowRect(hWindow, &r);

            // Prüfen, ob die Mausposition noch im Window ist
            if(p.x < r.left || p.x > r.right || p.y > r.bottom || p.y < r.top) result = INVALID_WINDOW_MOUSE_POS;
            else result = POINT{p.x - r.left, p.y - r.top}; // relative Mausposition
        }
        else result = p;

        command(result);
    }, cFunc, timeout};
}

