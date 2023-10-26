function makeStory(){
    var story = "";
    story += document.getElementById("person").value + " a vizitat ";
    story += document.getElementById("adjective").value;
    story += document.getElementById("places").value;
    document.getElementById("story").innerText = story;
}