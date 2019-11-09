#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>


enum
{
    GR_OFFSET = 3,
    US_OFFSET = 6
};


struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

static int is_in_group(int gid_count, unsigned gid, unsigned *gids) {
    for (int i = 0; i < gid_count; i++) {
        if (gids[i] == gid) {
            return 1;
        }
    }

    return 0;
}

static int is_user(unsigned fuid, unsigned uid) {
    return fuid == uid;
}

static int is_rights(int faccess, int access, int offset) {
    return (access & (faccess >> offset)) == access;
}

int myaccess(const struct stat *stb, const struct Task *task, int access) {
    int usr = is_user(stb->st_uid, task->uid);
    int grp = is_in_group(task->gid_count, stb->st_gid, task->gids);


    if (task->uid == 0) {
        return 1;
    }

    if (usr) {
        return is_rights(stb->st_mode, access, US_OFFSET);
    }
    if (grp) {
        return is_rights(stb->st_mode, access, GR_OFFSET);
    }
    return is_rights(stb->st_mode, access, 0);
}
