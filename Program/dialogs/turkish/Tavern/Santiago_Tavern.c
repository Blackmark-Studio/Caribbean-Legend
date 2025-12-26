// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bütün gün boyunca, bu soruyu üçüncü kez gündeme getiriyorsun...","Yine sorularınız var, öyle mi?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "Aziz babaların buraya bir Fransız kolonisinden bir heyetle geldiklerini duydum, bir konuda anlaşmak için mi? Muhtemelen o kanlı Martinique katliamından sonra esir değişimi yapmak için geldiler, öyle mi?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "Hayır señor, o hikaye çoktan çözüldü, hem de papazlar olmadan. Görüyorsunuz ya, siz herhalde bir palmiye ağacının altında yaşıyorsunuz, çünkü Papa Innocentius X ile Kardinal Mazarin'in sonunda anlaştığını duymamışsınız. Avrupa'nın savaşları ayrı mesele, ama bütün Hristiyanlar dünyanın sonundaki putperest karanlığa karşı birleşmeliymiş. Evet, kurbağa yiyenler de bize geldiler. Ama hiçbir konuda anlaşamadılar – değerli misafirlerimiz vali konağında, koruma altında, kahve içip koltuk ısıtıyorlar. Neredeyse bir aydır! Halk önce dedikodu yaptı, uzun uzun konuştu, sonra da alıştı – bakın, Fransız rahip akşamları kilisede dua ayini yapıyor. Adeta bir gösteri gibi, ahah!";
			link.l1 = "İlginç! Şu Fransız'a bir bakmalıyım, en azından bir kupaya bakmaktan daha eğlenceli.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
