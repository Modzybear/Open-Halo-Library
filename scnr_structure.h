#ifndef SCNR_STRUCTURE_H
#define SCNR_STRUCTURE_H

#include "datatypes.h"

struct scnr_header
{
	dependency dont_use;
	dependency wont_use;
	dependency cant_use;
	block_pointer skies;
	uint16_t type;
	uint16_t flags;
	block_pointer child_scenarios;
	float local_north;
	char unknown1[0x9c];
	block_pointer predicted_resources;
	block_pointer functions;
	uint32_t editor_scenario_data;
	//uint32_t unknown;
	//block_pointer unknown2;
	char unknown2[0x10];
	block_pointer comments;
	char unknown3[0xe0];
	block_pointer object_names;
	block_pointer scenery;
	block_pointer scenery_palette;
	block_pointer bipeds;
	block_pointer biped_palette;
	block_pointer vehicle;
	block_pointer vehicle_palette;
	block_pointer equipment;
	block_pointer equipment_palette;
	block_pointer weapons;
	block_pointer weapon_palette;
	block_pointer device_groups;
	block_pointer machines;
	block_pointer machine_palette;
	block_pointer controls;
	block_pointer control_palette;
	block_pointer light_fixtures;
	block_pointer light_fixtures_palette;
	block_pointer sound_scenery;
	block_pointer sound_scenery_palette;
	char unknown4[0x54];
	block_pointer player_starting_profile;
	block_pointer player_starting_locations;
	block_pointer trigger_volumes;
	block_pointer recorded_animations;
	block_pointer netgame_flags;
	block_pointer netgame_equipment;
	block_pointer starting_equipment;
	block_pointer bsp_switch_trigger_volumes;
	block_pointer decals;
	block_pointer decal_palette;
	block_pointer detail_object_collection_palette;
	char unknown5[0x54];
	block_pointer actor_palette;
	block_pointer encounters;
	block_pointer command_lists;
	block_pointer ai_animation_references;
	block_pointer ai_script_references;
	block_pointer ai_recording_references;
	block_pointer ai_conversations;
	uint32_t script_syntax_data;
	char unknown6[0x10];
	uint32_t script_string_data;
	char unknown7[0x10];
	block_pointer scripts;
	block_pointer globals;
	block_pointer references;
	char unknown8[0x24];
	block_pointer cutscene_flags;
	block_pointer cutscene_camera_points;
	block_pointer cutscene_titles;
	char unknown9[0x6c];
	dependency custom_object_names;
	dependency ingame_help_text;
	dependency hud_messages;
	block_pointer structure_bsps;
} __attribute__ ((packed)) ;

struct skies_block
{
	dependency sky;
} __attribute__ ((packed)) ;

struct child_scenarios_block
{
	dependency child_scenario;
} __attribute__ ((packed)) ;

struct predicted_resources_block
{
	uint16_t type;
	uint16_t resource_index;
	uint16_t tag_index;
} __attribute__ ((packed)) ;

struct functions_block
{
	uint32_t flags;
	char name[4];
	char unknown1[0x1c];
	float period;
	uint32_t scale_period_by;
	uint16_t function;
	uint32_t scale_function_by;
	uint16_t wobble_function;
	float wobble_period;
	float wobble_magnitude;
	float square_wave_threshold;
	uint16_t step_count;
	uint16_t map_to;
	uint16_t sawtooth_count;
	char unknown2[0x2];
	uint32_t scale_result_by;
	uint16_t bounds_mode;
	float bounds_from;
	float bounds_to;
	char unknown3[0x6];
	uint32_t turn_off_with;
} __attribute__ ((packed)) ;

struct comments_block
{
	float position_x;
	float position_y;
	float position_z;
	char unknown1[0x10];
	uint32_t comment_len;
	char unknown2[0x4];
	block_pointer comment;
} __attribute__ ((packed)) ;

struct comment_block
{
	char comment[16];
} __attribute__ ((packed)) ;

struct object_names_block
{
	char name[4];
} __attribute__ ((packed)) ;

struct scenery_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
} __attribute__ ((packed)) ;

struct scenery_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct bipeds_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x28];
	float body_vitality;
	uint32_t flags;
} __attribute__ ((packed)) ;

struct biped_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct vehicle_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x28];
	float body_vitality;
	uint32_t flags;
	char unknown2[0x8];
	char multiplayer_team_index[1];
	char unknown3[0x1];
	uint32_t multiplayer_spawn_flags;
} __attribute__ ((packed)) ;

struct vehicle_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct equipment_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x2];
	uint32_t miscellaneous_flags;
} __attribute__ ((packed)) ;

struct equipment_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct weapons_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x28];
	uint16_t rounds_left;
	uint16_t rounds_loaded;
	uint32_t miscellaneous_flags;
} __attribute__ ((packed)) ;

struct weapon_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct device_groups_block
{
	char name[4];
	char unknown1[0x1c];
	float initial_value;
	uint32_t flags;
} __attribute__ ((packed)) ;

struct machines_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x8];
	uint32_t power_group;
	uint32_t position_group;
	uint32_t flags_1;
	uint32_t flags_2;
} __attribute__ ((packed)) ;

struct machine_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct controls_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x8];
	uint32_t power_group;
	uint32_t position_group;
	uint32_t flags_1;
	uint32_t flags_2;
	uint16_t dont_touch_this;
} __attribute__ ((packed)) ;

struct control_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct light_fixtures_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
	char unknown1[0x8];
	uint32_t power_group;
	uint32_t position_group;
	uint32_t flags_1;
	colorrgb color;
	float intensity;
	float falloff_angle;
	float cutoff_angle;
} __attribute__ ((packed)) ;

struct light_fixtures_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct sound_scenery_block
{
	uint32_t type;
	uint32_t name;
	uint32_t not_placed;
	uint16_t desired_permutation;
	float position_x;
	float position_y;
	float position_z;
	float rotation_y;
	float rotation_p;
	float rotation_r;
} __attribute__ ((packed)) ;

struct sound_scenery_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct player_starting_profile_block
{
	char name[4];
	char unknown1[0x1c];
	float starting_health_modifier;
	float starting_shield_modifier;
	dependency primary_weapon;
	uint16_t primary_weapon_rounds_loaded;
	uint16_t primary_weapon_rounds_left;
	dependency secondary_weapon;
	uint16_t secondary_weapon_rounds_loaded;
	uint16_t secondary_weapon_rounds_left;
	char starting_fragmentation_grenade_count[1];
	char starting_plasma_grenade_count[1];
	char starting_unknown_1_grenade_count[1];
	char starting_unknown_2_grenade_count[1];
} __attribute__ ((packed)) ;

struct player_starting_locations_block
{
	float position_x;
	float position_y;
	float position_z;
	float facing;
	uint16_t team_index;
	uint16_t bsp_index;
	uint16_t type_0;
	uint16_t type_1;
	uint16_t type_2;
	uint16_t type_3;
} __attribute__ ((packed)) ;

struct trigger_volumes_block
{
	char name[4];
} __attribute__ ((packed)) ;

struct recorded_animations_block
{
	char name[4];
	char unknown1[0x1c];
	char version[1];
	char raw_animation_data[1];
	uint16_t unit_control_data_version;
	uint16_t length_of_animation;
	char unknown2[0x6];
	uint32_t recorded_animation_event_stream;
} __attribute__ ((packed)) ;

struct netgame_flags_block
{
	float position_x;
	float position_y;
	float position_z;
	float facing;
	uint16_t type;
	uint16_t team_index;
	dependency weapon_group;
} __attribute__ ((packed)) ;

struct netgame_equipment_block
{
	uint32_t flags;
	uint16_t type_0;
	uint16_t type_1;
	uint16_t type_2;
	uint16_t type_3;
	uint16_t team_index;
	uint16_t spawn_time;
	char unknown1[0x30];
	float position_x;
	float position_y;
	float position_z;
	float facing;
	dependency item_collection;
} __attribute__ ((packed)) ;

struct starting_equipment_block
{
	uint32_t flags;
	uint16_t type_0;
	uint16_t type_1;
	uint16_t type_2;
	uint16_t type_3;
	char unknown1[0x30];
	dependency item_collection_1;
	dependency item_collection_2;
	dependency item_collection_3;
	dependency item_collection_4;
	dependency item_collection_5;
	dependency item_collection_6;
} __attribute__ ((packed)) ;

struct bsp_switch_trigger_volumes_block
{
	uint32_t trigger_volume;
	uint16_t source;
	uint16_t destination;
} __attribute__ ((packed)) ;

struct decals_block
{
	uint32_t decal_type;
	uint8_t yaw;
	uint8_t pitch;
	float position_x;
	float position_y;
	float position_z;
} __attribute__ ((packed)) ;

struct decal_palette_block
{
	dependency reference;
} __attribute__ ((packed)) ;

struct detail_object_collection_palette_block
{
	dependency name;
} __attribute__ ((packed)) ;

struct actor_palette_block
{
	dependency reference;
} __attribute__ ((packed)) ;

struct encounters_block
{
	char name[4];
	char unknown1[0x1c];
	uint32_t flags;
	uint16_t team_index;
	char unknown2[0x2];
	uint16_t search_behavior;
	uint16_t manual_bsp_index;
	float respawn_delay_from;
	float respawn_delay_to;
	char unknown3[0x4c];
	block_pointer squads;
	block_pointer platoons;
	block_pointer firing_positions;
	block_pointer player_starting_locations;
} __attribute__ ((packed)) ;

struct squads_block
{
	char name[4];
	char unknown1[0x1c];
	uint32_t actor_type;
	uint16_t initial_state;
	uint16_t return_state;
	uint32_t flags;
	uint16_t unique_leader_type;
	char unknown2[0x22];
	float squad_delay_time;
	uint32_t attacking;
	uint32_t attacking_search;
	uint32_t attacking_guard;
	uint32_t defending;
	uint32_t defending_search_careful_unreliable;
	uint32_t defending_guard;
	uint32_t pursuing;
	char unknown3[0xc];
	uint16_t normal_difficulty_count;
	uint16_t insane_difficulty_count;
	uint16_t major_upgrade;
	char unknown4[0x2];
	uint16_t respawn_minimum_actors;
	uint16_t respawn_maximum_actors;
	uint16_t respawn_total;
	char unknown5[0x2];
	float respawn_delay_from;
	float respawn_delay_to;
	char unknown6[0x30];
	block_pointer move_positions;
	block_pointer starting_locations;
} __attribute__ ((packed)) ;

struct move_positions_block
{
	float position_x;
	float position_y;
	float position_z;
	float facing;
	float weight;
	float time_from;
	float time_to;
	uint32_t animations;
	char sequence_id[1];
	char unknown1[0x2d];
	uint32_t surface_index;
} __attribute__ ((packed)) ;

struct starting_locations_block
{
	float position_x;
	float position_y;
	float position_z;
	float facing;
	char unknown1[0x2];
	char sequence_id[1];
	uint8_t flags;
	uint16_t return__state;
	uint16_t initial_state;
	uint32_t actor_type;
	uint32_t command_list;
} __attribute__ ((packed)) ;

struct platoons_block
{
	char name[4];
	char unknown1[0x1c];
	uint32_t flags;
	char unknown2[0xc];
	uint16_t change_attacking_or_defending_status_when;
	char unknown3[0xa];
	uint16_t maneuver_when;
} __attribute__ ((packed)) ;

struct firing_positions_block
{
	float position_x;
	float position_y;
	float position_z;
	uint16_t group_index;
} __attribute__ ((packed)) ;

struct ai_starting_locations_block
{
	float position_x;
	float position_y;
	float position_z;
	float facing;
	uint16_t team_index;
	uint16_t bsp_index;
	uint16_t type_0;
	uint16_t type_1;
	uint16_t type_2;
	uint16_t type_3;
} __attribute__ ((packed)) ;

struct command_lists_block
{
	char name[4];
	char unknown1[0x1c];
	uint32_t flags;
	char unknown2[0x8];
	uint16_t manual_bsp_index;
	char unknown3[0x2];
	block_pointer commands;
	block_pointer points;
} __attribute__ ((packed)) ;

struct commands_block
{
	uint16_t atom_type;
	uint16_t atom_modifier;
	float parameter_1;
	float parameter_2;
	char unknown1[0x4];
	uint32_t animation;
	uint32_t script;
	uint32_t recording;
	uint32_t object_name;
} __attribute__ ((packed)) ;

struct points_block
{
	float position_x;
	float position_y;
	float position_z;
} __attribute__ ((packed)) ;

struct ai_animation_references_block
{
	char animation_name[4];
	char unknown1[0x1c];
	dependency animation_graph;
} __attribute__ ((packed)) ;

struct ai_script_references_block
{
	char script_name[4];
} __attribute__ ((packed)) ;

struct ai_recording_references_block
{
	char recording_name[4];
} __attribute__ ((packed)) ;

struct ai_conversations_block
{
	char name[4];
	char unknown1[0x1c];
	uint32_t flags;
	float trigger_distance;
	float runtoplayer_distance;
	char unknown2[0x24];
	block_pointer participants;
	block_pointer lines;
} __attribute__ ((packed)) ;

struct participants_block
{
	uint32_t flags;
	uint16_t selection_type;
	uint16_t actor_type;
	uint32_t use_this_object;
	uint32_t set_new_name;
	char unknown1[0x12];
	char encounter_name[4];
} __attribute__ ((packed)) ;

struct lines_block
{
	uint32_t flags;
	uint16_t addressee;
	char unknown1[0x6];
	float line_delay_time;
	char unknown2[0xc];
	dependency variant_1;
	dependency variant_2;
	dependency variant_3;
	dependency variant_4;
	dependency variant_5;
	dependency variant_6;
} __attribute__ ((packed)) ;

struct scripts_block
{
	char name[4];
	char unknown1[0x1c];
	uint16_t script_type;
	uint16_t return_type;
	uint32_t root_expression_index;
} __attribute__ ((packed)) ;

struct globals_block
{
	char name[4];
	char unknown1[0x1c];
	uint16_t type;
	char unknown2[0x6];
	uint32_t initialization_expression_index;
} __attribute__ ((packed)) ;

struct references_block
{
	dependency reference;
} __attribute__ ((packed)) ;

struct cutscene_flags_block
{
	char name[4];
	char unknown1[0x1c];
	float position_x;
	float position_y;
	float position_z;
	float facing_y;
	float facing_p;
} __attribute__ ((packed)) ;

struct cutscene_camera_points_block
{
	char name[4];
	char unknown1[0x20];
	float position_x;
	float position_y;
	float position_z;
	float orientation_y;
	float orientation_p;
	float orientation_r;
	float field_of_view;
} __attribute__ ((packed)) ;

struct cutscene_titles_block
{
	char name[4];
	char unknown1[0x20];
	uint16_t text_bounds_on_screen_t;
	uint16_t text_bounds_on_screen_l;
	uint16_t text_bounds_on_screen_b;
	uint16_t text_bounds_on_screen_r;
	uint16_t string_index;
	char unknown2[0x2];
	uint16_t justification;
	char unknown3[0x6];
	colorbyte text_color;
	colorbyte shadow_color;
	float fade_in_time;
	float up_time;
	float fade_out_time;
} __attribute__ ((packed)) ;

struct structure_bsps_block
{
	uint32_t bsp_start;
	uint32_t bsp_size;
	uint32_t bsp_magic;
	char unknown1[0x4];
	dependency structure_bsp;
} __attribute__ ((packed)) ;

#endif
