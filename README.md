# ![Pendrive Guard logo](pendriveGuard.png) Pendrive Guard 

## What?

This is a project done in my spare time as **a teenager in ~2008.** It was my protection from usb drive infections - much better than existing antiviruses at that time!

It is for _archive and nostalgy reason_.

Code was kept on gmail as attachment (pre-gdrive/gitlab era...) and lost access as was unable to download it due to some policy. Miraculously, recently discovered workaround to retrieve it using mobile, so here it is.

It is a tray app done in pure Win32 API :)

## Why?

At that time I used a lot moving files between school computers and my private PC on pendrives.

That was a disaster! as often there were worms/viruses that used autorun Windows to infect machines.

To end this I created this small program which monitored and tried to act before infection can begin.

I have also discovered that creating "autorun.inf" directory breaks logic so it also tries to add it as protection.

Also, this was a _nice guy_ way, as the second one was to create my own virus - ([amoeba](https://github.com/rAum/amoeba)) - which hunts other viruses...
