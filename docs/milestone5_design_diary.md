# Design Diary

MILESTONE #5

The assignment didn't specifically say it needed a design diary, but I figured why not. Might as well record my thoughts on this milestone for both things implemented as well as things yet to come. For this milestone I found myself with a number of obstacles - the first of which was time. I know that we were given three weeks to work on this assignment and I'm absolutely not complaining about that - but between midterms, homework, school work and power outages I ended up not having as much time as I hoped to work on this. 

Yes, I'm aware the power outage lasted a day for some people, but for me it meant I couldn't do anything Sat or Wed because no one knew when the power would go out (and I'd prefer not to lose my work) and Mon my fridge nearly died from the constant outages so I ended up spending the day DIY-ing repairs. 

That aside, what I'm trying to say is I genuinely worked on this milestone as much as I could and as much as I'm proud of how much I got done, I'm sorry I couldn't commit more often to github.

The second obstacle I faced was that it took a lot of time and effort to figure out how Tries work.  The addWord function wasn't too difficult to figure out after I got help with it, but trying to figure out how to travese a Trie node was a bit more complicated. I understand how to traverse trees because you just specify left or right subtree and go from there, but for a Trie it there wasn't left or right, it just moves down the subtree with recursion and it's no longer straightforward. Thankfully, after three different people explained it (multiple times) and walked me through the process I now have a better understanding of how it works.

In any case, for this milestone I manage to accomplish creating an addWord and a search function for the Trie. In addition to that, I created a function called callTrie which creates a subwindow (called autocomplete) when the user inputs the command to use auto-complete. In that window the list of words found by the search function are printed and, in time, the user will be able to input a number to choose which word in that list will go to the main screen.

For example, if the user types "de" then hits CTRL N, a list of words starting with "de" show up and each one is numbered, like so:

1 - default
2 - decoy
3 - delete

etc. I haven't implemented the word selection feature yet, but the user would choose the number associated with the word they want (or simply exit the window), the window (autocomplete) would close and the word would auto-fill onto the subwindow used for text input (sub_window). 

I have a vague idea how to do this, but I'll definitely have to play around with the code further in order to know for sure. My thought is that the user would input a number, it would check that number against the index value of the for loop used to print out the list and then print the word at that index location to the right window before exiting out of the autocomplete window. 

Another, more minor, thing I did during this milestone was clean up my keyboard_input function. The shortcuts used for saving, opening files, exiting, etc. were all over the place and it was getting difficult to remember what shortcut did what. So for this I changed everything to CTRL shortcuts and included a keyboard shortcut guide at the top of the screen.

The things that still need work that I can do if I complete Milestone #6 early:

-get backspace to work
-get arrow keys working
-fix the resize feature so it stops breaking everything
