// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, fale agora. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho, e você está me distraindo. "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Eu vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
