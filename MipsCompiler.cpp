//this will try to emulate converting c or c++ code into mips:
//current small functionalities like printf and scanf will be implemented simply.
//works by reading a c++ file then creating a .a file using fstream.
//right now stores the variables in separate t registers from t0 to t9
//i should definitely learn how to use try throw and catch for error management but ceebs


//for uni purposes i will have to make the mips do the math, which means using mips instructions for the math.

//do i need a whole entire another class to deal with file parsing?



#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>

enum class Var_type
{
    INTEGER,
    STRING,
    DOUBLE,
    EMPTY
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
    MOD,
    EMPTY,
    IF,
    ELSE,
    RETURN,
    FOR,
    WHILE,
};

struct Variable_Locate
{
    Variable_Locate()
    {
        type = Var_type::EMPTY;
        line_number = -1;
        char_position = -1;
    }
    enum Var_type type;
    int line_number;
    int char_position;
};

struct Operation_Locate
{
    Operation_Locate()
    {
        type = Operation_type::EMPTY;
        line_number = -1;
        char_position = -1;
    }
    enum Operation_type type;
    int line_number;
    int char_position;
    std::string line;
};


class File//need to create a file reader as well to parse all the lines from the input c file.
{
public:
    std::string in_filepath;
    std::string out_filepath;
    std::fstream outfile;
    std::ifstream infile;
    bool open_state;
    int line_count = 0;

    std::vector<std::string> keywords;

    std::vector<struct Operation_Locate> Op_Store;
    std::vector<struct Variable_Locate> Var_Store;
    
    File(std::string filepat,std::string output){
        in_filepath = filepat;
        infile.open(in_filepath);
        out_filepath = output;
        outfile.open(out_filepath,std::ios::out);
        
        if(!infile.is_open())
        {
            std::cout<<"Error: File \""<<in_filepath<<"\" could not be found\n";
            open_state = false;
            return;
        }
        std::cout<<std::endl<<"Found file \""<<in_filepath<<"\" Preview of File: \""<<std::endl<<std::endl;
        std::string line;
        while(getline ( infile , line ))
        {
            if(line_count < 5)
            {
                 std::cout<<line<<std::endl;
            }
            line_count++;
        }
        if(!outfile.is_open())
        {
            std::cout<<"error: \""<<out_filepath<<"\" could not be created"<<std::endl;
            open_state = false;
            return;
        }
        std::cout<<std::endl<<"\""<<out_filepath<<"\"was successfully created."<<std::endl;
        
        std::cout<<std::endl<<"compiling "<<in_filepath<<" into "<<output<<std::endl;
        open_state = true;
        
        //add possible keywords to search for in the parse.

        keywords.push_back("int");
        keywords.push_back("string(");
        keywords.push_back("double(");

        keywords.push_back("printf(");
        keywords.push_back("scanf(");

        keywords.push_back("+");
        keywords.push_back("-");
        keywords.push_back("/");
        keywords.push_back("%");

        keywords.push_back("return");
        keywords.push_back("while");
        keywords.push_back("if");
        keywords.push_back("else");
        keywords.push_back("{");
        keywords.push_back("}");

    }

//these are all the output functions, i.e adds to the a.out
    bool push_back_line()
    {

        return true;
    }

    bool pop_back_line()
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
        MIPS(const std::string& input, const std::string& output)
    : File(input, output) // Initialize the base class
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

        std::string get_line(int n)
        {
            
            if(n > line_count)
            {
                return NULL;
            }
            int current = 0;
            std::string result;
            while(getline(infile,result))
            {
                if(current == n)
                {
                    return result;
                }
                current++;
            }
            

            return result;
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
        struct Variable_Locate Find_Var(std::string line) //this checks if there contains any variable keywords, if none returns empty.
        {
            struct Variable_Locate temp;
            for (int i = 0 ; i < 3 ; i++)
            {
                std::size_t found = line.find(keywords[i]);
                if ( found != std::string::npos)
                {
                    if(line[found + keywords[i].size()] != ' '); //if the character after the word is not a space we discard.
                    {
                        continue;
                    }
                    switch(i)
                    {
                        case 0:
                            temp.char_position = found;
                            temp.type = Var_type::INTEGER;
                            return temp;
                        break;
                        
                        case 1:
                            temp.char_position = found;
                            temp.type = Var_type::STRING;
                            return temp;
                        break;

                        case 2:
                            temp.char_position = found;
                            temp.type = Var_type::DOUBLE;
                            return temp;
                        break;

                    }
                    
                }
            }
            return temp;
        }

        struct Operation_Locate Find_Op(std::string line) //checks if any contains any operation keywords (including variables) returns the enum for that else returns empty.
        {
            struct Operation_Locate temp;
            for (int i = 3 ; i < 15 ; i++)
            {
                std::size_t found = line.find(keywords[i]);
                if ( found != std::string::npos)
                {
                    if (i ==  3)
                    {
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::PRINTF;
                        return temp;
                    }
                    if (i == 4)
                    {
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::SCANF;
                        return temp;
                    }

                    if (line[found + keywords[i].size()] != ' ')
                    {
                        continue;
                    }
                    
                    switch (i)
                    {
                    case 5:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::ADD;
                        return temp;
                    case 6:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::SUBTRACT;
                        return temp;
                    case 7:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::DIVIDE;
                        return temp;
                    case 8:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::MOD;
                        return temp;
                    case 9:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::RETURN;
                        return temp;
                    case 10:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::WHILE;
                        return temp;
                    case 11:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::IF;
                        return temp;
                    case 12:
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::ELSE;
                        return temp;
                    case 13:
                        return temp;
                        break;
                    case 14:
                        return temp;
                        break;
                    default:
                        break;
                    }
                    
                }
            }
            return temp;

        }

        void parser(); //parses text in the input file into a vector of either operations or variable assigning

        void coder(); //adds the represented vectors as mips assembly in the output file.
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

    MIPS assemble(argv[1],argv[2]);
    if (!assemble.if_open())
    {
        std::cout<<"Exiting Program due to Error: File management issue.\n";
        return 1;
    }

    
}


inline void MIPS::parser()//here comes the hard part, searching for "key words like int, double, string printf etc."
{
    std::string current_line;
    struct Operation_Locate Op;
    struct Variable_Locate Var;
    for(int i = 0 ; i < line_count ; i++)
    {
        current_line = get_line(i);
        Var = Find_Var(current_line);
        Op = Find_Op(current_line);
        
        if (Var.type != Var_type::EMPTY)
        {
            Var.line_number = i;
            Var_Store.push_back(Var);
        }

        if (Op.type != Operation_type::EMPTY)
        {
            Op.line_number = i;
            Op_Store.push_back(Op);
        }
        
        //error need to fix: return type of findop and findvar need to be the struct to carry more info
        
    }
    
}