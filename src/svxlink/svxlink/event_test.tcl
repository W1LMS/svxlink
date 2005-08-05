#!/usr/bin/tclsh

proc playFile {filename} {
  puts "playFile(\"$filename\");";
  if {[file exists $filename] != 1} {
    puts "*** ERROR: file not found: $filename";
    exit 1;
  }
}


proc playTone {fq amp len} {
  puts "playTone($fq, $amp, $len);";
}


proc playSilence {milliseconds} {
  puts "playSilence($milliseconds);";
}


proc reportActiveModuleState {} {
  puts "reportActiveModuleState;";
}


proc SimplexLogic {} {
  puts "--- SimplexLogic::startup";
  SimplexLogic::startup;
  puts "";

  puts "--- SimplexLogic::no_such_module";
  SimplexLogic::no_such_module 1;
  puts "";

  puts "--- SimplexLogic::manual_identification";
  SimplexLogic::manual_identification;
  puts "";

  puts "--- SimplexLogic::send_rgr_sound";
  SimplexLogic::send_rgr_sound;
  puts "";

  #puts "--- SimplexLogic::no_such_module";
  #SimplexLogic::no_such_module 1;
  #puts "";

  puts "--- SimplexLogic::macro_empty";
  SimplexLogic::macro_empty;
  puts "";

  puts "--- SimplexLogic::macro_not_found";
  SimplexLogic::macro_not_found;
  puts "";

  puts "--- SimplexLogic::macro_syntax_error";
  SimplexLogic::macro_syntax_error;
  puts "";

  puts "--- SimplexLogic::macro_module_not_found";
  SimplexLogic::macro_module_not_found;
  puts "";

  puts "--- SimplexLogic::macro_module_activation_failed";
  SimplexLogic::macro_module_activation_failed;
  puts "";

  puts "--- SimplexLogic::macro_another_active_module";
  SimplexLogic::macro_another_active_module;
  puts "";

  puts "--- SimplexLogic::periodic_identify";
  SimplexLogic::periodic_identify;
  puts "";

  puts "--- SimplexLogic::command_failed";
  SimplexLogic::unknown_command 123;
  puts "";

  puts "--- SimplexLogic::command_failed";
  SimplexLogic::command_failed;
  puts "";

  puts "--- SimplexLogic::activating_link";
  SimplexLogic::activating_link "TEST";
  puts "";

  puts "--- SimplexLogic::deactivating_link";
  SimplexLogic::deactivating_link "TEST";
  puts "";

  puts "--- SimplexLogic::link_not_active";
  SimplexLogic::link_not_active "TEST";
  puts "";

  puts "--- SimplexLogic::link_already_active";
  SimplexLogic::link_already_active "TEST";
  puts "";
}


proc RepeaterLogic {} {
  puts "--- RepeaterLogic::startup";
  RepeaterLogic::startup;
  puts "";

  puts "--- RepeaterLogic::no_such_module";
  RepeaterLogic::no_such_module 1;
  puts "";

  puts "--- RepeaterLogic::manual_identification";
  RepeaterLogic::manual_identification;
  puts "";

  puts "--- RepeaterLogic::send_rgr_sound";
  RepeaterLogic::send_rgr_sound;
  puts "";

  #puts "--- RepeaterLogic::no_such_module";
  #RepeaterLogic::no_such_module 1;
  #puts "";

  puts "--- RepeaterLogic::macro_empty";
  RepeaterLogic::macro_empty;
  puts "";

  puts "--- RepeaterLogic::macro_not_found";
  RepeaterLogic::macro_not_found;
  puts "";

  puts "--- RepeaterLogic::macro_syntax_error";
  RepeaterLogic::macro_syntax_error;
  puts "";

  puts "--- RepeaterLogic::macro_module_not_found";
  RepeaterLogic::macro_module_not_found;
  puts "";

  puts "--- RepeaterLogic::macro_module_activation_failed";
  RepeaterLogic::macro_module_activation_failed;
  puts "";

  puts "--- RepeaterLogic::macro_another_active_module";
  RepeaterLogic::macro_another_active_module;
  puts "";

  puts "--- RepeaterLogic::command_failed";
  RepeaterLogic::unknown_command 123;
  puts "";

  puts "--- RepeaterLogic::command_failed";
  RepeaterLogic::command_failed;
  puts "";

  puts "--- RepeaterLogic::activating_link";
  RepeaterLogic::activating_link "TEST";
  puts "";

  puts "--- RepeaterLogic::deactivating_link";
  RepeaterLogic::deactivating_link "TEST";
  puts "";

  puts "--- RepeaterLogic::link_not_active";
  RepeaterLogic::link_not_active "TEST";
  puts "";

  puts "--- RepeaterLogic::link_already_active";
  RepeaterLogic::link_already_active "TEST";
  puts "";

  puts "--- RepeaterLogic::periodic_identify";
  RepeaterLogic::periodic_identify;
  puts "";
  
  puts "--- RepeaterLogic::repeater_up";
  RepeaterLogic::repeater_up;
  puts "";
  
  puts "--- RepeaterLogic::repeater_down";
  RepeaterLogic::repeater_down;
  puts "";
  
  puts "--- RepeaterLogic::repeater_idle";
  RepeaterLogic::repeater_idle;
  puts "";
}


proc Help {} {
  puts "--- Help::activating_module";
  Help::activating_module;
  puts "";

  puts "--- Help::deactivating_module";
  Help::deactivating_module;
  puts "";

  puts "--- Help::timeout";
  Help::timeout;
  puts "";

  puts "--- Help::play_help";
  Help::play_help;
  puts "";

  puts "--- Help::choose_module";
  Help::choose_module [list 0 Help 1 Parrot 2 EchoLink];
  puts "";

  puts "--- Help::no_such_module";
  Help::no_such_module 1;
  puts "";
}


proc Parrot {} {
  puts "--- Parrot::activating_module";
  Parrot::activating_module;
  puts "";

  puts "--- Parrot::deactivating_module";
  Parrot::deactivating_module;
  puts "";

  puts "--- Parrot::timeout";
  Parrot::timeout;
  puts "";

  puts "--- Parrot::play_help";
  Parrot::play_help;
  puts "";

  puts "--- Parrot::spell_digits";
  Parrot::spell_digits "0123456789";
  puts "";
}


proc EchoLink {} {
  puts "--- EchoLink::activating_module";
  EchoLink::activating_module;
  puts "";

  puts "--- EchoLink::deactivating_module";
  EchoLink::deactivating_module;
  puts "";

  puts "--- EchoLink::timeout";
  EchoLink::timeout;
  puts "";

  puts "--- EchoLink::play_help";
  EchoLink::play_help;
  puts "";

  puts "--- EchoLink::list_connected_stations";
  EchoLink::list_connected_stations [list SM0SVX *ECHOTEST* SM3SVX-L SM3SVX-R];
  puts "";

  puts "--- EchoLink::directory_server_offline";
  EchoLink::directory_server_offline;
  puts "";

  puts "--- EchoLink::no_more_connections_allowed";
  EchoLink::no_more_connections_allowed;
  puts "";

  puts "--- EchoLink::status_report";
  EchoLink::status_report;
  puts "";

  puts "--- EchoLink::station_id_not_found";
  EchoLink::station_id_not_found 12345;
  puts "";

  puts "--- EchoLink::lookup_failed";
  EchoLink::lookup_failed 12345;
  puts "";

  puts "--- EchoLink::self_connect";
  EchoLink::self_connect;
  puts "";

  puts "--- EchoLink::already_connected_to";
  EchoLink::already_connected_to SM0SVX;
  puts "";

  puts "--- EchoLink::internal_error";
  EchoLink::internal_error;
  puts "";

  puts "--- EchoLink::connecting_to";
  EchoLink::connecting_to SM0SVX;
  puts "";

  puts "--- EchoLink_disconnected";
  EchoLink::disconnected SM0SVX;
  puts "";

  puts "--- EchoLink::remote_connected";
  EchoLink::remote_connected SM0SVX;
  puts "";

  puts "--- EchoLink::connected";
  EchoLink::connected;
  puts "";

  puts "--- EchoLink::link_inactivity_timeout";
  EchoLink::link_inactivity_timeout;
  puts "";

  puts "--- EchoLink::remote_greeting";
  EchoLink::remote_greeting;
  puts "";

  puts "--- EchoLink::reject_remote_connection";
  EchoLink::reject_remote_connection;
  puts "";

  puts "--- EchoLink::remote_timeout";
  EchoLink::remote_timeout;
  puts "";
}

if {$argc < 1} {
  puts "Usage: $argv0 <path to events.tcl>";
  exit 1;
}

set mycall "SM0XXX";
set report_ctcss 136.5;
set active_module "EchoLink";
set script_path [lindex $argv 0];
set is_core_event_handler 1;

source [lindex $argv 0];

set EchoLink::num_connected_stations 2;

SimplexLogic;
RepeaterLogic;
Help;
Parrot;
EchoLink;

