var visible = document.getElementById("visible-x");
var visible_y = document.getElementById("visible-y");
visible.addEventListener("mouseenter", function(event) {
  visible.style.stroke = "green";
  visible_y.style.stroke = "green";
});
visible.addEventListener("mouseleave", function(event) {
  visible.style.stroke = "black";
  visible_y.style.stroke = "black";
});
visible_y.addEventListener("mouseenter", function(event) {
  visible_y.style.stroke = "yellow";
});
visible_y.addEventListener("mouseleave", function(event) {
  visible_y.style.stroke = "black";
});
