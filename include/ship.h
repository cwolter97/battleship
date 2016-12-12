#ifndef _SHIP_H_
#define _SHIP_H_

#include <string>

using namespace std;

int const MAX_SHIP_SIZE = 5;

struct coord{//coordinates used to place ship
    int x, y;
    coord(int j=0, int z=0){
        x = j;
        y = z;
    }

    friend bool operator==(const coord& c, const coord& x){
        if(c.x == x.x){
            return (c.y == x.y);
        }else{
            return false;
        }
    }
};

class ship
{
    public:
        ship(string name = "default", int length = 5);

        string m_name;
        int m_length;
        coord m_BoardPosition[MAX_SHIP_SIZE];
        bool m_hit[MAX_SHIP_SIZE];
};

#endif // _SHIP_H_
