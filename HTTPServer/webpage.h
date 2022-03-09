const char response[] =
    "<!DOCTYPE html>\r\n"
    "<html>\r\n"
    "<head>\r\n"
    "    <title>Hello from Mbed OS</title>\r\n"
    "    <style>html { font-family: sans-serif; } table { margin-top: 30px; border-collapse: collapse; } th { text-align: left; } th, td { border: solid 1px black; padding: 10px; }</style>\r\n"
    "</head>\r\n"
    "<body>\r\n"
    "<h1>Mbed OS Webserver</h1>\r\n"
    "<button id=\"toggle\">Toggle LED</button>\r\n"
    "<button id=\"stats\">Print Thread Stats</button>\r\n"
    "<div id=\"thread-info\"></div>\r\n"
    "<script>\r\n"
    "var stateArr = [ 'Inactive', 'Ready', 'Running', 'WaitingDelay',\r\n"
    "    'WaitingInterval', 'WaitingOr', 'WaitingAnd', 'WaitingSemaphore',\r\n"
    "    'WaitingMailbox', 'WaitingMutex', 'Deleted' ];\r\n"
    "\r\n"
    "document.querySelector('#toggle').onclick = function() {\r\n"
    "   var x = new XMLHttpRequest(); x.open('POST', '/toggle'); x.send();\r\n"
    "};\r\n"
    "\r\n"
    "document.querySelector('#stats').onclick = function() {\r\n"
    "   var x = new XMLHttpRequest(); \r\n"
    "   x.open('GET', '/api/stats');\r\n"
    "   x.onload = function() {\r\n"
    "       var ti = document.querySelector('#thread-info');\r\n"
    "       ti.innerHTML = '<table><tr><th>Name</th><th>State</th><th>Stack space</th></tr></table>'; // clear out element\r\n"
    "       var tb = ti.querySelector('table');\r\n"
    "       var resp = JSON.parse(x.responseText);\r\n"
    "       for (var ix = 0; ix < resp.length; ix++) {\r\n"
    "           var tr = document.createElement('tr');\r\n"
    "           var nameTd = document.createElement('td');\r\n"
    "           nameTd.textContent = resp[ix].name;\r\n"
    "           var stateTd = document.createElement('td');\r\n"
    "           stateTd.textContent = stateArr[resp[ix].state];\r\n"
    "           var stackTd = document.createElement('td');\r\n"
    "           stackTd.textContent = resp[ix].stack_space;\r\n"
    "           tr.appendChild(nameTd); tr.appendChild(stateTd); tr.appendChild(stackTd);\r\n"
    "           tb.appendChild(tr);\r\n"
    "       }\r\n"
    "   };\r\n"
    "   x.send();\r\n"
    "};\r\n"
    "</script>\r\n"
    "</body>\r\n"
    "</html>\r\n"
    ;
