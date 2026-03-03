// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você quer?","O que você gostaria de saber?"),"O que você precisa, "+GetAddress_Form(NPChar)+"?","Essa já é a terceira vez que você tenta me perguntar...","Já cansei de você, suma daqui!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Desculpe, mudei de ideia.","Não foi nada, me desculpe."),"Esqueci, me desculpe...","Terceira vez é a vencida, né? Com licença...","Desculpa, desculpa! Eu já estou de saída então...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Saudações. O inquisidor de Santiago, Padre Vincento, mencionou você em sua carta. Ele disse que talvez você possa me ajudar.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Alguma novidade do Padre Vincento? "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Preciso falar com o Padre Vincento. Encontrei os itens que interessam a ele.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Então, "+npchar.name+", o que o Padre Vincento te contou?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Claro, senhor. Você deve ser um homem de grande reputação se o Padre Vincento faz negócios com você pessoalmente.";
			link.l1 = "Excelente. Então você será nosso mensageiro. Agora preste atenção, esse homem interessa muito ao Padre Vincento. Ele está sob sua responsabilidade agora, você precisa levá-lo até Santiago ou encontrar alguém que o faça.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Você é responsável pelo prisioneiro em nome do Inquisidor. Eu não aconselharia tirar as algemas dele, Gaius Marchais é um homem forte. Entregue esta carta ao Padre Vincento e diga a ele que aguardo uma resposta em dois dias. Isso deve ser suficiente, espero.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Entendido, senhor. Vou fazer o melhor que puder. Não é a primeira vez que ajudo o padre.";
			link.l1 = "Isso não é tudo. O capitão da carraca San Gregorio, Carlos Guevara, deve ter passado por aqui. Ele trouxe baunilha pra mim. Ele te entregou minha carta?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Sim, sua carga está em ordem e esperando por você, Señor.";
			link.l1 = "Ótimo, vou mandar levar isso para o meu navio então. Vou ficar aqui por dois dias esperando a resposta do Padre Vincento. Então, por enquanto, isso não é uma despedida, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Sim, senhor. Aqui está uma carta do Padre Vincento. Ele está muito satisfeito com você, o resto você saberá lendo a carta.";
			link.l1 = "Perfeito. Até lá, "+npchar.name+". E por agora - até logo.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Muito bem. Me entregue e eu levarei ao Santo Padre.";
			link.l1 = "De jeito nenhum, camarada! Não foi fácil conseguir isso e não vou entregar assim, de mão beijada. Só vou dar para o Padre Vincento pessoalmente.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Mas senhor! Como posso saber que o senhor não está me enganando?";
			link.l1 = "Dá uma olhada: o turíbulo, o cálice e a cruz com a lazurita... "+npchar.name+", quem você acha que eu sou? Acha mesmo que eu seria tolo o bastante pra ir até a Inquisição sem eles?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Me perdoe, senhor... Volte amanhã e eu aviso o Padre Vincento da sua chegada.";
			link.l1 = "Ótimo. Até amanhã.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Sua Graça vai recebê-lo, senhor. Não demore para fazer sua visita. Aqui está o documento, mostre-o aos guardas e eles vão deixá-lo entrar. Mas primeiro levante uma bandeira espanhola, senão os soldados provavelmente vão prendê-lo.";
			link.l1 = "Entendi. Espanhol então. Valeu, amigo! Estou a caminho!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
