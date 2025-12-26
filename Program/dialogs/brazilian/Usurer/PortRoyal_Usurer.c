// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas dúvidas?","Como posso ajudá-lo?"),"Você já tentou me fazer essa pergunta há pouco tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Ouça, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Você adivinhou, sinto muito...","Entendi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "Me diga, o Coronel veio até você? Ele disse que você tinha uma recompensa preparada para mim.";
				link.l1.go = "DTSG_depozit_1";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_depozit_1":
			dialog.text = "Que coronel?";
			link.l1 = "Thomas Lynch.";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "Fale baixo! Eu conheço esse homem. Sim, ele passou por aqui. Sua recompensa está esperando por você, Capitão.";
			link.l1 = "E quanto tem lá?";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "Exatamente dez mil em ouro. Nem um único peso – só ouro.";
			link.l1 = "Pelo menos não são trinta moedas de prata...";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("You have received 70 chests");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "O que foi isso?";
			link.l1 = "Oh, nada... Obrigado. Adeus.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
