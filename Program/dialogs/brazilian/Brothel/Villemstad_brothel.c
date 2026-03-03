// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("rapaz","senhorita")+"?","O que você precisa, "+GetSexPhrase("bonito","bonitinha")+"? Pode perguntar."),"Perguntas de novo?","Tee-hee, se não se importa - perguntas...",""+GetSexPhrase("Hum, por que você não escolhe uma beleza pra você? Estou começando a ficar desconfiada de você...","Hm, por que você não escolhe uma beleza para si? Receio que não temos nenhum rapaz por aqui, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, com licença.","Na verdade, deixa pra lá..."),"Eu... desculpe, não tenho perguntas por enquanto.","Você tem razão, já é a terceira vez. Me perdoe.","Talvez da próxima vez, madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
