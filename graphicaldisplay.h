#ifndef __GRAPHICALDISPLAY_H__
#define __GRAPHICALDISPLAY_H__
#include "window.h"
#include "observer.h"
#include "coordinates.h"

class Board;

class GraphicalDisplay : public Xwindow, public Observer {

    const int blockLength = 10;

    const Coordinates topLeftBoard1 = Coordinates{50, 0};
    const Coordinates topLeftBoard2 = Coordinates{200, 0};

    int highScore; 

    public:
        GraphicalDisplay(int width = 400, int height = 360);
        void notify(Cell &s) override;
        void updateScore(int score, int boardNum);
        void updateLevel(int level, int boardNum);
        void setHighScore(int _highScore);

        // whites out the display and redraws an empty one
        // also draws the highscore
        void reset(int _highScore);
};

#endif
