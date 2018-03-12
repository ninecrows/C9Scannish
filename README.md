# C9Scannish
A more complete sandbox scanner coded in C# with C++/CLI interop for features unavailable in CLR

11-March-2018

I've been looking at putting together a tool to check, index and de-duplicate files to manage archiving and deplicate removal.

Over the weekend I wrapped this together. Still very rough but has many of the pieces and the hard interop stuff is sketched in. 

There is more native interop code to be added to get access to volume serial numbers and file identity information.

The processing code needs to be pushed onto a worker thread and some sort of progress monitoring needs to get put
into place. 

The back-end should go into MongoDB with indexes to manage access. On the futures list at the moment. I also need to get my MongoDB 
network security figured out so that I can have one target DB on my local network.

Ideally I'd like to index both online and nearline (archive) storage and have a system that allows me to manage duplication of files
while ensuring that I have at least two copies of everything that matters to me (largely my photography archives).

There's still a long way to go, but this code is a good step along the way.

Next step is probably to push the computation and file access onto a worker thread and add a little validity checking for some types 
of files.

Once that's running I'll get the MongoDB back-end set and start pushing data to a persistent store.
