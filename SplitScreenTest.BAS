'demo for split screen library
#INCLUDE "SplitScreen.INC"

'dim array of control strings
DIM STRING scr(3) LENGTH 30, lf = CHR$(10), tb = CHR$(9), in$

'calculate screen areas
DIM INTEGER x1 = MM.HRES*0.75, y1 = MM.VRES*0.40, y2 = MM.VRES*0.80
'all areas will have TAB set for 2 characters wide
'we clear the screen after init, so background can be seen...

'screen 0, biggest area (75% width, 80% of height), biggest font
init.SPLIT(scr(0), 0, 0, x1, y2)
setStyle.SPLIT(scr(0), 32, 3, RGB(NOTBLACK), RGB(YELLOW))
cls.SPLIT(scr(0))
print.SPLIT(scr(0), lf+lf) 'line feed
print.SPLIT(scr(0), tb+"Enter word 'start'")

'screen 1, right upper part (25% width, 40% height), smallest font
init.SPLIT(scr(1), x1, 0, MM.HRES-x1, y1)
setStyle.SPLIT(scr(1), 12, 7, RGB(CYAN), RGB(GRAY))
cls.SPLIT(scr(1))
print.SPLIT(scr(1), lf) 'line feed
print.SPLIT(scr(1), tb+"Then either wait 10s for change")

'screen 2, right middle part (25% width, 40% height), standard font
init.SPLIT(scr(2), x1, y1, MM.HRES-x1, y2-y1)
setStyle.SPLIT(scr(2), 16, 1, RGB(GRAY), RGB(CYAN))
cls.SPLIT(scr(2))
print.SPLIT(scr(2), lf) 'line feed
print.SPLIT(scr(2), tb+"or press key again")


'screen 3, bottom (full width, 25% height), big font
init.SPLIT(scr(3), 0, y2, MM.HRES, MM.VRES-y2)
setStyle.SPLIT(scr(3), 20, 4, RGB(NOTBLACK), RGB(WHITE))
cls.SPLIT(scr(3))

DO
  print.SPLIT(scr(3), tb+">")
  setStyle.SPLIT(scr(3), -1, -1, RGB(RED), -1)
  in$ = input.SPLIT(scr(3))
  print.SPLIT(scr(3), lf)
  setStyle.SPLIT(scr(3), -1, -1, RGB(NOTBLACK), RGB(WHITE))
  IF in$<>"start" THEN
    print.SPLIT(scr(0), lf+tb+"You entered '"+in$)
    print.SPLIT(scr(0), "', enter word 'start'")
  ENDIF
LOOP UNTIL in$="start" 

'let's start
DO
  'all parts with text
  TIMER = 0
  DO WHILE TIMER<10000 AND INKEY$=""
    print.SPLIT(scr(0), "This is SCREEN 0,")
    print.SPLIT(scr(1), "This is SCREEN 1,")
    print.SPLIT(scr(2), "This is SCREEN 2,")
    print.SPLIT(scr(3), "This is SCREEN 3,")
  LOOP
  DO WHILE INKEY$<>""
  LOOP
  DO WHILE INKEY$<>""
  LOOP

  'main area with image
  IF loadImage.SPLIT(scr(0), "midear(320x200).BMP", 320, 200) THEN
    TIMER = 0
    DO WHILE TIMER<10000 AND INKEY$=""
      print.SPLIT(scr(1), "This is SCREEN 1,")
      print.SPLIT(scr(2), "This is SCREEN 2,")
      print.SPLIT(scr(3), "This is SCREEN 3,")
    LOOP
    DO WHILE INKEY$<>""
    LOOP
    DO WHILE INKEY$<>""
    LOOP
  ENDIF

  'image top right
  IF loadImage.SPLIT(scr(1), "Gorilla(320x200).BMP", 320, 200) THEN
    TIMER = 0
    DO WHILE TIMER<10000 AND INKEY$=""
      print.SPLIT(scr(0), "This is SCREEN 0,")
      print.SPLIT(scr(2), "This is SCREEN 2,")
      print.SPLIT(scr(3), "This is SCREEN 3,")
    LOOP
    DO WHILE INKEY$<>""
    LOOP
    DO WHILE INKEY$<>""
    LOOP
  ENDIF

  'image middle right
  IF loadImage.SPLIT(scr(2), "Mercenary(256x192).BMP", 192, 256) THEN
    TIMER = 0
    DO WHILE TIMER<10000 AND INKEY$=""
      print.SPLIT(scr(0), "This is SCREEN 0,")
      print.SPLIT(scr(1), "This is SCREEN 1,")
      print.SPLIT(scr(3), "This is SCREEN 3,")
    LOOP
    DO WHILE INKEY$<>""
    LOOP
    DO WHILE INKEY$<>""
    LOOP
  ENDIF
LOOP
