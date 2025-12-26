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
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já fez essa pergunta pela terceira vez hoje...","Olha, se não tem nada a me dizer sobre assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não me interesso por assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Estou navegando para Blueweld para vender um pouco de páprica. Me diga, senhor, você tem algum passageiro indo para Blueweld? Ou pelo menos para Port Royal. Seria ótimo ganhar um dinheiro com um passageiro, ajudaria a pagar os salários da tripulação. Já reduzi ao mínimo, mas esses desgraçados preguiçosos ainda pedem dinheiro...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Havia um galeão chamado 'Admirável' fretado em Philipsburg sob o comando de Gaius Marchais. Ele deveria entregar uma carga de páprica aqui. Você pode me ajudar a encontrar esse capitão?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Queria perguntar sobre um xebec com um nome estranho.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Ouvi dizer que um xebec pertencente a um capitão Jack... ou Jackson costuma visitar seu porto. Você poderia me dizer onde posso encontrá-lo?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Infelizmente, não há passageiros para Blueweld ou Port-Royal. Volte amanhã ou depois.";
			link.l1 = "Que pena. Então, adeus.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
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
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Você quebrou as regras da regata e eu preciso desclassificá-lo. Sinto muito. Você não participará da próxima viagem. Já preparei um despacho para Port Royal.";
				link.l1 = "Ah... que pena! Mas não há nada que eu possa fazer aqui, você foi atento demais. Adeus!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Talvez tenha notado, capitão, que a cidade está sitiada. Esperamos um ataque dos espanhóis a qualquer momento e estamos mobilizando nossas forças. Mas a regata continua acontecendo\nVamos nos inscrever, capitão "+GetFullName(pchar)+", o navio está - "+pchar.Ship.Name+"... Tempo da regata em horas é "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Pronto, seu resultado foi registrado, você pode seguir seu caminho.";
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
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, sim... Me desculpe, eu estava ocupado demais para isso. Você é o primeiro.";
			link.l1 = "Entendi. Obrigado pela informação.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, sim... Me desculpe, estou ocupado demais para isso. Você é o último.";
				link.l1 = "Entendi. Obrigado pela informação.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, sim... Me desculpe, estou ocupado demais para isso. Você é o segundo. Só tem um capitão na sua frente. O nome dele é "+sName+" no navio "+sShip+".";
						link.l1 = "Entendi. Obrigado pela informação.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ah, sim... Me desculpe, estou ocupado demais para isso. Seu posto é "+n+" . Seu oponente mais próximo é "+sName+" no navio "+sShip+".";
						link.l1 = "Entendi. Obrigado pela informação.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Sim, esse galeão esteve aqui, descarregou suas mercadorias e depois deixou nosso porto. Informação sobre o destino dele... hm... nenhuma, não há nada. Sinto muito, mas não posso fazer nada.";
			link.l1 = "Entendi. Que pena... Vou continuar procurando por isso.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Senhor, preciso do nome exato do navio. Temos muitos Jacks e Jacksons passando pelo nosso porto. Então, qual é o nome?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "O problema é que eu não sei o nome do velho barco dele. É estranho, uma mulher meio esquisita, dizem que nasceu...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Senhor, vá contar suas histórias e enigmas na taverna, aqui temos um estabelecimento respeitável. Ou me diga o nome daquele xebec, ou pare de me atrapalhar no meu trabalho.";
			link.l1 = "Certo, vou tentar descobrir.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "E então? Você tem o nome do navio? Estou ouvindo.";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? Claro, eu conheço esse xebec. O capitão dele é Reginald Jackson. Mas ele não está em Bridgetown há muito tempo. Ouvi dizer que agora ele trabalha para a Companhia Holandesa das Índias Ocidentais. Então você deve procurá-lo em Willemstad.";
				link.l1 = "Muito obrigado! Você me ajudou bastante.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Sinto muito, mas isso não me é familiar. Tem certeza de que seu capitão já esteve aqui, em Bridgetown?";
				link.l1 = "Tenho certeza. Tudo bem, talvez eu pense em alguma coisa ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
