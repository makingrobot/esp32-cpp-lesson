#ifndef _JPEG_DECODER_CONFIG_H
#define _JPEG_DECODER_CONFIG_H

#define CONFIG_JD_USE_ROM       1   //"Use TinyJPG Decoder from ROM" 
        //depends on ESP_ROM_HAS_JPEG_DECODE
    
#define CONFIG_JD_SZBUF         512  // "Size of stream input buffer"

#define CONFIG_JD_FORMAT        0   //"Support RGB565 and RGB888 output (16-bit/pix and 24-bit/pix)"

#define CONFIG_JD_USE_SCALE     1   // "Enable descaling"
    // depends on !JD_USE_ROM
    
#define CONFIG_JD_TBLCLIP       1   // "Use table conversion for saturation arithmetic"
    //depends on !JD_USE_ROM
    
#define CONFIG_JD_FASTDECODE    1   // "+ 32-bit barrel shifter. Suitable for 32-bit MCUs"

#define CONFIG_JD_DEFAULT_HUFFMAN   0  // "Support images without Huffman table"
    //depends on !JD_USE_ROM

#endif
       