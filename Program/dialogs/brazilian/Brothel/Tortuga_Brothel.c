// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("rapaz","senhorita")+"?","O que você precisa, "+GetSexPhrase("bonito","bonitinha")+"? Pode perguntar."),"Perguntas de novo?","Tee-hee, se não se importa - perguntas...",""+GetSexPhrase("Hum, por que você não escolhe uma bela para você? Estou começando a desconfiar de você...","Hm, por que você não escolhe uma das nossas belezas para si? Infelizmente, não temos rapazes aqui, viu, hehe...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, com licença.","Na verdade, deixa pra lá..."),"Eu... desculpe, não tenho perguntas por agora.","Você tem razão, já é a terceira vez. Me perdoe.","Talvez numa próxima vez, madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
