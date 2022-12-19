
// remove highlight later after it implemented in themata
function loadScript(url, callback)
{
    // Adding the script tag to the head as suggested before
    var head = document.head;
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;

    // Then bind the event to the callback function.
    // There are several events for cross browser compatibility.
    script.onreadystatechange = callback;
    script.onload = callback;

    // Fire the loading
    head.appendChild(script);
}

loadScript("https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.5.1/highlight.min.js", () => {
    hljs.highlightAll();
});
