# CommentDocumentation


## Template
### Frontpage
```
/**
 * #frontpage Cool Front Page |
 * @author My Name |
 * @date Feb 28th 2020 |
 * @version 1.0.0 |
 * @company My Company |
 * @title Title of Doc |
 * @location my Location |
 * @email my email |
 * @office my office |
 */
```
### Classes
```
/**
 * #class myClassTitle |
 * @author my Name |
 * @language javascript | 
 * @desc This is my desc to talk about what this class does |
 */

/**
 * #class myClassTitle |
 * @author my Name |
 * @language javascript | 
 * @desc This is my really long desc
 * that explains how great my class is
 * and what it does. |
 */
```
### Functions
```
/**
 * #function myClassTitle::myFunctionName |
 * @author My name |
 * @desc This is another desc but once again
 * can be one line or multi line. It just
 * depeneds where you put the pipe to 
 * tell
 * it
 * to stop reading. | 
 * @param int num : tells how many numbers there are |
 * @returns int : how many numbers are left | 
 */
```

### inline code
Inside desc and param's you can put @inline{code}. The code will
be assumed to be the same type as the class its in. 

Ex.
```
/**
 * #function StartScreen::constructor |
 * @author Steven Dellamore |
 * @desc The constructor gets called when making a 
 * startscreen object. It will init all the values 
 * and set up the socket listener for the server to 
 * send things too. Here are the init values of the class
 * variables: 
 * @link{StartScreenContorVars} 
 * These varibles will be updated throughout the life of 
 * start screen. @inline{this.TokenBoxText} will init 
 * the token box to nothing, since the user has yet to do anyhting. 
 * the @inline{this.usernameBoxStroke} will be set to false so the program knows if
 * the user as tried to sumbit. @inline{this.titleAnimation = [300, 500, 400, 700];} 
 * is the starting position of the title, and will fall every X frames. |
 * @header constructor() | 
 * @param void : constructor takes no params |
 * @returns StartScreen : An object of start class class | 
 */
```
### Block Code
Block code allows you to create comment varibles and use them anywhere in ur program.

Ex.
```
// #code StartScreenContorVars javascript
this.TokenBoxText = ""; 
this.usernameBoxStroke = false; 
this.usernameText = "username"; 
this.usernameTextTouched = false; 
this.gameStateStartScreen = 0;
this.titleAnimation = [300, 500, 400, 700];
// |
```
// #code tells us its a code block, 
// StartScreenContorVars is the var name 
// javascript is the language

To use this varible you can use the @link{StartScreenContorVars} as seen above in 
inline example.