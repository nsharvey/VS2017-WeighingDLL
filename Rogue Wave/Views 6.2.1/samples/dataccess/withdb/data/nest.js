static function jcreate(obj) {
  var cont = obj.container;
  var ds = cont.create8;
  var lab = "creation of oracle9i tables";
  var msg = cont.msg;
  if (jexecute(ds))
    msg.label = "creation of oracle9i tables finished";
}

static function jdrop(obj) {
  var cont = obj.container;
  var ds = cont.drop8;
  var lab = "drop of oracle9i tables";
  var msg = cont.msg;
  if (jexecute(ds))
    msg.label = "drop of oracle9i tables finished";
}

static function jexecute(ds) {
  var session = IliSQLSession.Main;
  var msg = ds.container.msg;
  var cursor=session.newCursor();
  for (i = 0; i < ds.rowsCount ; i++) {
     ds.gotoRow(i);
     cursor.execute(ds.getColumnAt(1).value);
     if (cursor.isErrorRaised()) {
        msg = cursor.getErrorMessage().prettyMessage;
        if (!IlvCommonDialog.messageBox(msg, 1, "Error"))
          break;
     }
  }
  if (!session.commit()) {
     msg = session.getErrorMessage().prettyMessage;
     IlvCommonDialog.messageBox(msg, 0, "Error");
  }
  return 1;
}

static function jmaj(g) {
  var cont = g.container;
  var prod_ds = cont.PROD_DS;
  var parts2_ds = cont.PARTS2_DS;
  parts2_ds.select();
}

static function jmaj2(g) {
  var cont = g.container;
  var parts_ds = cont.PARTS_DS;
  parts_ds.select();
}

static function jselect(g) {
  var cont = g.container;
  var prod_ds = cont.PROD_DS;
  var tcb = cont.tcb;
  var row = prod_ds.table.getColumn("PRODNAME").findFirstRow(tcb.value);
  prod_ds.gotoRow(row);
  var parts_ds = cont.PARTS_DS;
  parts_ds.select();
  var parts2_ds = cont.PARTS2_DS;
  parts2_ds.table.cache = prod_ds.table.at(row, 2);
}
