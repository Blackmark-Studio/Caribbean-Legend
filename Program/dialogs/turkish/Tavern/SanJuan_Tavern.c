// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm dedikodular "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Az önce bundan bahsediyorduk. Herhalde unuttunuz...","Bugün bu soruyu üçüncü kez gündeme getiriyorsun...","Aynı şeyleri papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
