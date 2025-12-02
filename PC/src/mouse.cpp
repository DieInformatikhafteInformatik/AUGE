#include <iostream>
#include <chrono>

#include "mouse.h"

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
    }, cFunc};
}
