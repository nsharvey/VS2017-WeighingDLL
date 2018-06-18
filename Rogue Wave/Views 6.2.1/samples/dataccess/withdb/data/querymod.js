static function japply(g) {
  var cont=g.container;
  var emp_ds=cont.EMP;
  var msg=cont.msg;
  if (emp_ds.applyQueryMode()) {
    msg.label="Applying Query succeeded";
  } else {
    if (emp_ds.isInQueryMode())
      msg.label="Applying Query failed";
    else
      msg.label="Not in Query Mode";
  }
}

static function jcancel(g) {
  var cont=g.container;
  var emp_ds=cont.EMP;
  var msg=cont.msg;
  if (emp_ds.isInQueryMode()) {
    emp_ds.cancelQueryMode();
    msg.label="Query cancelled";
  } else 
    msg.label="Not in Query Mode";
}

static function jconnect(g) {
  var session=IliSQLSession.Main;
  if (session.queryConnect(g.container, "IliSQLQueryIfNeeded")) {
    var ds=g.container.EMP;
    ds.select();
  }
}

static function jswitch(g) {
  var cont=g.container;
  var emp_ds=cont.EMP;
  var msg=cont.msg;
  if (emp_ds.switchToQueryMode()) {
    msg.label="Switching to Query Mode succeeded";
  } else {
    if (emp_ds.isInQueryMode())
      msg.label="Already in Query Mode";
    else
      msg.label="Switching to Query Mode failed";
  }
}
