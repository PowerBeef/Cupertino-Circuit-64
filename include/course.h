#ifndef COURSE_H
#define COURSE_H

#include <libultraship.h>
#include <libultra/gbi.h>
#include <macros.h>

/**
 * @file Include for course gfx.inc.c.
 */

/**
 * @brief A structure representing a section of a race track.
 */
typedef struct {
    Gfx* addr;          ///< A pointer to the display list for this track section.
    u8 surfaceType;     ///< The type of surface for this section (e.g., asphalt, grass).
    u8 sectionId;       ///< The ID of this track section.
    u16 flags;          ///< Flags associated with this track section.
} TrackSections;

#endif // COURSE_H
