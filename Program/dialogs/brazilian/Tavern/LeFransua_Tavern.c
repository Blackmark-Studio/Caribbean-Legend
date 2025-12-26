// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","Durante todo este dia, já é a terceira vez que você faz essa pergunta...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Umph, onde foi parar minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Escute, "+npchar.name+", vim falar com você sobre um assunto incomum. Preciso encontrar um homem que queira uma vida tranquila e sossegada na baía, trabalhando como assistente de comerciante em uma loja de Saint-Pierre. O salário é bom e ele terá um teto garantido. Você saberia me indicar alguém a quem eu possa recorrer?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Vim falar sobre os barris de vinho que você está prestes a carregar no meu navio para entregar em Guadalupe...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Sabe, "+npchar.name+", estou procurando um amigo meu. Era para ele ter chegado aqui, mas não estava se sentindo bem. Talvez os amigos dele tenham ajudado...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm... Temos várias pessoas aqui que gostariam de trocar a vida de marinheiro pela de alguém em terra firme. Posso te ajudar, mas já aviso: não vai ser de graça.";
			link.l1 = "Hein! E quanto você quer?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "One thousand pieces of eight. And there's nothing you'll have to do; in an hour, your candidates for the job will be in my tavern—several candidates. You'll be able to talk with them and select the one who appeals to you more than the rest.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Tá bom, aqui, pega mil!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Desculpe, mas eu não tenho tanto dinheiro assim!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Don't worry, mate. You'll get half of this amount back from the candidate. I'll tell him that's the cost of your services, heh heh... They won't give any more than five hundred. Stop by my tavern in an hour; by that time I'll have the people you need waiting for you.";
			link.l1 = "Certo. Eu volto em uma hora, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Sinto muito, você também não tem esse tipo de dinheiro. Mas você sabe, coisas assim não se fazem só por um 'obrigado'. Então...";
			link.l1 = "Eu entendo. Mas eu realmente não tenho dinheiro. Tudo bem, adeus...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "Do que você está falando, camarada? Que vinho é esse de que está falando?";
			link.l1 = "Fui enviado até você por um homem chamado Walter Catcher. Ele disse que você precisava de um navio para transportar uma carga de vinho até Guadalupe por dez mil pesos. E que só o meu navio serviria para esse trabalho...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Olha, eu não vendo vinho, não preciso dos seus serviços e não conheço nenhum Walter Catcher.";
			link.l1 = "Veja só! Então, aquele Caçador não foi enviado por você afinal... Então, do que se trata toda essa comédia?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Bem, isso ou é algum tipo de engano, ou uma piada ruim, ou...";
			link.l1 = "Ou o quê?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Não consegue perceber sozinho? Alguém precisava te atrair até Le Francois, embora eu não saiba o motivo. Se fosse você, eu me apressaria para sair daqui, tomando todo cuidado possível. Isso cheira a encrenca, camarada...";
			link.l1 = "Acho que você tem razão. Não gostei da cara daquele Catcher. Tudo bem, vou seguir seu conselho. Tchau, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Sim, seu amigo chegou aqui, capitão. Ele chegou ontem e alugou um quarto no andar de cima. Os companheiros dele também estão aqui, hehe... Eles estão sentados ali. Pergunte a eles!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
