# Design Diary
Design Diary – 
Milestone 2

So, to put it simply, this milestone has not gone smoothly at all. It’s understandable considering the features being implemented this time around are more complicated than before, but needless to say, it’s been a series of ups and downs. The things that are working are text input to screen and … I think that’s about it. The things that are PARTIALLY working are word wrap and opening a file to the screen – the reason why they’re partially working is because the word wrap works, but if it reaches the limit point mid word then that word gets cut in two and it’s hard to tell if someone is say f inal or they were typing final and it got cut off. The file open feature is partially working because it opens a file (if ESC is pressed), but it can’t handle certain characters as a string and trying to convert the string to wstring has been a nightmare and a half. 

Finally, the features that aren’t working at all are scrolling and opening a file from the command line. I’ve spent hours alternating between trying to get the two features to work so I wouldn’t lose my patience with either, but unfortunately did not get far. The cmd console acts like pdcurses isn’t installed (so that will take some looking into to figure out why it’s broken) and the scroll feature lets me type offscreen vertically, but doesn’t move the screen itself so I can see what’s being written. 

I’m not really sure what I could have done differently here to make this milestone less frustrating mainly because it was entirely touch and go from the minute it was assigned. I still enjoyed the challenge (and still plan to try and figure out what the heck is going on) but I can’t deny wanting to kick my computer out the window a few times over. 

Because the next milestone is fairly straightforward, I’ll most likely end up coming back to these broken features so I can troubleshoot further (but only after the next milestone is done, of course.) I’m hoping concentrating on something else will give me enough space from what I’m doing now to clear my head so that way I can come back with fresh eyes and see where things got derailed. 

My gif demo of the TextEditor is linked below (and is also saved in the projects folder)

C:\Users\April\Desktop\School\2019\Fall 2019\2019-fall-cs211\projects\TextEditor\docs\demo2.gif

