# Popup Adventure
There is nothing of value here

We're using QT to generate the popups, based on the narrative structure defined in ```story_template.json```. The current position in the narrative is saved in a ```save.json``` file.  

## Narrative Json File Structure
The story files are json files, and must be placed in the ```Stories``` directory with the program.

The json file contents hav a "title" item which is the game title, and a list of "level" items, which denote each popup. The "name" item for each level is used as a reference for button linking, with certain names being expected to be present. 

### Special Level Names
The list of special level names and the associated functionality is shown below.

 - Title ---- Your story title screen! It can link to as many other things as you want, but you need to link to newGame eventually to get save functionality
 - NewGame ------ Provides the information for starting a new game and what the starting level of the narrative is in the "yes" button. If there is existing save data it will add a no button that links to the current level in the saved data.
 - Help ------ Provides the text that's shown when a user pressed the Help button

The "title" and "body" denote the text shown in the popup. The "icon" field is optional, and will default to no icon if not provided. The icon is a numeric value associated with the underlying enum defined [here](https://doc.qt.io/qt-6/qmessagebox.html#Icon-enum). And in the list below for local reference:

 0. No icon
 1. Information
 2. Warning
 3. Critical
 4. Question

The "choices" item is a list of buttons to display in the textbox, and where they link to. The "goto" item is the name of the level to jump to, and the "type" is which standard button to display. These correspond to the button options [here](https://doc.qt.io/qt-6/qmessagebox.html#StandardButton-enum) and use just the constant name text without the starting "QMessageBox::". The list and any associated special qualities is shown below for local reference:

 - Ok
 - Open
 - Save
 - Cancel
 - Close ----> Used for game save and close. It's present on all popups, and also linked to the escape button.
 - Discard
 - Apply
 - Reset
 - RestoreDefaults
 - Help ----> Always available. Displays information displayed in the level named "Help"
 - SaveAll
 - Yes
 - YesToAll
 - No
 - NoToAll
 - Abort
 - Retry
 - Ignore
 - NoButton

## ToDo:
 - Get Linux and Mac builds working correctly. 
 - Have everything port to a clean folder setup for distribution.
 - We have a test story! Now to make the [Goncharov](https://en.wikipedia.org/wiki/Goncharov_(meme)) story
 - Maybe remove the close button use and just use the top right x instead --> This doesn't work right, if there's no close button, I can't press the x, but if there is, the x counts as another close button. Also I can't get it to let me hide the close button >.>
 - Some sort of visual story builder tool or conversion system from twine/yarn


## References
1. [Powershell functions](https://learn.microsoft.com/en-us/powershell/scripting/learn/ps101/09-functions?view=powershell-7.3)
2. [QT Save Game Json Example](https://doc.qt.io/qt-6/qtcore-serialization-savegame-example.html)
3. [QtNodeEditorBuilder](https://github.com/paceholder/nodeeditor)