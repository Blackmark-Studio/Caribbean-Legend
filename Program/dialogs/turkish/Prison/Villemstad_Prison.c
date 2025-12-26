// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Subay, burada Bartolomeo the Portuguese adında bir mahkumu tutuyorsunuz...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Var. Peki, neden ilgileniyorsun? Sadece Hollanda Batı Hindistan Şirketi'nin elçileri onu görebilir, o da sadece valinin yazılı emriyle. Şirketin subaylarından biri şu anda bu korsanı sorguluyor. Yani buraya onu görmek için geldiysen, en iyisi yoluna devam et. Onu ancak asılırken görebilirsin. Şimdi git.";
			link.l1 = "Onu görmeye gelmedim.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Neden, peki, sorabilir miyim?";
			link.l1 = "Onu   kurtarmak   için   geldim!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
