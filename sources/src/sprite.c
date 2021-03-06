/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#include <SDL/SDL_image.h>
#include <assert.h>

#include <sprite.h>
#include <misc.h>

// Sprites general
#define MAP_CASE        "sprite/wood_box.png"
#define MAP_KEY			"sprite/key.png"
#define MAP_DOOR_OPENED	"sprite/door_opened.png"
#define MAP_DOOR_CLOSED	"sprite/door_closed.png"

// Scenery elements
#define MAP_STONE		"sprite/stone.png"
#define MAP_TREE        "sprite/tree.png"

// Sprites of Banner
#define BANNER_LINE		"sprite/banner_line.png"
#define BANNER_DIVIDER	"sprite/banner_divider.png"
#define BANNER_LIFE		"sprite/banner_life.png"
#define BANNER_BOMB		"sprite/bomb3.png"
#define BANNER_RANGE		"sprite/banner_range.png"
#define BANNER_0			"sprite/banner_0.png"
#define BANNER_1			"sprite/banner_1.png"
#define BANNER_2			"sprite/banner_2.png"
#define BANNER_3			"sprite/banner_3.png"
#define BANNER_4			"sprite/banner_4.png"
#define BANNER_5			"sprite/banner_5.png"
#define BANNER_6			"sprite/banner_6.png"
#define BANNER_7			"sprite/banner_7.png"
#define BANNER_8			"sprite/banner_8.png"
#define BANNER_9			"sprite/banner_9.png"

// Sprites of Bombs
#define BOMB_TTL1       "sprite/bomb1.png"
#define BOMB_TTL2       "sprite/bomb2.png"
#define BOMB_TTL3       "sprite/bomb3.png"
#define BOMB_TTL4       "sprite/bomb4.png"

//explosion
#define EXPLOSION       "sprite/explosion.png"

// Sprites of Bonus
#define IMG_BONUS_BOMB_RANGE_INC  "sprite/bonus_bomb_range_inc.png"
#define IMG_BONUS_BOMB_RANGE_DEC  "sprite/bonus_bomb_range_dec.png"
#define IMG_BONUS_BOMB_NB_INC     "sprite/bonus_bomb_nb_inc.png"
#define IMG_BONUS_BOMB_NB_DEC     "sprite/bonus_bomb_nb_dec.png"

// Sprites of Players
#define PLAYER_LEFT     		"sprite/player_left.png"
#define PLAYER_IMMUNE_LEFT      "sprite/player_left_immune.png"
#define PLAYER_UP       		"sprite/player_up.png"
#define PLAYER_IMMUNE_UP        "sprite/player_up_immune.png"
#define PLAYER_RIGHT    		"sprite/player_right.png"
#define PLAYER_IMMUNE_RIGHT 	"sprite/player_right_immune.png"
#define PLAYER_DOWN     		"sprite/player_down.png"
#define PLAYER_IMMUNE_DOWN		"sprite/player_down_immune.png"
#define PLAYER_PRINCESS			"sprite/bomberwoman.png"

// Sprites of monsters
#define MONSTER_LEFT     "sprite/monster_left.png"
#define MONSTER_UP       "sprite/monster_up.png"
#define MONSTER_RIGHT    "sprite/monster_right.png"
#define MONSTER_DOWN     "sprite/monster_down.png"

// Sprites of Menu
#define MENU_LOGO		"sprite/logo.png"
#define MENU_WALLPAPER	"sprite/menu_wallpaper.jpg"
#define MENU_CREDITS 	"sprite/credits.png"
#define MENU_BUTTON_REPRENDRE			"sprite/button_reprendre.jpg"
#define MENU_BUTTON_REPRENDRE_HOVER		"sprite/button_reprendre_hover.jpg"
#define MENU_BUTTON_REPRENDRE_DISABLED	"sprite/button_reprendre_disabled.jpg"
#define MENU_BUTTON_FACILE				"sprite/button_facile.jpg"
#define MENU_BUTTON_FACILE_HOVER		"sprite/button_facile_hover.jpg"
#define MENU_BUTTON_DIFFICILE			"sprite/button_difficile.jpg"
#define MENU_BUTTON_DIFFICILE_HOVER		"sprite/button_difficile_hover.jpg"
#define MENU_GAME_OVER					"sprite/game_over.png"
#define MENU_VICTORY					"sprite/victory.png"
#define MENU_BREAK	"sprite/break.png"
#define MENU_BOUTON_SAUVER_QUITTER			"sprite/bouton_sauver_quitter.jpg"
#define MENU_BOUTON_SAUVER_QUITTER_HOVER	"sprite/bouton_sauver_quitter_hover.jpg"

// banner
SDL_Surface* numbers[10];
SDL_Surface* banner_life;
SDL_Surface* banner_bomb;
SDL_Surface* banner_range;
SDL_Surface* banner_line;
SDL_Surface* banner_divider;

// map
SDL_Surface* box;
SDL_Surface* goal;
SDL_Surface* key;
SDL_Surface* door_opened;
SDL_Surface* door_closed;
SDL_Surface* stone;
SDL_Surface* tree;

// bombs
#define NB_BOMBS 4
SDL_Surface* bombs[NB_BOMBS + 1];
SDL_Surface* explosion;

// bonus
#define NB_BONUS 4
SDL_Surface* bonus[NB_BONUS + 1];

// player
SDL_Surface* player_img[4];
SDL_Surface* player_immune_img[4];
SDL_Surface* princess;

// monster
SDL_Surface* monster_img[4];

// menu elements
#define NB_BUTTONS 9
SDL_Surface* logo;
SDL_Surface* menu_wallpaper;
SDL_Surface* credits;
SDL_Surface* buttons[NB_BUTTONS];
SDL_Surface* game_over;
SDL_Surface* victory;
SDL_Surface* menu_break;


static void banner_load() {
	// numbers imgs
	numbers[0] = load_image(BANNER_0);
	numbers[1] = load_image(BANNER_1);
	numbers[2] = load_image(BANNER_2);
	numbers[3] = load_image(BANNER_3);
	numbers[4] = load_image(BANNER_4);
	numbers[5] = load_image(BANNER_5);
	numbers[6] = load_image(BANNER_6);
	numbers[7] = load_image(BANNER_7);
	numbers[8] = load_image(BANNER_8);
	numbers[9] = load_image(BANNER_9);

	// other banner sprites
	banner_life = load_image(BANNER_LIFE);
	banner_bomb = load_image(BANNER_BOMB);
	banner_range = load_image(BANNER_RANGE);
	banner_line = load_image(BANNER_LINE);
	banner_divider = load_image(BANNER_DIVIDER);
}

static void banner_unload() {
	// numbers imgs
	for (int i = 0; i < 10; i++) {
		SDL_FreeSurface(numbers[i]);
	}

	// other banner sprites
	SDL_FreeSurface(banner_life);
	SDL_FreeSurface(banner_bomb);
	SDL_FreeSurface(banner_range);
	SDL_FreeSurface(banner_line);
	SDL_FreeSurface(banner_divider);
}
// static void bomb_load et bomb_unload (cf banner laod)
static void bombs_load() {
	bombs[0] = load_image(BOMB_TTL1);
	bombs[1] = load_image(BOMB_TTL2);
	bombs[2] = load_image(BOMB_TTL3);
	bombs[3] = load_image(BOMB_TTL4);
}

static void bombs_unload() {
	for (int i = 0; i <= 4; i++) {
			SDL_FreeSurface(bombs[i]);
		}
}

//idem pour explosion load (cf logo load)
static void explosion_load() {
	explosion = load_image(EXPLOSION);
}

static void explosion_unload() {
	SDL_FreeSurface(explosion);
}

static void map_load() {
	// Sprite loading
	tree = load_image(MAP_TREE);
	box = load_image(MAP_CASE);
	key = load_image(MAP_KEY);
	stone = load_image(MAP_STONE);
	door_opened = load_image(MAP_DOOR_OPENED);
	door_closed = load_image(MAP_DOOR_CLOSED);
}

static void map_unload() {
	SDL_FreeSurface(tree);
	SDL_FreeSurface(box);
	SDL_FreeSurface(goal);
	SDL_FreeSurface(key);
	SDL_FreeSurface(stone);
	SDL_FreeSurface(door_opened);
	SDL_FreeSurface(door_closed);
}


static void bonus_load() {
	bonus[0] = NULL;
	bonus[BONUS_BOMB_RANGE_INC] = load_image(IMG_BONUS_BOMB_RANGE_INC);
	bonus[BONUS_BOMB_RANGE_DEC] = load_image(IMG_BONUS_BOMB_RANGE_DEC);
	bonus[BONUS_BOMB_NB_INC] = load_image(IMG_BONUS_BOMB_NB_INC);
	bonus[BONUS_BOMB_NB_DEC] = load_image(IMG_BONUS_BOMB_NB_DEC);
}

static void bonus_unload() {
	for (int i = 0; i < NB_BONUS; i++)
		if(bonus[i])
			SDL_FreeSurface(bonus[i]);
}

static void player_load() {
	player_img[WEST] = load_image(PLAYER_LEFT);
	player_immune_img[WEST] = load_image(PLAYER_IMMUNE_LEFT);
	player_img[EAST] = load_image(PLAYER_RIGHT);
	player_immune_img[EAST] = load_image(PLAYER_IMMUNE_RIGHT);
	player_img[NORTH] = load_image(PLAYER_UP);
	player_immune_img[NORTH] = load_image(PLAYER_IMMUNE_UP);
	player_img[SOUTH] = load_image(PLAYER_DOWN);
	player_immune_img[SOUTH] = load_image(PLAYER_IMMUNE_DOWN);
	princess = load_image(PLAYER_PRINCESS);
}


static void player_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(player_img[i]);
	for (int i = 0; i < 4; i++)
			SDL_FreeSurface(player_immune_img[i]);
	SDL_FreeSurface(princess);
}

static void monster_load() {
	monster_img[WEST] = load_image(MONSTER_LEFT);
	monster_img[EAST] = load_image(MONSTER_RIGHT);
	monster_img[NORTH] = load_image(MONSTER_UP);
	monster_img[SOUTH] = load_image(MONSTER_DOWN);
}

static void monster_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(monster_img[i]);
}

static void menu_load()
{
	logo = load_image(MENU_LOGO);
	credits = load_image(MENU_CREDITS);
	menu_wallpaper = load_image(MENU_WALLPAPER);
	game_over=load_image(MENU_GAME_OVER);
	victory=load_image(MENU_VICTORY);
	menu_break=load_image(MENU_BREAK);
}

static void menu_unload()
{
	SDL_FreeSurface(logo);
	SDL_FreeSurface(credits);
	SDL_FreeSurface(menu_wallpaper);
	SDL_FreeSurface(game_over);
	SDL_FreeSurface(victory);
	SDL_FreeSurface(menu_break);
}

static void buttons_load()
{
	buttons[0] = load_image(MENU_BUTTON_REPRENDRE);
	buttons[1] = load_image(MENU_BUTTON_REPRENDRE_HOVER);
	buttons[2] = load_image(MENU_BUTTON_FACILE);
	buttons[3] = load_image(MENU_BUTTON_FACILE_HOVER);
	buttons[4] = load_image(MENU_BUTTON_DIFFICILE);
	buttons[5] = load_image(MENU_BUTTON_DIFFICILE_HOVER);
	buttons[6] = load_image(MENU_BOUTON_SAUVER_QUITTER);
	buttons[7] = load_image(MENU_BOUTON_SAUVER_QUITTER_HOVER);
	buttons[8] = load_image(MENU_BUTTON_REPRENDRE_DISABLED);
}

static void buttons_unload()
{
	for (int i = 0; i < NB_BUTTONS; i++)
		SDL_FreeSurface(buttons[i]);
}

void sprite_load() {
	map_load();
	bonus_load();
	banner_load();
	bombs_load();
	explosion_load();
	player_load();
	menu_load();
	buttons_load();
	monster_load();
}

void sprite_free() {
	map_unload();
	bonus_unload();
	banner_unload();
	bombs_unload();
	explosion_unload();
	player_unload();
	menu_unload();
	buttons_unload();
	monster_unload();
}

SDL_Surface* sprite_get_number(short number) {
	assert(number >= 0 && number < 9);
	return numbers[number];
}

SDL_Surface* sprite_get_player(enum direction direction) {
	assert(player_img[direction]);
	return player_img[direction];
}

SDL_Surface* sprite_get_player_immune(enum direction direction) {
	assert(player_immune_img[direction]);
	return player_immune_img[direction];
}

SDL_Surface* sprite_get_monster(enum direction direction) {
	assert(monster_img[direction]);
	return monster_img[direction];
}

SDL_Surface* sprite_get_princess(){
	assert(princess);
	return princess;
}

SDL_Surface* sprite_get_banner_life() {
	assert(banner_life);
	return banner_life;
}

SDL_Surface* sprite_get_banner_bomb() {
	assert(banner_bomb);
	return banner_bomb;
}

SDL_Surface* sprite_get_banner_line() {
	assert(banner_line);
	return banner_line;
}

SDL_Surface* sprite_get_banner_divider() {
	assert(banner_divider);
	return banner_divider;
}

SDL_Surface* sprite_get_banner_range() {
	assert(banner_range);
	return banner_range;
}

SDL_Surface* sprite_get_bomb(int state) {
	SDL_Surface* bomb;
	switch (state){
	case 0:
		assert(bombs[0]);
		bomb = bombs[0];
		break;
	case 1:
		assert(bombs[1]);
		bomb = bombs[1];
		break;
	case 2:
		assert(bombs[2]);
		bomb = bombs[2];
		break;
	case 3:
		assert(bombs[3]);
		bomb = bombs[3];
		break;
	case -1:
		assert(explosion);
		bomb = explosion;
	}
	return bomb;
}

SDL_Surface* sprite_get_explosion(){
	assert(explosion);
	return explosion;
}

SDL_Surface* sprite_get_bonus(enum bonus_type bonus_type) {
	assert(bonus[bonus_type]);
	return bonus[bonus_type];
}

SDL_Surface* sprite_get_tree() {
	assert(tree);
	return tree;
}

SDL_Surface* sprite_get_box() {
	assert(box);
	return box;
}

SDL_Surface* sprite_get_key() {
	assert(key);
	return key;
}

SDL_Surface* sprite_get_stone() {
	assert(stone);
	return stone;
}

SDL_Surface* sprite_get_door_opened() {
	assert(door_opened);
	return door_opened;
}

SDL_Surface* sprite_get_door_closed() {
	assert(door_closed);
	return door_closed;
}

SDL_Surface* sprite_get_logo()
{
	assert(logo);
	return logo;
}

SDL_Surface* sprite_get_menu_wallpaper()
{
	assert(menu_wallpaper);
	return menu_wallpaper;
}

SDL_Surface* sprite_get_credits()
{
	assert(credits);
	return credits;
}

SDL_Surface* sprite_get_button(int button_number) {
	assert(button_number >= 0 && button_number < NB_BUTTONS && buttons[button_number]);
	return buttons[button_number];
}

SDL_Surface* sprite_get_game_over() {
	assert(game_over);
	return game_over;

}

SDL_Surface* sprite_get_victory() {
	assert(victory);
	return victory;
}

SDL_Surface* sprite_get_menu_break() {
	assert(menu_break);
	return menu_break;
}
