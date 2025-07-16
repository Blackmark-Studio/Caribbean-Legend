// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa desideri?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. La gente compra roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
