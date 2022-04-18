#ifndef _BUILDINFO_H_
#define _BUILDINFO_H_
#pragma once

typedef struct {
    const char *name;
    const char *version;
    const char *repoident;
    const char *date;
    const char *time;
    const char *hostname;
} BuildInfo;

const BuildInfo *getBuildInfo();

#endif
