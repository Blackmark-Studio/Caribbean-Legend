// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu üçüncü kez sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben koloni işleriyle meşgul, yoğun bir adamım ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, üzgünüm.","Şimdi değil. Yeri ve zamanı değil."),"Doğru, şu anda söyleyecek bir şeyim yok, üzgünüm.","Daha sonra sorarım.","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Sayın Ekselansları, Nisan 1654'te Miguel Dichoso'nun komutasında bir fırkateyn vardı. O zamandan beri kendisinden haber alınamıyor. Onunla ilgili bir şey hatırlıyor musunuz? Belki sizi ziyaret etti, bir sohbetiniz oldu...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Evet, o adamı hatırlıyorum. Ama onunla ilgili hiçbir ayrıntıyı hatırlamıyorum. Buraya geldi ve sonra gitti. Size yardımcı olamam.";
			link.l1 = "Anladım. Sizi rahatsız ettiğim için üzgünüm.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
