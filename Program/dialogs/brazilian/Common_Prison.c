// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Eu sou o diretor da prisão. O que você precisa aqui?","O que você quer? Por que veio até a prisão?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Senhorita MacArthur? Que surpresa vê-la aqui. Até onde eu sei, não prendemos ninguém da sua tripulação nem da do Capitão Swenson.";
				link.l1 = "Eu só estou aqui, senhor. Isso não é permitido? Eu não estava conversando com os prisioneiros pelas suas costas.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ah, Charles de Maure... Você deveria ser preso e se juntar ao seu oficial, mas... o incidente no banco foi considerado um lamentável mal-entendido.";
				link.l1 = "Gosto do jeito que você começou essa conversa, senhor. "+GetFullName(NPChar)+". Eu posso explicar tudo.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Oficial, ouvi dizer que há um homem chamado Folke Deluc na sua prisão. Há algo que eu possa fazer para conseguir a libertação dele?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Oficial, sou eu de novo sobre o prisioneiro Folke Deluc. Comprei os direitos da dívida dele e quero que esse homem seja liberado sob minha custódia. Aqui estão os papéis da dívida, dê uma olhada.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Saudações, capitão. O que o traz aqui?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saudações, Vice-Almirante! Como posso ajudar?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Sua Excelência, Governador-Geral! Tem alguma ordem?";
			}
			// <-- legendary edition
			link.l1 = "Ah, nada de especial, sabe, só estou dando uma olhada pela cidade, acabei vindo parar aqui por acaso.";
			link.l1.go = "exit";
			link.l2 = "Queria conversar sobre alguns negócios.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Quero entrar na prisão.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Ei, você poderia me dizer qual foi o crime cometido pelo condenado chamado "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"está cumprindo pena por quê?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Ouvi dizer que o antigo capitão de uma patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" está sendo mantido aqui sob custódia. Posso falar com ele?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Eu "+GetFullName(pchar)+", agindo em nome e sob as ordens do governador "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"preciso falar com o antigo capitão "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Isto é sobre sua filha...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Tenho negócios com você, oficial. Acredito que isso vai lhe interessar, pois está relacionado às suas funções.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Quero falar com você sobre um certo homem - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". Ele é seu prisioneiro, se não me engano.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Olá, oficial. Pelo que eu sei, algum tempo atrás, um cidadão bêbado foi detido depois de tentar brigar com um guarda nas ruas."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Oficial, falei com o sentinela e ele retirou as acusações. Aqui está um comprovante dele."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Sim? O que você deseja me dizer?";
			link.l1 = "Recentemente, fui parado na rua por "+pchar.GenQuest.Marginpassenger.Name+" que se ofereceu para organizar um serviço sujo para mim: capturar e depois pedir resgate por uma pessoa chamada "+pchar.GenQuest.Marginpassenger.q1Name+". É "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... Isso é muito interessante - por favor, continue!";
			link.l1 = "Ele sabia o nome do navio em que estava, "+pchar.GenQuest.Marginpassenger.q1Name+" estava planejando zarpar. É "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" chamado de '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Além disso, ele me contou a hora em que aquele navio deveria zarpar.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "E ele sugeriu que você capturasse o passageiro e depois exigisse um resgate por ele?";
			link.l1 = "Exatamente. Para receber o resgate, eu iria até "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", para uma certa pessoa chamada "+pchar.GenQuest.Marginpassenger.q2Name+". Eu paguei por essa informação, mas é claro que eu não ia sequestrar aquela pessoa.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Então você decidiu vir me ver e me avisar?";
			link.l1 = "Exatamente. Tenho certeza de que as ações desse canalha ameaçam os cidadãos da sua cidade, e espero que você tome as medidas adequadas.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Você estava absolutamente certo quando veio até mim, "+GetAddress_Form(NPChar)+"! Esse canalha, "+pchar.GenQuest.Marginpassenger.Name+", está sob nossa vigilância há muito tempo. Vou investigar e, se tudo o que você disse for confirmado, vamos jogar esse canalha na cadeia por meio ano. Isso vai ensinar a ele a não tramar essas artimanhas contra cidadãos respeitáveis!\nBem, pela sua honestidade e disposição em servir a uma boa causa, certamente vou relatar seu feito ao nosso governador, o que, claro, vai influenciar a opinião dele sobre você... de um jeito positivo, é claro. Obrigado pela ajuda, capitão!";
			link.l1 = "Hum... De nada, foi um prazer ajudar. Adeus!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Trouxe o seu fugitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitão, muito obrigada! Como ela está? Ela se machucou? Por que ela fugiu? Por quê?\nEla não entende? O noivo é um homem rico e importante! A juventude é tão ingênua e tola... até cruel. Lembre-se disso!";
			link.l1 = "Bem, você é o pai dela e a decisão final é sua, mas eu não me apressaria com o casamento...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "O que você sabe? Você tem filhos? Não? Quando tiver um, venha falar comigo, aí conversamos.\nPrometi uma recompensa para quem a trouxesse de volta para a família dela.";
			link.l1 = "Obrigado. Fique de olho nela. Tenho a impressão de que ela não vai parar por aí.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Estou ouvindo, capitão.";
			link.l1 = "Quero lhe contar sobre uma conspiração criminosa entre um oficial da sua guarnição e piratas (explica a situação).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Obrigado,"+GetSexPhrase("senhor","senhorita")+"! Vou dar ordem para prender o canalha imediatamente.\nNo entanto, você teve despesas, e os cofres municipais, infelizmente, estão vazios...";
				link.l1 = "Senhor! Eu não fiz isso pelo dinheiro...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Obrigado, "+GetSexPhrase("senhor","perder")+"! Vou imediatamente dar a ordem para prender o canalha.\nSó de pensar! Estávamos prestes a recompensá-lo com uma arma pessoal pelo excelente serviço. Que sorte que tudo foi esclarecido, e não tenho nada do que me envergonhar!";
				link.l1 = "Sempre feliz em fazer justiça.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("ster","ss")+"!   Já estávamos desconfiando daquele oficial e dos seus capangas há um bom tempo, mas acho que você foi precipitado ao lidar com eles sem testemunhas.";
				link.l1 = "Senhor! Mas eu precisei me defender...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Capitão, você tem ideia do que fez?! Passamos mais de um mês preparando essa armadilha! E agora, só para se divertir, você estragou o encontro entre nossa patrulha e o mensageiro "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" e agora você vem aqui se gabar?! Talvez agora você possa me dizer como devo explicar todas as despesas e custos desta operação?!";
				link.l1 = "Sua Graça! Você simplesmente se recusa a entender o que estou dizendo...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Deixe-me ver esse mapa...\nVocê está brincando comigo? Esse pedaço de pergaminho rasgado é a prova?";
				link.l1 = "Vossa Graça! Você simplesmente se recusa a entender o ponto...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Agora essa é uma justificativa original para a destruição de toda a patrulha. Bem, pelo menos vindo até aqui você nos poupou o trabalho de procurar o assassino.";
				link.l1 = "Vossa Graça! Você simplesmente se recusa a entender o que estou dizendo...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Muito obrigado, isso é muito generoso da sua parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Seu zelo é admirável. Por favor, aceite esta espada como recompensa – é o mínimo que posso fazer por você. Ah, e pode ficar com este mapa para você. Tenho certeza de que há muitos desses falsos pelo Arquipélago.";
			link.l1 = "Muito obrigado, isso é muito generoso da sua parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Pode ser, pode ser... Bem, digamos apenas que este acordo foi decidido pela justiça divina e pela vontade do nosso Senhor.";
			link.l1 = "Muito obrigado, isso é muito generoso da sua parte!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Não ouse me dar lição de moral! Pra mim, está claro que você está colaborando com esses canalhas! Guardas, prendam esse 'benfeitor'!";
			link.l1 = "De jeito nenhum!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "E que assunto você tem com ele?";
			link.l1 = "Tenho vários assuntos particulares para discutir.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Capitão, tenho ordens diretas para deter e encaminhar para a residência qualquer um que perguntar sobre "+pchar.GenQuest.CaptainComission.Name+"para mais interrogatório.";
			link.l1 = "Belo esquema o seu aqui! Os prisioneiros vêm até você para serem presos!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "E ainda assim, eu peço que entregue suas armas!";
			link.l1 = "Vai se ferrar! Então pega de mim à força, vai!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Sim, claro. Tenho ordens do governador para lhe prestar assistência neste assunto. Agora você pode visitar o prisioneiro.";
			link.l1 = "Obrigado...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ehm, capitão, eu não tenho autoridade para liberar este prisioneiro da custódia. Você precisa pedir permissão ao governador.";
			link.l1 = "Oficial, estou agindo pelo bem da investigação. O prisioneiro concordou em cooperar com as autoridades e revelar o esconderijo. O tempo é crucial – os contrabandistas podem encontrar a carga valiosa, e então ela estará perdida para o povo.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Você não devia tê-lo matado, Capitão... Mas isso não faz diferença pra mim. Teremos que executar você no lugar dele. Guardas! Peguem-no!";
            link.l2 = "Você escolheu o homem errado para se meter!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Mas eu poderia designar uma escolta para ele.";
			link.l1 = "Não precisa - já tenho guardas suficientes. Além disso, não quero que o local do esconderijo se torne público.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hum... ah, tudo bem. Mas você vai responder por ele com a sua cabeça.";
			link.l1 = "Claro.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Fale agora, estou ouvindo.";
			link.l1 = "Tenho aqui alguns documentos de navio. O dono deve ter perdido, e acredito que isso possa te interessar.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Besteira! Não me distraia do meu trabalho! Vá falar com as autoridades portuárias se você se importa!";
				link.l1 = "Bem, obrigado, eu acho...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Sim, é o dono local. Talvez um prêmio de "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pesos serão uma recompensa adequada pela sua vigilância, capitão.";
					link.l1 = "Talvez não.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Uma oferta generosa. Os documentos são seus, então!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Ah, isso é realmente interessante! Acredito que o tesouro da cidade vai pagar você com prazer "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" pesos pela sua contribuição no combate ao comércio ilegal.";
						link.l1 = "Talvez não.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Uma oferta generosa. Os documentos são seus, então!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Meu Deus! Que sorte boa você ter vindo até mim. Imagino que meu colega azarado vai lhe pagar com prazer "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pesos para evitar que este caso venha a público.";
						link.l1 = "Talvez não.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Uma oferta generosa. Os documentos são seus, então!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Esta é a minha cidade, capitão.";
			link.l1 = "Vou me lembrar disso.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Claro, pode ver tudo – está tudo em perfeita ordem aqui!";
				link.l1 = "Bem, vamos dar uma olhada, Tenente.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Claro, Sua Excelência. Pode passar.";
				link.l1 = "Obrigado, oficial.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Bem, não vejo motivo para recusar você – afinal, você é o capitão do navio a serviço de "+NationNameGenitive(sti(npchar.nation))+". Pode entrar."; 
				link.l1 = "Obrigado, oficial.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Mas por que você precisa disso? Acredite, não há nada de interessante lá, só ladrões e bandidos.","Já tínhamos conversado sobre esse seu desejo.","De novo? Já falamos sobre isso duas vezes!","Hum, de novo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No entanto, eu gostaria de acompanhar sua visita às casamatas. Estou muito interessado!","Sim, exatamente. Mas eu queria conversar sobre isso.","Bem, talvez na terceira vez...","Espero que seus prisioneiros não me deixem na mão.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Bem, não vejo motivo para recusar. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - e até você sair da prisão, pode andar livremente pelos corredores e até conversar com os outros presos.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Concordo, aqui estão suas moedas!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Isso não vai funcionar. É demais só pra ficar vagando sem rumo pelos corredores.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Não, isso é estritamente proibido pelos regulamentos. O quê? Você acha que isso aqui é um circo? Cai fora e não me atrapalhe no meu trabalho.","Não posso permitir que estranhos andem pela minha prisão. Por favor, pare de me incomodar!");
				link.l1 = "Certo, como você quiser...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Certo, você pode começar sua excursão agora...";
			link.l1 = "Obrigado, oficial.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Entendo... Entregue-o a mim, oficial, e eu mesmo decidirei o destino deste prisioneiro.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Entendo... Entregue-o a mim, oficial, e eu mesmo decidirei o destino deste prisioneiro.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Entendo... E existe a possibilidade de um resgate, fiança... ou de libertá-lo de alguma outra forma?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Claro que não. Aquele desgraçado vai direto pro inferno. O governador está cuidando pessoalmente do caso dele!";
			link.l1 = "Heh, entendi...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Está brincando? Ele deve ter ido para a forca faz tempo! Logo vai se casar com a corda. Esquece isso.";
			link.l1 = "Entendi. E já esqueci...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Acho que não. Ele já causou muitos problemas para o nosso povo. Então, nem peça por isso.";
			link.l1 = "Hum, entendi.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Provavelmente não. Ele é um ladrão, e ladrão tem que ficar na cadeia.";
			link.l1 = "Oh! Muito bem dito, tenente!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Eu realmente não sei. Ele só roubou uma coisa sem valor. Não posso soltá-lo, mas deixá-lo apodrecer na cadeia também não está certo.";
			link.l1 = "Então me entregue ele, tenente. Eu pago a fiança — uma quantia razoável, é claro.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Soltar? Parece provável. Na minha opinião, não faz sentido manter esse criminoso de quinta aqui.";
			link.l1 = "Então, entregue-o para mim, tenente. Vou pagar a fiança dele – um valor razoável, é claro.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hum... Faz sentido o que você diz. Esse vagabundo não pertence a este lugar – só está espalhando sujeira e doença...";
			link.l1 = "Então, entregue-o a mim, tenente. Vou pagar a fiança por ele – uma quantia razoável, é claro.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Certo, temos um acordo. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" na hora, e você pode levá-lo agora mesmo.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Excelente! Concordo!","Está fechado, oficial!","Excelente. Estou pronto para pagar essa contribuição.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Não, isso está caro demais. Acho que vou deixar passar.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Certo, você pode ir até a cela dele e levar esse moleque com você.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Bem, a escolha é sua. Não vou te dar outra chance...";
			link.l1 = "Não precisa.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Claro, excelência, se assim desejar, leve este infeliz. Só tome cuidado, ele ainda é um criminoso...";
			link.l1 = "Ótimo. Não se preocupe, tenente, eu sei o que estou fazendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Bem... Eu nem sei direito... Na verdade, não posso simplesmente soltar os prisioneiros. Mas você ainda é vice-almirante, então provavelmente tem o direito de levar esse criminoso.";
			link.l1 = "Isso é ótimo. Não se preocupe, tenente, eu sei o que estou fazendo.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Governador Geral, Vossa Excelência! Entre, mas tome cuidado: pode esperar qualquer coisa desses criminosos...";
				link.l1 = "Não se preocupe, soldado, eu cuido disso se acontecer alguma coisa.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saudações, Vice-Almirante! Estou de serviço aqui: garanto que ninguém entre ou saia sem permissão. Mas você, é claro, tem o direito de passar livremente.";
				link.l1 = "Bem, isso é maravilhoso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Pode passar, o guarda autorizou.","Recebi uma ordem do diretor da prisão. Você pode passar livremente.");
				link.l1 = "Muito bom.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Você não pode passar daqui sem permissão específica do diretor da prisão!","Eu só respondo ao diretor da prisão! Se tentar ir além sem a permissão dele, você está perdido!");
				link.l1 = RandPhraseSimple("Entendi","Certo")+", soldado.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Estou de serviço, não me incomode.","Segue em frente, não posso falar com você.");
			link.l1 = "Tudo bem, soldado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, não é um ótimo momento!","Corte-os, "+GetSexPhrase("companheiro","moça")+", corta!!!","Ah, inferno! Eu já tinha perdido toda a esperança de ver o cadáver do meu carcereiro!");
				link.l1 = RandPhraseSimple("Heh!","Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Espere, "+GetSexPhrase("companheiro","moça")+"!! Me solte!","Escute, "+GetSexPhrase("companheiro","moça")+", por favor, abra a cela.");
					link.l1 = "Por qual motivo?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Me acusam de roubo, mas eu não sou culpado!","Arrgh, seu canalha bem arrumado... Quer passar um tempinho na minha cela?! Kheh-heh-heh...","Eu não sou culpado!");
				link.l1 = RandPhraseSimple("Cale a boca!","Eu não dou a mínima pra você...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Espere, "+GetSexPhrase("companheiro","moça")+", não vá com tanta pressa!","Não se apresse, "+GetSexPhrase("companheiro","moça")+", vamos conversar.");
					link.l1 = "Por qual motivo?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Escuta aqui, camarada. Não pense que eu não estou bem ou algo assim. Só preciso sair daqui...";
			link.l1 = "O quê?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "O que você ouviu! Me dá uma força, que eu vou te recompensar...";
			link.l1 = "Isso é interessante. Quem é você, e o que pode me oferecer?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Meu nome é "+GetFullName(npchar)+". Eu tenho algumas coisas guardadas em um lugar seguro. Só me tire daqui e me leve para "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Lá, numa gruta, está o tesouro. Vamos pegar e dividir!";
			link.l1 = "E o que você tem guardado no seu esconderijo? E como posso saber se está falando a verdade?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Eu juro que estou dizendo a verdade! Quanto ao esconderijo – tem tesouro e dinheiro...";
			link.l1 = "Não, amigo. Não vou arriscar meu pescoço por um tesouro duvidoso. Me desculpe...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Bem, talvez valha a pena arriscar... Eu proponho o seguinte: posso eliminar os guardas da prisão e te levar para o meu navio. Se tudo der certo, quero que fique ao meu lado o tempo todo até chegarmos à gruta em  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Fechado?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Certo, vou tentar te ajudar. Vou falar com o chefe da prisão. Talvez eu consiga te tirar daqui sob fiança.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Certo, vou confiar em você e abrir sua cela. Quero que fique ao meu lado o tempo todo até chegarmos à gruta em "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Fechado?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Maldito seja, seu canalha!","Maldito seja, você me roubou, seu canalha...");
			link.l1 = RandPhraseSimple("E tudo de bom pra você também. Adeus...","A lua não precisa dos latidos dos cães...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Tudo bem. Não estou em posição de escolher.";
			link.l1 = "Certo. Vou arrombar sua fechadura agora pra te tirar daqui, e depois a gente segue em frente. Está pronto?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Sim, "+GetSexPhrase("companheiro","moça")+", estou pronto!";
			link.l1 = "Então vamos nessa!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Tudo bem. Não estou em posição de escolher.";
			link.l1 = "Certo. Venha comigo o mais rápido que puder – ainda precisamos chegar ao meu navio. Não demore!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Bem, você pode tentar. Espero que a gente consiga! Mas não perca tempo – em alguns dias eu vou estar fora daqui...";
			link.l1 = "Espere aqui, vou resolver tudo.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Então, o que me diz, "+GetSexPhrase("companheiro","moça")+"?";
			link.l1 = "Está tudo acertado, posso te levar daqui.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Então vamos sair daqui! Meu Deus, como estou feliz!";
			link.l1 = "Vamos resumir. Quero que fique ao meu lado o tempo todo até chegarmos à gruta em "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", você não vai ficar mais do que um passo atrás. Só por precaução. Concorda?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Claro, eu concordo! Ainda mais porque não estou em posição de escolher.";
			link.l1 = "Então você está livre.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Então, o que me diz, "+GetSexPhrase("companheiro","moça")+"?";
			link.l1 = "Não consegui providenciar sua libertação. Você está sendo acusado de "+sTemp+", então você não pode ser libertado sob fiança.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Mas fui caluniado! Ah, diabo! E o que vou fazer agora? Vou apodrecer aqui vivo!";
			link.l1 = "Desculpe, camarada, mas não posso fazer nada por você.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Só resta uma chance – libertar você à força. Vou arrombar sua fechadura agora para te tirar daqui, e vamos abrir caminho juntos. Está pronto?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Maldito seja!","Maldita, você me roubou, sua desgraçada...");
			link.l1 = "E tudo de bom pra você também. Adeus...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Então, alguma novidade boa, "+GetSexPhrase("companheiro","moça")+"?";
			link.l1 = "A fiança para sua libertação é alta demais, eu não tenho esse dinheiro. Vou ter que parar de te ajudar.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Olha, eu revirei tudo, mas não achei nenhum tesouro. Uma pena que acabou assim. Alguém deve ter desenterrado antes da gente.";
					link.l1 = "E como isso é possível?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Eu encontrei! O tesouro ainda está onde eu deixei.";
					link.l1 = "Excelente. Então, vamos nos separar?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Bem, aqui está, meu esconderijo. Não é muita coisa, mas é tudo o que eu tenho. Como combinamos, metade é sua.";
					link.l1 = "É, o tesouro é modesto mesmo. Bem, ainda é melhor do que nada.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Capitão, me desculpe, mas... Não existe nenhum tesouro.";
					link.l1 = "O quê?! Você me enganou, seu canalha! Eu te levei até aquela ilha – e pra quê? Você não vai sair impune dessa!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Olha, eu revirei tudo, mas não achei nenhum tesouro. É uma pena que tenha sido assim. Alguém deve ter desenterrado antes da gente.";
                        link.l1 = "E como isso é possível?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Maldição... Como isso pode ser? Não é possível!";
                        link.l1 = "O que está acontecendo, camarada? Onde está o tesouro? Não me diga que não tem nenhum!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Claro, como combinado. Metade do tesouro é sua.";
			link.l1 = "Santo Deus, tem mesmo muita coisa valiosa!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Capitão, tem também aquele artefato indígena entre outras coisas. Você pode ficar com ele além da sua parte.";
			link.l1 = "Bem, pelo menos algo de valor pelo seu resgate! Entregue agora.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Espere, Capitão, não se exalte, deixe-me explicar. Eu também sou marinheiro, assim como você. Fui preso por engano, eu juro. Você era minha única chance de escapar, e eu precisei mentir sobre o tesouro.\nNão existe tesouro, mas escondi uma coisa valiosa lá. Pegue, e me deixe ir em paz. Quem sabe, em uma batalha um dia, isso possa te ajudar a sobreviver.";
			link.l1 = "Tá bom, eu também não esperava muito de você. Ainda bem que não sou de guardar rancor.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Não!!! Não está aqui! Maldito papel... Capitão, eu tinha certeza absoluta de que encontraria aqui! Mas pelo visto, me enganei! Tinha algo naquele pedaço de papel que estava realmente confuso...";
			link.l1 = "Ah, então... Você está encrencado de verdade, meu amigo. Mas ainda assim quero ouvir sua explicação.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Eu tinha um pedaço do mapa. Era um mapa de verdade, eu juro! Mas é muito difícil dizer qual ilha estava desenhada nele... Eu achei que era aqui... Mas, como você pode ver agora, eu estava enganado.";
			link.l1 = "Que pedaço de papel? Me entregue isso agora mesmo!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Claro, pode pegar. Capitão, me solte... por favor? Eu realmente acreditei que o tesouro estava lá. Talvez você descubra onde está e fique com ele para você. Eu te imploro.";
			link.l1 = "Entendo... Realmente, é difícil tirar alguma coisa desse pedaço. Preciso da segunda metade do mapa. Certo, suma daqui. Agora vejo que não foi culpa sua.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Muito simples, "+GetSexPhrase("companheiro","moça")+". Tudo na vida acontece.\nBem, você está aqui - se quiser: fique, procure por mais. Bem, eu preciso ir!\nAdeus, "+GetSexPhrase("meu amigo","moça")+", obrigado por salvar minha vida. Vou me lembrar de você para sempre!";
			link.l1 = "Canalha! Você acha que vou deixar você sair dessa?! Ei! Espera aí, covarde!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Aqui está. Obrigado!";
			link.l1 = "Adeus...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Obrigada, capitão! Vou rezar por você pelo resto dos meus dias!";
			link.l1 = "Ah, cala a boca! Vai em paz...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Me chamam de "+GetFullName(npchar)+". Eu tenho um pedido pra você, he-he...";
			link.l1 = "E aí?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Preciso que uma carta seja enviada da prisão. Você pode fazer isso?";
			link.l1 = "E o que eu ganho com isso?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Os rapazes não vão te decepcionar, eu prometo... E aí? Vai topar?";
			link.l1 = "Não, não estou interessado.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Bem, se não exigir muito esforço da minha parte, eu posso fazer isso.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Certo. Agora preste muita atenção. Dois camaradas estão esperando meu recado numa casa, para não serem pegos durante uma batida. Mas eu não faço ideia de qual casa exatamente. Você vai ter que procurar.";
			link.l1 = "O que você quer dizer com 'procurar'?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Procurar é procurar. Você vai andar pela cidade, espiar dentro das casas. Quando chegar ao lugar certo, não vão te deixar sair sem conversar. Mas lembre-se de que eu ficaria lá, no máximo, mais dois dias. Então não demore.";
			link.l1 = "Entendi. Então, entregue sua mensagem.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, sabe, eu simplesmente não gosto de você. Mudei de ideia. Venha, não fique aí parado!";
				link.l1 = "Olhe só pra você! Bem, como quiser...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Aqui. Obrigado. "+GetSexPhrase("companheiro","moça")+"!";
				link.l1 = "De jeito nenhum.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Sim, ele foi preso por contrabando. Mas por que você se importa com esse canalha, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "A gangue dele está planejando organizar sua fuga e continuar com suas tramoias.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Ouvi dizer que ele não era culpado.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Você deve avisar o governador, "+GetAddress_Form(NPChar)+", esses canalhas precisam ser todos capturados!";
			link.l1 = "Vou fazer exatamente isso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Escute, "+GetFullName(PChar)+", aquele homem foi preso tentando vender mercadorias proibidas, bem no meio da cidade! Como pode dizer que ele não é culpado?";
			link.l1 = "Ouvi dizer que a acusação era infundada e que você não tem provas, é isso mesmo? Você não pode simplesmente prender um homem que foi injustiçado.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Não temos testemunhas nem as mercadorias, mas isso não muda nada, Capitão "+GetFullName(PChar)+"! Essa pessoa é definitivamente culpada – e talvez não só de comércio ilegal. De qualquer forma, por que você se importa com o prisioneiro?";
			link.l1 = "Talvez minha palavra possa servir como fiança para aquele prisioneiro infeliz?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Talvez esses 5000 pesos possam servir como fiança para aquele prisioneiro infeliz?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Certo, "+GetAddress_Form(NPChar)+", leve esse canalha daqui e suma antes que eu mude de ideia.";
				link.l1 = "É ótimo ver a justiça vencer, não acha?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Não, "+GetAddress_Form(NPChar)+", isso não vai dar certo.";
				link.l1 = "Então, talvez esses 5.000 pesos possam ser um argumento mais convincente?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Certo, "+GetAddress_Form(NPChar)+", leve esse canalha e vá, antes que eu mude de ideia.";
			link.l1 = "É bom ver a justiça prevalecer, não acha?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Sim, houve um desses bem violento. Foi grosseiro com um sentinela e depois arrumou uma briga. Nada além disso: vai passar alguns dias na cadeia pra esfriar a cabeça. Por que se interessa por ele? Você parece ser capitão, e esse bêbado não tem cara de marinheiro.";
			link.l1 = "Sim, é isso mesmo, eu sou capitão. A questão é que esse bêbado é um velho conhecido meu. Só não conte isso pra ninguém, por favor. Pelo que entendi, ele nem chegou a sacar uma arma. Quem sabe você não o libera dessa vez, como um favor pra mim?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Sim, é um bom amigo meu. Não se preocupe, não vou contar pra ninguém. Na verdade, ele nem conseguiu acertar um golpe de verdade, foi só uma tentativa — por isso que o prenderam. Já que você está pedindo, por respeito a você, vou soltá-lo. Só avise pra ele se controlar da próxima vez. Ou melhor ainda, garanta que ele beba menos.";
				link.l1 = "Obrigado, oficial.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Sim, bom amigo. Não se preocupe, não vou contar pra ninguém. Só que ele conseguiu dar um soco no rosto do sentinela antes de ser amarrado. Então não posso soltá-lo. A menos, é claro, que o sentinela concorde em retirar a queixa. Você pode falar com ele mesmo, ele está patrulhando a cidade hoje.";
				link.l1 = "Não, receio que se ele agrediu o guarda, então não posso ajudá-lo. Vai ter que ficar preso por alguns dias. Sinto incomodar você, oficial.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Certo, vou lá tentar negociar com o sentinela.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Sim, bom amigo. Fique tranquilo, não vou contar pra ninguém. Mas veja bem, atacar um membro das forças armadas em serviço é crime. Posso ceder um pouco e liberar ele, mas só mediante fiança.";
				link.l1 = "E quanto eu preciso pagar por isso?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*lendo* Então... então... Bem, já que o sentinela não tem reclamações, eu também não. Pode levar seu amigo. Só avise pra ele se controlar da próxima vez. Melhor ainda, faça ele beber menos.";
			link.l1 = "Obrigado, oficial.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Bem, já que ele não pegou uma arma, isso dá só 1.500 pesos.";
			link.l1 = "Receio que não estou pronta para dar tanto assim. Bem, considerando que ele só vai ficar aqui por alguns dias, acho que não vai lhe fazer mal. Talvez ele até beba menos.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Certo, estou pronto para pagar a fiança.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Pode levar seu amigo. Só avise pra ele se controlar da próxima vez. Ou melhor ainda, garanta que ele beba menos.";
			link.l1 = "Obrigado, oficial.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Obrigado por aceitar vir em vez de começar um massacre. Pelo menos alguém ainda tem bom senso hoje em dia.";
				link.l1 = "Então, a que devo essa atenção, Monsieur Oficial? Tem algo a ver com o fato de eu estar procurando um chinês?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Que bom que você veio até nós por vontade própria. Já tivemos encrenca demais ultimamente.";
				link.l1 = "Bem, como pode ver, não sou do tipo violento. Mas... por que estou aqui, oficial? Já perguntei aos seus homens, mas não recebi resposta – é porque estou procurando por um certo chinês na cidade?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Claro que não! Por favor, entre. Você é sempre bem-vindo nas nossas masmorras. Digo, no bom sentido, é claro. Então, o que traz você aqui?";
			link.l1 = "Ah, nada de especial, sabe, só estou dando uma olhada pela cidade, acabei vindo parar aqui por acaso.";
			link.l1.go = "exit";
			link.l2 = "Queria conversar sobre alguns negócios.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Quero entrar na prisão.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
