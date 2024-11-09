Practical Applications
======================

This section demonstrates a few ways that ShippingLanes `Route` objects can be used in supply chain analysis.

Plotting Routes with CoordinatePaths
----------------

The primary purpose of the `CoordinatePath` attribute is to visualize routes. There are many modules that can help with this endeavor - this tutorial will use `plotly.express` for simplicity.
To get 


.. code-block:: python

   from ShippingLanes import findRoutes
   from geopy.geocoders import Nominatim
   import plotly.express as px
   import pandas as pd
   
   geolocator = Nominatim(user_agent="TestApp")
   
   def GetCoords(origin, destination):
       origin = geolocator.geocode(origin)
       destination = geolocator.geocode(destination)
       return [[origin.latitude, origin.longitude, destination.latitude, destination.longitude]]
   
   
   def plotRoute(origin, destination):
       
       coordinates = GetCoords(origin,destination)
       route = findRoutes(coordinates)[0]
       coordinatePath = route.CoordinatePath
       distance = route.Distance
       
       df = pd.DataFrame(coordinatePath, columns=["lat", "lon"])
   
       # Create the route plot
       fig = px.line_geo(df, lat="lat", lon="lon", projection="albers usa")
       
       # Customize layout
       fig.update_layout(
           title="",
           height=600
       )
   
       print("Your origin is: {}".format(origin))
       print("Your destination is: {}".format(destination))
       print("Your driving distance is: {}".format(distance))
       fig.show()
       return None
   
   
   origin = 'Chicago'
   destination = 'Boulder CO'
   
   plotRoute(origin, destination)


This will generate the following plot:

[Placeholder Image]

We can compare this against a premium mapping service like Google maps:

[Placeholder Image]


Identifying Synergies with NodePaths
--------------------------

The `compare_routes` function in `ShippingLanes` allows you to analyze and compare multiple routes. You can use this to determine optimal paths or identify key differences between alternate routes.

.. code-block:: python

    from ShippingLanes import compare_routes

    # Example route data
    route1 = [...]
    route2 = [...]

    # Compare the routes
    results = compare_routes(route1, route2)

    # Display comparison results
    print(results)

This function provides a detailed comparison of each route, highlighting metrics such as distance, time, or other relevant attributes.

Conclusion
----------

Using `ShippingLanes`, you can easily plot complex graphs and perform detailed comparisons between routes, giving you valuable insights into optimal paths and shipping strategies.
