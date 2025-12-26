// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormayı denedin "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer liman işleriyle ilgili bana söyleyecek bir şeyin yoksa, o zaman beni sorularınla meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boş ver.","Gerçekten de, bu üçüncü kez oldu...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
