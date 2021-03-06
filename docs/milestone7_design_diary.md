# Design Diary

MILESTONE #7

For this milestone my biggest challenge was trying to figure out how to get the input from the user (and by extension, the keyboard). This was mainly a problem because my code is a mess - yes, I will admit it. I spent a lot of time during this milestone scrolling up and down because I couldn't find where a variable was saved or where the keyboard prompts were and wow, yeah. Now I just keep thinking of how I'd like to re-do the entire code from scratch (while still using the code I created because I know it works) and from there organize the program in a way that actually makes sense. I had tried to do it earlier this week, but in the process of trying to organize it I started breaking things left and right and I ultimately decided that clean up was going to have to wait until there wasn't a looming deadline. That way I can take the time to figure out why the things that are breaking keep doing so to prevent it from happening again.  

Regardless, my second hurdle was one that tied back into my first one. Nearly all of my user input is saved as vector<char> for the sake of pushing it into a 2D vector for the ultimate goal of saving to a file. This led to a few issues when I was trying to count word frequency/save the text on the screen as a binary file, but it wasn't until I needed to sort whole words that I started having real problems. Yet because my code was a bit scattered, I spent a lot of time trying to remember where I had the keyboard input and why it was in certain locations so that way I could piggyback onto the user input for the sake of sorting it upon request...

And so on. 

Despite all this, I did eventually manage to get the sorting algorithms to work and in a way that users would want to use it, which is a wonderful feeling. Yeah, it feels like my program is simply a bunch of functions glued together that'll fall apart the minute I add one too many things, BUT it works. For now. Which is all I ask.

I'm really looking forward to re-doing this project later on though considering I have a end-goal in mind which means I can think more long-term and plan/design/program with that in mind rather than one step at a time. Not to say that the step by step process didn't work, just that while I was thinking of short-term goals I didn't really take the time to care about the overall design/programmer friendliness of the code because if it works, it works. So I think it'll be fun to go back and redesign what I already have and see where it turns up. 

Edit: https://raw.githubusercontent.com/amt954/CS211-TextEditor/master/docs/ms7-demo.gif
