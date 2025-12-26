// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Bir askere ne sormak istersin?","Askerin tüm hayatı planlı - nöbet tutmak, koşturmak... Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bir askeri aptalca sorularla rahatsız etmemelisin, "+GetAddress_Form(NPChar)+"...","Bugün bana soru sormaya üçüncü kez çalışıyorsun...","Bir askerin kaderi kolay değildir, ve şimdi sen, pislik, beni deli ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Anlaşıldı...","Evet, haklısın, bu zaten üçüncü sefer...","Üzgünüm...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, Juan ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Hayır. Hepsi bu mu?";
			link.l1 = "Evet. Rahatsız ettiğim için kusura bakma, asker...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
