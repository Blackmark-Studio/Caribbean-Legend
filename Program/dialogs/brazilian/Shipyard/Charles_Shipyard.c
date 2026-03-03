// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas perguntas?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas tão curiosas no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Hum, onde foi parar minha memória...","Hum, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Escute, mestre, vocês constroem navios aqui, certo?.. E também trocam velas... já pensou em... algum tecido de vela melhor?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Você está falando em enigmas, senhor... Fale claramente, o que o traz aqui? Não se preocupe, não sou nenhum burocrata e isto aqui não é uma alfândega.";
			link.l1 = "Ah, fico feliz que estamos de acordo! Velas de seda, senhor. Pelo que sei, não existe material melhor para as velas se a sua preocupação é velocidade.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Not only speed, but also her ability to sail close to the wind. You are offering ship silk for purchase? It's a valuable cargo, indeed. But there is an obstacle: I simply don't know how to use it in production. Do you follow? A material like this requires a very special set of abilities and skills which I lack. To be honest, my shipyard has a very different specialization; if you had offered me some ropes from the Tsardom of Russia, I'd gladly buy them all, no matter the price. We are in constant need of ropes, however, ship silk is not in demand here, I am sorry!";
			link.l1 = "Hm. Entendi. Obrigado pelo seu tempo, mestre. Boa sorte!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
