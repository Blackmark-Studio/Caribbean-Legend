// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün o soruyu üçüncü kez gündeme getiriyorsun...","Bak, eğer limanın işleriyle ilgili bana anlatacak bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, üçüncü kez oldu artık...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, 'Juan' ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, Nisan 1654'te burada Miguel Dichoso'nun komutasında bir fırkateyn vardı. O zaman ortadan kayboldu. Hiçbir şey hatırlamıyor musunuz? Belki Dichoso buradaydı ve gemisini kaydettirdi...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? Sadece bu mu? Señor, sarhoş musunuz yoksa benimle alay mı ediyorsunuz? Bir soyadı ya da en azından gemisinin adını hatırlıyor musunuz? Burası bir İspanyol kolonisi, Tanrı aşkına. Burada kaç tane Juan dolaşıyor, biliyor musunuz? Hiçbir ayrıntı olmadan size yardımcı olamam.";
			link.l1 = "Anladım. Rahatsız ettiğim için kusura bakmayın...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Notlarıma bir bakayım... aha! Evet, Kaptan Miguel Dichoso Nisan 1654'te burada, 'Santa-Quiteria' firkateyniyle bulunmuş. San-Andres, Providence kolonisinden geldiğini kaydetmiş. İstikameti İspanya, Cadiz'miş. 14 Nisan 1654'te denize açılmış. Bende olan bilgiler bu kadar.";
			link.l1 = "Avrupa'ya yelken açıyor musunuz? Anladım. Bunun için teşekkürler!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
