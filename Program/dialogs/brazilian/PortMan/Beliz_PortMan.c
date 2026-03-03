// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "O que você quer? Ah, você está participando da regata! Acertei?";
				link.l1 = "Exatamente, senhor. Preciso me registrar aqui conforme as regras.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já fez a mesma pergunta pela terceira vez hoje...","Olha, se você não tem nada pra me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não me interesso pelos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Dizem por aí que alguém tentou tirar sua vida, e agora você está tentando encontrar o culpado?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "O homem que tentou tirar sua vida caiu, senhor. "+npchar.lastname+". Nada mais ameaça você.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Você quebrou as regras da regata e eu preciso desclassificá-lo. Sinto muito. Você não participará da próxima viagem. Já preparei um despacho para Port Royal.";
			link.l1 = "Opa... que pena! Mas não posso fazer nada aqui, você foi atento demais. Adeus!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Vamos registrar: Capitão "+GetFullName(pchar)+", navio é "+pchar.Ship.Name+"... a duração da regata em horas é "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Pronto, seu resultado foi registrado, você pode seguir seu caminho.";
			link.l1 = "Me diga meu posto.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Você está aqui, mas não vejo seu navio. Onde ele está?";
			link.l1 = "Me desculpe, senhor. Vou transferir meu navio para o porto imediatamente.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Você está na liderança. Parabéns! Continue assim!";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Você é o último. É melhor se apressar.";
				link.l1 = "Estou a caminho!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Você é o segundo. O líder é "+sName+" no navio "+sShip+". Suponho que você ainda consiga deixá-lo para trás.";
					link.l1 = "Obrigado! Vou tentar!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Seu posto é "+n+". Seu adversário mais próximo é "+sName+" no navio "+sShip+".";
					link.l1 = "Obrigado!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "A tentativa contra minha vida de fato aconteceu, isso é verdade. Quanto à busca... não é bem isso. Não preciso que capturem um fugitivo — preciso da cabeça dele. Só assim terei paz novamente.";
			Link.l1 = "Você faz ideia de quem te atacou e por quê?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Eu... eu não sei quem ele é! Não sei de onde veio, nem por que me atacou. Mas uma coisa é certa — ele queria me ver morto. E agora... agora eu desejo a morte dele com a mesma fúria! Você me entende?\nEntão poupe-me das suas perguntas inúteis. Sua curiosidade não me interessa — só a ação pode ajudar agora. Duzentos dobrões pela cabeça dele, esse é meu preço. Comece a caçada, ou pare de desperdiçar meu tempo.";
			Link.l1 = "Eu entendo que o medo e a raiva estão te cegando, e até vou relevar o seu tom. Mas se controle. Não vejo uma fila de voluntários querendo resolver seus problemas, então segure esse ímpeto. Duzentos dobrões está aceitável, mas antes de aceitar o trabalho, preciso saber de tudo.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Suas palavras são só conversa fiada, e não há nenhuma pista. Procurar alguém desconhecido na selva é como achar uma agulha no palheiro. Não vou perder meu tempo numa busca inútil. Boa sorte. Você vai precisar mesmo.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Argh... Me perdoe, "+GetAddress_Form(NPChar)+", meus nervos estão à flor da pele... O que exatamente você quer saber?";
			Link.l1 = "Você notou alguma característica que possa ajudar a identificá-lo? Ele estava sozinho ou tinha o apoio de alguém mais poderoso? Quanto mais você me contar, mais cedo poderá dormir em paz.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Que inimigo?! Eu não tenho inimigos! Nunca tive! Não fiz nada para merecer morrer no meio da rua, em plena luz do dia\nAquele canalha... é só um lunático amargurado, desses que você encontra em qualquer cidade colonial\nQuanto a onde procurar... Acho que ele está escondido na selva. É fácil sumir naquelas matas malditas, mas tenho certeza de que ele vai acabar indo para alguma gruta ou enseada — é mais fácil se esconder lá\nSobre a aparência, o rosto dele estava coberto com um lenço, chapéu na cabeça, e carregava mais armas do que os próprios guardas de Sua Majestade. Não deu tempo de reparar em mais nada.";
			Link.l1 = "Bem, não é muito, mas já dá para começar a busca. Vou partir agora mesmo. Guarde esse ouro — volto logo.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_5");
		break;
		
		case "GS_Portman_6":
			dialog.text = "Magnífico, "+GetFullName(pchar)+"! Absolutamente magnífico! Você provou que sua habilidade é incomparável. Aqui está sua recompensa – duzentos dobrões. Por favor, aceite!";
			Link.l1 = "Meu agradecimento a você! Mas me diga, você tem algum motivo para suspeitar que o assassino foi contratado por um dos seus antigos clientes?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Ex-clientes?.. Que absurdo!... Sou um homem honesto, e meus negócios sempre foram limpos! Mas já que você me ajudou, vou lhe contar uma coisa. Não faz muito tempo, piratas vieram até mim\nOfereceram dinheiro por informações sobre navios mercantes. Recusei, e eles me lançaram ameaças e xingamentos antes de saírem furiosos. Acredito que o assassino foi obra deles. Eles não aceitam um 'não' de bom grado.";
			Link.l1 = "Nesse caso, cuide-se. Quem sabe quantos mercenários esses 'piratas' ainda podem mandar? Com isso, preciso me retirar — o dever me chama.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Espere, Capitão. Quero agradecer mais uma vez. Além do ouro, você conquistou meu respeito. Enquanto eu for o Chefe do Porto aqui, pode deixar qualquer um dos seus navios atracado pelo tempo que quiser com cinquenta por cento de desconto. O que acha?";
			Link.l1 = "Uma oferta muito generosa! Muito obrigado mais uma vez!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "E agradeço mais uma vez pelos seus esforços. Tenho certeza de que, enquanto mantiver o foco no que importa, seus negócios continuarão prosperando como hoje. Até logo, Capitão.";
			Link.l1 = "Adeus.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_10");
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
