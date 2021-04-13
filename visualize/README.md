# Why should we do this?

GNOME Evolution has the ability to print calendars, but it doesn't help us understand the temporal dimension of things. It looks more like a list of tasks. 

MacOS iCalendar has the ability to print calendars, and they look rather pretty. It is, however, something of a pain to synchronize my calendar over there and then go through the UI to export the PDF. Perhaps this could be tackled with `osascript`; it appears that `osascript` could work through `ssh`... Something to think about in any case. 

# Things to take in

- The paper size
- The week
- Start and end times wishing to be represented
- The events themselves

# Things to draw

- Gridlines 

# Things I learned

https://stackoverflow.com/questions/29354780/flexible-array-member-in-a-nested-struct

> A structure or union shall not contain a member with incomplete or function type (hence, a structure shall not contain an instance of itself, but may contain a pointer to an instance of itself), except that the last member of a structure with more than one named member may have incomplete array type; such a structure (and any union containing, possibly recursively, a member that is such a structure) shall not be a member of a structure or an element of an array.
