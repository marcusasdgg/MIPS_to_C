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
    EMPTY,
    VOID
};

enum class Operation_type
{
    INITIALIZE_VARIABLE,
    PRINTF,
    SCANF,
    ASSIGN_VARIABLE,
    EMPTY,
    IF,
    ELSE,
    RETURN,
    FOR,
    WHILE,
};

enum class Equ_type
{
    EQUAL,
    BIGGER,
    SMALLER,
    NOT_EQUAL,
    BIGGER_EQUAL,
    SMALLER_EQUAL,
    EMPTY
};

enum class Mat_type
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MOD,
    EMPTY
};

enum class Rd_Brkt_type
{
    ROUND_LEFT,
    ROUND_RIGHT,
    EMPTY
};

enum class Sqr_Brkt_type
{
    SQUARE_LEFT,
    SQUARE_RIGHT,
    EMPTY
};

enum class Sqig_Brkt_type
{
    SQUIGGLY_LEFT,
    SQUIGGLY_RIGHT,
    EMPTY
};

struct Equality_Locate
{
    Equality_Locate(Equ_type t, int ln, int cp, const std::string& l)
        : type(t), line_number(ln), char_position(cp), line(l)
    {
    }
    enum Equ_type type;
    int line_number;
    int char_position;
    std::string line;
};

struct Math_Locate
{
    Math_Locate(Mat_type t, int ln, int cp, const std::string& l)
        : type(t), line_number(ln), char_position(cp), line(l)
    {
    }
    enum Mat_type type;
    int line_number;
    int char_position;
    std::string line;
};


struct Variable_Locate
{
   Variable_Locate(Var_type t, int ln, int cp, const std::string& l)
        : type(t), line_number(ln), char_position(cp), line(l)
    {
    

    }
    enum Var_type type;
    int line_number;
    int char_position;
    std::string line;
};

struct Operation_Locate
{
    Operation_Locate(Operation_type t, int ln, int cp, const std::string& l)
        : type(t), line_number(ln), char_position(cp), line(l)
    {

    }
    enum Operation_type type;
    int line_number;
    int char_position;
    std::string line;
};


struct Everything_Locate
{
    std::vector<Operation_Locate> Temp_Op_Store;
    std::vector<Variable_Locate> Temp_Var_Store;
    std::vector<Equality_Locate> Temp_Equ_Store;
    std::vector<Math_Locate> Temp_Mat_Store;
};

struct Function_Locate
{
    Var_type return_type;
    std::string name;
    int start_line; //where the function is declared. {line before { operator}
    int end_line; //where the block end is declared (i.e } operator)

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

    std::vector<Operation_Locate> Op_Store;
    std::vector<Variable_Locate> Var_Store;
    std::vector<Equality_Locate> Equ_Store;
    std::vector<Math_Locate> Mat_Store;
    std::vector<Function_Locate> function_store;
    
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

        keywords.push_back("int "); //index 0
        keywords.push_back("string "); //index 1 //function to find implemented find_var
        keywords.push_back("double "); //index 2

        keywords.push_back("printf(");//index 3 //function to find implemented_op
        keywords.push_back("scanf("); //index 4


        keywords.push_back("return");//index 5
        keywords.push_back("while");//index 6
        keywords.push_back("if");//index 7 //function to find implemented find_op will make a new one in future
        keywords.push_back("else");//index 8
    
        keywords.push_back("=");//index 9
        keywords.push_back("<");//index 10
        keywords.push_back(">");//index 11 //not yet implemented
        keywords.push_back("<=");//index 12
        keywords.push_back(">=");//index 13

        keywords.push_back("+");//index 14
        keywords.push_back("-");//index 15  //not yet implmented
        keywords.push_back("/");//index 16
        keywords.push_back("*");//index 17
        keywords.push_back("%");//index 18

        keywords.push_back("for "); //index 19
        keywords.push_back("void "); //index 20

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
            case Var_type::VOID:
                std::cout <<"Var Void\n";
                break;
            default:
                std::cout << "Unknown Var_type\n";
        }
    }
   
    else if constexpr (std::is_same_v<T,Equ_type>)
    {
        switch (foo) 
        {
            case Equ_type::EQUAL:
                std::cout<<"Equal operator\n";
                break;
            case Equ_type::BIGGER:
                std::cout<<"Bigger operator\n";
                break;
            case Equ_type::SMALLER:
                std::cout<<"Smaller operator\n";
                break;
            case Equ_type::BIGGER_EQUAL:
                std::cout<<"Bigger or Equal operator\n";
                break;
            case Equ_type::SMALLER_EQUAL:
                std::cout<<"Smaller or Equal operator\n";
                break;
            case Equ_type::EMPTY:
                std::cout<<"Empty operator\n";
                break;
        }
    }

    
    
    else if constexpr (std::is_same_v<T,Mat_type>)
    {
        switch (foo) 
        {
            case Mat_type::ADD:
                std::cout<<"Add operation\n";
                break;
            case Mat_type::DIVIDE:
                std::cout<<"Divide operation\n";
                break;
            case Mat_type::SUBTRACT:
                std::cout<<"Subtract operation\n";
                break;
            case Mat_type::MOD:
                std::cout<<"Mod operation\n";
                break;
            case Mat_type::MULTIPLY:
                std::cout<<"Multiply operation\n";
                break;
            case Mat_type::EMPTY:
                std::cout<<"Empty operation\n";
                break;
        }

    }

    else
    {
        std::cout<<"unknown type";
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
        

        std::cout<<"\tfound "<<Var_Store.size()<<" variables.\n\n";
        for (int i = 0 ; i < Var_Store.size() ; i++)
        {
            std::cout<<"information on vector variable "<<i<<"\n\t";
            print_type(Var_Store[i].type);
            std::cout<<"\tline data: "<<Var_Store[i].line<<std::endl;
            std::cout<<"\tstart char position in line: "<<Var_Store[i].char_position<<std::endl;
            std::cout<<"\tline number in file: "<<Var_Store[i].line_number<<std::endl;
            std::cout<<"\n";
        }

        std::cout<<"\tfound "<<Equ_Store.size()<<" equality operations.\n\n";
        for (int i = 0 ; i < Equ_Store.size() ; i++)
        {
            std::cout<<"information on vector equality Operation "<<i<<"\n\t";
            print_type(Equ_Store[i].type);
            std::cout<<"\tline data: "<<Equ_Store[i].line<<std::endl;
            std::cout<<"\tstart char position in line: "<<Equ_Store[i].char_position<<std::endl;
            std::cout<<"\tline number in file: "<<Equ_Store[i].line_number<<std::endl;
            std::cout<<"\n";
        }

        std::cout<<"\tfound "<<Mat_Store.size()<<" math operations.\n\n";
        for (int i = 0 ; i < Mat_Store.size() ; i++)
        {
            std::cout<<"information on vector Operation "<<i<<"\n\t";
            print_type(Mat_Store[i].type);
            std::cout<<"\tline data: "<<Mat_Store[i].line<<std::endl;
            std::cout<<"\tstart char position in line: "<<Mat_Store[i].char_position<<std::endl;
            std::cout<<"\tline number in file: "<<Mat_Store[i].line_number<<std::endl;
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

int main_start_line = 0;

        

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

         //okay control structure of this thing.
 Everything_Locate Find_Thing(std::string line) 
{   //alright need to know how this works.
//problem is i is used both to check if found and to iterate, solution is to maybe add a new int variable to check.

    int char_pos = 0;
    Everything_Locate result;
    std::vector<int> find(keywords.size());
   while (1)
   {
    int count = 0;
    for (int val : find)
    {
        if (val >= line.size())
        {
            count++;
        }
    }
    if (count == keywords.size())
    {   
        return result;
    }
    std::size_t found;
    for(int i = 0 ; i < keywords.size() ; i++)
    {
        
       found = line.find(keywords[i],find[i]);

        if(found == std::string::npos)
        {
            find[i] = line.size();
            continue;
        }


        switch(i)
        {
            case 0:
                result.Temp_Var_Store.push_back({Var_type::INTEGER,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 1:
                result.Temp_Var_Store.push_back({Var_type::STRING,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 2:
                result.Temp_Var_Store.push_back({Var_type::DOUBLE,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 3:
                result.Temp_Op_Store.push_back({Operation_type::PRINTF,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 4:
                result.Temp_Op_Store.push_back({Operation_type::SCANF,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 5:
                result.Temp_Op_Store.push_back({Operation_type::RETURN,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 6:
                result.Temp_Op_Store.push_back({Operation_type::WHILE,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 7:
                result.Temp_Op_Store.push_back({Operation_type::IF,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 8:
                result.Temp_Op_Store.push_back({Operation_type::ELSE,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 9:
                result.Temp_Equ_Store.push_back({Equ_type::EQUAL,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 10:
                result.Temp_Equ_Store.push_back({Equ_type::SMALLER,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 11:
                result.Temp_Equ_Store.push_back({Equ_type::BIGGER,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 12:
                result.Temp_Equ_Store.push_back({Equ_type::SMALLER_EQUAL,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 13:
                result.Temp_Equ_Store.push_back({Equ_type::BIGGER_EQUAL,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 14:
                result.Temp_Mat_Store.push_back({Mat_type::ADD,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 15:
                result.Temp_Mat_Store.push_back({Mat_type::SUBTRACT,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 16:
                result.Temp_Mat_Store.push_back({Mat_type::DIVIDE,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 17:
                result.Temp_Mat_Store.push_back({Mat_type::MULTIPLY,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 18:
                result.Temp_Mat_Store.push_back({Mat_type::MOD,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 19:
                result.Temp_Op_Store.push_back({Operation_type::FOR,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
            case 20:
                result.Temp_Var_Store.push_back({Var_type::VOID,-1,static_cast<int>(found),line});
                find[i] = found + keywords[i].size() + 1;
                break;
        } 
    }
   }
    
    return result;
}
        

        void parser(); //parses text in the input file into a vector of either operations or variable assigning

        void variable_assign();

        void coder(); //adds the represented vectors as mips assembly in the output file.

        void find_function();

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
{ //need to write in support for new find_thing template function that returns in a vector of find results.
    std::string current_line;

    for(int i = 0 ; i < line_count ; i++)
    {
        current_line = get_line(i);
        Everything_Locate temp = Find_Thing(current_line);
        for(auto val : temp.Temp_Equ_Store)
        {   
            val.line_number = i;
            Equ_Store.push_back(val);
        }

        for(auto val : temp.Temp_Mat_Store)
        {
            val.line_number = i;
            Mat_Store.push_back(val);
        }

        for(auto val : temp.Temp_Op_Store)
        {
            val.line_number = i;
            Op_Store.push_back(val);
        }

        for(auto val : temp.Temp_Var_Store)
        {
            val.line_number = i;
            Var_Store.push_back(val);
        }
        
    }

    //now we find any functions, 
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


inline void MIPS::find_function()
{
    std::vector<Function_Locate> temp;
    for (auto val : Var_Store)
    {
        //find the word after the int, var or string or void specifier, if ( is after then all good.
         switch (val.type)
         {
            case Var_type::DOUBLE:
                
            case Var_type::INTEGER:
            case Var_type::STRING:
            case Var_type::VOID:
         } 
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

//alright now i have a decision to make, i have another solution that i can implement, which is to remove that word from the string and have a int counter showing new position.

