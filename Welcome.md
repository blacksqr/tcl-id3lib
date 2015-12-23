# simple stuff now... #

---

**tcl namespace id3**
  * proc close {} { return bool }
  * proc config {p\_confid p\_value} { return bool }
  * proc flush {} { return bool }
  * proc get {p\_tagid} { return value }
  * proc isset {p\_tagid} { return bool }
  * proc open {p\_fn} { return bool }
  * proc set {p\_tagid p\_value} { return bool }
  * proc strip {} { return bool }
  * proc write {} { return bool }

_id3::close_
<br>
closes file and deletes remaining id3tag.<br>
returns success.<br>
<br>

<br>
<i>id3::config</i>
<br>
sets configuration for strip and write commands.<br>
<ul><li>deletemask { id3v1, id3v2, both }<br>
</li><li>updatemask { id3v1, id3v2, both }<br>
returns success.<br>
<br></li></ul>

<br>
<i>id3::flush</i>
<br>
clears internal tag queue.<br>
returns success.<br>
<br>

<br>
<i>id3::get</i>
<br>
finds tag by tagid and returns text field content or "not found".<br>
<br>

<br>
<i>id3::isset</i>
<br>
finds tag by tagid and returns success.<br>
<br>

<br>
<i>id3::open</i>
<br>
loads mp3 file and links it with id3lib.<br>
returns success.<br>
<br>

<br>
<i>id3::set</i>
<br>
sets tag frame by tagid or if no valid id it sets a usertext frame with its name to the specified value.<br>
returns success.<br>
<br>

<br>
<i>id3::strip</i>
<br>
clears id3 frames specified by id3::config and returns success.<br>
<br>

<br>
<i>id3::write</i>
<br>
updates id3 frames specified by id3::config from the tag queue and returns success.<br>
<br>