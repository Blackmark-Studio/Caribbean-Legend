void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug. Não se esqueça de avisar os desenvolvedores.";
			link.l1 = "OK";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Saudações, capitão. Quer alguma coisa de mim?";
			link.l1 = "Sim. Exatamente. "+GetAddress_FormToNPC(NPChar)+". Há um passageiro no seu navio que me interessa bastante. O nome é "+pchar.GenQuest.Marginpassenger.q1Name+". Quero que seu passageiro se torne meu passageiro. Se você concordar com isso, então vamos seguir caminhos diferentes e nunca mais nos veremos.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "É mesmo? E se eu disser não?";
			link.l1 = "Então vou ter que te fazer reconsiderar sua decisão com algumas rajadas dos meus canhões, que estão apontados na sua direção neste exato momento. Não force a sorte, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Então não tenho escolha. O destino da minha tripulação vale mais para mim do que o de um só homem. Mas você não vai se safar tão fácil! Eu não vou esquecer isso!";
				link.l1 = "Calma, e poupe-se de um ataque do coração... Traga meu novo passageiro!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "É melhor você sair do meu navio, senhor, enquanto ainda permito. Não tente me intimidar. E nem pense em atacar meu navio, ou será expulso imediatamente. Saia, enquanto ainda estou de bom humor!";
				link.l1 = "Eu te avisei. Estou a caminho. Até logo, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Já tivemos essa conversa, lembra? Saia do meu navio!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Maldito! Queime no inferno pelos seus atos!";
				link.l1 = "Eu te dei a chance de entregar o passageiro em paz... e você recusou minha oferta. Agora a culpa é só sua!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Maldito! Por que você atacou este navio pacífico? Não temos ouro nem mercadorias valiosas!";
				link.l1 = "Mas você tem uma pessoa valiosa a bordo..."+pchar.GenQuest.Marginpassenger.q1Name+". Eu quero o seu passageiro.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Você... é o pirata imundo!";
			link.l1 = "Menos conversa, meu amigo...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "E é por isso que você cometeu um massacre no meu navio? Muitos homens estão mortos! Pirata!";
			link.l1 = "Menos conversa, meu amigo...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "O que você quer, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Você é "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Sim, sou eu. Quer se inscrever? Então saiba que...";
			link.l1 = "Espere um instante, senhor. Tenho um pedido um pouco diferente... Você conhece alguém chamado "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Sim, eu conheço ela... Claro que conheço! O que aconteceu?";
					link.l1 = "Ela se viu numa situação bem desagradável: o navio dela foi capturado por piratas. Por sorte, eu consegui subir a bordo e salvar a pobre coitada. Ela me contou seu nome, e aqui estou eu.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Sim, eu conheço muito bem esse homem. O que houve?";
					link.l1 = "Ele se meteu numa situação bem desagradável: o navio dele foi capturado por piratas. Por sorte, consegui subir a bordo do navio deles e resgatar esse prisioneiro. Ele me disse seu nome, e aqui estou eu.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Meu Deus! Onde ela está agora? Por que você não a trouxe aqui?";
			link.l1 = "Ela está a salvo. E quanto à sua pergunta... não é tão simples assim. Eu mesmo poderia tê-la levado de volta para casa, mas posso dar essa oportunidade a você. Por uma quantia modesta, é claro.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Não entendi...";
			link.l1 = "Why don't you? You pay me in gold, I give you the girl, and you can use this situation to your advantage... You want to marry her, am I right? And I'll repair my ship with those coins; she was damaged during that fight with the pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Meu Deus! Onde ele está agora? Por que você não o trouxe aqui?";
			link.l1 = "Ele está seguro. E quanto à sua pergunta... não é tão simples assim. Eu poderia tê-lo levado de volta para casa, mas posso te dar essa oportunidade, já que você tem seus próprios interesses na família dele. Por uma taxa modesta, é claro.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm... Eu não entendo...";
			link.l1 = "Why don't you? You pay me in gold, I'll give you your friend, and you'll be able to use this situation to your advantage. I have some information, you know... I'll repair my ship with those coins; she was damaged during that fight with pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Então, então... e quanto você quer?";
			link.l1 = "Tenha em mente, eu quero dobrões, não pesos.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Tá bom, tá bom... Então quantos dobrões você quer?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Muito engraçado. Tá bom, vamos fingir que sua piada foi realmente engraçada. Adeus!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Certo, eu concordo. Tenho o valor necessário. Onde está "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Deve estar no cais agora. Então pode ir buscar o passageiro.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Me desculpe, mas não tenho tantos dobrões assim. Pesos servem?";
				link.l1 = "Quero dobrões, mas suponho que o mestre do navio aceite pesos... Me dê eles.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Não, só preciso de doblões.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Infelizmente, não tenho essa quantia. Então não posso aceitar sua proposta, por mais que eu queira.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Senhor, o senhor ao menos entende do que está falando? Tem noção de que essa quantia é absurda? Cai fora daqui!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Bem... Senhor, o senhor precisa ver um médico imediatamente. Parece que está com febre alta ou... enfim, precisa de um médico. E eu estou muito ocupado. Adeus!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Aqui está, a soma inteira em pesos, exatamente como você pediu... Onde está "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Já deve estar no cais agora. Então você pode ir buscar o passageiro.";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*500;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Não posso aceitar sua proposta então, por mais que eu quisesse. Adeus!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "O que... O que está acontecendo aqui?!";
			link.l1 = "É muito simples, "+NPCharSexPhrase(NPChar,"amigo","garota")+". Agora você é meu passageiro querido. Um passageiro sob vigilância. Não tente resistir ou vai acabar no porão de carga.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Você quer dizer que eu sou seu prisioneiro?";
			link.l1 = "Ah, não. Claro que não. Não é um prisioneiro, mas sim um convidado querido. Um convidado muito valioso...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Você... você vai pagar pelo que fez!";
			link.l1 = "Você está errado de novo,"+NPCharSexPhrase(NPChar,", camarada",", querido")+". Eu não vou pagar, mas vou receber. Chega de conversa, vá para sua cabine!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
