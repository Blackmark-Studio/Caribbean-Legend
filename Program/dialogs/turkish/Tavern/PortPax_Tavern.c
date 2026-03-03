// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Biz de tam bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Aynı şeyleri papağan gibi tekrarlıyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Evet, nedense unuttum...","Evet, gerçekten üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Bana söyle, 'Santa Margarita' adında bir kalyon son zamanlarda koloninize uğradı mı? Belki de bir korsanın ganimeti olarak?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Tristan Renier son zamanlarda buralardan geçti mi?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "Mate, it's pretty rare for anyone to stop by our colony with prizes, and we haven't seen a galleon by that name. Hispaniola is a wild island and we're a small colony. It's quiet here. We trade with the buccaneers in the highlands for cowhides and dried beef. Privateers don't usually linger; we don't have any brothels here, and the Spanish are close by. Go search for your galleon somewhere else.";
			link.l1 = "Anladım. Tavsiyen için teşekkürler!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Renier mi? Evet, buradaydı, hatta hâlâ burada. Bir oda tuttu.";
			link.l1 = "Şans bana gülümsüyor! İyi kaptanla olan işim gecikmeye gelmez—mahremiyeti zarurete boyun eğmeli. Onu hangi odada bulabilirim?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
