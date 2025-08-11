// 里瓦多斯领袖的保镖 埃迪 - 齐科莫
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
			dialog.text = "你想干什么, 白人? 齐科莫不跟你说话。 跟黑埃迪说。 他是老大。 ";
			link.l1 = "你才不这么说呢! ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}