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

#include <gmodule.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ufo/ufo-resource-manager.h>
#include <ufo/ufo-filter.h>
#include <ufo/ufo-buffer.h>
#include "ufo-filter-pipe-output.h"

/**
 * SECTION:ufo-filter-pipe-output
 * @Short_description: Write input to a named pipe
 * @Title: pipeoutput
 *
 * To communicate with foreign processes a named pipe (also called FIFO) can be
 * used. To create a named pipe call mkfifo FILENAME and point to FILENAME with
 * #UfoFilterPipeOutput:pipe-name.
 */

struct _UfoFilterPipeOutputPrivate {
    gchar *pipe_name;
    int pipe_fd;
};

G_DEFINE_TYPE(UfoFilterPipeOutput, ufo_filter_pipe_output, UFO_TYPE_FILTER_SINK)

#define UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), UFO_TYPE_FILTER_PIPE_OUTPUT, UfoFilterPipeOutputPrivate))

enum {
    PROP_0,
    PROP_PIPE_NAME,
    N_PROPERTIES
};

static GParamSpec *pipe_output_properties[N_PROPERTIES] = { NULL, };

static void
ufo_filter_pipe_output_initialize(UfoFilterSink *filter, UfoBuffer *inputs[], GError **error)
{
    UfoFilterPipeOutputPrivate *priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(filter);
    if (priv->pipe_name == NULL)
        /* TODO: output error */
        return;

    priv->pipe_fd = open(priv->pipe_name, O_WRONLY);
}

static void
ufo_filter_pipe_output_consume(UfoFilterSink *filter, UfoBuffer *inputs[], GError **error)
{
    UfoFilterPipeOutputPrivate *priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(filter);
    guint *dim_size = NULL;
    guint num_dims = 0;
    cl_command_queue cmd_queue = ufo_filter_get_command_queue (UFO_FILTER (filter));

    ufo_buffer_get_dimensions(inputs[0], &num_dims, &dim_size);
    const gssize size = (gssize) (sizeof(float) * dim_size[0] * dim_size[1]);
    gchar *data = (gchar *) ufo_buffer_get_host_array(inputs[0], cmd_queue);
    gssize written = 0;

    while (written < size) {
        gssize result = (gssize) write(priv->pipe_fd, data + written, (gsize) (size - written));

        if (result < 0) {
            /* TODO: create proper error */
            g_error("Error writing to pipe %s\n", priv->pipe_name);
            return;
        }

        written += result;
    }
}

static void
ufo_filter_pipe_output_finalize(GObject *object)
{
    UfoFilterPipeOutputPrivate *priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE (object);

    close (priv->pipe_fd);

    G_OBJECT_CLASS (ufo_filter_pipe_output_parent_class)->finalize (object);
}

static void 
ufo_filter_pipe_output_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    UfoFilterPipeOutputPrivate *priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(object);

    switch (property_id) {
        case PROP_PIPE_NAME:
            g_free(priv->pipe_name);
            priv->pipe_name = g_value_dup_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void 
ufo_filter_pipe_output_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    UfoFilterPipeOutputPrivate *priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(object);

    switch (property_id) {
        case PROP_PIPE_NAME:
            g_value_set_string(value, priv->pipe_name);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void 
ufo_filter_pipe_output_class_init(UfoFilterPipeOutputClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    UfoFilterSinkClass *filter_class = UFO_FILTER_SINK_CLASS(klass);

    gobject_class->set_property = ufo_filter_pipe_output_set_property;
    gobject_class->get_property = ufo_filter_pipe_output_get_property;
    gobject_class->finalize = ufo_filter_pipe_output_finalize;
    filter_class->initialize = ufo_filter_pipe_output_initialize;
    filter_class->consume = ufo_filter_pipe_output_consume;

    pipe_output_properties[PROP_PIPE_NAME] = 
        g_param_spec_string("pipe-name",
            "Path to the named pipe created with mkfifo",
            "Path to the named pipe created with mkfifo",
            "",
            G_PARAM_READWRITE);

    g_object_class_install_property(gobject_class, PROP_PIPE_NAME, pipe_output_properties[PROP_PIPE_NAME]);

    g_type_class_add_private(gobject_class, sizeof(UfoFilterPipeOutputPrivate));
}

static void 
ufo_filter_pipe_output_init(UfoFilterPipeOutput *self)
{
    UfoFilterPipeOutputPrivate *priv = self->priv = UFO_FILTER_PIPE_OUTPUT_GET_PRIVATE(self);
    UfoInputParameter input_params[] = {{2, UFO_FILTER_INFINITE_INPUT}};

    priv->pipe_name = NULL;

    ufo_filter_register_inputs (UFO_FILTER (self), 1, input_params);
}

G_MODULE_EXPORT UfoFilter *
ufo_filter_plugin_new(void)
{
    return g_object_new(UFO_TYPE_FILTER_PIPE_OUTPUT, NULL);
}

