#ifndef KASM_ERR
#define KASM_ERR


namespace KASM{

    enum ErrCode{

        ERR_OK,

        //Code errors
        ERR_MISSING_ARG,
        ERR_ILLEGAL_SYNTAX,
        ERR_TYPE_MISMATCH,
        ERR_UNIMPLEMENTED,
        ERR_ILLEGAL_ARG,
        ERR_EMPTY_STACK,
        ERR_OUT_OF_RANGE,

        ERR_COMMAND_NOT_FOUND,
        ERR_REGISTER_NOT_FOUND,
        
        //Internal errors
        ERR_INTERNAL
    };

}

#endif