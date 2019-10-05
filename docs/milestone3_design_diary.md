# Design Diary

MILESTONE #3

This milestone was just as much of a roller-coaster ride as milestone 2, but I seel like I'm slowly getting the hang of figuring out PDcurses. I'm not 100% proficient in the language, but I'm finding it easier to figure out how to manipulate the library to suit my needs compared to how it was when I first started using it. 

I am still having a great amount of trouble wrapping my head around how to get the screen to scroll down. I've tried multiple methods with varying degrees of scuess. My first attempt was mostly just "let's throw this bit of code in and see if it works" but I didn't really understand how to use the code so it understandably did not work at all. Then, I tried using a variable called "top" to keep track of the top of the screen and used the dimensions of the sub_window's height to try and keep track of the text that's inside it, but I'm not following what I'm supposed to do from there. I converted all the text that is inputted from the user to the screen from a regular 1d vector to a 2d vector that will allow me to not only save the text if I ever manage to scroll, but also help me keep track of the rows. I also know that I need to refresh the screen after I scroll down or up, but I'm still working out how to CODE THAT.

PDcurses isn't talked about alot on the internet and even when it is the documentation is nonexistent so figuring out what works and what doesn't has been tons of fun. I mean that with a mixture of despair, sarcasm and genuine relish (challenges are a lot of fun,, but there comes a time when hittiing up against one brick wall after another only leads to annoyance!) My latest attempt to get scrolling to work has been to use "REQ_SCR_FLINE", which the documentation said will cause the page to scroll down one line if the text exceeds the size of the window. It doesn't work the way I have it, unsurprisingly, so I need to keep searching for how this is used (do I say sub_window = REQ_SCR_FLINE or use it as a function or define it as a parameter somewhere...?).

Other information about my progress so far:

-I originally had file IO and user inputted text use wstring vectors (so dashes and wide characters could be read to the screen) but it made switching to a 2d vector incredibly complicated, so for the moment I'm switching back to regular char and have to decide where to go from there. So far it seems to be working fine :)

-The "Save File" formatting really needs work. Writing a file to another file works fine, but if I try to save any user inputted text it strips out all line formatting and smushes everything together. 

-Currently trying to figure out how to get backspace working