//this will try to emulate converting c or c++ code into mips:
//current small functionalities like printf and scanf will be implemented simply.
//works by reading a c++ file then creating a .a file using fstream.
//right now stores the variables in separate t registers from t0 to t9
//i should definitely learn how to use try throw and catch for error management but ceebs


//for uni purposes i will have to make the mips do the math, which means using mips instructions.


#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>


class File//need to create a file reader as well to parse all the lines from the input c file.
{
public:
    std::string filepath;
    std::ofstream outfile;
    File(){

    }
    int varloader()
    {

    }

    bool push_back_line()
    {
        return true;
    }
    
    bool insert_line(int num)
    {
        return true;
    }


    ~File()
    {

    }

};


class MIPS : public File//this class stores 10 variables, i need to figure out how to do math operations, probably using operator overloading. for now only able to use integer math operations. as of 17/08 planning only to have printf and scanf functionality
{   
    public:
        int registercounter = 0;
        std::map<std::string, int> variables; //typical map to assign a name to an integer, need to figure out how to map these to a register
        std::map<std::string, int> var_register_map;  //solution to above, just have 2 maps one to point to the integer and one to point to the register to be used
        //limitations of this system is no 2 same names for variables can be used

        bool assign(int num,const std::string& str) // assign an integer variable
        {
            if(registercounter > 9)
            {
                std::cout<<"Max variable count reached";
                return false; //error for too many variables
            }
            variables[str] = num;
            var_register_map[str] = registercounter;
            registercounter++;
            return true;
        }

        int getVal(const std::string& name) const{ //a typical number getter not sure where i will use this
            if (variables.count(name) > 0){
            return variables.at(name);
            } else {
                std::cout<<"variable"<<name<<"not found \n";
                return 0;
            }
        }



        bool printf(int var)
        {

            return true;
        }

        bool printf(double var)
        {
            return true;
        }

        bool printf(const std::string& var)
        {
            return true;
        }

        bool scanf(int var)
        {
            return true;
        }

        bool scanf(double var)
        {
            return true;
        }

        bool scanf(const std::string& var)
        {
            return true;
        }




};





int main(int argc, char** argv) //has 2 arguments, one for filepath to cpp file and then the other to create a .a file
{
    if(argc < 3)
    {
        std::cout<<"Error: Arguments are missing";
        return 0;
    }

    if(argc > 3)
    {
        std::cout<<"Error: too many arguments";
        return 0;
    }

    File assemble;

    assemble.filepath = argv[1];

    


}
