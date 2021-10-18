# neuromag2mne
The goal of this application is to be able to get data from an acquisition machine and put is somewhere. 

### Design
As it stands now, we envision the application to be a collection of "watchers" that react to something and then call some callback function. Right now, we have a CommandWatcher and a DataWatcher, which monitor the telnet server and the shared memory respectivley.

### Constraints
This needs to be built on a machine running a version of RHEL that is over a decade old, and a version of gcc that supports, at most C++ 03. And no cmake.