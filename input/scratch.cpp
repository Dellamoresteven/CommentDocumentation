// #frontpage test |
// @author Steven Dellamore |
// @date Feb 28th 2020 |
// @version 1.0.0 |
// @company TeamTris |
// @title StartScreen Class Documentation |
// @location West Lafayette, IN |
// @email dellamoresteven@gmail.com |
// @office CS407 |


// #class StartScreen |
// @author Steven Dellamore |
// @desc Startscreen will build the startscreen and
// create all the buttons needed for the user to 
// get into a game with their friends. The mouseClicks
// and the keyboard imports all all forwarded to this class
// when gamestate == 0 |
// @language javascript | 
class StartScreen {

    // #function StartScreen::constructor |
    // @author Steven Dellamore |
	// @desc The constructor gets called when making a 
	// startscreen object. It will init all the values 
	// and set up the socket listener for the server to 
	// send things too. Here are the init values of the class
	// variables: 
	// @link{StartScreenContorVars} 
	// These varibles will be updated throughout the life of 
	// start screen. @inline{this.TokenBoxText} will |
    // @header constructor() | 
	// @param x : x cord |
	// @param y : y cord |
	// @returns StartScreen : An object of said class | 
	constructor() {
		if (startscreen_constructor) console.log("Creating StartScreen Object");
		/* 							X, Y 				 , W  			  , H 				 , gamestate, default color	*/
		buttonList.push(new Buttons(0, windowHeight / 2.8, windowWidth / 5, windowHeight / 10, 0, "blue"));
		buttonList[buttonList.length - 1].text = "Create Game"; // Text to put in the button
		buttonList[buttonList.length - 1].hoverColor = "yellow"; // What color to make the button on mouse hover
		buttonList[buttonList.length - 1].id = "createGame"; // ID of the button
		buttonList.push(new Buttons(0, windowHeight / 4, windowWidth / 5, windowHeight / 10, 0, "red"));
		buttonList[buttonList.length - 1].text = "Join game"; // Text to put in the button
		buttonList[buttonList.length - 1].hoverColor = "yellow"; // What color to make the button on mouse hover
		buttonList[buttonList.length - 1].id = "joinGame"; // ID of the button

		// #code StartScreenContorVars javascript
		this.TokenBoxText = ""; 
		this.usernameBoxStroke = false; 
		this.usernameText = "username"; 
		this.usernameTextTouched = false; 
		this.gameStateStartScreen = 0;  
		this.titleAnimation = [300, 500, 400, 700];
		// |
	}
