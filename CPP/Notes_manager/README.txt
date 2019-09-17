Project: Notes manager
Creator: Emil Eyvazov
Date: 09/06/2019

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
The program consists of categories and notes. There could be any number of categories and any number of notes.
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
-----------------
Categories list:|
-----------------
After running the makefile a window opens.
On the left side of the window there is a rectangle with the text in it: "Category".
Below it You can see another rectangle that contains all categories. If mouse points to it, the "ADD", "NUMBER", "UP", and "DOWN" buttons occur.
1) The "ADD" sign adds new category with "NewCategory" header. If the name of the newly created category isn't changed, it is not possible to add a new category.
If You try to do so, the error message will occur on the top of the window: "Message: "New Category" already presents. Change the header of it to add any new
category".
2) The "NUMBER" is in the format: <offset/size>, where offset is the index of the first category shown on the scree and the size is the size of all categories.
3) The "UP" and "DOWN" buttons are to traverse through the categories: that is possible to show only 12 categories at once on the screen. By pushing "UP" button, the
the offset decreases: the previous 12 categories are shown. By pushing "DOWN" the offset increases: the next 12 categories are shown.
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
---------
Category|
---------
If any of the category is pressed, the header and the notes of that particular category are shown on the screen.
The header could be changed by clicking on it -- the input is going to be taken till the next mouse click. The header size is limited to 30 characters. There allowed
uppercase/lowercase letters, digits and
uderscore as the header of the category, if such the header is changed and mouse is clicked anywhere, the program is going to check if the header is empty or such a
header already exists. In the mentioned previously two cases the error message: "Such category already exists or it is empty" is going to be shown, and the header is
left as it was before changing it.
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
-----
Note|
-----
The rectangle with all the notes contains notes(from the most recent to the oldest) themselves(dates of the notes) and "ADD", "DELETE", "NUMBER", "UP", and "DOWN"
buttons. The purposes of these notes are the same as before, but with notes(previously these buttons operated with categories). "DELETE" button deletes particular
category with all the notes in it.
If any of the notes is pressed, the body of that note and the "DELETE" sign is shown on the newly created rectangle. "DELETE" actually deletes a note.
Initially note is created with empty body. To change a note body it is only needed to click on its body and add text.
Supported characters: uppercase/lowercase letters, digits, and signs: <.><,></><?><'><"><:><;><!><@><#><$><%><^><&><*><(><)><_><+><-><=>.
After each addition of character the time of the note is updated. There is a limit for notes size -- no more than 559 characters. The input of the note is done till
the next mouse click.
The '.md' format of the notes could be found in the directory with this project in "examples" folder.

Good luck!
