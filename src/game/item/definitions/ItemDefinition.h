/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

struct ItemDefinition {
    int id;
    std::string public_name;
    std::string item_name;
    std::string type;
    int width;
    int length;
    double height;
    bool can_stack;
    bool can_sit;
    bool is_walkable;
    int sprite_id = -1;
    bool allow_recycle;
    bool allow_trade;
    bool allow_marketplace_sell;
    bool allow_gift;
    bool allow_inventory_stack;
    std::string interaction_type;
    int interaction_modes_count;
    int vending_id;
    int effect_id;
    int height_adjustible;
    int flat_id;
    int song_id;
    bool requires_rights;
    bool is_arrow;
};
/*interaction: default
interaction: bed
interaction: vendingmachine
interaction: bottle
interaction: gift
interaction: teleport
interaction: dice
interaction: trophy
interaction: gate
interaction: scoreboard
interaction: alert
interaction: roller
interaction: onewaygate
interaction: loveshuffler
interaction: rentals
interaction: postit
interaction: habbowheel
interaction: dimmer
interaction: roomeffect
interaction: water
interaction: pressure_pad
interaction: pet5
interaction: pet3
interaction: pet4
interaction: pet1
interaction: pet0
interaction: pet2
interaction: ball
interaction: football_goal
interaction: fbgate
interaction: football_timer
interaction: football_score
interaction: pet8
interaction: pet11
interaction: pet10
interaction: pet12
interaction: pet9
interaction: beach_shower
interaction: wf_act_move_rotate
interaction: wired
interaction: wf_floor_switch2
interaction: wf_xtra_random
interaction: wf_trg_periodically
interaction: wf_pyramid
interaction: wf_trg_atscore
interaction: wf_act_teleport_to
interaction: wf_trg_says_something
interaction: wf_colorwheel
interaction: wf_trg_walks_off_furni
interaction: wf_trg_attime
interaction: wf_trg_gameend
interaction: wf_act_show_message
interaction: wf_trg_enter_room
interaction: wf_act_toggle_state
interaction: wf_ringplate
interaction: wf_pressureplate
interaction: wf_cnd_furnis_hv_avtrs
interaction: wf_arrowplate
interaction: wf_cnd_trggrer_on_frn
interaction: wf_cnd_match_snapshot
interaction: wf_act_givepoints
interaction: wf_act_match_to_sshot
interaction: wf_floor_switch1
interaction: wf_trg_gamestart
interaction: wf_trg_walks_on_furni
interaction: pet15
interaction: rollerskate
interaction: pet7
interaction: pet6
interaction: halo_tile
interaction: puzzlebox
interaction: wf_cnd_has_furni_on
interaction: tagpole
interaction: roombg
interaction: mannequin
interaction: group_item
interaction: hopper
interaction: blue_score
interaction: bb_green_gate
interaction: green_score
interaction: yellow_score
interaction: bb_red_gate
interaction: bb_patch
interaction: bb_yellow_gate
interaction: bb_teleport
interaction: bb_blue_gate
interaction: red_score
interaction: pet14
interaction:
interaction: wf_cnd_actor_in_group
interaction: wf_act_give_reward
interaction: badge_display
interaction: wf_cnd_wearing_badge
interaction: wf_cnd_wearing_effect
interaction: wf_cnd_not_trggrer_on
interaction: wf_cnd_not_hv_avtrs
interaction: wf_cnd_not_user_count
interaction: wf_cnd_user_count_in
interaction: wf_cnd_not_in_group
interaction: wf_cnd_not_match_snap
interaction: adjustable_height
interaction: group_forum
interaction: pet16
interaction: group_gate*/