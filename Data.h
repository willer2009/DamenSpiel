#ifndef DATA_H
#define DATA_H

/**
  * class which represents all the constant datas(parameter values) we need in the game
  */
class Data{
   public:
    //width of the game area
    static const int WIDTH_GAMEFIELD = 670;

    //height of the game area
    static const int HEIGHT_GAMEFIELD = 722;

    //width of a unique field in the game area
    static const int WIDTH_FIELD = 50;

    //height of a unique field in the game area
    static const int HEIGTH_FIELD = 50;

    // dimension of a tile (width and height)
    static const int WIDTH_TILE = 30;
    static const int HEIGTH_TILE = 30;

    //number of rows and columns of the game area
    static const int NUMBER_ROWS = 10;
    static const int NUMBER_COLUMNS = 10;

    //number of tiles per player
    static const int NUMBER_TILES = 20;

    // time which ich use to show the possible destination where to play
    static const int DELAY_TO_SHOW_DESTINATION_FIELD = 500;

};

#endif // DATA_H
