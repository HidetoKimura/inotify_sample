# inotify_sample

# How to build
~~~
$ mkdir buid
$ cd build
$ cmake ..
$ make
~~~
# How to use
~~~
$ mkdir -p /tmp/event/test
$ ./inotify_sample /tmp/event
event->wd=1, mask=0x40000200(IN_DELETE), cookie=0x0, len=16, name=test 
~~~
- launch other terminal.
~~~
$ rmdir /tmp/event/test
~~~
