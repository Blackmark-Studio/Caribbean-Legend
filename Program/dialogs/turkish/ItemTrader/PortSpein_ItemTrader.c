// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Yine sorular, "+GetAddress_Form(NPChar)+"...","Sorular, sorular... Ne dersiniz, takas yapalım, "+GetAddress_Form(NPChar)+"ha?","Dinle, ne kadar daha konuşmayı düşünüyorsun?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Şimdilik sorum yok...","Üzgünüm, şu anda söyleyecek bir şeyim yok..."),"Tekrar özür dilerim...","Belki de gerçekten ticaret yapmanın zamanı gelmiştir...","Üzgünüm, hadi ticaret yapalım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dinle, 'Juan' ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Hayır, etmiyor... Şimdi lütfen beni rahatsız etme, oldukça meşgulüm... Ne saçma bir soru...";
			link.l1 = "Anladım. Zamanınızı boşa harcadığım için üzgünüm...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
