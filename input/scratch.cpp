// #frontpage test |
// @author Steven Dellamore |
// @date Feb 28th 2020 |
// @version 1.0.0 |
// @company Garmin |
// @title This shows how to use Doc |
// @location West Lafayette, IN |
// @email dellamoresteven@gmail.com |

// #class StartScreen |
// @date Feb 29th 2020 |
// @version 1.0.0 |
// @desc StartScreen will render the first screen that people go to when joining the game. It will contain all the buttons to create, join, and view the highscore screen. |
// @author Steven Dellamore |
class StartScreen {

    // #function StartScreen::constructor |
    // @author Steven Dellamore |
    // @desc This function gets called when making a startscreen object. It will init all the values and set up the socket listener for the server to send things too |
    // @header constructor() | 
    // @param int x : This is the xcord of the params |
    // @param int y : This is the ycord of the params | 
    // @param int z : This is the zcord of the params | 
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

		this.TokenBoxText = ""; // default token

		this.usernameBoxStroke = false; // true: highlight box red. false: go back to normal

		this.usernameText = "username"; // default username
		this.usernameTextTouched = false; // checks to see if the box has been touched by the user yet

		this.gameStateStartScreen = 0; // where in the start screen you are. @draw has a good comment on this.

		this.titleAnimation = [300, 500, 400, 700] //drops the peices 
	}

    // #function StartScreen::draw |
    // @author Steven Dellamore |
    // @desc This funcion will be ran at 60 frames a second and will call all the functions needed to draw the launch screen. |
    // @header draw() |
    // @param void : Takes no params |
	draw() {
		this.drawTitle(); // Draws the title
		this.animateTitle(); // Draws the T's dropping
		this.drawHighScoreButton();
		// this.titleVarible -= 4;
		if (startscreen_draw) console.log("Drawing on Startscreen");
		Buttonloop();
		/**
		 * This switch statment will tell us where we are on the launch screen i.e
		 * 0 - username box field and join/create game buttons are active
		 * 1 - token field and accept button fields are active
		 */
		switch (this.gameStateStartScreen) {
			case 0:
				this.drawUsernameBox(); // Draws the usernameBox
				break;
			case 1:
				this.drawTokenBox();
				break;
		}
	}

    // #function StartScreen::animateTitle |
    // @author Steven Dellamore |
    // @desc Will check and add/subtract the locations of the T's falling when you go to the launch screen. Once the animation is done, this function will return instantly. |
	// @header animateTitle() |
    animateTitle() {
		for (let i = 0; i < this.titleAnimation.length; i++) {
			if (this.titleAnimation[i] > 0) {
				this.titleAnimation[i] -= 10;
			}
		}
	}
 
    // #function StartScreen::drawUsernameBox |
    // @author Steven Dellamore |
    // @desc This function will draw the username bot onto the screen |
    // @header drawUsernameBox() |
	drawUsernameBox() {
		push(); // Push my settings
		translate(windowWidth / 2, windowHeight / 2); // translate cord plane to center of screen
		fill(255); // setting my color to white
		if(this.usernameBoxStroke == true) {
			stroke("red"); // change to red
			strokeWeight(4); // make it thicker
		}
		rect(0, windowHeight / 15, windowWidth / 3, windowHeight / 12, 15); // drawing my username textbox
		stroke("black"); // reset my old stroke color
		strokeWeight(0); //reset my old strokeweight
		textSize(windowWidth / 30);
		fill(0, 0, 0, 100); // Set alpha to 100
		if (this.usernameTextTouched) { // If they are touching it then make it black.
			fill(0, 0, 0, 255); // Black with 100% alpha
		}
		text(this.usernameText, 0, windowHeight / 15); // draw username into text box. 
		pop(); // restore my settings
	}
	