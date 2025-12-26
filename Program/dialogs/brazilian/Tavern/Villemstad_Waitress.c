// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Perguntas, "+GetAddress_Form(NPChar)+"?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, qual é a grande ideia, "+GetAddress_Form(NPChar)+"? ","De novo com essas perguntas estranhas? Vai tomar um rum ou sei lá...")+"","Durante todo este dia, já é a terceira vez que você faz essa pergunta..."+GetSexPhrase(" Isso são sinais de carinho?","")+"","Mais perguntas, imagino eu, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia","Não tenho nada para conversar no momento."),"Não, não, linda...","Não, querido...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
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
