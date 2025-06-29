#include<iostream>
#include"calc.cpp"
int main (int argv,char* argc[]) {	
    std::string s1(argc[1]);
    std::string s2(argc[2]);
    std::string s3(argc[3]);
    std::string s4(argc[4]);
    if(s1 == "int" ) {
        InfiniteArithmetic::Integer const num1(s3);
        InfiniteArithmetic::Integer const num2(s4);
        if(s2 == "add") {
            std::cout<<num1+num2<<std::endl;
        }
        if(s2  == "sub") {
            std::cout<<num1-num2<<std::endl;
        }
        if(s2 == "mul") {
            std::cout<<num1*num2<<std::endl;
        }
        if(s2 == "div") {
            if(num2.val()=="0") {
                std::cout<<"Division by zero error"<<std::endl;
            }
            else{
                std::cout << num1 / num2 << std::endl;
            }
        }
    }
    if(s1 == "float" ) {
        InfiniteArithmetic::Float const num1(s3);
        InfiniteArithmetic::Float const num2(s4);
        if(s2 == "add") {
            std::cout<<num1+num2<<std::endl;
        }
        if(s2 == "sub") {
            std::cout<<num1-num2<<std::endl;
        }
        if(s2 == "mul") {
            std::cout<<num1*num2<<std::endl;
        }
        if(s2 == "div") {
            if(num2.val() == "0.0") {
                std::cout<<"Division by zero error"<<std::endl;
            }
            else{
                std::cout << num1 / num2 << std::endl;
            }
        }
    }
    return 0;
}
