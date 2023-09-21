//this will try to emulate converting c or c++ code into mips:
//current small functionalities like printf and scanf will be implemented simply.
//works by reading a c++ file then creating a .a file using fstream.
//right now stores the variables in separate t registers from t0 to t9
//i should definitely learn how to use try throw and catch for error management but ceebs


//for uni purposes i will have to make the mips do the math, which means using mips instructions for the math.

//do i need a whole entire another class to deal with file parsing?

//also this compiler is built ina  manner where it will not matter how the line is ended i.e no ;



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
    EQUAL,
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
    std::string line;
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

        keywords.push_back("int"); //index 0
        keywords.push_back("string"); //index 1 //function to find implemented find_var
        keywords.push_back("double"); //index 2

        keywords.push_back("printf");//index 3 //function to find implemented_op
        keywords.push_back("scanf"); //index 4

        keywords.push_back("+");//index 5
        keywords.push_back("-");//index 6  //function to find implemented find_op
        keywords.push_back("/");//index 7
        keywords.push_back("%");//index 8

        keywords.push_back("return");//index 9
        keywords.push_back("while");//index 10
        keywords.push_back("if");//index 11 //function to find implemented find_op will make a new one in future
        keywords.push_back("else");//index 12
        
        keywords.push_back("{");//index 13
        keywords.push_back("}");//index 14 //not yet implemented

        keywords.push_back("=");//index 15
        keywords.push_back("<");//index 16
        keywords.push_back(">");//index 17 //not yet implemented
        keywords.push_back("<=");//index 18
        keywords.push_back(">=");//index 19

        keywords.push_back("(");//index 13
        keywords.push_back(")");//index 14 //not yet implemented

        keywords.push_back("["); //index 15 //not yet implemented
        keywords.push_back("]"); //index 16
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
        return infile.is_open();
    }


    ~File()
    {
        infile.close();
    }

    template<typename T>
void print_type(T foo)
{
    if constexpr (std::is_same_v<T, Operation_type>) {
        switch (foo) {
            case Operation_type::INITIALIZE_VARIABLE:
                std::cout << "Op Initialize Variable\n";
                break;
            case Operation_type::PRINTF:
                std::cout << "Op Printf\n";
                break;
            case Operation_type::SCANF:
                std::cout << "Op Scanf\n";
                break;
            case Operation_type::ASSIGN_VARIABLE:
                std::cout << "Op Assign Variable\n";
                break;
            case Operation_type::ADD:
                std::cout << "Op Addition\n";
                break;
            case Operation_type::SUBTRACT:
                std::cout << "Op Subtract\n";
                break;
            case Operation_type::MULTIPLY:
                std::cout << "Op Multiply\n";
                break;
            case Operation_type::DIVIDE:
                std::cout << "Op Divide\n";
                break;
            case Operation_type::MOD:
                std::cout << "Op Mod\n";
                break;
            case Operation_type::EMPTY:
                std::cout << "Op Empty\n";
                break;
            case Operation_type::IF:
                std::cout << "Op If\n";
                break;
            case Operation_type::ELSE:
                std::cout << "Op Else\n";
                break;
            case Operation_type::RETURN:
                std::cout << "Op Return\n";
                break;
            case Operation_type::FOR:
                std::cout << "Op For\n";
                break;
            case Operation_type::WHILE:
                std::cout << "Op While\n";
                break;
            case Operation_type::EQUAL:
                std::cout<<"Op equal\n";
                break;
            default:
                std::cout << "Unknown Operation_type\n";
        }
    }
    else if constexpr (std::is_same_v<T, Var_type>) {
        switch (foo) {
            case Var_type::INTEGER:
                std::cout << "Var Integer\n";
                break;
            case Var_type::STRING:
                std::cout << "Var String\n";
                break;
            case Var_type::DOUBLE:
                std::cout << "Var Double\n";
                break;
            case Var_type::EMPTY:
                std::cout << "Var Empty\n";
                break;
            default:
                std::cout << "Unknown Var_type\n";
        }
    }
    else {
        std::cout << "Unknown type\n";
    }
}

    void debug_vector()
    {
        std::cout<<"Information on all the vectors so far: \n\n";

        std::cout<<"\tfound "<<Op_Store.size()<<" operations.\n\n";
        for (int i = 0 ; i < Op_Store.size() ; i++)
        {
            std::cout<<"information on vector Operation "<<i<<"\n\t";
            print_type(Op_Store[i].type);
            std::cout<<"\tline data: "<<Op_Store[i].line<<std::endl;
            std::cout<<"\tstart char position in line: "<<Op_Store[i].char_position<<std::endl;
            std::cout<<"\tline number in file: "<<Op_Store[i].line_number<<std::endl;
            std::cout<<"\n";
        }
        
       std::cout<<std::endl;

        std::cout<<"\tfound "<<Var_Store.size()<<" variables.\n\n";
        for (int i = 0 ; i < Var_Store.size() ; i++)
        {
            std::cout<<"information on vector variable "<<i<<"\n";
            std::cout<<"\tline data: "<<Var_Store[i].line<<std::endl;
            std::cout<<"\tstart char position in line: "<<Var_Store[i].char_position<<std::endl;
            std::cout<<"\tline number in file: "<<Var_Store[i].line_number<<std::endl;
            std::cout<<"\n";
        }

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

        std::string get_line(int n) //issue is the getline(infile,result) aint even instantiating which means something wrong with the file itself?
        {
             
            if (!infile.is_open())
            {
                std::cout<<"not open";
                return NULL;
            }
            if(n > line_count)
            {
                std::cout<<"error accessing uninitialized line";
                return NULL;
            }
            int current = 0;
            std::string result;
            infile.clear();
            infile.seekg(0); 
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
                    
                    if(line[found + keywords[i].size()] != ' ') //if the character after the word is not a space we discard.
                    {
                        continue;
                    }
                    switch(i)
                    {
                        case 0:
                            temp.char_position = found;
                            temp.line = line;
                            temp.type = Var_type::INTEGER;
                            return temp;
                        break;
                        
                        case 1:
                            temp.char_position = found;
                            temp.line = line;
                            temp.type = Var_type::STRING;
                            return temp;
                        break;

                        case 2:
                            temp.char_position = found;
                            temp.line = line;
                            temp.type = Var_type::DOUBLE;
                            return temp;
                        break;

                    }
                    
                }
            }

            return temp;
        }
 
        struct Operation_Locate Find_Op(std::string line) //checks if any contains any operation keywords (including variables) returns the enum for that else returns empty. alright no now we are returning an array of structs, this is because

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
                        temp.line = line;
                        temp.char_position = found;
                        temp.type = Operation_type::EQUAL;
                        return temp;
                        break;
                    case 14:
                        return temp;
                        break;
                    case 15:
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

        void variable_assign();

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

    
    assemble.parser();
    assemble.debug_vector();

    
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


inline void MIPS::variable_assign()
{

}



inline void MIPS::coder() //this will read the stuff in the 2 vectors and actually start adding the assembly in to the out file. bfore we finish this need to add in assembly for printf etc. initiazlie variable.
{
    // std::vector<struct Operation_Locate> Op_Store;
    //std::vector<struct Variable_Locate> Var_Store;
    for (int j = 0 ; j < Var_Store.size() ; j++)
    {

    }
    for (int i = 0 ; i < Op_Store.size() ; i ++)
    {
    }

    

}


//huge error: forgot to add the variable initializer. need to create a function that reads the line 
    
// this will be complicated, every line will also have to search for the mapped 'variables'.
// i.e intiazlie variable integer i = 0;
// integer will be added into the vector map with value 0
// afterwards will need a function to searchfor the name of that variable anywhere after the point where it was initialized.
//oh wait no need can just call a function to search for name of a variable that is used after any operation.


//21/09 error: getline function not working at all ... now working, added a ; to if...

//steps to do now: write a function that takes in the vector of variables then adds it into the map with the name and int value. afterwards function overload a couple times to do for double and string.
//okay now there is a problem, it is not reading the = in my current example.cpp this is due to the find_op function only capable of returning 1 type operation in this case if and not =, 
// to fix this we can try just make a vector of structure and then return that and then deal with that instead.
//ok hwo about this, we create a 3rd function just for equality, inequality, and < and > this is a lot easier than searching for multiple keywords.