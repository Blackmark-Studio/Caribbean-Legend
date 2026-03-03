// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sorular, "+GetAddress_Form(NPChar)+"?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, neyin peşindesin, "+GetAddress_Form(NPChar)+"? ","Yine tuhaf sorularla mı geldin? Hadi canım, git biraz rom iç ya da başka bir şey yap...")+"","Bütün gün boyunca, bu soruyu üçüncü kez gündeme getiriyorsun..."+GetSexPhrase(" Bunlar bir ilgi göstergesi mi?","")+"","Sanırım daha fazla sorunuz var, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim","Şu anda konuşacak bir şeyim yok."),"Hayır, hayır, güzelim...","Hayır, canım...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//--> Тайна Бетси Прайс
		case "TBP_BetsiPriceSex1":
			DoFunctionReloadToLocation("Villemstad_tavern_upstairs", "quest", "quest4", "TBP_Betsi_sex_2");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
