void kmain(void)
{
    const char *str = "Never gonna give you up\
                       Never gonna let you down!\
                       Never gonna run around and desert you";
    char *vidptr = (char*)0xb8000;          //video memory starts from this memory address
    unsigned int i = 0;
    unsigned int j = 0;

    //this loop clears the screen
    while (j < 80 * 50 * 2) {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;               //0x07 is the colour address for gray, which is the font color of the text in the loader
        j += 2;
    }

    j = 0;
    //this loop writes the string
    while (str[j] !=  '\0') {
        vidptr[i] = str[j];
        vidptr[i + 1] = 0x07;
        ++j;
        i += 2;
    }
    return;
}


