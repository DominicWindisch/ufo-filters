=====
Sinks
=====

Sinks are endpoints and have at least one input but no output.


File writer
===========

.. gobj:class:: write

    Writes input data to the file system. Support for writing depends on compile
    support, however raw (`.raw`) files can always be written. TIFF (`.tif` and
    `.tiff`), HDF5 (`.h5`) and JPEG (`.jpg` and `.jpeg`) might be supported
    additionally.

    .. gobj:prop:: filename:string

        Format string specifying the location and filename pattern of the
        written data. It must contain at most *one* integer format specifier
        that denotes the current index of a series. For example,
        ``"data-%03i.tif"`` produces ``data-001.tif``, ``data-002.tif`` and so
        on. If no specifier is given, the data is written preferably to a single
        file (i.e. multi-tiff, HDF5 data set). If no filename is given the data
        is written as-is to stdout.

    .. gobj:prop:: append:boolean

        Append rather than overwrite if ``TRUE``.

    .. gobj:prop:: bits:uint

        Number of bits to store the data if applicable to the file format.
        Possible values are 8 and 16 which are saved as integer types and 32 bit
        float. By default, the minimum and maximum for scaling is determined
        automatically, however depending on the use case you should override
        this with the ``minimum`` and ``maximum`` properties.

    .. gobj:prop:: minimum:float

        This value will represent zero for discrete bit depths, i.e. 8 and 16
        bit.

    .. gobj:prop:: minimum:float

        This value will represent the largest possible value for discrete bit
        depths, i.e. 8 and 16 bit.

    For JPEG files the following property applies:

    .. gobj:prop:: quality:uint

        JPEG quality value between 0 and 100. Higher values correspond to higher
        quality and larger file sizes.


Memory writer
=============

.. gobj:class:: memory-out

    Writes input to a given memory location. Unlike input and output tasks this
    can be used to interface with other code more directly, e.g. to write into a
    NumPy buffer::

        from gi.repository import Ufo
        import numpy as np
        import tifffile

        ref = tifffile.imread('data.tif')
        a = np.zeros_like(ref)

        pm = Ufo.PluginManager()
        g = Ufo.TaskGraph()
        sched = Ufo.Scheduler()
        read = pm.get_task('read')
        out = pm.get_task('memory-out')

        read.props.path = 'data.tif'
        out.props.pointer = a.__array_interface__['data'][0]
        out.props.max_size = ref.nbytes

        g.connect_nodes(read, out)
        sched.run(g)

        assert np.sum(a - ref) == 0.0

    .. gobj:prop:: pointer:ulong

        Pointer to pre-allocated memory.

    .. gobj:prop:: max-size:ulong

        Size of the pre-allocated memory area in bytes. Data is written up to
        that point only.


Auxiliary sink
==============

Null
====

.. gobj:class:: null

    Eats input and discards it.

    .. gobj:prop:: download:boolean

        If *TRUE* force final data transfer from device to host if necessary.

    .. gobj:prop:: finish:boolean

        Call finish on the associated command queue.

    .. gobj:prop:: durations:boolean

        Print durations computed from timestamps on ``stderr``.
