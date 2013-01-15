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

#ifndef __UFO_FILTER_CV_SHOW_H
#define __UFO_FILTER_CV_SHOW_H

#include <glib.h>
#include <ufo/ufo-filter-sink.h>

#define UFO_TYPE_FILTER_CV_SHOW             (ufo_filter_cv_show_get_type())
#define UFO_FILTER_CV_SHOW(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), UFO_TYPE_FILTER_CV_SHOW, UfoFilterCvShow))
#define UFO_IS_FILTER_CV_SHOW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), UFO_TYPE_FILTER_CV_SHOW))
#define UFO_FILTER_CV_SHOW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), UFO_TYPE_FILTER_CV_SHOW, UfoFilterCvShowClass))
#define UFO_IS_FILTER_CV_SHOW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), UFO_TYPE_FILTER_CV_SHOW))
#define UFO_FILTER_CV_SHOW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), UFO_TYPE_FILTER_CV_SHOW, UfoFilterCvShowClass))

typedef struct _UfoFilterCvShow           UfoFilterCvShow;
typedef struct _UfoFilterCvShowClass      UfoFilterCvShowClass;
typedef struct _UfoFilterCvShowPrivate    UfoFilterCvShowPrivate;

struct _UfoFilterCvShow {
    /*< private >*/
    UfoFilterSink parent_instance;

    UfoFilterCvShowPrivate *priv;
};

/**
 * UfoFilterCvShowClass:
 *
 * #UfoFilterCvShow class
 */
struct _UfoFilterCvShowClass {
    /*< private >*/
    UfoFilterSinkClass parent_class;
};

GType ufo_filter_cv_show_get_type(void);
UfoFilter *ufo_filter_plugin_new(void);

#endif
