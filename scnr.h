#ifndef SCNR_H
#define SCNR_H

/*
Copyright 2017 Andrew Burnett

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "scnr_structure.h"

class scnr
{
	public:
		scnr(char *, int);
		void parse();

		scnr_header * tag_header;
		skies_block * skies;
		child_scenarios_block * child_scenarios;
		predicted_resources_block * predicted_resources;
		functions_block * functions;
		comments_block * comments;
		object_names_block * object_names;
		scenery_block * scenery;
		scenery_palette_block * scenery_palette;
		bipeds_block * bipeds;
		biped_palette_block * biped_palette;
		vehicle_block * vehicle;
		vehicle_palette_block * vehicle_palette;
		equipment_block * equipment;
		equipment_palette_block * equipment_palette;
		weapons_block * weapons;
		weapon_palette_block * weapon_palette;
		device_groups_block * device_groups;
		machines_block * machines;
		machine_palette_block * machine_palette;
		controls_block * controls;
		control_palette_block * control_palette;
		light_fixtures_block * light_fixtures;
		light_fixtures_palette_block * light_fixtures_palette;
		sound_scenery_block * sound_scenery;
		sound_scenery_palette_block * sound_scenery_palette;
		player_starting_profile_block * player_starting_profile;
		player_starting_locations_block * player_starting_locations;
		trigger_volumes_block * trigger_volumes;
		recorded_animations_block * recorded_animations;
		netgame_flags_block * netgame_flags;
		netgame_equipment_block * netgame_equipment;
		starting_equipment_block * starting_equipment;
		bsp_switch_trigger_volumes_block * bsp_switch_trigger_volumes;
		decals_block * decals;
		decal_palette_block * decal_palette;
		detail_object_collection_palette_block * detail_object_collection_palette;
		actor_palette_block * actor_palette;
		encounters_block * encounters;
		command_lists_block * command_lists;
		ai_animation_references_block * ai_animation_references;
		ai_script_references_block * ai_script_references;
		ai_recording_references_block * ai_recording_references;
		ai_conversations_block * ai_conversations;
		scripts_block * scripts;
		globals_block * globals;
		references_block * references;
		cutscene_flags_block * cutscene_flags;
		cutscene_camera_points_block * cutscene_camera_points;
		cutscene_titles_block * cutscene_titles;
		structure_bsps_block * structure_bsps;

		char * buff;
		int offset;
};

#endif
