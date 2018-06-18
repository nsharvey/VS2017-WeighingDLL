static function OnLoad(cont) {
  var ds = cont.EMP_MS;
  var pm1 = ds.table.newNamedPropertyManager("PM1");
  pm1.setStringProperty(-2, -1, "background", "yellow");
  pm1.setIntProperty(-1, -1, "readOnly", 1);
  pm1.setIntProperty(-2, -1, "readOnly", 0);
  var tg = cont.tg;
  tg.useTableProperties = true;
  tg.tablePropertyManagerName = "PM1";
  var pm2 = ds.table.newNamedPropertyManager("PM2");
  pm2.setStringProperty(-1, 3, "font", "bold");
  pm2.setStringProperty(-1, 5, "foreground", "red");
  pm2.setStringProperty(-1, 5, "background", "red");
  var dbf4 = cont.dbf4;
  dbf4.tablePropertyManagerName = "PM2";
  var dbt = cont.dbt;
  dbt.tablePropertyManagerName = "PM2";
}

function jentrow(g) {
  cont = g.container;
  var pm2 = g.table.getNamedPropertyManager("PM2")
  var dbf4 = cont.dbf4;
  if (g.table.at(g.currentRow, 3)>18)
    dbf4.useTableProperties = false;
  else
    dbf4.useTableProperties = true;
  var dbt = cont.dbt;
  if (g.table.at(g.currentRow, 5)) {
    dbt.useTableProperties = true;
    dbt.label = "Mgr";
  } else {
    dbt.useTableProperties = false;
    dbt.label = "Emp";
  }
}
