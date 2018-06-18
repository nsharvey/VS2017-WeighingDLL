var picnum = 0;

function cbZoom(g) {
  var panel = g.container;

  if (panel.oZoom.value == 1)
    panel.oPic.adjust = true;
  else {
    panel.oPic.adjust = false;
    panel.oPic.bitmapName = "rwlogo.png";
  }
}

function cbFreq(g) {
  var panel = g.container;
  var val = panel.oFreq.value;
  var perio = 0;
 
  if (val == 1) perio = 1;
  else if (val == 2) perio = 10;
  else if (val == 3) perio = 20;

  panel.oTimer2.period = perio; 
}

function cbTimer2(g) {
  var panel = g.container;
  var pict  = panel.oPic;

  if (panel.oZoom.value == 1) {
    if (picnum == 1) {
      pict.bitmapName = "rwlogo2.png";
      picnum = 0;
    } else {
      pict.bitmapName = "rwlogo1.png";
      picnum = 1;
    }
  } else {
    pict.alignment = ((picnum % 4) == 0) ? "left"
      : (((picnum % 2) == 1) ? "center" : "right");
    pict.bitmapName = ((picnum % 3) == 0) ? "rwlogo1.png"
      : (((picnum % 3) == 1) ? "rwlogo.png" : "rwlogo2.png");
    picnum++;
    if (picnum == 12)
      picnum = 0;
  }
}
