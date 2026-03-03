// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, fale agora. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho a fazer e você está me distraindo, "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Eu vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Santo Padre, estou procurando o Abade Benoit, tenho um assunto urgente para ele. Pode me dizer onde posso encontrá-lo?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "O Abade Benoit deixou a cidade em missão da igreja com representantes da missão católica espanhola no Novo Mundo. Não sei detalhes, mas o Abade Benoit está ausente há tempo suficiente para supor que as negociações se prolongaram, ou que algo pode ter acontecido no caminho. Estamos todos apreensivos, mas só nos resta rezar e esperar por notícias.";
			link.l1 = "Não posso assumir que tudo será fácil. Padre, o senhor pode me dizer exatamente para onde o Abade Benoit foi? Preciso encontrá-lo o mais rápido possível.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Receio que não posso, meu filho. Pelo que sei, o abade Benoit foi negociar com o bispo da Nova Espanha e o prelado da Inquisição, padre Vincento Palotti, mas ele não especificou onde a reunião aconteceria.";
			link.l1 = "Isso deve bastar, Padre, obrigado. Conheço o Padre Palotti de certa forma... Vou procurar por Santiago.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
