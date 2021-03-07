# KASM
[Github](https://github.com/knoxaramav2/KASM)

A proof of concept library for extendable runtime assembly-like language. Allows for registration of custom functions beyond the base language. See below for base API.


## Roadmap
Goal | Progress
---- | --------
Linux Support | Priority
Windows Support | In Progress
Base Instructions | In Progress
Call Frames | Done
Global Stack | Done
Default Registers | Done
Custom Registers | In Progress
Function Registration | Done
```Graphics Library``` | In Progress
Special graphics registers | Not started
Pointer support | Not started
Keyboard support | In Progress
Terminal windows | Not Started
Terminal color | Not Started
Terminal shapes | Not Started
Basic Move/Print | In Progress
```Audio Library``` | Not Started
Beep Support | Not Started
WAV Support | Not Started
MP3 Support | Not Started
```Multithread Support``` | Not started
Thread Controller | Not Started
Thread Scheduling | Not Started
Thread Selector | Not Started


## Compilation:

### LINUX:
1) Cd into Src directory
2) Run makefile
3) libkasm.a will appear in the /bin directory


### WINDOWS: (WIP)
1) Requires cygwin/mingw or similar
2) Requires ncurses
3) Follow Linux instructions above
4) libkasm.dll will appear in the .bin directory



## Technical


### Types
Type | Size (bytes)
---- | -------------
INT | 4
FLOAT | 4
BYTE (unsigned) | 1
CHAR (signed) | 1
STRING | NA
Ref | (internal)
Custom | NA

### Basic API:
##### See README.md of other sub-libraries for their respective API extensions.
(Note: String support only where specified. String/Numeric conversions will otherwise result in type mismatch error.)
Assigns to right value:
Constant = cn
Register = rg
Label = lb
? = optional

Instruction | Arg0 | Arg1 | Arg2 | Description | State
----------- | ---- | ---- | ---- | ----------- | -----
noop        |  |  |  | Placeholder instruction | Done
mov         | cn/rg| rg | | Copy value to register | Done
exit        | cn/rg ? | | | Exit program. Optionally set an integer return value. | Done
add         | cn/rg | rg | | Add lv to rv register. | Done
mult        | cn/rg | rg | | Multiply lv to rv register. | Done
div         | cn/rg | rg | | Divide rv by lv. Store in rv register. | Done
pow         | cn/rg | rg | | Store rv^lv to rv. | Done
cmp         | cn/rg | cn/rg | | Supports string. Sets result to CMR register. | Done
jlss        | lb | | | Jump to label if cmr is < 0. | Done
jgtr        | lb | | | Jump to label if cmr is > 0. | Done
jeql        | lb | | | Jump to label if cmr is = 0. | Done
jneql       | lb | | | Jump to label if cmr is != 0. | Done
jmp         | lb | | | Jump to label. | Done
call        | lb | | | Push new call frame and jump to function. | Done
ret         | cn/rg ? | | | Pop call frame and return to callee. Optional return value. | Done
push        | cn/rg | | | Push value to stack. | Done
pop         | rg | | | Pop last stack value and store in register. | Done
getl        | rg | | | Read user input to string register. | Done
prnt        | cn/rg | | | | Done

### Terminal Api
##### * Must call KASM::LoadGraphics
Instruction | Arg0 | Arg1 | Arg2 | Description | State
----------- | ---- | ---- | ---- | ----------- | -----
pushxwin | | | | Create new window | Not Started
setxy | cn/rg | cn/rg | | Move cursor to X, Y | Done
setclr | | | | | Not Started
rect | | | | | Not Started
circ | | | | | Not Started
plotxy | cn/rg| cn/rg| cn/rg| Move cursor to X,Y and print| Done
mvwin | | | | | Not Started
settrmsz | | | | | Not Started
gettrmattr | cn/rg| cn/rg| | | Not Started

### Registers:

List of current registers and their types. Registers are not case sensitive.
Registers 0-3 are considered preserved, while 3+ are scratch. All string registers should be preserved as needed.

Register | Type | Description
-------- | ---- | -----------
RI0      | Int  | Preserved
RI1      | Int  | Preserved
RI2      | Int  | Preserved
RI3      | Int  | Preserved
RI4      | Int  | Scratch
RI5      | Int  | Scratch
RI6      | Int  | Scratch
RI7      | Int  | Scratch
RF0      | Int  | Preserved
RF1      | Int  | Preserved
RF2      | Int  | Preserved
RF3      | Int  | Preserved
RF4      | Int  | Scratch
RF5      | Int  | Scratch
RF6      | Int  | Scratch
RF7      | Int  | Scratch
RB0      | Int  | Preserved
RB1      | Int  | Preserved
RB2      | Int  | Preserved
RB3      | Int  | Preserved
RB4      | Int  | Scratch
RB5      | Int  | Scratch
RB6      | Int  | Scratch
RB7      | Int  | Scratch
RS0      | Int  | Preserved
RS1      | Int  | Preserved
RS2      | Int  | Preserved
RS3      | Int  | Preserved
RAC      | Int  | Accumulator
RIR      | Int  | Integer return
RFR      | Int  | Float return
RBR      | Int  | Byte return
CTR      | Int  | Instruction counter (not used)
CMR      | Int  | Comparison result


### Syntax
[Instruction] [Arg0] [Arg1] [Arg2]
:[label]
$[Directive] [Value]
#comment

### PreProcessor Directives
$import [file path] : Injects specified file in place of this directive. Labels and other references are resolved only when all scripts are fully read.


## C++ Api
ErrCode (\*InstructionProc)(Instruction*, InstructionFrame*);

bool RegisterInstruction(string instructionName, InstructionProc proc);

### Example
##### Format a function with this signature in your code
    ErrCode _example (Instruction\* inst, InstructionFrame\* frame){

    MemItem * mi = inst->Rv0;
    MemItem * reg = frame->GetRegisters->GetRegister("ri0");
    if (mi == nullptr) { return ERR_MISSING_ARG;}
    *(int*) reg = *(int *) mi->data;
    
    return ERR_OK;
    }

    //Register function
    KASM::AsmController ctrl;
    ctrl.RegisterFunction("example", _example);
    
    //call custom function from .kasm file
    :start
        ...
        example 42 #42 passed to arg0, moved to ri0
        prnt RI0 #prints 42
        exit 0

