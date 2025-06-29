#include "calc.h"

/*input :- 2 Integer class objects
 * output :- true(1) or false(0)
 *ture if a<b a string is smaller than b else false
 */
bool InfiniteArithmetic::Integer::operator<(const InfiniteArithmetic::Integer& given) const{
    string num1=int0,num2=given.int0;
    size_t len1 = num1.size() , len2 = num2.size();
    //if both strings negative
    if(num1[0]=='-'&&num2[0]=='-'){
        num1.erase(0,1),num2.erase(0,1);
        return InfiniteArithmetic::Integer{num2}<InfiniteArithmetic::Integer{num1};
    }
    //if one string negative another positive
    else if (num1[0]=='-'&&num2[0]!='-'){
        return true;
    }
    else if (num1[0]!='-'&&num2[0]=='-'){
        return false;
    }
    //both positive 2 cases
    if ( len1 < len2 ){
        return true;
    }
    if( len2 == len1 ){
        for(int j = 0 ; j < len1 ; j++){
            if(num1[j] < num2[j]){
                return true;
            }
            else if (num1[j] > num2[j]) {
                break;
            }
        }
    }
    //when all cases done there is only else case remaining so returning false
    return false;
}
/*operator overloading for -
* if -a where a = -2
* returns 2
*/
InfiniteArithmetic::Integer InfiniteArithmetic::Integer::operator-() const {
    string x { int0 };
    //if string is negative andd we put -a returns the string after making it positive
    if (x[0] == '-') {
        return x.substr(1);
    }
    //if string is positive andd we put -a returns the string after making it negative
    x.insert(0, 1, '-');
    return x;
}
/*input :- 2 Integer objects
 *output:-an Integer object which is the 2 strings added as if they are numbers
 */
InfiniteArithmetic::Integer InfiniteArithmetic::Integer::operator+(const InfiniteArithmetic::Integer& given) const {
    string num1 = int0 , num2 = given.int0, sum;
    //short circuiting the case when both 0
    if(num1=="0"&&num2=="0"){
        return InfiniteArithmetic::Integer{};
    }
    int carry {};
    size_t len1 = num1.size() , len2 = num2.size();
    //case where one of the strings are negative where we directly return the difference of the two
    if((num1[0] == '-') != (num2[0] == '-')) {
        if(num1[0] == '-') {
            if(num1.substr(1)==num2){
                return InfiniteArithmetic::Integer{};
            }
            return (InfiniteArithmetic::Integer(num2) - (-InfiniteArithmetic::Integer(num1)));
        }
        if(num2.substr(1)==num1){
            return InfiniteArithmetic::Integer{};
        }
        return (InfiniteArithmetic::Integer{num1} - (-InfiniteArithmetic::Integer(num2)));
    }
    //both negative where we return the negative of the sum of both strings
    if((num1[0] == '-') && (num2[0] == '-')) {
        if(num2=="-0"&&num1=="-0"){
            return InfiniteArithmetic::Integer{};
        }
        return -((-InfiniteArithmetic::Integer{num1}) + (-InfiniteArithmetic::Integer{num2}));
    }
    //algorithm for the sum of two strings
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());

    //loop runs till the point when atleast on the strings reach its end
    for (size_t i = 0; i < std::min(len1, len2); i++) {
        sum.push_back(num1[i] + num2[i] + carry - '0');
        carry = 0;
        if (sum[i] > '9') {
            sum[i] -= 10;
            carry = 1;
        }
    }

    string bigger {};
    if (std::max(len1, len2) == len1) {
        bigger = num1;
    } else {
        bigger = num2;
    };

    //if one of the strings length is longer then we start pushing the bigger strings values from the point where the other string ended
    for (size_t i = std::min(len1, len2); i < std::max(len1, len2); i++) {
        sum.push_back(bigger[i] + carry);
        carry = 0;
        if (sum[i] > '9') {
            sum[i] -= 10;
            carry = 1;
        }
    }

    //after everything is pushed back if there still remains a carry we push it into the string like 99 + 9
    if (carry) {
        sum.push_back('1');
    }

    std::reverse(sum.begin(), sum.end());

    return sum;

}

/*input :- 2 Integer objects
 *output:-an Integer object which is the 2 strings subracted as if they are numbers
 */
InfiniteArithmetic::Integer InfiniteArithmetic::Integer::operator-(const InfiniteArithmetic::Integer &given) const {
    string num1 = int0 , num2 = given.int0 , diff;
    //short circuiting the case when both 0
    if(num1=="0"&&num2=="0"){
        return InfiniteArithmetic::Integer{};
    }
    //short circuiting the case when both are equal
    if (num1 == num2) {
        return InfiniteArithmetic::Integer {};
    }
   //case when first one is negative and the other is positive
    if(num1[0]=='-'&&num2[0]!='-'){
        num1 = (-InfiniteArithmetic::Integer{num1 }).val();
        return -(InfiniteArithmetic::Integer{num1} + InfiniteArithmetic::Integer{num2});
    }
    //case when second one is negative and the other is positive
    if (num1[0]!='-'&&num2[0]=='-'){
        num2 = (-InfiniteArithmetic::Integer{num2 }).val();
        return (InfiniteArithmetic::Integer{num1} + InfiniteArithmetic::Integer{num2});
    }
    //case where both strings negative we return the difference is the opposite order
    if (num1[0]=='-'&&num2[0]=='-'){
        num1 = (-InfiniteArithmetic::Integer{num1 }).val();
        num2 = (-InfiniteArithmetic::Integer{num2 }).val();
        return (InfiniteArithmetic::Integer{num2} - InfiniteArithmetic::Integer{num1});
    }
    size_t len1 = num1.size() , len2 = num2.size();
    //if first integer is smaller return negative of difference between both
    if ( InfiniteArithmetic::Integer{num1}<InfiniteArithmetic::Integer{num2} ){
        return -(InfiniteArithmetic::Integer(num2) - InfiniteArithmetic::Integer(num1));
    }
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    //algorithm to find difference
    int carry = 0;

    for (size_t i = 0; i < len2; i++) {
        diff.push_back(num1[i] - num2[i] + '0' + carry);
        carry = 0;
        if (diff[i] < '0') {
            diff[i] += 10;
            carry = -1;
        }
    }
    //if one of the strings length is longer then we start pushing the bigger strings values from the point where the other string ended
    for (size_t i = len2; i < len1; i++) {
        diff.push_back(num1[i] + carry);
        carry = 0;
        if (diff[i] < '0') {
            diff[i] += 10;
            carry = -1;
        }
    }
    std::reverse(diff.begin(), diff.end());
    return diff.substr(diff.find_first_not_of('0'));
}

InfiniteArithmetic::Integer InfiniteArithmetic::Integer::operator*(const InfiniteArithmetic::Integer &given) const {
    string num1=int0, num2=given.int0, num3 {}, product;
    //short circuiting the case when one of them 0
    if(num1=="0"||num2=="0"){
        return InfiniteArithmetic::Integer{};
    }
    //when one of the numbers is excatly negative removing the sign and multiplying.
    if((num1[0]=='-')!=(num2[0]=='-')){
        if(num1[0]=='-'){
            num1=(-InfiniteArithmetic::Integer(num1)).val();
        }
        else if(num2[0]=='-'){
            num2=(-InfiniteArithmetic::Integer(num2)).val();
        }
        return -(InfiniteArithmetic::Integer(num1) * InfiniteArithmetic::Integer(num2));
    }
    //when both are negative
    if((num1[0]=='-')&&(num2[0]=='-')) {
        num1=(-InfiniteArithmetic::Integer(num1)).val();
        num2=(-InfiniteArithmetic::Integer(num2)).val();
    }
    //carry is the carrying number for the next digit and temp is the digit which should be in the product result we are gonna push it to the result.
    int carry=0,temp=0;
    size_t len1 = num1.size() , len2 = num2.size();
    //reversing the string to use the common index
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    for(size_t i=0;i<len2;i++){
        //this for adding zeros like if we are multiplying the 1st number by the hundreds place of first second number we have to add 2 zeros .
        //in here as we are reversing the string we have to add them at the start
        num3.insert(0,i,'0');
        for(size_t j=0;j<len1;j++){
            temp=(num1[j] - '0')*(num2[i] - '0')+carry;
            carry=0;
            if(temp>9){
                carry=(temp/10);
                num3.push_back((temp%10)+'0');
            }
            else{
                num3.push_back(temp+'0');
            }
        }
        //this for the last digit there would be no digit to multiply so we have to do it like this
        if (carry!=0){
            num3.push_back(carry+'0');
            carry=0;
        }
        //if we reverse the string the string we can directly use the add function created to use for integers.
        std::reverse(num3.begin(), num3.end());
        if (i==0){
            product=num3;
        }
        else{
            product=(InfiniteArithmetic::Integer{product} + InfiniteArithmetic::Integer{num3}).val();
        }
        //making num3 null to re use it
        num3="";
    }
    //for example 65*65 is done as
    //56 56
    //56 * 5 = (25) (30)
    //       = 5 (32)
    //       =523
    //reversing product=325
    //56 * 6 = 0(30)(36)
    //       = 00(39)
    //       = 0093
    //reversing 3900
    //product=3900+325
    //       =4225
    return product;
}
InfiniteArithmetic::Integer InfiniteArithmetic::Integer::operator/(const InfiniteArithmetic::Integer &given) const {
    //doing the main division in float converting these numbers to float and dividing and truncating the numbers after decimal
    string num1=int0,num2=given.int0,result;
    result=(InfiniteArithmetic::Float{num1}/InfiniteArithmetic::Float{num2}).val();
    int position=result.find_first_of('.');
    result.erase(position,(result.size()-position));
    return result;
}
InfiniteArithmetic::Float InfiniteArithmetic::Float::operator-() const {
    //similar to integer just adding negative sign if not present and removing negative sign if present
    string x { float0 };
    if (x[0] == '-') {
        return x.substr(1);
    }
    x.insert(0, 1, '-');
    return x;
}

InfiniteArithmetic::Float InfiniteArithmetic::Float::operator+(const InfiniteArithmetic::Float &given) const {
    //overally removing the decimal and sending it to integer addition keeping decimal again
    string num1=float0,num2=given.float0,sum;
    //these are same condition as integers (+,-);(-,+);(-,-)
    if((num1[0] == '-') != (num2[0] == '-')) {
        if(num1[0] == '-') {
            if(num1.substr(1)==num2){
                return InfiniteArithmetic::Float{};
            }
            return (InfiniteArithmetic::Float(num2) - (-InfiniteArithmetic::Float(num1)));
        }
        if(num2.substr(1)==num1){
            return InfiniteArithmetic::Float{};
        }
        return (InfiniteArithmetic::Float{num1} - (-InfiniteArithmetic::Float(num2)));
    }
    if((num1[0] == '-') && (num2[0] == '-')) {
        if(num2=="-0"&&num1=="-0"){
            return InfiniteArithmetic::Float{};
        }
        return -((-InfiniteArithmetic::Float{num1}) + (-InfiniteArithmetic::Float{num2}));
    }
    int place1=num1.find_first_of('.'),place2=num2.find_first_of('.');
    //while adding we should make sure that the ones digit is added to once digit and in decimal too respectively
    //so we have to add trailing zeros to make the no of numbers after decimal same for that
    //first we should make the decimal place value same that is adding leadin zeros.
    if(place1>place2){
        num2.insert(0,place1-place2,'0');
    }
    else if (place2>place1){
        num1.insert(0,place2-place1,'0');
    }
    size_t len1 = num1.size() , len2 = num2.size();
    //adding trailing zeros as said
    if(len1>len2){
        num2.insert(len2,len1-len2,'0');
    }
    else if(len1<len2){
        num1.insert(len1,len2-len1,'0');
    }
    //removing the decimal.
    int place_decimal=num1.find_first_of('.');
    num1.erase(place_decimal,1);
    num2.erase(place_decimal,1);
    InfiniteArithmetic::Integer i1{num1},i2{num2};
    //sending them to int addition
    sum=(i1+i2).val();
    size_t len3 = sum.size();
    //placing the decimal as it is to not lose the place value
    if (len3 > (std::max(len2, len1) )) {
        sum.insert(len3 - (std::max(len2, len1) - place_decimal - 1), 1, '.');
    }
    else{
        sum.insert(0,std::max(len1,len2)-len3,'0');
        len3 = sum.size();
        sum.insert(len3 - (std::max(len2, len1) - place_decimal - 1), 1, '.');
    }
    //constructor takes care of trailing zeros and leading zeros if any
    return sum;
}

InfiniteArithmetic::Float InfiniteArithmetic::Float::operator-(const InfiniteArithmetic::Float &given) const {
    //just similar to float addition
    //removing the decimal sending it to int subtraction
    //errors are handeled by constructor
    string num1=float0,num2=given.float0,sum;
    if(num1[0]=='-'&&num2[0]!='-'){
        num1 = (-InfiniteArithmetic::Float{num1 }).val();
        if(num1=="0"&&num2=="0"){
            return InfiniteArithmetic::Float{};
        }
        return -(InfiniteArithmetic::Float{num1} + InfiniteArithmetic::Float{num2});
    }
    if (num1[0]=='-'&&num2[0]=='-'){
        num1 = (-InfiniteArithmetic::Float{num1 }).val();
        num2 = (-InfiniteArithmetic::Float{num2 }).val();
        return (InfiniteArithmetic::Float{num2} - InfiniteArithmetic::Float{num1});
    }
    if (num1[0]!='-'&&num2[0]=='-'){
        num2 = (-InfiniteArithmetic::Float{num2 }).val();
        return (InfiniteArithmetic::Float{num1} + InfiniteArithmetic::Float{num2});
    }
    if (num1 == num2) {
        return InfiniteArithmetic::Float{};
    }
    int place1=place,place2=given.place;
    if(place1>place2){
        num2.insert(0,place1-place2,'0');
    }
    else if (place2>place1){
        num1.insert(0,place2-place1,'0');
    }
    size_t len1 = num1.size() , len2 = num2.size();
    if(len1>len2){
        num2.insert(len2,len1-len2,'0');
    }
    else if(len1<len2){
        num1.insert(len1,len2-len1,'0');
    }
    int place_decimal=num1.find_first_of('.');
    num1.erase(place_decimal,1);
    num2.erase(place_decimal,1);
    InfiniteArithmetic::Integer i1{num1},i2{num2};
    sum=(i1-i2).val();
    size_t len3 = sum.size();
    if (len3 > (std::max(len2, len1) )) {
        sum.insert(len3 - (std::max(len2, len1) - place_decimal - 1), 1, '.');
    }
    else{
        sum.insert(0,std::max(len1,len2)-len3,'0');
        len3 = sum.size();
        sum.insert(len3 - (std::max(len2, len1) - place_decimal - 1), 1, '.');
    }
    return sum;
}
InfiniteArithmetic::Float InfiniteArithmetic::Float::operator*(const InfiniteArithmetic::Float &given) const {
    //removing the decimal and sending it to integer multiplication and adding the decimal again
    string num1 = float0,num2 = given.float0;
    if((num1[0]=='-')!=(num2[0]=='-')){
        if(num1[0]=='-'){
            num1=(-InfiniteArithmetic::Float(num1)).val();
        }
        else if(num2[0]=='-'){
            num2=(-InfiniteArithmetic::Float(num2)).val();
        }
        return -(InfiniteArithmetic::Float(num1) *InfiniteArithmetic::Float(num2));
    }
     if(num1[0] == '-' && num2[0] == '-') {
        num1=(-InfiniteArithmetic::Float(num1)).val();
        num2=(-InfiniteArithmetic::Float(num2)).val();
        return (InfiniteArithmetic::Float(num1)*InfiniteArithmetic::Float(num2));
    }
    num1.erase(place,1);
    num2.erase(given.place,1);
    size_t len1 = num1.size() , len2 = num2.size();
    string mul = ((InfiniteArithmetic::Integer(num1) * InfiniteArithmetic::Integer(num2))).val();
    size_t len3 = (mul).size();
    //placing the decimal correctly
    if(len3>len1- place+len2 - given.place) {
        mul.insert( len3 -(len1- place+len2 - given.place),1,'.');
    }
    else {
        mul.insert(0,len1+len2-len3,'0');
        len3 = mul.size();
        mul.insert( len3 -(len1- place+len2 - given.place),1,'.');
    }
    return mul;
    //example(2.2)(0.2)
    //22*02=44
    //.44
    //in constructor it changes to 0.44 while returning
}

InfiniteArithmetic::Float InfiniteArithmetic::Float::operator/(const InfiniteArithmetic::Float &given) const {
    string num1 = float0,num2 = given.float0,result;
    if(num1[0] == '-' && num2[0] == '-') {
        num1=(-InfiniteArithmetic::Float(num1)).val();
        num2=(-InfiniteArithmetic::Float(num2)).val();
        return (InfiniteArithmetic::Float(num1)/InfiniteArithmetic::Float(num2));
    }
    //when one of the numbers is excatly negative removing the sign and multiplying.
    if((num1[0]=='-')!=(num2[0]=='-')) {
        if(num1[0]=='-'){
            num1=(-InfiniteArithmetic::Float(num1)).val();
            return -(InfiniteArithmetic::Float(num1)/InfiniteArithmetic::Float(num2));
        }
        else if(num2[0]=='-') {
            num2=(-InfiniteArithmetic::Float(num2)).val();
            return -(InfiniteArithmetic::Float(num1)/InfiniteArithmetic::Float(num2));
        }
    }
    int place1=num1.find_first_of('.'),place2=num2.find_first_of('.');
    //removing the decimal by multiplying with tens.
    //example 1.23/1.2 is written as 123/120
    int power=(num2.size() - place2 - 1) - (num1.size() - place1 - 1);
    num1.erase(place1,1);num2.erase(place2,1);
    if(power>0){
        num1.insert(num1.size(),power,'0');
    }
    else if(power<0){
        power=power*-1;
        num2.insert(num2.size(),power,'0');
    }
     num1 = Integer{num1}.val() , num2 = Integer{num2}.val();
    string temp;
    //doing long division while doing it genrally if we are doing 31233/2 we take first digit and divide so for that created temp
    //temp takes the value 3 in above example
    //in some cases like 19323232/2
    //temp takes 1 and checks wheter greater than 2 or not
    //as it is less than 2 it takes 19 and do it
    if (num1.size()>=num2.size()){
        temp=num1.substr(0,num2.size());
    }
    bool decimal= false;
    int i=0;
    bool temp_less_num2=InfiniteArithmetic::Integer{temp}<InfiniteArithmetic::Integer{num2};
    int j=0;
    //in some cases like 1/2
    //there is no number beside 1 so we are gonna make it 10/2 and also adding . to result
    if (temp_less_num2){
        if(num2.size()<num1.size()) {
            temp.push_back(num1[num2.size()]);
            i++;
        }
        else{
            result.push_back('.');
            decimal=true;
            temp=num1;
            temp.push_back('0');
            j++;
        }
    }
    int x;
    for(  i  ; j<=1000 ;  i  ++){
        x=0;
        temp_less_num2= false;
        //doing repeated subtraction to know the quotient.
        //in the for loop j is no of digits after the decimal.
        for(x;!temp_less_num2;x++){
            temp_less_num2=InfiniteArithmetic::Integer{temp}<InfiniteArithmetic::Integer{num2};
            if(!temp_less_num2){
                temp=(InfiniteArithmetic::Integer{temp}-InfiniteArithmetic::Integer{num2}).val();
            }
        }
        x--;
        temp_less_num2=InfiniteArithmetic::Integer{temp}<InfiniteArithmetic::Integer{num2};
        result.push_back(x + '0');
        if (temp_less_num2){
            if(num2.size()+  i  <num1.size()) {
                temp.push_back(num1[num2.size() +   i  ]);
            }
            else{
                if (!decimal) {
                    result.push_back('.');
                    decimal=true;
                }
                temp.push_back('0');
                j++;

            }
        }
    }
    return result;
}

