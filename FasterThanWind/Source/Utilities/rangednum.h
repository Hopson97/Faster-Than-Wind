#ifndef RANGEDNUM_H
#define RANGEDNUM_H

#include <iostream>

namespace util {

template<typename t>
class RangedNum
{
    public:

        RangedNum(t minimum, t maximum, t initialValue)
        :   minimumNumber   (minimum)
        ,   maximumNumber   (maximum)
        ,   value           (initialValue)
        { }

        void setValue(const t other)
        {
            if (other == value) {
               return;
            }

            if (other <= maximumNumber
                &&
                other >= minimumNumber) {
                value = other;
            }
            else {
                std::cout << "Number out of of range! (" << minimumNumber << " <= n <= " << maximumNumber << ")! \n";
                if ( other > maximumNumber ) {
                   value = maximumNumber;
                }
                else if ( other < minimumNumber) {
                    value = minimumNumber;
                }
            }
        }


        t getValue()
        {
            return value;
        }

    private:
        t minimumNumber;
        t maximumNumber;

        t value;
};
}//namespace util
#endif // RANGEDNUM_H
