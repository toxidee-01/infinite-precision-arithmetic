#pragma once//so that no code is repeated twice if the same .h file is included twice

#include <algorithm>
#include <iostream>

using std::string;
/*The whole class is written in a different namespace called InfiniteArithmetic.
 *It is done so that the people using this library can also use other libraries which have classes whose names are same as these and they could be differentiated with each other.
 */
namespace InfiniteArithmetic {
    class Integer {

    private:
        string int0{};
        //private variable int0 storing a large integer which can not be stored using int datatype or bigger datatypes
    public:
        //default constructor
        Integer() : int0{"0"} {}

        /*normal constructor
         *input :- string(000 or 12351430123510 or -0 or -002435)
         *int0 becomes :- 0 or 12351430123510 or 0 or -2435)
         */
        Integer(const string s) {
            int0 = s;
            // Eliminate negative sign.
            bool negative = s[0] == '-';//to check weather first char is - or not.
            if (negative) {
                int0 = int0.substr(1);
                //Removing the first negative character and adding it after removing leading zeroes.
            }
            // Eliminate leading zeros.
            int first_non_zero = int0.find_first_not_of('0');
            if (first_non_zero == string::npos) {
                // Integer is zero.
                int0 = "0";
            } else {
                int0 = int0.substr(first_non_zero);
            }
            // Insert negative sign.
            if (negative && int0 != "0") {
                int0.insert(0, 1, '-');
            }
            if (int0 == "-0") {
                //-0 = 0
                int0 = "0";
            }
        }
        //copy constructor
        Integer(const Integer &given) : int0{given.int0} {}
        //destructor
        ~Integer() {
            int0 = "";
        }
        //checks weather first integer less than secong integer and returns a true or false
        bool operator<(const Integer &given) const;
        /*operator overloading for -
         * if -a where a = -2
         * returns 2
         */
        Integer operator-() const;
        /*operator overloading for subraction addition multiplication division for 2 Integer objects
         *returns a Integer*/
        Integer operator+(const Integer &given) const;

        Integer operator-(const Integer &given) const;

        Integer operator*(const Integer &given) const;

        Integer operator/(const Integer &given) const;

        string val() const { return int0; }//makes the private variable accessble to non class functions
        //parse function which makes a string into this classes object
        static Integer parse(string s) {
            return Integer {s};
        }
        //overloading << operator in order to directly print the Integers private string
        friend std::ostream &operator<<(std::ostream &out, const Integer &c);
    };

    std::ostream &operator<<(std::ostream &out, const Integer &c) {
        out << c.int0;
        return out;
    }

    class Float {
    private:
        string float0{};
        //private variable float0 storing a large float which can not be stored using int datatype or bigger datatypes
        int place{-1};
        //the index of the decimal in a sring
    public:
        //default constructor
        Float() : float0{"0.0"}, place{1} {}
        /*normal constructor
        *input :- string(00.00 or 1235143012.3510 or -0 or -00.24350)
        *Float0 becomes :- 0.0 or 1235143012.351 or 0.0 or -0.2435)
        *place becomes :- 1 or 10 or 1 or 2
        */
        Float(const string s) {
            float0 = s;
            // Add .0 if '.' not present
            place = float0.find_first_of('.');
            if (place == string::npos) {
                float0.push_back('.');
                float0.push_back('0');
                place = float0.size() - 2;
            }
            bool negative = s[0] == '-';//to check weather first char is - or not.
            if (negative) {
                float0 = float0.substr(1);
                //Removing the first negative character and adding it after removing leading zeroes.
            }
            // Eliminate leading zeros
            int first_non_zero = float0.find_first_not_of('0');
            if (float0[first_non_zero] == '.' && float0.find_first_of('.') > 0) {
                // Integer part is zero.
                float0 = float0.substr(place - 1);
            } else {
                float0 = float0.substr(first_non_zero);
            }
            // Eliminate trailing zeros
            int last_non_zero = float0.find_last_not_of('0');
            if (float0[last_non_zero] == '.') {
                // Fractional part is zero.
                float0 = float0.substr(0, last_non_zero + 2);
            } else {
                float0 = float0.substr(0, last_non_zero + 1);
            }
            if (negative && float0 != "0") {
                float0.insert(0, 1, '-');
            }
            place = float0.find_first_of('.');
            if (float0 == "-0.0") {
                float0 = "0.0";
            }//-0.0 = 0.0
            if (float0[0] == '-' && float0[1] == '.') {
                float0.insert(1, 1, '0');;
            }//inserted a 0 if no preceeding digit before . if the number is negative
            if (float0[(float0.size() - 1)] == '.') {
                float0.push_back('0');
            }//if there is no digit succeeding . then 0 is added
            if (float0[0] == '.') {
                float0.insert(0, 1, '0');
            }//if the number is starting from a . then 0 is inserted in the beginning
            place = float0.find_first_of('.');
        }
        //copy constructor
        Float(const Float &given) : place{given.place}, float0{given.float0} {}
        //destructor
        ~Float() {
            float0 = "";
            place = -1;
        }
        /*operator overloading for -
        * if -a where a = -2.0
        * returns 2.0
        */
        Float operator-() const;
        /*operator overloading for subraction addition multiplication division for 2 Float objects
        returns a Float*/
        Float operator+(const Float &given) const;

        Float operator-(const Float &given) const;

        Float operator*(const Float &given) const;

        Float operator/(const Float &given) const;
        //overloading << operator in order to directly print the Floats private string
        friend std::ostream &operator<<(std::ostream &out, const Float &c);
        //makes the private variable float0 accessible
        string val() const { return float0; }
        //parse function which makes a string into this classes object
        static Float parse (string s) {
            return Float {s};
        }
    };

    std::ostream &operator<<(std::ostream &out, const Float &c) {
        out << c.float0;
        return out;
    }
}