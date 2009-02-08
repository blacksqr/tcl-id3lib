# test environment for tcl_id3lib

load tcl_id3lib.dll

puts "set deletemask"
puts [id3::config deletemask both]
puts "set updatemask"
puts [id3::config updatemask both]
puts "open test.mp3"
puts [id3::open "test.mp3"]
puts "strip"
puts [id3::strip]
puts "set TPE1"
puts [id3::set TPE1 "Scott Brown"]
puts "set TIT2"
puts [id3::set TIT2 "F0ckin Mix"]
puts "write"
puts [id3::write]
puts "get TPE1"
puts [id3::get TPE1]
puts "get TIT2"
puts [id3::get TIT2]
puts "close"
puts [id3::close]