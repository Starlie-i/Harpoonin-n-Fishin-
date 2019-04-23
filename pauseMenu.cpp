// NOTE: x and y are where the pauseMenu object are located. It is a persistent object in the game room at x = 512 and y = 364
// ************* CREATE EVENT *************

gameIsPaused = false;
allObjects[0, 0] = noone;

pauseX = x;
pauseY = y;
buttonHeight = 64;
titleHeight = -150;

button[0] = "Options";
button[1] = "Exit to menu";
button[2] = "Quit";

buttons = array_length_1d(button);

pauseIndex = 0;
lastSelected = 0;

// ************* STEP EVENT *************

menuMove = keyboard_check_pressed(vk_down) - keyboard_check_pressed(vk_up);

pauseIndex += menuMove;
if(pauseIndex < 0)				{ pauseIndex = buttons - 1; }
if(pauseIndex > (buttons - 1))	{ pauseIndex = 0; }

// ************* DRAW EVENT *************

/// @description While game is paused
if(gameIsPaused)
{

	for(var i = 0; i < array_height_2d(allObjects); ++i){
		draw_sprite_ext(allObjects[i, 0], allObjects[i, 1], allObjects[i, 2], allObjects[i, 3], 
		allObjects[i, 4], allObjects[i, 5], allObjects[i, 6], allObjects[i, 7], 
		allObjects[i, 8] / 2); 
	}

	draw_set_font(f_2);
	draw_set_halign(fa_center);
	// darker teal RGB rgb(0, 100, 95)
	draw_set_color(make_color_rgb(0, 100, 95));
	draw_text(pauseX, pauseY + titleHeight, "Paused");

var i = 0;

repeat(buttons){
	draw_set_font(f_1);
	draw_set_halign(fa_center);
	draw_set_color(make_color_rgb(0, 100, 95));
	if(pauseIndex == i)	{ draw_set_color(c_black); }
	draw_text(pauseX, pauseY + (buttonHeight * i) , button[i]);
	i++
}
// This draws all of the objects at half transparency to the pause screen when paused

}

// ************* KEY PRESS ENTER EVENT *************

switch(pauseIndex){
	case 0:
		instance_deactivate_object(obj_pause);
		//instance_activate_object(obj_options);
		break;
	case 1:
		room_goto(rm_menu);
		instance_destroy(obj_pause);
		allObjects = 0;
		gameIsPaused = false;
		break;
	case 2: 
		game_end();
		break;
}

// ************* KEY PRESS ESCAPE EVENT *************


if (gameIsPaused == false){
	var offset = 0;
	for(var i = 0; i < instance_count; ++i){
	if (instance_find(all, i).sprite_index != -1)	{
			allObjects[i - offset, 0] = instance_find(all, i).sprite_index;
			allObjects[i - offset, 1] = instance_find(all, i).image_index;
			allObjects[i - offset, 2] = instance_find(all, i).x;
			allObjects[i - offset, 3] = instance_find(all, i).y;
			allObjects[i - offset, 4] = instance_find(all, i).image_xscale;
			allObjects[i - offset, 5] = instance_find(all, i).image_yscale;
			allObjects[i - offset, 6] = instance_find(all, i).image_angle;
			allObjects[i - offset, 7] = instance_find(all, i).image_blend;
			allObjects[i - offset, 8] = instance_find(all, i).image_alpha;
		}
	else
		++offset;
	}
	
	instance_deactivate_all(true);
	gameIsPaused = true;
}
else{
	instance_activate_all();
	gameIsPaused = false;
	
	allObjects = 0;
}
