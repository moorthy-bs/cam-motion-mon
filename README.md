# cam-motion-mon
Camera motion monitor service is a WPEFramework based plugin that is used to monitor the motion capture of a Camera and download the image to show notification on the TV.

## APIs

### Methods
1. sendPath

A post method to send the IP address and the path where the captured image resides

JSON RPC:

command - { "jsonrpc":"2.0", "id":4, "method":CamMotionMonitor.1.sendPath", "params":{"ipAddress":"192.168.xx.yy", "path":"image/path", "file":"filename.jpg"}}

response - { "jsonrpc":"2.0", "success":true}

### Events
1. onMotionCaptured

A event to send across saying the motion was captured
