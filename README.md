# Popup Adventure
There is nothing of value here


## Text Adventure Through Windows Popup Message Boxes
Preferably calling the popups through powershell, but I guess I could make it another way so you can have terrible popups cross platform. If we're doing cross platform, Qt is probably the right answer.

Correct answer: We're using QT to generate the popups, based on the narrative structure defined in ```story.json```. The current position in the narrative will eventually be saved in a ```save.json``` file, but we're not there yet.  

## ToDo:
 - Save game functionality
 - Handle starting a new game/continuing an old game properly
 - Fix the hang on exit problem
 - Write the actual story, I guess lolol. Might write it in yarn and then port it to our json.
 - Edit make instructions to actually copy ```story.json``` to the output directory.
 - Figure out how to make the popup box titles have the title text properly
 - Double check the icon choices


## References
1. [Powershell functions](https://learn.microsoft.com/en-us/powershell/scripting/learn/ps101/09-functions?view=powershell-7.3)
2. [QT Save Game Json Example](https://doc.qt.io/qt-6/qtcore-serialization-savegame-example.html)
