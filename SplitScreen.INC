'SPLIT SCREEN library
'JirSoft 2021

CONST VERSION.SPLIT = "0.02"

'can be used for spltting the screen into areas, where can be either printed-out text or loaded image
'area is defined in control string, so you can define many areas...
'overlapping of areas is not checked
'SUBs are used because every needs CONTROL STRING as pasrameter and it's also updated
  
'CONTROL STRING DESCRIPTION (cs$, 22 bytes)
'  dx% = STR2BIN(UINT16, LEFT$(cs$, 2))     x-coordinate of Left upper corner of the screen part
'  dy% = STR2BIN(UINT16, MID$(cs$, 3, 2))   y-coordinate of Left upper corner of the screen part
' 
'  w% = STR2BIN(UINT16, MID$(cs$, 5, 2))      width of the screen part
'  h% = STR2BIN(UINT16, MID$(cs$, 7, 2))      height of the screen part
' 
'  x% = STR2BIN(UINT16, MID$(cs$, 9, 2))      x-coordinate of the cursor (left upper)
'  y% = STR2BIN(UINT16, MID$(cs$, 11, 2))   y-coordinate of the cursor (left upper)
' 
'  t% = STR2BIN(UINT8, MID$(cs$, 13, 1))      TAB width in pixels
' 
'  f% = STR2BIN(UINT8, MID$(cs$, 14, 1))      FONT
' 
'  fc% = STR2BIN(UINT32, MID$(cs$, 15, 4))    foreground color
'  bc% = STR2BIN(UINT32, MID$(cs$, 19, 4))    background color

'SUB init.SPLIT(cs$, dx%, dy%, w%, h%)
  'creates new screen part X/Y/WIDTH/HEIGHT and sets control string cs$
 
'SUB setStyle.SPLIT(cs$, t%, f%, fc%, bc%)
  'sets TAB, FONT, FOREGROUND and BACKGROUND
  'for not changing default, set the value to -1
 
'SIB cls.SPLIT(cs$)
  'clears the screen, sets X/Y to 0
 
'SUB print.SPLIT(cs$, txt$)
  'main FUNCTION for string output, parameteres are control string and txt$ to output
  'CHR$(8) is TAB character, used to go to the next TAB position
  'CHR$(10) is line feed character, uset to go to begin of the next line (screen can be scrolled up)
  'other ASCII codes bellow CHR$(32) are ignored
 
'FUNCTION loadImage.SPLIT(cs$, fn$, iw%, ih%)
  'load image into full part of the screen
  'when we know image width/height (iw%/ih%) is used (need to be smaller than MM.XRES/MM.YRES)
  'returns TRUE (=1) when OK
 
SUB init.SPLIT(cs$, dx%, dy%, w%, h%)
  'creates new screen part X/Y/WIDTH/HEIGHT and sets control string cs$
 
  cs$ = BIN2STR$(UINT16, dx%) + BIN2STR$(UINT16, dy%)  'x/y position of the LEFT upper screen corner
  CAT cs$, BIN2STR$(UINT16, w%) + BIN2STR$(UINT16, h%) 'width/height of the screen
  CAT cs$, BIN2STR$(UINT16, 0) + BIN2STR$(UINT16, 0)   'x/y position of the cursor relative to dx%/dy%
  CAT cs$, BIN2STR$(UINT8, 20)                         'default TAB in pixels
  CAT cs$, BIN2STR$(UINT8, 1)                          'default FONT
  CAT cs$, BIN2STR$(UINT32, RGB(WHITE)) + BIN2STR$(UINT32, RGB(NOTBLACK))  'default FOREGROUND and BACKGROUND colors
END SUB
 
 
SUB setStyle.SPLIT(cs$, t%, f%, fc%, bc%)
  'sets TAB, FONT, FOREGROUND and BACKGROUND
  'for not changing default, set the value to -1
 
  IF t%>0 THEN 'TAB in pixels
    MID$(cs$, 13, 1) = BIN2STR$(UINT8, t% AND 255)
  ENDIF
 
  IF f%>0 AND f%<9 THEN  'FONT
    MID$(cs$, 14, 1) = BIN2STR$(UINT8, f%)
  ENDIF
 
  IF fc%>=0 THEN  'FOREGROUND color
    MID$(cs$, 15, 4) = BIN2STR$(UINT32, fc% AND &hFFFFFF)
  ENDIF
 
  IF bc%>=0 THEN  'BACKGROUND color
    MID$(cs$, 19, 4) = BIN2STR$(UINT32, bc% AND &hFFFFFF))
  ENDIF
END SUB
 
SUB cls.SPLIT(cs$)
  'clears the screen, sets X/Y to 0
 
  MID$(cs$, 9, 4) = BIN2STR$(UINT16, 0) + BIN2STR$(UINT16, 0)
  BOX STR2BIN(UINT16, LEFT$(cs$, 2)), STR2BIN(UINT16, MID$(cs$, 3, 2)), STR2BIN(UINT16, MID$(cs$, 5, 2)), STR2BIN(UINT16, MID$(cs$, 7, 2)), 0, STR2BIN(UINT32, MID$(cs$, 19, 4)), STR2BIN(UINT32, MID$(cs$, 19, 4))
END SUB
  
SUB print.SPLIT(cs$, txt$)
  'main SUB for string output, parameteres are control string and txt$ to output
  'CHR$(8) is TAB character, used to go to the next TAB position
  'CHR$(10) is line feed character, uset to go to begin of the next line (screen can be scrolled up)
  'other ASCII codes bellow CHR$(32) are ignored
 
  LOCAL INTEGER dx = STR2BIN(UINT16, LEFT$(cs$, 2))
  LOCAL INTEGER dy = STR2BIN(UINT16, MID$(cs$, 3, 2))
  LOCAL INTEGER w = STR2BIN(UINT16, MID$(cs$, 5, 2))
  LOCAL INTEGER h = STR2BIN(UINT16, MID$(cs$, 7, 2))
  LOCAL INTEGER x = STR2BIN(UINT16, MID$(cs$, 9, 2))
  LOCAL INTEGER y = STR2BIN(UINT16, MID$(cs$, 11, 2))
  LOCAL INTEGER t = STR2BIN(UINT8, MID$(cs$, 13, 1))
  LOCAL INTEGER f = STR2BIN(UINT8, MID$(cs$, 14, 1))
  LOCAL INTEGER fc = STR2BIN(UINT32, MID$(cs$, 15, 4))
  LOCAL INTEGER bc = STR2BIN(UINT32, MID$(cs$, 19, 4))
  FONT f, 1
  LOCAL INTEGER fh = MM.INFO(FONTHEIGHT)
  LOCAL INTEGER fw = MM.INFO(FONTWIDTH)
  LOCAL INTEGER i
  LOCAL STRING ch
  
  FOR i = 1 TO LEN(txt$)
    ch = MID$(txt$, i, 1)
    IF ch<" " THEN
      IF ch=CHR$(10) THEN 'line feed
        x = 0
        IF (y+fh)<h THEN
          INC y, fh
        ELSE
          'scrolling, repeated because of saving SUB/FUNCTION slot
          INC y, -fh
          BLIT dx, dy+fh, dx, dy, w, h-fh
          BOX dx, dy+y, w, h-y, 0, bc, bc

        ENDIF
       
      elseIF ch=CHR$(8) THEN 'TAB
        nx = t*INT(x\t)
        IF nx<=x THEN INC nx, t
        IF nx+fw<w THEN
          x = nx
        else
          x = 0
          IF (y+fh)<h THEN
            INC y, fh
          ELSE
            'scrolling, repeated because of saving SUB/FUNCTION slot
            INC y, -fh
            BLIT dx, dy+fh, dx, dy, w, h-fh
            BOX dx, dy+y, w, h-y, 0, bc, bc

          ENDIF
        ENDIF
      ENDIF
     
    ELSE
      'normal char to output
      IF (x+fw)>=w THEN 'char can't be placed into current line
        x = 0
        IF (y+fh)<h THEN
          INC y, fh
        ELSE
          'scrolling, repeated because of saving SUB/FUNCTION slot
          INC y, -fh
          BLIT dx, dy+fh, dx, dy, w, h-fh
          BOX dx, dy+y, w, h-y, 0, bc, bc
        ENDIF
      ENDIF
      TEXT dx+x, dy+y, ch, "LT", f, 1, fc, bc
      INC x, fw
    ENDIF
  NEXT i
 
  MID$(cs$, 9, 4) = BIN2STR$(UINT16, x) + BIN2STR$(UINT16, y)
END SUB
 
FUNCTION loadImage.SPLIT(cs$, fn$, iw%, ih%) AS INTEGER
  'load image into full part of the screen
  'when we know image width/height (iw%/ih%) is used (need to be smaller than MM.XRES/MM.YRES)
  'returns TRUE (=1) when OK
 
  LOCAL STRING ext = UCASE$(RIGHT$(fn$, 4))
  LOCAL INTEGER dx = STR2BIN(UINT16, LEFT$(cs$, 2))
  LOCAL INTEGER dy = STR2BIN(UINT16, MID$(cs$, 3, 2))
  LOCAL INTEGER w = STR2BIN(UINT16, MID$(cs$, 5, 2))
  LOCAL INTEGER h = STR2BIN(UINT16, MID$(cs$, 7, 2))
 
  loadImage.SPLIT = 0 'ERROR
  PAGE WRITE 1
 
  SELECT CASE ext
    CASE ".GIF"
      ON ERROR SKIP
      LOAD GIF fn$
      IF NOT MM.ERRNO THEN loadImage.SPLIT = 1
         
    CASE ".BMP"
      ON ERROR SKIP
      LOAD BMP fn$
      IF NOT MM.ERRNO THEN loadImage.SPLIT = 1
 
    CASE ".JPG"
      ON ERROR SKIP
      LOAD JPG fn$
      IF NOT MM.ERRNO THEN loadImage.SPLIT = 1
 
    CASE ".PNG"
      ON ERROR SKIP
      LOAD PNG fn$
      IF NOT MM.ERRNO THEN loadImage.SPLIT = 1
 
  END SELECT
 
  PAGE WRITE 0
  IF loadImage.SPLIT THEN
    IF iw%>0 AND ih%>0 THEN 'image width and height is known and used
      IMAGE RESIZE 0, 0, iw%, ih%, dx, dy, w, h, 1
     
    ELSE 'resize whole page to selected area
      IMAGE RESIZE 0, 0, MM.HRES, MM.VRES, dx, dy, w, h, 1
     
    ENDIF
  ENDIF
END FUNCTION
