// 矿场囚犯对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("抱歉, 但如果我们不再交谈, 对彼此都好。 他们会惩罚我的, 而你也会被要求离开。 ", "朋友, 我已经把知道的都告诉你了。 你是想让我因为你而被鞭打吗? ", "我不听... ", "铁镐敲击着, 凿子啃噬着岩石... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你们这里的规矩真严... ", "不, 当然不想。 ", "嗯... ", "爸爸, 你能听到我吗... ", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "船长, 你在干什么? 快把武器收起来, 不然会惹上大麻烦的! ";
			link.l1 = LinkRandPhrase("好吧。 ", "好吧。 ", "别担心, 我这就收起来... ");
			link.l1.go = "exit";
		break;  
	}
}