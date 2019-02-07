# /opt/SVXLink/share/svxlink/events.d/local/EchoLink.tcl

namespace eval EchoLink {
  proc activating_module {} { }
  proc deactivating_module {} { }
  proc timeout {} { }

  proc disconnected {call} { }
  proc remote_connected {call} { }
  proc remote_greeting {call} { }

  proc link_inactivity_timeout {} { }
}
