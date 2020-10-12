# cam-motion-mon
Camera motion monitor service is a WPEFramework based plugin that is used to monitor the motion capture of a Camera and download the image to show notification on the TV.

## APIs
Activate Plugin

Command - { "jsonrpc":"2.0", "id":3, "method":"Controller.1.activate", "params":{"callsign":"CameraMotionMonitor"} }

Response - {"jsonrpc":"2.0","id":3,"result":null}

Deactivate Plugin

Command - { "jsonrpc":"2.0", "id":3, "method":"Controller.1.deactivate", "params":{"callsign":"CameraMotionMonitor"} }

Response - {"jsonrpc":"2.0","id":3,"result":null}

### Methods
1. sendPath

A post method to send the IP address and the path where the captured image resides

JSON RPC:

command - { "jsonrpc":"2.0", "id":4, "method":"CameraMotionMonitor.1.sendPath", "params":{"ipaddress":"192.168.xx.yy", "imagepath":"image/path", "filename":"filename.jpg"} }

response - { "jsonrpc":"2.0", "success":true}

### Events
1. onMotionCaptured

A event to send across saying the motion was captured
