// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Bir askere ne sormak istersin?","Askerin tüm hayatı planlanmış - nöbet tutmak, koşturmak... Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bir askeri aptalca sorularla rahatsız etmemelisin, "+GetAddress_Form(NPChar)+"...","Bugün üçüncü kez bana bir soru sormaya çalışıyorsun...","Bir askerin kaderi kolay değildir, ve şimdi sen, pislik, beni deli ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Anlaşıldı...","Evet, haklısın, bu zaten üçüncü sefer...","Üzgünüm...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
