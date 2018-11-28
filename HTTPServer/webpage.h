char response[] =
    "<html>"
    "<head><title>Hello from mbed</title></head>"
    "<body>"
    "<h1>mbed webserver</h1>"
    "<button id=\"toggle\">Toggle LED</button>"
    "<script>document.querySelector('#toggle').onclick = function() {"
    "var x = new XMLHttpRequest(); x.open('POST', '/toggle'); x.send();"
    "}</script>"
    "<button id=\"stats\">Print Thread Stats</button>"
    "<script>document.querySelector('#stats').onclick = function() {"
    "var x = new XMLHttpRequest(); x.open('POST', '/stats'); x.send();"
    "}</script>"

    "</body>"
    "</html>";
