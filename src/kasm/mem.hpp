#ifndef KASM_MEM
#define KASM_MEM

#include <vector>
#include <map>

namespace KASM{

    enum KASMType{
        KT_INT,
        KT_FLOAT,
        KT_BYTE,    //signed byte
        KT_CHAR,    //unsigned byte
        KT_STRING,
        KT_WIN,     //window for graphics
        
        KT_REF,     //inst ref
        KT_NA,      //illegal


        KT_SPECIAL, //start index for custom
    };

    //Rx0-Rx3 preserved
    //Rx4-Rx7 scratch
    enum KRegister{
        //integers
        KT_RI0,
        KT_RI1,
        KT_RI2,
        KT_RI3,
        KT_RI4,
        KT_RI5,
        KT_RI6,
        KT_RI7,

        //floats
        KT_RF0,
        KT_RF1,
        KT_RF2,
        KT_RF3,
        KT_RF4,
        KT_RF5,
        KT_RF6,
        KT_RF7,

        //bytes
        KT_RB0,
        KT_RB1,
        KT_RB2,
        KT_RB3,
        KT_RB4,
        KT_RB5,
        KT_RB6,
        KT_RB7,

        //strings
        KT_RS0,
        KT_RS1,
        KT_RS2,
        KT_RS3,

        //Special
        KT_RAC,     //accumulator
        KT_RIR,     //integer return
        KT_RFR,     //float return
        KT_RBR,     //byte return
        KT_CTR,     //instruction counter,
        KT_CMR,     //compare result

        KT_OFF,     //offset register (internal)

        //End
        KT_REG_CAP  //Not a register
    };

    enum KFlags{
        KT_CONDITION, //Comparison result
    };

    struct MemItem{
        KASMType type;
        void * data;
        bool isConst;

        MemItem();
        MemItem(KASMType type, bool isConst, void*data);
        ~MemItem();
    };

    //void ClearMemItem(MemItem*);

    //Stack frame
    struct Instruction;
    class CallFrame{

        public:

        CallFrame();
        ~CallFrame();

        Instruction * Callee;
        std::vector<MemItem*> Stack;

        MemItem* Pop();
        void Push(KASMType type, void * data, bool isConst);
    };

    //For safely freeing custom registers
    struct KCustomRegInfo{
        MemItem * Item;
        size_t Size;
    };

    //Registers
    class KAsmRegisters{

        //MemItem* _registers [KT_REG_CAP];
        std::map<std::string, MemItem*> _registers;
        std::vector<KCustomRegInfo> _custRegInfo;
        
        void LoadRegisters();

        public:

        KAsmRegisters();
        ~KAsmRegisters();

        void * GetValue(std::string& reg);
        bool SetValue(std::string& reg, void * data);
        MemItem * GetRegister(std::string& reg);
        MemItem * GetRegister(const char reg[]);

        bool AddCustom(std::string&, size_t );
    };

    class FlagController{

        unsigned _flag;

        public:
        
        void Set(KFlags val);
        bool Get(KFlags val);
    };

}


#endif