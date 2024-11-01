Usage
=====

.. _installation:

Installation
------------

To use ShippingLanes, first install it using pip:

.. code-block:: console

   (.venv) $ pip install ShippingLanes


Initialization
----------------

At this time, ShippingLanes only contains one major functionality: to convert latitude and longitude pairs into meaningful routes.

As such, it is easiest to directly import the ``ShippingLanes.findRoutes()`` method into your project as follows:


>>> from ShippingLanes import findRoutes


