# Freebusy to PDF

Here is a simple program for generating a PDF from the free/busy endpoint of a CalDAV server.

See here some example output:

![Example output](doc/example-freebusy.png)

# Why should we do this?

GNOME Evolution has the ability to print calendars, but it doesn't help us understand the temporal dimension of things. It looks more like a list of tasks. 

![GNOME Evolution example](./doc/alternatives/gnome-evolution/week.png)
![GNOME Evolution work week example](./doc/alternatives/gnome-evolution/work-week.png)

MacOS iCalendar has the ability to print calendars, and they look rather pretty. It is, however, something of a pain to synchronize my calendar over there and then go through the UI to export the PDF. Perhaps this could be tackled with `osascript`; it appears that `osascript` could work through `ssh`... Something to think about in any case. 

![MacOS iCalendar example](./doc/alternatives/macos-icalendar/icalendar.png)

# Usage

```
./range-query 'last Sunday' Sunday Personal Work
```

# TODO

- Split into multiple binaries
  1. Read FREEBUSY response from CalDAV server (or local FREEBUSY file)
  2. Read busy times from user specified struct
- Take in start and end times from argv
- Take in calendar paths from argv
