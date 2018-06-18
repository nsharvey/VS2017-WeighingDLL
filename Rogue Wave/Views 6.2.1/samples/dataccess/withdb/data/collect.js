static function jcreate(obj) {
  var cont = obj.container;
  var ds = cont.create9;
  var lab = "creation of informix9 tables";
  var msg = cont.msg;
  if (jexecute(ds))
    msg.label = "creation of informix9 tables finished";
}

static function jdrop(obj) {
  var cont = obj.container;
  var ds = cont.drop9;
  var lab = "drop of informix9 tables";
  var msg = cont.msg;
  if (jexecute(ds))
    msg.label = "drop of informix9 tables finished";
}

static function jexecute(ds) {
  var session = IliSQLSession.Main;
  var msg = ds.container.msg;
  if (session.dbmsName!="informix9") {
    msg.label = "database should be informix9";
    return 0;
  } else {
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
}

static function jselect(g) {
  var cont = g.container;
  var aut_ds = cont.AUT_DS;
  if (!aut_ds.catchingNestedChanges)
    aut_ds.catchingNestedChanges = true;
  var tg = cont.tg;
  var tab = aut_ds.table;
  if (tab.at(aut_ds.currentRow, 2))
    tg.table = tab.at(aut_ds.currentRow, 2);
  else
    tg.table = tab.getColumnAt(2).makeNestedTable();
}
