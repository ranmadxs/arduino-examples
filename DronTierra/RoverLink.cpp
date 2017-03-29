#include "RoverLink.h"

RoverLink::RoverLink(){}

String RoverLink::getIndex(){
  //char indexHtml[800];
  String indexHtml = 
"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>Rover Link Message Set</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Rover Link Message Set</h1>\
<table class='sortable'>\
   <thead>\
      <tr>\
         <th class='mavlink_field_header'>CMD ID</th>\
         <th class='mavlink_field_header'>Field Name</th>\
         <th class='mavlink_field_header'>Description</th>\
      </tr>\
   </thead>\
   <tbody>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_GENERIC'>\
         <td class='mavlink_type' valign='top'>0</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_GENERIC</td>\
         <td class='mavlink_comment'>Generic autopilot, full support for everything</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_RESERVED'>\
         <td class='mavlink_type' valign='top'>1</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_RESERVED</td>\
         <td class='mavlink_comment'>Reserved for future use.</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_SLUGS'>\
         <td class='mavlink_type' valign='top'>2</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_SLUGS</td>\
         <td class='mavlink_comment'>SLUGS autopilot, http://slugsuav.soe.ucsc.edu</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_ARDUPILOTMEGA'>\
         <td class='mavlink_type' valign='top'>3</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_ARDUPILOTMEGA</td>\
         <td class='mavlink_comment'>ArduPilotMega / ArduCopter, http://diydrones.com</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_OPENPILOT'>\
         <td class='mavlink_type' valign='top'>4</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_OPENPILOT</td>\
         <td class='mavlink_comment'>OpenPilot, http://openpilot.org</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY'>\
         <td class='mavlink_type' valign='top'>5</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY</td>\
         <td class='mavlink_comment'>Generic autopilot only supporting simple waypoints</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY'>\
         <td class='mavlink_type' valign='top'>6</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY</td>\
         <td class='mavlink_comment'>Generic autopilot supporting waypoints and other simple navigation commands</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_GENERIC_MISSION_FULL'>\
         <td class='mavlink_type' valign='top'>7</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_GENERIC_MISSION_FULL</td>\
         <td class='mavlink_comment'>Generic autopilot supporting the full mission command set</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_INVALID'>\
         <td class='mavlink_type' valign='top'>8</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_INVALID</td>\
         <td class='mavlink_comment'>No valid autopilot, e.g. a GCS or other MAVLink component</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_PPZ'>\
         <td class='mavlink_type' valign='top'>9</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_PPZ</td>\
         <td class='mavlink_comment'>PPZ UAV - http://nongnu.org/paparazzi</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_UDB'>\
         <td class='mavlink_type' valign='top'>10</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_UDB</td>\
         <td class='mavlink_comment'>UAV Dev Board</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_FP'>\
         <td class='mavlink_type' valign='top'>11</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_FP</td>\
         <td class='mavlink_comment'>FlexiPilot</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_PX4'>\
         <td class='mavlink_type' valign='top'>12</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_PX4</td>\
         <td class='mavlink_comment'>PX4 Autopilot - http://pixhawk.ethz.ch/px4/</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_SMACCMPILOT'>\
         <td class='mavlink_type' valign='top'>13</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_SMACCMPILOT</td>\
         <td class='mavlink_comment'>SMACCMPilot - http://smaccmpilot.org</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_AUTOQUAD'>\
         <td class='mavlink_type' valign='top'>14</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_AUTOQUAD</td>\
         <td class='mavlink_comment'>AutoQuad -- http://autoquad.org</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_ARMAZILA'>\
         <td class='mavlink_type' valign='top'>15</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_ARMAZILA</td>\
         <td class='mavlink_comment'>Armazila -- http://armazila.com</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_AEROB'>\
         <td class='mavlink_type' valign='top'>16</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_AEROB</td>\
         <td class='mavlink_comment'>Aerob -- http://aerob.ru</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
      <tr class='mavlink_field' id='MAV_AUTOPILOT_ASLUAV'>\
         <td class='mavlink_type' valign='top'>17</td>\
         <td class='mavlink_name' valign='top'>MAV_AUTOPILOT_ASLUAV</td>\
         <td class='mavlink_comment'>ASLUAV autopilot -- http://www.asl.ethz.ch</td>\
      </tr>\
      <tr>\
         <td></td>\
      </tr>\
      <tr>\
         <td colspan='3'><br></td>\
      </tr>\
   </tbody>\
</table>\
  </body>\
</html>";
  return indexHtml;
}

