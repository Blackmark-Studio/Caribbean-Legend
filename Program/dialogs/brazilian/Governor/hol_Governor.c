// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que deseja?");
				link.l1 = "Eu sei que a Companhia Holandesa das Índias Ocidentais colocou uma boa recompensa pela cabeça do famoso pirata Bartolomeu, o Português. Consegui capturá-lo. Ele está agora no porão do meu navio, e estou pronto para entregá-lo às autoridades.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você precisa?");
			link.l1 = RandPhraseSimple("Nada de importante, senhor.","Não tenho nada a dizer, me desculpe.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Infelizmente, não posso lhe oferecer um trabalho. No momento, você não é alguém com quem eu queira trabalhar. Adeus.";
                link.l1 = "Você não pode estar falando sério... mas tudo bem.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart, o Português?! Você está com ele? Vivo?";
			link.l1 = "Eu sei que você não precisa que ele morra. Ele está vivo. Tive que me esforçar muito para mantê-lo assim!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Excelente! Agora ele vai nos contar tudo... Mynheer, prepare o prisioneiro para a transferência. Vamos enviar uma barca militar ao seu navio imediatamente. ";
			link.l1 = "Gostaria de falar sobre minha recompensa primeiro, senhor... Se não se importar.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Não se preocupe com sua recompensa, capitão. Você vai recebê-la. Colocamos um preço na cabeça de Bartolomeu, o Português – mil e quinhentos dobrões. Tenente! Traga a recompensa do capitão!";
			link.l1 = "Hm... Parece que o Hugo mentiu pra mim sobre dois mil dobrões... Tudo bem então.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "E agora, capitão, poderia ter a gentileza de entregar o português à Companhia? Mal podemos esperar para conversar com ele.";
			link.l1 = "Claro, senhor, mande a barca para o meu navio.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
