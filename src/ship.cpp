#include "ship.h"

ship::ship(string name, int length):m_name(name),m_length(length){
    for(int i = MAX_SHIP_SIZE; i<0; i++){ m_hit[i]=0; }
}
