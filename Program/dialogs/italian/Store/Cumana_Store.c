// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Vai avanti, cosa desideri?","Ne stavamo proprio parlando. Devi aver dimenticato...","È la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
