// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você quer?","O que você gostaria de saber?"),"O que você precisa, "+GetAddress_Form(NPChar)+"?","Essa já é a terceira vez que você tenta me perguntar...","Já cansei de você, suma daqui!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Desculpe, mudei de ideia.","Não foi nada, me desculpe."),"Esqueci, me desculpe...","Terceira vez é a certa, né? Com licença...","Desculpa, desculpa! Eu já estou de saída então...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Escute – passou por aqui um homem chamado Joachim Merriman? Ele é um senhor português de meia-idade, com bigode, cavanhaque e olhar penetrante. Talvez tenha desembarcado numa enseada ou perto do farol? Você viu alguém assim?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "Não, não vi ninguém assim. Eu teria notado, sim.";
			link.l1 = "Entendi, que pena. Obrigado pelo seu tempo, vou continuar minha busca então.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
