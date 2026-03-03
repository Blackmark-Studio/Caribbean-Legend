// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, 'Juan' ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Dinle dostum, Nisan 1654'te Miguel Dichoso'nun komutasındaki bir fırkateyn burada limana demirledi. O gün ortadan kayboldu. Bu konuda bir şey hatırlıyor musun?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli servis için mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O halde hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şey bilmiyorum.";

            link.l1 = "Ne kadar da kafan karışık! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Benimle dalga mı geçiyorsun? Her kolonide iki düzine Juan var!";
			link.l1 = "Anladım. Rahatsız ettiğim için özür dilerim...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hadi ama kaptan! Böyle şeyleri hatırlayacağımı mı sanıyorsun?","Beni affedin Señor, bu konuda size yardımcı olamam.","Beyim, gerçekten böyle saçmalıkları hatırlayacağımı mı sanıyorsunuz? Zaten başım yeterince dertte.");
			link.l1 = LinkRandPhrase("Anladım. Rahatsız ettiğim için özür dilerim...","Ne yazık. Hoşça kal.","Pekâlâ, hoşça kal...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
