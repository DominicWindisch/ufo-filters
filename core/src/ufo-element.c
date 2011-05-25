#include "ufo-element.h"
#include "ufo-filter.h"

static void ufo_element_default_init(UfoElementInterface *iface);
G_DEFINE_INTERFACE(UfoElement, ufo_element, G_TYPE_OBJECT)

/* 
 * Public Interface
 */

/**
 * ufo_element_set_input_queue:
 * @element: A #UfoElement
 * @queue: (transfer full): A #GAsyncQueue
 *
 * Sets @queue that is used for an element to pop input buffers from
 */
/**
 * \brief Set an input queue
 * \public \memberof UfoElement
 * \param[in] element UfoElement whose input queue is changed
 * \param[in] queue a GAsyncQueue
 */
void ufo_element_set_input_queue(UfoElement *element, GAsyncQueue *queue)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->set_input_queue != NULL)
        iface->set_input_queue(element, queue);
}

/**
 * \brief Set an output queue
 * \public \memberof UfoElement
 * \param[in] element UfoElement whose output queue is changed
 * \param[in] queue a GAsyncQueue
 */
void ufo_element_set_output_queue(UfoElement *element, GAsyncQueue *queue)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->set_output_queue != NULL)
        iface->set_output_queue(element, queue);
}

/**
 * ufo_element_get_input_queue:
 * @element: A #UfoElement
 * Returns: (transfer none): A #GAsyncQueue that is used to pop input buffers from
 */
/**
 * \brief Get the input queue
 * \public \memberof UfoElement
 * \param[in] element UfoElement whose output queue returned
 * \return A GAsyncQueue
 */
GAsyncQueue *ufo_element_get_input_queue(UfoElement *element)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->get_input_queue != NULL)
        return iface->get_input_queue(element);
    return NULL;
}

/**
 * \brief Get the output queue
 * \public \memberof UfoElement
 * \param[in] element UfoElement whose output queue returned
 * \return A GAsyncQueue
 */
GAsyncQueue *ufo_element_get_output_queue(UfoElement *element)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->get_output_queue != NULL)
        return iface->get_output_queue(element);
    return NULL;
}

void ufo_element_set_command_queue(UfoElement *element, gpointer command_queue)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->set_command_queue != NULL)
        iface->set_command_queue(element, command_queue);
}

gpointer ufo_element_get_command_queue(UfoElement *element)
{
    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->get_command_queue != NULL)
        return iface->get_command_queue(element);
    return NULL;
}

void ufo_element_print(UfoElement * element)
{
    g_return_if_fail(UFO_IS_ELEMENT(element));

    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->print != NULL)
        iface->print(element);
}

/**
 * \brief Execute an element
 *
 * Processing an UfoElement means to process an associated UfoFilter or the
 * children of UfoSplit or UfoSequence.
 *
 * \public \memberof UfoElement
 * \param[in] element An UfoElement to process
 */
void ufo_element_process(UfoElement *element)
{
    g_return_if_fail(UFO_IS_ELEMENT(element));

    UfoElementInterface *iface = UFO_ELEMENT_GET_INTERFACE(element);
    if (iface->process != NULL)
        iface->process(element);
    else
        g_message("UfoElement::process not implemented");
}


/*
 * Type/Class Initialization
 */
static void ufo_element_default_init(UfoElementInterface *iface)
{
}

