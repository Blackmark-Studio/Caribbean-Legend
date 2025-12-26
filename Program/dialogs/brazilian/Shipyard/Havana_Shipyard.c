// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas tão curiosas no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Hum, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Escute, um homem chamado Joachim Merriman esteve aqui recentemente? Um senhor de meia-idade, português, com bigode, barba imperial e olhar penetrante? Talvez ele quisesse comprar um navio?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Não, senhor. Não vi nenhum cliente assim.";
			link.l1 = "Entendi. Que pena. Vou continuar minha busca então...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
