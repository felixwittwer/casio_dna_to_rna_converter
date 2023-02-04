/*****************************************************************/
/*                                                               */
/*   Casio DNA to RNA converter                                  */
/*                                                               */
/*   File name : DNATORNA.c                                      */
/*                                                               */
/*   Copyright (c) 2023 Felix Wittwer                            */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>

void RenderStrand(int x, int y, int marker, int ends, char symbols[], int line){
    //int x ; int y are for the position
    //int marker specifies in which direction and how long the markers get rendered
    //int ends defines how the ends of the stands should be labeled
    //chat symbols[] is a list of the rendered characters 

    int iteration = 0;
    int xaddition;
    unsigned char buffer[12];

    if(line==1){
        Bdisp_DrawLineVRAM(x,y,x+102,y);

        // function just for this specific program  shortend because of storage
        if(ends==3 && marker<0){
            PrintMini(x-7,y-4,(unsigned char*)"3'", MINI_OVER);
            PrintMini(x+104,y-4,(unsigned char*)"5'", MINI_OVER);
        }else if(ends==5 && marker>0){
            PrintMini(x-7,y,(unsigned char*)"5'", MINI_OVER);
            PrintMini(x+104,y,(unsigned char*)"3'", MINI_OVER);
        }
    }

    while(iteration<15){
        xaddition = (iteration)*5+(7*((iteration)/3))+2;

        if(line==1){
            Bdisp_DrawLineVRAM(x+xaddition,y,x+xaddition,y+marker);
        }

        sprintf(buffer, "%c", symbols[iteration]);
        if(marker>0){
            PrintMini(x+xaddition-1,y+3, buffer, MINI_OVER);
        }else if(marker<0){
            PrintMini(x+xaddition-1,y-7, buffer, MINI_OVER);
        }

        iteration = iteration + 1;
    }
}

void RendertRNA(int x, int y){
    Bdisp_DrawLineVRAM(x-5,y,x-5,y+1);
    Bdisp_DrawLineVRAM(x,y,x,y+2);
    Bdisp_DrawLineVRAM(x+5,y,x+5,y+1);
    Bdisp_DrawLineVRAM(x-5,y+1,x+5,y+1);
}

void RendertRNAS(int x, int y, char mrna[]){
    RendertRNA(x,y);
    RendertRNA(x+22,y);
    RendertRNA(x+44,y);
    RendertRNA(x+66,y);
    RendertRNA(x+88,y);

    RenderResult(x-6,y+5,0,1,2,mrna);
    RenderResult(x+16,y+5,3,4,5,mrna);
    RenderResult(x+38,y+5,6,7,8,mrna);
    RenderResult(x+60,y+5,9,10,11,mrna);
    RenderResult(x+82,y+5,12,13,14,mrna);
}

RenderPointer(int x, int y, int pointer, int render){
    int xaddition;
    xaddition = (pointer)*5+(7*((pointer)/3))+2;
    if(render==1){
        Bdisp_DrawLineVRAM(x+xaddition-1,y,x+xaddition+1,y);
    }else if(render==0){
        Bdisp_ClearLineVRAM(x+xaddition-1,y,x+xaddition+1,y);
    }
}

void Render_F_Button(int x, int y, unsigned char *str){
    Bdisp_DrawLineVRAM(x, y-1, x+17, y-1);
    Bdisp_DrawLineVRAM(x-1, y-1, x-1, y+5);
    Bdisp_DrawLineVRAM(x+17, y-1, x+17, y+5);
    Bdisp_DrawLineVRAM(x+16, y-1, x+16, y+5);
    PrintMini(x,y, str, MINI_REV);

    Bdisp_ClearLineVRAM(x+17, y+4, x+15, y+6);
    Bdisp_ClearLineVRAM(x+17, y+5, x+16, y+6);
    Bdisp_SetPoint_VRAM(x+17, y+6, 0);
}

void Render_Buttons(){
    Render_F_Button(24,58, "ALL ");
    Render_F_Button(45,58, "D>D ");
    Render_F_Button(66,58, "M>T ");
    Render_F_Button(87,58, "HELP");
    // Render_F_Button(110,58, "HELP");
}

RenderResult(int x, int y, int pos1, int pos2, int pos3, char symbols[]){
    if(symbols[pos1]=='A'){
        if(symbols[pos2]=='U'){
            if(symbols[pos3]=='G'){
                PrintMini(x,y, (unsigned char*)"Met", MINI_OVER);
            }else if(symbols[pos3]=='U'||symbols[pos3]=='C'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Ile ", MINI_OVER);
            }
        }else if(symbols[pos2]=='C'){
            PrintMini(x,y, (unsigned char*)"Thr ", MINI_OVER);
        }else if(symbols[pos2]=='A'){
            if(symbols[pos3]=='G'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Lys ", MINI_OVER);
            }else if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Asn  ", MINI_OVER);
            }
        }else if(symbols[pos2]=='G'){    
            if(symbols[pos3]=='G'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Arg ", MINI_OVER);
            }else if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Ser  ", MINI_OVER);
            }
        }

    }else if(symbols[pos1]=='G'){
        if(symbols[pos2]=='U'){
            PrintMini(x,y, (unsigned char*)"Val ", MINI_OVER);
        }else if(symbols[pos2]=='C'){
            PrintMini(x,y, (unsigned char*)"Ala ", MINI_OVER);
        }else if(symbols[pos2]=='A'){
            if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Asp ", MINI_OVER);
            }else if(symbols[pos3]=='G'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Glu ", MINI_OVER);
            }
        }else if(symbols[pos2]=='G'){
            PrintMini(x,y, (unsigned char*)"Gly ", MINI_OVER);
        }

    }else if(symbols[pos1]=='U'){
        if(symbols[pos2]=='U'){
            if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Phe ", MINI_OVER);
            }else if(symbols[pos3]=='G'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Leu ", MINI_OVER);
            }
        }else if(symbols[pos2]=='C'){
            PrintMini(x,y, (unsigned char*)"Ser ", MINI_OVER);
        }else if(symbols[pos2]=='A'){
            if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Tyr ", MINI_OVER);
            }else if(symbols[pos3]=='A'||symbols[pos3]=='G'){
                PrintMini(x,y, (unsigned char*)"Stop", MINI_OVER);
            }
        }else if(symbols[pos2]=='G'){
            if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"Cys ", MINI_OVER);
            }else if(symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Stop", MINI_OVER);
            }else if(symbols[pos3]=='G'){
                PrintMini(x,y, (unsigned char*)"Trp ", MINI_OVER);
            }
        }

    }else if(symbols[pos1]=='C'){
        if(symbols[pos2]=='U'){
            PrintMini(x,y, (unsigned char*)"Leu ", MINI_OVER);
        }else if(symbols[pos2]=='C'){
            PrintMini(x,y, (unsigned char*)"Pro ", MINI_OVER);
        }else if(symbols[pos2]=='A'){
            if(symbols[pos3]=='U'||symbols[pos3]=='C'){
                PrintMini(x,y, (unsigned char*)"His ", MINI_OVER);
            }else if(symbols[pos3]=='G'||symbols[pos3]=='A'){
                PrintMini(x,y, (unsigned char*)"Gln ", MINI_OVER);
            }
        }else if(symbols[pos2]=='G'){
            PrintMini(x,y, (unsigned char*)"Arg ", MINI_OVER);
        }
    }else if(symbols[pos1]==' '||symbols[pos2]==' '||symbols[pos3]==' '){
        PrintMini(x,y, (unsigned char*)"    ", MINI_OVER);
    }
}

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    int iteration = 0;
    int pointer = 1;
    char dnaone [15] = "ATG";
    char dnatwo [15] = "";
    char mrna [15] = "AUG";
    char trna [15] = "";

    Bdisp_AllClr_DDVRAM();

    PrintMini(10,10,(unsigned char*)"Professional Edition",MINI_OVER);
    PrintMini(10,20,(unsigned char*)"V 1.00.00",MINI_OVER);
    PrintMini(10,30,(unsigned char*)"(c) 2023 Felix Wittwer",MINI_OVER);
    Render_Buttons();

    while(1){
        GetKey(&key);
        if(key==KEY_CTRL_F2||key==KEY_CTRL_F3||key==KEY_CTRL_F4||key==KEY_CTRL_F5){
            break;
        }
    }

    while(1){
        // GetKey(&key);
        if(key==KEY_CTRL_F3){
            Bdisp_AllClr_DDVRAM();
            RenderStrand(12,2,1,5, dnaone,1);
            RenderStrand(12,20,-1,3, dnatwo,1);
            Render_Buttons();
            while(1){
                GetKey(&key);
                //clear last pointer
                RenderPointer(12, 11, pointer-1, 0);
                Render_Buttons();
                
                if(key==KEY_CTRL_F2||key==KEY_CTRL_F3||key==KEY_CTRL_F4||key==KEY_CTRL_F5){
                    break;
                }

                //input for first DNA strand
                if(key==KEY_CHAR_1){
                    dnaone[pointer-1] = 'T';
                }else if(key==KEY_CHAR_4){
                    dnaone[pointer-1] = 'A';
                }else if(key==KEY_CHAR_3){
                    dnaone[pointer-1] = 'C';
                }else if(key==KEY_CHAR_6){
                    dnaone[pointer-1] = 'G';
                }else if(key==KEY_CTRL_DEL){
                    dnaone[pointer-1] = ' ';
                }

                while(iteration<15){
                    if(dnaone[iteration]=='T'){
                        dnatwo[iteration]='A';
                    }else if(dnaone[iteration]=='A'){
                        dnatwo[iteration]='T';
                    }else if(dnaone[iteration]=='G'){
                        dnatwo[iteration]='C';
                    }else if(dnaone[iteration]=='C'){
                        dnatwo[iteration]='G';
                    }else if(dnaone[iteration]==' '){
                        dnatwo[iteration]=' ';
                    }
                    iteration = iteration + 1;
                }
                iteration = 0;

                //if strand changed pointer + 1
                if(key==KEY_CHAR_1||key==KEY_CHAR_3||key==KEY_CHAR_4||key==KEY_CHAR_6){
                    pointer = pointer + 1;
                }

                //move pointer with arrowkeys
                if(key==KEY_CTRL_RIGHT){
                    pointer = pointer + 1;
                }else if(key==KEY_CTRL_LEFT){
                    pointer = pointer - 1;
                }

                //dont move pointer out of range
                if(pointer < 1){
                    pointer = 15;
                }else if(pointer > 15){
                    pointer = 1;
                }
                
                RenderPointer(12, 11, pointer-1, 1);

                //display strands
                RenderStrand(12,2,1,5, dnaone,1);
                RenderStrand(12,20,-1,3, dnatwo,1);

                RenderPointer(12, 11, pointer-1, 1);
            }
        }


        if(key==KEY_CTRL_F2){
            Bdisp_AllClr_DDVRAM();
            //initialise
            RenderStrand(12,2,1,5, dnaone,1);
            RenderStrand(12,20,-1,3, dnatwo,1);
            RenderStrand(12,22,1,5, mrna,1);
            RenderStrand(12,29,1,5, trna,0);
            RendertRNAS(19,38, mrna);
            Render_Buttons();

            while(1){
                GetKey(&key);
                //clear last pointer
                RenderPointer(12, 11, pointer-1, 0);
                Render_Buttons();

                if(key==KEY_CTRL_F2||key==KEY_CTRL_F3||key==KEY_CTRL_F4||key==KEY_CTRL_F5){
                    break;
                }
                
                //input for first DNA strand
                if(key==KEY_CHAR_1){
                    dnaone[pointer-1] = 'T';
                }else if(key==KEY_CHAR_4){
                    dnaone[pointer-1] = 'A';
                }else if(key==KEY_CHAR_3){
                    dnaone[pointer-1] = 'C';
                }else if(key==KEY_CHAR_6){
                    dnaone[pointer-1] = 'G';
                }else if(key==KEY_CTRL_DEL){
                    dnaone[pointer-1] = ' ';
                }

                while(iteration<15){
                    if(dnaone[iteration]=='T'){
                        dnatwo[iteration]='A';
                    }else if(dnaone[iteration]=='A'){
                        dnatwo[iteration]='T';
                    }else if(dnaone[iteration]=='G'){
                        dnatwo[iteration]='C';
                    }else if(dnaone[iteration]=='C'){
                        dnatwo[iteration]='G';
                    }else if(dnaone[iteration]==' '){
                        dnatwo[iteration]=' ';
                    }

                    //copy dnaone to mrna
                    if(dnaone[iteration] != 'T'){
                        mrna[iteration] = dnaone[iteration];
                    }else if(dnaone[iteration]=='T'){
                        mrna[iteration] = 'U';
                    }

                    if(dnatwo[iteration] != 'T'){
                        trna[iteration] = dnatwo[iteration];
                    }else if(dnatwo[iteration]=='T'){
                        trna[iteration] = 'U';
                    }
                    iteration = iteration + 1;
                }
                iteration = 0;

                //if strand changed pointer + 1
                if(key==KEY_CHAR_1||key==KEY_CHAR_3||key==KEY_CHAR_4||key==KEY_CHAR_6){
                    pointer = pointer + 1;
                }

                //move pointer with arrowkeys
                if(key==KEY_CTRL_RIGHT){
                    pointer = pointer + 1;
                }else if(key==KEY_CTRL_LEFT){
                    pointer = pointer - 1;
                }

                //dont move pointer out of range
                if(pointer < 1){
                    pointer = 15;
                }else if(pointer > 15){
                    pointer = 1;
                }
                
                RenderPointer(12, 11, pointer-1, 1);

                //display strands
                RenderStrand(12,2,1,5, dnaone,1);
                RenderStrand(12,20,-1,3, dnatwo,1);
                RenderStrand(12,22,1,5, mrna,1);
                RenderStrand(12,29,1,5, trna,0);

                RenderPointer(12, 11, pointer-1, 1);

                //displa tRNA
                RendertRNAS(19,38,mrna);
            }
        }

        if(key==KEY_CTRL_F4){
            //initialise
            int pointer = 1;
            Bdisp_AllClr_DDVRAM();
            Render_Buttons();
            RenderStrand(12,2,1,5, mrna,1);
            RenderStrand(12,10,1,5, trna,0);
            RendertRNAS(19,19,mrna);

            while(1){
                GetKey(&key);
                RenderPointer(12, 11, pointer-1, 0);
                Render_Buttons();

                if(key==KEY_CTRL_F2||key==KEY_CTRL_F3||key==KEY_CTRL_F4||key==KEY_CTRL_F5){
                    break;
                }

                if(key==KEY_CHAR_1){
                    mrna[pointer-1] = 'U';
                }else if(key==KEY_CHAR_4){
                    mrna[pointer-1] = 'A';
                }else if(key==KEY_CHAR_3){
                    mrna[pointer-1] = 'C';
                }else if(key==KEY_CHAR_6){
                    mrna[pointer-1] = 'G';
                }else if(key==KEY_CTRL_DEL){
                    mrna[pointer-1] = ' ';
                }

                while(iteration<15){
                    if(mrna[iteration]=='U'){
                        trna[iteration]='A';
                    }else if(mrna[iteration]=='A'){
                        trna[iteration]='U';
                    }else if(mrna[iteration]=='G'){
                        trna[iteration]='C';
                    }else if(mrna[iteration]=='C'){
                        trna[iteration]='G';
                    }else if(mrna[iteration]==' '){
                        trna[iteration]=' ';
                    }
                iteration = iteration + 1;
                }  
                iteration = 0;

                //if strand changed pointer + 1
                if(key==KEY_CHAR_1||key==KEY_CHAR_3||key==KEY_CHAR_4||key==KEY_CHAR_6){
                    pointer = pointer + 1;
                }

                //move pointer with arrowkeys
                if(key==KEY_CTRL_RIGHT){
                    pointer = pointer + 1;
                }else if(key==KEY_CTRL_LEFT){
                    pointer = pointer - 1;
                }

                //dont move pointer out of range
                if(pointer < 1){
                    pointer = 15;
                }else if(pointer > 15){
                    pointer = 1;
                }
        
                RenderPointer(12, 11, pointer-1, 1);

                RenderStrand(12,2,1,5, mrna,1);
                RenderStrand(12,10,1,5, trna,0);

                //displa tRNA
                RendertRNAS(19,19,mrna);
            }
        }

    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

