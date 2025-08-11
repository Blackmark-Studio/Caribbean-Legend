// 温德索尔勋爵 - 英国殖民地总督兼将军
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = "你想要什么? ";
            link.l1 = "没什么。 ";
            link.l1.go = "exit";            
            NextDiag.TempNode = "First time";
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "";            
        break;
        
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
    }
}