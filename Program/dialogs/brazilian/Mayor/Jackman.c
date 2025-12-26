// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Quis bancar o açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor dar o fora daqui...","Parece que você enlouqueceu, garoto. Queria se mostrar um pouco? Sem ofensa, mas você não tem nada pra fazer aqui. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Tem alguma coisa pra me dizer? Não? Então cai fora daqui!",
						"Acho que fui bem claro, pare de me irritar.","Apesar de eu já ter deixado tudo claro, você continua me irritando!",
						"Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.",
						"Claro, "+npchar.name+"...",
						"Desculpa, "+npchar.name+"...",
						"Ai...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Onde posso encontrar Jimmy Higgins?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "De novo eu aqui, Jackman. Dizem que você está procurando umas pessoas desaparecidas...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "É sobre o seu prisioneiro.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Olá, Jackman. Sobre a sua missão...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "É sobre o seu prisioneiro.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Queria bancar o açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor sair daqui...");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Tem alguma coisa pra me dizer? Não? Então cai fora daqui!",
						"Acho que fui bem claro, pare de me irritar.","Apesar de eu já ter deixado tudo claro, você continua me irritando!",
						"Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.",
						"Claro, "+npchar.name+"...",
						"Desculpa, "+npchar.name+"...",
						"Ai...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "É sobre o seu prisioneiro.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Sério! Alguém ainda se importa com esse vagabundo? Ele está bebendo rum sozinho na cabana dele faz dias. Eu não te aconselharia a ir atrás dele. Ele não é lá grande coisa, mesmo quando está sóbrio...";
			link.l1 = "Está certo, eu também não sou nenhum santo. Onde fica a cabana dele?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "Fica bem na frente da taverna. Ele escolheu um bom lugar pra dar uma escapada rápida e tomar um gole.";
			link.l1 = "Valeu!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "E quem te contou isso? Aquele bêbado do Higgins? Descobriu algo sobre a Gladys Chandler ou o Henry Carrasco?";
			link.l1 = "Nada de especial, na verdade, mas quero saber algo específico sobre aquele carrasco.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Não tem muito o que saber. Poucos ainda se lembram dele, mas há vinte anos o Henry era famoso entre as prostitutas de Bridgetown até Tortuga. Pode apostar! Era contramestre do 'Neptune', sob o comando do próprio Capitão Butcher! Deve estar bem velho agora, se ainda estiver vivo, claro.\nAs chances são pequenas, mas você sabe, nada é impossível. Pago vinte mil pesos por qualquer informação sobre ele, e o dobro se trouxer ele vivo até aqui.";
			link.l1 = "Quanto você vai pagar pela Gladys e pela filha dela?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Ah, ela não é filha dela. Se você trouxer aquela garota de volta viva, eu te pago uma pilha de dobrões. Não estou interessado na Gladys. Alguma pergunta?";
			link.l1 = "Queria saber o motivo desse alvoroço, mas não vou perguntar. Parece que isso pode encurtar minha biografia.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Talvez... Esses segredos não te dizem respeito. Quanto menos souber, mais tempo vai viver. Não me faça esse tipo de pergunta de novo, porque estou começando a achar que tem algo estranho em você. Cai fora antes que eu mude de ideia.";
			link.l1 = "Até mais, Barão!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! Nos encontramos de novo, Capitão "+GetFullName(pchar)+". Admito, você é um adversário digno, apesar de tentar se passar por tolo em Maroon-Town. Descobri algo sobre você, suas intrigas com a Companhia Holandesa das Índias Ocidentais foram reveladas... Agora entendo bem que tipo de pessoa você é.";
			link.l1 = "Eu também conheço o seu tipo, Jacob. Então vamos parar de nos enganar.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "E como você me enganou com o 'Marlin'! Suponho que meu pobre irmão esteja morto...";
			link.l1 = "Então você quer vingança por causa dele? Mas eu também tenho uma longa lista contra você. Pelo Nathaniel encurralado, pela esposa dele, pela fragata, pelo Tubarão caluniado, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? Eu não matei ele.";
			link.l1 = "Mesmo que seja verdade, o resto da minha lista já basta. Estou de saco cheio do seu nome. Chega de conversa, Jackman! Nossas lâminas vão falar por nós!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Que idiota impetuoso... Maldito seja! Agora é melhor se segurar! Jacob Jackman nunca foi derrotado! Carpacho, você chegou na hora certa! Venha aqui!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Você acha que só tenho um prisioneiro aqui? Diga o nome dele.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ele está aqui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Ele era. Eu o vendi para aquele fazendeiro de Barbados – o Coronel Bishop, quando ele esteve aqui há uma semana.";
				link.l1 = "Droga...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Eu já estava pensando em vendê-lo para aquele fazendeiro de Barbados, ele deve chegar em uma ou duas semanas... Você trouxe o resgate?";
				link.l1 = "Olha, tem um pequeno problema... Na verdade, eu não tenho tanto dinheiro assim. Mas estou disposto a trabalhar.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas – 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Você foi lento demais... E por que se importa com ele? Eu só estive negociando com os parentes dele.";
			link.l1 = "Me pediram para vir aqui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Bem, você está atrasado. Não posso fazer nada.";
			link.l1 = "Escuta, por quanto você vendeu ele, se não for segredo?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Ah, não é. Mas não vou te contar... Você vai rir se eu contar. Ha-ha-ha-ha! Adeus.";
			link.l1 = "Até mais...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Pois é, pois é... Tenho um assunto pra resolver... Nem sei por onde começar. Preciso afundar um pirata que passou dos limites.";
				link.l1 = "Ele não pode simplesmente ser morto na selva?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Bem, "+pchar.name+", sabe, não é assim que funciona. Volte com o dinheiro e vai levar seu fracote, ha-ha.";
				link.l1 = "Tá bom. Até mais.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Não é assim que os negócios funcionam, sabia... Não preciso que ele morra, só quero ensinar pra alguns que é melhor não mexer na minha parte do saque. Mas se ele acabar servindo de comida pros tubarões, não vou ficar chateado.";
			link.l1 = "Por que você mesmo não manda seus homens atrás dele?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Bem, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" convenceu alguns piratas de que a parte deles do saque está guardada no nosso esconderijo não muito longe de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Os dois navios deles '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' levantou âncora há pouco tempo e partiu para "+sLoc+". Agora você entende por que não posso confiar esse trabalho aos meus homens?";
			link.l1 = "Sim. Quanto tempo eu tenho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 a 15 dias, não mais que isso, eu acho. Não quero que eles cheguem ao esconderijo, senão seria inútil afundá-los com a carga valiosa. Nesse caso, seria melhor se eles trouxessem tudo pra cá...";
			link.l1 = "Tá bom, eu topo. Vou tentar pegá-los.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Não se preocupe. Meus homens vão levá-lo até o seu navio. E por que você se importa com ele?";
			link.l1 = "Não. Os parentes dele me pediram para entregá-lo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, tudo bem. Quase fiquei com pena de oferecer um preço tão baixo pelo seu homem. Ha-ha-ha-ha. Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Então, , "+GetFullName(pchar)+", você afundou meu camarada? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Não. Não consegui pegá-los. E também não os encontrei no caminho de volta.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Fui eu. Mandei eles virarem comida de tubarão.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Droga! Se eu os encontrei ou não, tanto faz agora! E qual vai ser sua próxima sugestão?";
			link.l1 = "Talvez você tenha um trabalho mais fácil pra mim?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Escuta, Jackman, abaixa o preço pelo prisioneiro...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Não.";
			link.l1 = "Adeus então...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Baixar o preço? Acabei de perder meu estoque por causa da sua incompetência! Agora é que eu posso aumentar o preço! Pode levar ele por 200.000 pesos se quiser, ou então cai fora daqui.";
			link.l1 = "Está caro demais... Adeus...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Droga, pega suas moedas.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Tá bom, pode levar esse fracote...";
			link.l1 = "Adeus.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Muito bem! Leve seu fracote e boa sorte.";
			link.l1 = "Obrigado. Adeus.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Trouxe o dinheiro, Charles? Eu não estava brincando sobre vender o homem para a plantação.";			
			link.l1 = "Escuta, "+NPChar.name+", tem um problema... Eu não tenho tanto dinheiro assim. Mas estou disposto a trabalhar.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas - 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo! Isso é inaceitável! Prepare-se, "+GetSexPhrase("garoto","garota")+"...","Ei, que diabos você está fazendo aí?! Achou que podia me roubar? Você está acabado...","Espera aí, que porra é essa? Tira as mãos de mim! Então você é um ladrão! Chegou seu fim, desgraçado...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!!","Droga!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Saia daqui!","Saia da minha casa!");
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me venha com essa conversa fiada. Da próxima vez, você não vai gostar do resultado...";
        			link.l1 = "Entendi.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Acabou, sem conversa.""Não quero mais falar com você, então é melhor não me incomodar.";
			link.l1 = RandPhraseSimple("Como quiser...","Então tá...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que você mostre mais respeito e pare de ser grosseiro. Caso contrário, vou ter que te matar. Isso seria bem desagradável.";
        			link.l1 = "Pode ter certeza, Jackman, eu vou.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Resolver o problema? Você faz ideia do que fez? Enfim, traga-me um milhão de pesos e eu convenço os rapazes a esquecerem suas 'proezas'. Se não gostar da ideia, pode ir para o inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Certo, estou pronto para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Entendi. Estou indo embora.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Ótimo! Considere-se limpo de novo. Mas espero que não volte a fazer coisas tão nojentas.";
			link.l1 = "Não vou. Muito caro pra mim. Adeus...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Já falamos sobre isso hoje.",
													  "Fui pouco claro?",
													  "Sua insistência já está passando dos limites.",
													  "Já estou de saco cheio. Cai fora!",
													  "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Então, deixamos pra outra vez...",
												   "Claro, "+npchar.name+"...",
												   "Desculpa, "+npchar.name+"...",
												   "Ai...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! A galera da nossa irmandade tá pegando no seu pé, né, " + GetSexPhrase("camarada", "amiga") + "? Claro que posso conter eles por um tempo. Mas você vai ter que desembolsar uma boa grana. " + FindRussianDublonString(iBarbazonTotalTemp) + " na mesa e temos um acordo.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Claro, aqui está o seu dinheiro.";
					else link.l0 = "Parece que não tenho escolha. Aqui está o seu dinheiro.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Acho melhor voltar outra hora...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Você ficou maluco" + GetSexPhrase("", "a") + "? Nossos caras fogem de você como o diabo foge da cruz. Some daqui e para de encher!";
				else
					dialog.text = "Do que você tá falando, " + GetSexPhrase("camarada", "amiga") + "? Você é uma dor de cabeça — até os cachorros sentem isso. Ninguém quer se meter contigo.";
				link.l1 = "Entendi...";
				link.l1.go = "exit";
			}
		break;
		
		case "pirate_threat_pay":
            iGPThreatRate = 0;
            iGPThreat = 0;
            SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
            DialogExit();
            PiratesDecreaseNotif("");
		break;
	}
}
