var InChangeSel = false;

function addIndex(ds, index) {
  var buf = ds.table.getBuffer();
  buf.Index.value = index;
  ds.table.appendRow(buf);
}

function getIndexAt(ds, rowno, def, except) {
  if (except >= 0 && rowno >= except)
    ++rowno;
  var idx = ds.table.at(rowno, 0);
  if (typeof(idx) != "undefined")
    return idx;
  else
    return def;
}

function onSelChange(obj)
{
  if (!InChangeSel) {
    var selDs = obj.container.SelectionDS;
    var selTg = obj.container.SelTg;
    var typeCombo = obj.container.TypeCombo;
    var i;
    if (selDs) {
      selDs.clear();
      var sel = obj.selection;
      if (sel.isFull()) {
        typeCombo.value = "Full";
        selTg.showInsertRow = false;
      }
      else if (sel.isCell()) {
        typeCombo.value = "Cell";
        addIndex(selDs, sel.row);
        addIndex(selDs, sel.column);
        selTg.showInsertRow = false;
      }
      else if (sel.isRow()) {
        typeCombo.value = "Row";
        selTg.showInsertRow = true;
        if (sel.isMulti()) {
          for (i = 0; i < sel.rowsCount; ++i) {
            addIndex(selDs, sel.getRowAt(i)); 
          }
        }
        else {
          addIndex(selDs, sel.row); 
        }
      }
      else if (sel.isColumn()) {
        typeCombo.value = "Column";
        selTg.showInsertRow = true;
        if (sel.isMulti()) {
          for (i = 0; i < sel.columnsCount; ++i) {
            addIndex(selDs, sel.getColumnAt(i)); 
          }
        }
        else {
          addIndex(selDs, sel.column); 
        }
      }
      else {
        typeCombo.value = "None";
        selTg.showInsertRow = false;
      }
    }
  }
}

function changeSel(obj, except) {
    var selDs = obj.container.SelectionDS;
    var selTg = obj.container.SelTg;
    var typeCombo = obj.container.TypeCombo;
    var realTg = obj.container.Tg;
    var sel = realTg.selection;
    var count;
    var i;
    var idx;

    sel.setEmpty();
    var type = typeCombo.value;
    if (type == "Full") {
      sel.type = "IliSelectAll";
      selTg.showInsertRow = false;
    }
    else if (type == "Cell") {
      sel.type = "IliSelectCell";
      sel.row = getIndexAt(selDs, 0, 0, except);
      sel.column = getIndexAt(selDs, 1, 0, except);
      selTg.showInsertRow = false;
    }
    else if (type == "Column") {
      sel.type = "IliSelectColumn";
      count = selDs.table.rowsCount;
      sel.column = getIndexAt(selDs, 0, 0, except);
      for (i = 1; i < count; ++i) {
        idx = getIndexAt(selDs, i, -1, except)
        if (idx >= 0 && idx < realTg.columnsCount)
          sel.addColumn(idx);
      }
      selTg.showInsertRow = true;
    }
    else if (type == "Row") {
      sel.type = "IliSelectRow";
      count = selDs.table.rowsCount;
      idx = getIndexAt(selDs, 0, 0, except);
      sel.row = idx;
      for (i = 1; i < count; ++i) {
        idx = getIndexAt(selDs, i, -1, except)
        if (idx >= 0 && idx < realTg.table.rowsCount) {
          sel.addRow(idx);
        }
      }
      selTg.showInsertRow = true;
    }
    realTg.selection = sel;
}

function onRowInserted(obj) {
    changeSel(obj, -1);
}

function onRowUpdated(obj) {
    changeSel(obj, -1);
}

function onRowDeleted(obj) {
  if (!InChangeSel) {
    InChangeSel = true;
    var rowno = obj.deletedRow;
    changeSel(obj, rowno);
    InChangeSel = false;
  }
}

function onTypeChanged(obj) {
    changeSel(obj, -1);
}
