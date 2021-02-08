#ifndef KASM_ERR
#define KASM_ERR


namespace KASM{

    enum ErrCode{

        ERR_OK,

        //Code errors
        ERR_MISSING_ARG,
        ERR_TYPE_MISMATCH,
        ERR_UNIMPLEMENTED,
        
        //Internal errors
        ERR_INTERNAL
    };

}

#endif