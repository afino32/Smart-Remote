#include "Codes.h"

//stores codes into preferences
void get_codes(Preferences &preferences) {
  preferences.begin("IR_CODES", false);
  preferences.clear();

  //LG codes recorded manually...
  //LSB first
  //power
  preferences.putString("tv_lg_1_pwr", "0xF708FB04");
  //up
  preferences.putString("tv_lg_1_up", "0xBF40FB04");
  //down
  preferences.putString("tv_lg_1_dwn", "0xBE41FB04");
  //left
  preferences.putString("tv_lg_1_lft", "0xF807FB04");
  //right
  preferences.putString("tv_lg_1_rht", "0xF906FB04");
  //ok
  preferences.putString("tv_lg_1_ok", "0xBB44FB04");
  //volume up
  preferences.putString("tv_lg_1_vu", "0xFD02FB04");
  //volume down
  preferences.putString("tv_lg_1_vd", "0xFC03FB04");
  //settings
  preferences.putString("tv_lg_1_stgs", "0xBC43FB04");
  //source
  preferences.putString("tv_lg_1_src", "0xF40BFB04");
  //back
  preferences.putString("tv_lg_1_bck", "0xD728FB04");


  /*
    //same codes that I read in above...
    //https://tasmota.github.io/docs/Codes-for-IR-Remotes/#ir-codes-tv-lg-55uh8509
    //LSB first
    //20DF10EF (MSB first)
    preferences.putString("tv_lg_2_pwr", "0xF708FB04");
    //20DF02FD (MSB first)
    preferences.putString("tv_lg_2_up", "0xBF40FB04");
    //20DF827D (MSB first)
    preferences.putString("tv_lg_2_dwn", "0xBE41FB04");
    //20DFE01F (MSB first)
    preferences.putString("tv_lg_2_lft", "0xF807FB04");
    //20DF609F (MSB first)
    preferences.putString("tv_lg_2_rht", "0xF906FB04");
    //20DF22DD (MSB first)
    preferences.putString("tv_lg_2_ok", "0xBB44FB04");
    //20DF40BF (MSB first)
    preferences.putString("tv_lg_2_vu", "0xFD02FB04");
    //20DFC03F (MSB first)
    preferences.putString("tv_lg_2_vd", "0xFC03FB04");
    //20DFC23D (MSB first)
    preferences.putString("tv_lg_2_stgs", "0xBC43FB04");
    //20DFD02F (MSB first)
    preferences.putString("tv_lg_2_src", "0xF40BFB04");
    //20DF14EB (MSB first)
    preferences.putString("tv_lg_2_bck", "0xD728FB04");
  */

  //https://github.com/lepiaf/IR-Remote-Code
  //LSB first
  //E0E040BF (MSB first)
  preferences.putString("tv_ss_1_pwr", "0xFD020707");
  //E0E006F9 (MSB first)
  preferences.putString("tv_ss_1_up", "0x9F600707");
  //E0E08679 (MSB first)
  preferences.putString("tv_ss_1_dwn", "0x9E610707");
  //E0E0A659 (MSB first)
  preferences.putString("tv_ss_1_lft", "0x9A650707");
  //E0E046B9 (MSB first)
  preferences.putString("tv_ss_1_rht", "0x9D620707");
  //E0E016E9 (MSB first)
  preferences.putString("tv_ss_1_ok", "0x97680707");
  //E0E0E01F (MSB first)
  preferences.putString("tv_ss_1_vu", "0xF8070707");
  //E0E0D02F (MSB first)
  preferences.putString("tv_ss_1_vd", "0xF40B0707");
  //E0E0D22D (MSB first)
  preferences.putString("tv_ss_1_stgs", "0xB44B0707");
  //E0E0807F (MSB first)
  preferences.putString("tv_ss_1_src", "0xFE010707");
  //E0E01AE5 (MSB first)
  preferences.putString("tv_ss_1_bck", "0xA7580707");

  //samsung speaker codes recorded manually...
  //LSB first
  preferences.putString("spkr_ss_1_pwr", "0xE11E2C2C");
  preferences.putString("spkr_ss_1_vu", "0xE8172C2C");
  preferences.putString("spkr_ss_1_vd", "0xE9162C2C");
  preferences.end();
}
