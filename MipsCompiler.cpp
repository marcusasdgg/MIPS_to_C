//this will try to emulate converting c or c++ code into mips:
//current small functionalities like printf and scanf will be implemented simply.
//works by reading a c++ file then creating a .a file using fstream.
//right now stores the variables in separate t registers from t0 to t9
//i should definitely learn how to use try throw and catch for error management but ceebs


//for uni purposes i will have to make the mips do the math, which means using mips instructions for the math.


#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>

enum class File_type
{
    INTEGER,
    STRING,
    DOUBLE
};

enum class Operation_type
{
    INITIALIZE_VARIABLE,
    PRINTF,
    SCANF,
    ASSIGN_VARIABLE,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    EMPTY,
    IF,
    ELSE
};


class File//need to create a file reader as well to parse all the lines from the input c file.
{
public:
    std::string in_filepath;
    std::string out_filepath;
    std::fstream outfile;
    std::ifstream infile;
    bool open_state;
    
    File(std::string filepat,std::string output){
        in_filepath = filepat;
        infile.open(in_filepath);
        output = out_filepath;
        outfile.open(out_filepath);
        if(!outfile.is_open())
        {
            std::cout<<"error: "<<out_filepath<<"could not be created"<<std::endl;
            open_state = false;
            return;
        }
        std::cout<<out_filepath<<"was successfully created."<<std::endl;
        std::string line;
        if(!infile.is_open())
        {
            std::cout<<"errors\n";
            open_state = false;
            return;
        }
        std::cout<<std::endl<<"Found file "<<in_filepath<<" Preview of File: "<<std::endl<<std::endl;

        int count = 0;
        while(getline ( infile , line ))
        {
            if(count > 5)
            {
                break;
            }
            std::cout<<line<<std::endl;
            count++;
        }
        std::cout<<std::endl<<std::endl<<"compiling "<<in_filepath<<" into "<<output<<std::endl;
        open_state = true;
    }
    int varloader()
    {
        return 0;
    }

    bool push_back_line()
    {

        return true;
    }
    
    bool insert_line(int num)//adds lines in specific line number pushing stuff back
    {

        return true;
    }

    bool if_open()
    {
        return open_state;
    }


    ~File()
    {
        infile.close();
    }

};


class MIPS : public File//this class stores 10 variables, i need to figure out how to do math operations, probably using operator overloading. for now only able to use integer math operations. as of 17/08 planning only to have printf and scanf functionality
{   
    
    public:
        int registercounter;
        void initializer()
        {
            registercounter = 0;
        }
        std::map<std::string, int> variables; //typical map to assign a name to an integer, need to figure out how to map these to a register
        std::map<std::string, int> var_register_map;  //solution to above, just have 2 maps one to point to the integer and one to point to the register to be used
        //limitations of this system is no 2 same names for variables can be used

        bool assign(int num,const std::string& str) // assign an integer variable //will be overloaded with different types like string and double.
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

        bool file_parser()
        {
            return true;
        }

        bool is_open()
        {
            if()
        }

//all of the input and output stuff
//i think all the arguments should be of type string cus thats how we named the 'variables'. take from the predefined map we just made. oh but like we can build this into the parser
// idk though, nah lets just let the parser do the
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
        std::cout<<"Error: Arguments are missing\n";
        return 0;
    }

    if(argc > 3)
    {
        std::cout<<"Error: too many arguments\n";
        return 0;
    }


    File assemble(argv[1],argv[2]);
    if (!assemble.if_open())
    {
        std::cout<<"Exiting Program due to Error: File management issue.\n";
        return 1;
    }



    


}
