// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Perguntas, "+GetAddress_Form(NPChar)+"?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hum, qual é a sua, "+GetAddress_Form(NPChar)+"? ","De novo com essas perguntas estranhas? Querido, vai tomar um rum ou algo assim...")+"","Durante todo este dia, essa é a terceira vez que você faz essa pergunta..."+GetSexPhrase(" Isso são sinais de afeto?","")+"","Mais perguntas, imagino eu, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia","Não tenho nada para conversar no momento."),"Não, não, linda...","De jeito nenhum, querido...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
