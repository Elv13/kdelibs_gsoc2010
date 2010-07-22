var emailRegEx = "[a-zA-Z0-9'_]*@[a-zA-Z0-9_.]*.[a-zA-Z][a-zA-Z]?[a-zA-Z]"; //Match an e-mail address
var dateRegEx = "[0-9][0-9]/[0-9][0-9]/[0-9][0-9]"; //Detect a date
var trippleBracketPattern = 0;
var abcPattern = 0;
var parentesisPattern = 0;
var numberPattern = 0;
var numberPattern2 = 0;


function create()
{
 this.regExMatchFound.connect(this, regExFound);
 //this.patternFound.connect(this, patternFound);
 this.newContextMenu.connect(this, contextMenuRequest);
 
 this.registerRegEx(emailRegEx);
 this.registerRegEx(dateRegEx);
 trippleBracketPattern = this.registerWatchListItem("[[[","testFunc");
 abcPattern = this.registerWatchListItem("abc","");
 numberPattern2 = this.registerWatchListItem("12345","");
 parentesisPattern = this.registerWatchListItem("(","");
 numberPattern = this.registerWatchListItem("87654321","");
}

function regExFound(regEx)
{
  
  var subMenu = {};
  subMenu['action1'] = "Action1";
  subMenu['action2'] = "Action2";
  subMenu['action3'] = "Action3";
  subMenu['action4'] = "Action4";
  this.addSubMenu("Test",subMenu);
  action4.triggered.connect(this, function() {this.insertText("Action4 trigered");});
  
  
  this.debug("The selection:\""+this.getSelection()+"\"");
  if (regEx == emailRegEx) {
    this.addMenuTitle("Email");
    this.addMenuItem("emailAction","email");
    this.addMenuItem("emailAction2","email2");
    this.insertText(regEx,KInsertPolicy.InsertBeforeCursor);
    var test2 = handleEmail("test");
  }
  else if (regEx == dateRegEx) {
    var monthName = [ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" ];
    var selection = this.getSelection();
    this.addMenuTitle("Date");
    var newDate = monthName[selection.substring(0,2)-1] + " " + selection.substring(3,5);
    if (selection.substring(6,8) > 20)
      newDate = newDate + " 19" + selection.substring(6,8);
    else
      newDate = newDate + " 20" + selection.substring(6,8);
    this.addMenuItem("toMMMddYYYY",newDate);
    toMMMddYYYY.triggered.connect(this, function() {this.insertText(newDate);});
  }
}

function patternFound(value)
{
  /*if (value == trippleBracketPattern)
    this.insertText("]]]",KInsertPolicy.InsertAfterCursor);
  else */if (value == abcPattern)
    this.insertText("def",KInsertPolicy.InsertBeforeCursor);
  else if (value == parentesisPattern)
    this.insertText(")",KInsertPolicy.InsertAtDocBeginning);
  else if (value == numberPattern)
    this.insertText("9",KInsertPolicy.ReplaceDocument);
  else if (value == numberPattern2)
    this.insertText("---",KInsertPolicy.InsertAtLineBeginning);
}

function handleEmail(arg) 
{
  this.debug("handleEmail have been executed");
  this.addMenuItem("email");
  this.addMenuItem("email2");
  this.insertText(regEx);
  return "test";
}

function contextMenuRequest(length)
{
  this.debug("New content menu");
  if (length > 0) {
    this.debug("This is a selection");
    this.getSelectionLines("lines");
    var counter =1;
    for (var line in lines) {
      this.debug("line "+line+": "+lines[line]);
    }
  }
}

function testFunc() 
{
  this.insertText("]]]",KInsertPolicy.InsertAfterCursor);
}

function changeDate()
{
  this.insertText("]werwerwre]]",KInsertPolicy.InsertAfterCursor);
}