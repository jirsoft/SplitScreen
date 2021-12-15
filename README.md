# SplitScreen
Library for screen splitting and printing text into parts for Colour Maximite 2 computer. Included is also file **SplitScreenTest.BAS**, where can be seen simple use of this library.<br><br>
  
*CONTROL STRING DESCRIPTION (cs$, 22 bytes)*<br>
*dx% = STR2BIN(UINT16, LEFT$(cs$, 2))*     x-coordinate of Left upper corner of the screen part<br>
*dy% = STR2BIN(UINT16, MID$(cs$, 3, 2))*   y-coordinate of Left upper corner of the screen part<br>
<br>
*w% = STR2BIN(UINT16, MID$(cs$, 5, 2))*     width of the screen part<br>
*h% = STR2BIN(UINT16, MID$(cs$, 7, 2))*      height of the screen part<br>
<br>
*x% = STR2BIN(UINT16, MID$(cs$, 9, 2))*      x-coordinate of the cursor (left upper)<br>
*y% = STR2BIN(UINT16, MID$(cs$, 11, 2))*   y-coordinate of the cursor (left upper)<br>
<br>
*t% = STR2BIN(UINT8, MID$(cs$, 13, 1))*      TAB width in pixels<br>
<br>
*f% = STR2BIN(UINT8, MID$(cs$, 14, 1))*      FONT<br>
<br>
*fc% = STR2BIN(UINT32, MID$(cs$, 15, 4))*    foreground color<br>
*bc% = STR2BIN(UINT32, MID$(cs$, 19, 4))*    background color<br>
<br>
**SUB init.SPLIT(cs$, dx%, dy%, w%, h%)**<br>
*creates new screen part X/Y/WIDTH/HEIGHT and sets control string cs$*<br>
 <br>
**SUB setStyle.SPLIT(cs$, t%, f%, fc%, bc%)**<br>
*sets TAB, FONT, FOREGROUND and BACKGROUND*<br>
*for not changing default, set the value to -1*<br>
 <br>
**SUB cls.SPLIT(cs$)**<br>
*clears the screen, sets X/Y to 0*<br>
<br>
**SUB print.SPLIT(cs$, txt$)**<br>
*main FUNCTION for string output, parameteres are control string and txt$ to output*<br>
*CHR$(8) is TAB character, used to go to the next TAB position*<br>
*CHR$(10) is line feed character, uset to go to begin of the next line (screen can be scrolled up)*<br>
*other ASCII codes bellow CHR$(32) are ignored*<br>
<br>
**FUNCTION loadImage.SPLIT(cs$, fn$, iw%, ih%)**<br>
*load image into full part of the screen<br>
*when we know image width/height (iw%/ih%) is used (need to be smaller than MM.XRES/MM.YRES)<br>
*returns TRUE (=1) when OK<br>
 <br>
 **FUNCTION input.SPLIT(cs$, allowedChars$, maxLen%) AS STRING**<br>
*allows to input string in any split area, use any charaters from allowedChar$ (or any, if this string is empty)<br>
*you can delete last character with BACKSPACE, finish the input with ENTER or RETURN (this will be not part of the returned string)<br>
*with maxLen% you can limit length of the input, if it's <=0 or >255 then the limit will be 255 characters<br>
