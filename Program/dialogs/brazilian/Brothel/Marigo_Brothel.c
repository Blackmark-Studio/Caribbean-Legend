// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("rapaz","senhorita")+"?","O que você precisa, "+GetSexPhrase("bonito","bonitinha")+"? Pergunte o que quiser."),"Perguntas de novo?","Tee-hee, se não se importa - perguntas...",""+GetSexPhrase("Hum, por que você não escolhe uma das beldades pra você? Estou começando a ficar desconfiada de você...","Hm, por que não escolhe uma beleza para si? Receio que não temos rapazes por aqui, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, com licença.","Na verdade, deixa pra lá..."),"Eu... desculpe, não tenho perguntas por enquanto.","Você tem razão, já é a terceira vez. Me desculpe.","Talvez da próxima vez, Madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
