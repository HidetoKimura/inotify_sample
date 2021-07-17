#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

void inotify_events_loop( int fd );
int inotify_read_events( int fd );

int main( int argc, char **argv ) 
{
    int fd = -1;
    int wd = -1;
    char *filename = NULL;

    if  ( argc != 2 ) {
        fprintf( stderr, "Usage:%s filepath\n", argv[0]);
        goto ERROR;
    } 

    filename = argv[1];

    if( (fd = inotify_init()) == -1 ) {
        perror( "inotify_init" );
        goto ERROR;
    }
    
    wd = inotify_add_watch( fd, argv[1], IN_ALL_EVENTS);

    inotify_events_loop( fd );

    inotify_rm_watch( fd, wd );
    close( fd );

    return 0;
ERROR:
    return 1;
}

void inotify_events_loop( int fd )
{
    int count = -1;
    while(1) {
        count = inotify_read_events( fd );
    }
}



int inotify_read_events( int fd )
{
    int count = 0;
    int i = 0;
    char buffer[BUF_LEN];
    int length = 0;
    char *event_mask_name;

    if( (length = read( fd, buffer, BUF_LEN ) ) < 0 ) return count;

    while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];

#if 0
struct inotify_event {
	__s32		wd;		/* watch descriptor */
	__u32		mask;		/* watch mask */
	__u32		cookie;		/* cookie to synchronize two events */
	__u32		len;		/* length (including nulls) of name */
	char		name[0];	/* stub for possible name */
};

/* the following are legal, implemented events that user-space can watch for */
#define IN_ACCESS		    0x00000001	/* File was accessed */
#define IN_MODIFY		    0x00000002	/* File was modified */
#define IN_ATTRIB		    0x00000004	/* Metadata changed */
#define IN_CLOSE_WRITE		0x00000008	/* Writtable file was closed */
#define IN_CLOSE_NOWRITE	0x00000010	/* Unwrittable file closed */
#define IN_OPEN			    0x00000020	/* File was opened */
#define IN_MOVED_FROM		0x00000040	/* File was moved from X */
#define IN_MOVED_TO		    0x00000080	/* File was moved to Y */
#define IN_CREATE		    0x00000100	/* Subfile was created */
#define IN_DELETE		    0x00000200	/* Subfile was deleted */
#define IN_DELETE_SELF		0x00000400	/* Self was deleted */
#define IN_MOVE_SELF		0x00000800	/* Self was moved */
#define IN_UNMOUNT		    0x00002000	/* Backing fs was unmounted */
#define IN_Q_OVERFLOW		0x00004000	/* Event queued overflowed */
#define IN_IGNORED	    	0x00008000	/* File was ignored */
#define IN_ONLYDIR		    0x01000000	/* only watch the path if it is a directory */
#define IN_DONT_FOLLOW		0x02000000	/* don't follow a sym link */
#define IN_EXCL_UNLINK		0x04000000	/* exclude events on unlinked objects */
#define IN_MASK_ADD		    0x20000000	/* add to the mask of an already existing watch */
#define IN_ISDIR	    	0x40000000	/* event occurred against dir */
#define IN_ONESHOT	    	0x80000000	/* only send event once */

define IN_ALL_EVENTS	(IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | \
			 IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | \
			 IN_MOVED_TO | IN_DELETE | IN_CREATE | IN_DELETE_SELF | \
			 IN_MOVE_SELF
#endif
        event_mask_name = "";
        if ( event->mask & IN_ACCESS ) {
            event_mask_name = "IN_ACCESS";
        }
        if ( event->mask & IN_MODIFY ) {
            event_mask_name = "IN_MODIFY";
        }
        if ( event->mask & IN_ATTRIB ) {
            event_mask_name = "IN_ATTRIB";
        }
        if ( event->mask & IN_CLOSE_WRITE ) {
            event_mask_name = "IN_CLOSE_WRITE";
        }
        if ( event->mask & IN_CLOSE_NOWRITE ) {
            event_mask_name = "IN_CLOSE_NOWRITE";
        }
        if ( event->mask & IN_OPEN ) {
            event_mask_name = "IN_OPEN";
        }
        if ( event->mask & IN_MOVED_FROM ) {
            event_mask_name = "IN_MOVED_FROM";
        }
        if ( event->mask & IN_MOVED_TO ) {
            event_mask_name = "IN_MOVED_TO";
        }
        if ( event->mask & IN_MOVED_FROM ) {
            event_mask_name = "IN_MOVED_FROM";
        }
        if ( event->mask & IN_CREATE ) {
            event_mask_name = "IN_CREATE";
        }
        if ( event->mask & IN_DELETE ) {
            event_mask_name = "IN_DELETE";
        }
        if ( event->mask & IN_DELETE_SELF ) {
            event_mask_name = "IN_DELETE_SELF";
        }
        if ( event->mask & IN_MOVE_SELF ) {
            event_mask_name = "IN_MOVE_SELF";
        }
        printf("event->wd=%d, mask=0x%x(%s), cookie=0x%x, len=%d, name=%s \n", 
            event->wd,
            event->mask,
            event_mask_name,
            event->cookie,
            event->len,
            event->name);

        i += EVENT_SIZE + event->len;
        count++;
    }
    return count;
}