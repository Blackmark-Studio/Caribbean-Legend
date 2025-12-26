// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sorular, "+GetAddress_Form(NPChar)+"?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, neyin peşindesin, "+GetAddress_Form(NPChar)+"? ","Yine tuhaf sorularla mı geldin? Hadi, git biraz rom iç ya da başka bir şey yap...")+"","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun..."+GetSexPhrase(" Bunlar bir ilgi göstergesi mi?","")+"","Sanırım daha fazla sorunuz var, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim","Şu anda konuşacak bir şeyim yok."),"Hayır, hayır, güzelim...","Olmaz, canım...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
