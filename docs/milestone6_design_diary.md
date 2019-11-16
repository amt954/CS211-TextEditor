# Design Diary

MILESTONE #6

This was a pretty fun milestone to complete. I got a bit stuck at trying to figure out how to assign binary values (unique binary values that increment) to a character, but I was lucky enough that you went over it in class. Once I got that out of the way, my next big challenge (besides trying to get all keyboard input into a vector, more on that later) was trying to match the keyboard input to a key in an unordered map so I could then get the binary value associated with it and output it to a brand new binary file. 

A few things I still need to deal with are a few bugs that happen whenever a file is imported and then saved. Unfortunately the binary file breaks when this is done and I've yet to narrow down exactly what could be causing this issue. The reason for my puzzlement is because I've run the debugger multiple times to keep track of the progression of a file being opened, then read, then pushed to a single vector before eventually being sent to the char to functions that convert to binary and then save. Yet despite all this everthing works as expected, all the chars are being pushed back without issue, the conversion happens without problem and then it's saved to an unordered map. 

So, yeah. This is a bug that's going to persist for a while until I can do a some trial and error rounds 

The good news though is that I managed to fix the problem with my invisible file. During a past update the Open File feature broke partially and the text became insibile even though the file would open, the cursor would move and then the file saved without problem. I wasn't able to get back to working on it because I had so many things to do, but I decided to spend some time working on it during this milestone and voilà!

It's not perfect, it can't seem to deal with apostrophes, but other than that it works great!

In any case, I'm not so sure what I'll choose to do for the next milestone. I won't be able to start it just yet because I have an enormous amount of homework and tests looming, but after those are complete I'll get straight to work. Personally I'd like to have some time to go back and fix previous milestone issues or features left incomplete (and maybe go through my code and clean it up.)


Link to demo gif - https://github.com/amt954/CS211-TextEditor/blob/master/docs/ms6-demo.gif

NOTE: For whatever reason, the demo gifs are ridiculously slow (or just freeze mid frame) in github, most likely due to their size. If you click the "download" button you'll see the gif at full speed. 