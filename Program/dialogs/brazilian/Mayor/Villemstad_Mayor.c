// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você deseja? Pergunte logo.","Estou ouvindo, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando de assuntos coloniais, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, desculpe.","Agora não. Lugar e hora errados."),"É verdade, não tenho nada a dizer agora, desculpe.","Vou perguntar depois.","Me desculpe, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "Sei que a Companhia Holandesa das Índias Ocidentais colocou um preço pela cabeça de um certo pirata — Bartolomeu, o Português. Consegui capturá-lo. Ele está atualmente em meu porão de carga e estou pronto para entregá-lo às autoridades.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já levou tudo. O que mais você quer?","Restou alguma coisa que você não levou?");
            link.l1 = RandPhraseSimple("Só dando uma olhada por aqui...","Só estou conferindo, talvez tenha esquecido de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "Bart, o Português?! Você o capturou vivo?!";
			link.l1 = "Eu sei que ele não lhe serve de nada morto. Ele está vivo e, que os deuses me perdoem, tive que me segurar para deixá-lo assim!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "Excelente! Agora ele vai nos contar tudo... Mynheer, prepare o prisioneiro para a transferência. Enviaremos uma barca militar ao seu navio imediatamente. ";
			link.l1 = "Gostaria de falar sobre minha recompensa primeiro, Mynheer, se não se importar.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "Não se preocupe com sua recompensa, senhor. Você a receberá. Colocamos um preço pela cabeça de Bartolomeu, o Português – mil e quinhentos dobrões. Tenente! Traga a recompensa ao capitão!";
			link.l1 = "Hm... Hugo me disse que eram dois mil doblões... Está bem então.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "E agora, senhor, poderia ter a gentileza de entregar o português à Companhia? Estamos ansiosos para ter uma conversa com ele.";
			link.l1 = "Claro, senhor, envie a barca para o meu navio.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
