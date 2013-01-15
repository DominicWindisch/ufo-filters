/*
 * Copyright (C) 2011-2013 Karlsruhe Institute of Technology
 *
 * This file is part of Ufo.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __UFO_FILTER_DEMUX_H
#define __UFO_FILTER_DEMUX_H

#include <glib.h>
#include <ufo/ufo-filter.h>

#define UFO_TYPE_FILTER_DEMUX             (ufo_filter_demux_get_type())
#define UFO_FILTER_DEMUX(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), UFO_TYPE_FILTER_DEMUX, UfoFilterDemux))
#define UFO_IS_FILTER_DEMUX(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), UFO_TYPE_FILTER_DEMUX))
#define UFO_FILTER_DEMUX_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), UFO_TYPE_FILTER_DEMUX, UfoFilterDemuxClass))
#define UFO_IS_FILTER_DEMUX_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), UFO_TYPE_FILTER_DEMUX))
#define UFO_FILTER_DEMUX_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), UFO_TYPE_FILTER_DEMUX, UfoFilterDemuxClass))

typedef struct _UfoFilterDemux           UfoFilterDemux;
typedef struct _UfoFilterDemuxClass      UfoFilterDemuxClass;
typedef struct _UfoFilterDemuxPrivate    UfoFilterDemuxPrivate;

struct _UfoFilterDemux {
    /*< private >*/
    UfoFilter parent_instance;

    UfoFilterDemuxPrivate *priv;
};

/**
 * UfoFilterCvShowClass:
 *
 * #UfoFilterCvShow class
 */
struct _UfoFilterDemuxClass {
    /*< private >*/
    UfoFilterClass parent_class;
};

GType ufo_filter_demux_get_type(void);
UfoFilter *ufo_filter_plugin_new(void);

#endif
