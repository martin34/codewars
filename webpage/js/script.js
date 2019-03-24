var button = document.getElementById("buttonId"),
    count = 0;
button.onclick = function() {
  count += 1;
  $("#alertText").text("Button clicked " + count + " times");
};