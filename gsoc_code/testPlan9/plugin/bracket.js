function create()
{
  //this.patternFound.connect(this, patternFound);
  this.registerWatchListItem("[","bracket");
  this.registerWatchListItem("(","parentesis");
  this.registerWatchListItem("{","brace");
  this.registerWatchListItem("{\n","newLine");
  this.registerWatchListItem("\"","guilmet");
  this.registerWatchListItem("'","apostrophe");
  this.registerWatchListItem("/*","comment");
  this.registerWatchListItem("||","orClause");
  this.registerWatchListItem("&&","andClause");
  this.registerWatchListItem("<","needTitle1");
  this.registerWatchListItem("<!--","htmlComment");
  this.registerWatchListItem(">","needTitle2");
  this.registerWatchListItem("<?php","phpBlock");
  this.registerWatchListItem("<?=","phpShortBlock");
  this.registerWatchListItem(")","parentesisEnd");
  this.registerWatchListItem("]","bracketEnd");
  this.registerWatchListItem("}","braceEnd");
}

function patternFound(value)
{

}

function bracket()
{
  this.insertText("]",KInsertPolicy.InsertAfterCursor);
}

function parentesis()
{
  this.insertText(")",KInsertPolicy.InsertAfterCursor);
}

function brace()
{
  this.insertText("}",KInsertPolicy.InsertAfterCursor);
}

function newLine()
{
  this.insertText("   \n}",KInsertPolicy.InsertAfterCursor);
}

function guilmet()
{
  this.insertText("\"",KInsertPolicy.InsertAfterCursor);
}

function apostrophe()
{
  this.insertText("'",KInsertPolicy.InsertAfterCursor);
}

function comment()
{
  this.insertText("*/",KInsertPolicy.InsertAfterCursor);
}

function orClause()
{
  
}

function andClause()
{
  
}

function needTitle1()
{
  
}

function htmlComment()
{
  this.insertText(" ",KInsertPolicy.InsertBeforeCursor);
  this.insertText(" -->",KInsertPolicy.InsertAfterCursor);
}

function needTitle2()
{
  
}

function phpBlock()
{
  this.insertText(" ?>",KInsertPolicy.InsertAfterCursor);
}

function phpShortBlock()
{
  this.insertText(" ?>",KInsertPolicy.InsertAfterCursor);
}

function parentesisEnd()
{
  var cursor = this.getCurrentCursorPos();
  if (this.getCurrentLine().substring(cursor-2,cursor-1) == "(")
    this.removeCharacters(1);  
}

function bracketEnd()
{
  var cursor = this.getCurrentCursorPos();
  if (this.getCurrentLine().substring(cursor-2,cursor-1) == "[")
    this.removeCharacters(1);  
}

function braceEnd()
{
  var cursor = this.getCurrentCursorPos();
  if (this.getCurrentLine().substring(cursor-2,cursor-1) == "{")
    this.removeCharacters(1);  
}
