void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				if (Pchar.quest.contraband.CurrentPlace == "shore30" || Pchar.quest.contraband.CurrentPlace == "shore31")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Marie Galante");
				}
				if (Pchar.quest.contraband.CurrentPlace == "shore59")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Tobago");
				}
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetLocationNameByID(Pchar.quest.contraband.CurrentPlace));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Monsieur, saia daqui. Duvido que tenhamos algo a conversar.";
				link.l1 = "Ah, é mesmo? Não gosta da minha cara? Tudo bem, estou indo embora...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Sem negócios hoje.";
				link.l1 = "Entendi.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Meus amigos e eu estamos extremamente ocupados hoje.";
				link.l1 = "Mas eu preciso...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "O que você quer, capitão?";
				link.l1 = "Podemos conversar um pouco?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "O que você quer, capitão? Eu não sei seu nome e não posso te dizer o meu.";
				Link.l1 = "Eu sou o capitão "+GetFullName(pchar)+".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Sem negócios hoje. Tem patrulhas em todas as baías, nosso governador está procurando uma carga que foi confiscada por algum capitão de"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" e ele escondeu isso em algum lugar.";
						link.l1 = "E onde está esse capitão"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Sem negócios hoje.";
						link.l1 = "Entendi.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Sem negócios hoje.";
					link.l1 = "Entendi.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Sem negócios hoje.";
					link.l1 = "Entendi.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "O que você quer, capitão?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Seja rápido, "+GetSexPhrase("amigo","garota")+", o que você quer? Eles estão atrás de você!","Diga logo o que quer! Os soldados estão atrás de você e não temos muito tempo...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Gostaria de comprar ou vender alguma coisa.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Sobre a viagem...";
				else
					Link.l2 = "Preciso chegar a um lugar.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Tenho algumas mercadorias 'especiais' e acho que você pode se interessar. Dê uma olhada!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Tenho um negócio incomum para você.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Escute, amigo, preciso de uma remessa de vinho e rum. Quanto mais, melhor, e o quanto antes.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Preciso me encontrar com Michael Rosenkraft. Tenho uma carga que vai interessar a ele.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Preciso descobrir uma coisa, camarada.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Um colega seu e um grande amigo meu de  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" me disseram que você está por dentro de alguns negócios.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Nada. Até mais.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "No porão do forte, onde mais? Aquele capitão pode contar sobre o esconderijo para as autoridades a qualquer momento, e aí não vai sobrar nada pra gente. Nem pense em negócios até essa confusão acabar.";
				link.l1 = "Escuta, você conhece cada canto desta ilha. Tem certeza de que não faz ideia de onde está o capitão "+pchar.GenQuest.CaptainComission.Name+"esconderijo é?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Acho que ele está no céu agora. Foi enforcado junto com a tripulação. Mas na sentença de morte não disseram que era um navio pirata.";
				link.l1 = "E por que você tem tanta certeza de que a embarcação era um navio pirata?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Estávamos observando a luta das pedras. Com uma luneta, vimos o navio hasteando a Jolly Roger. Depois, cerca de cinco horas depois, vimos um clarão na escuridão — parecia uma explosão no paiol de pólvora. Esse tempo foi suficiente para levar a carga para terra.";
			link.l1 = "Você não sabe onde está o capitão "+pchar.GenQuest.CaptainComission.Name+"O esconderijo do [[[VARx]]]? Você conhece cada canto desta ilha.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Não. E nós também estamos procurando por isso, mas não para divertir o governador...";
			link.l1 = "Entendi... Tenha um bom dia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Não. E nós também estamos procurando, mas não é para divertir o governador... he-he";
			link.l1 = "Entendi... Tenha um bom dia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Por que você decidiu isso? Eu sou um comerciante honesto. Vá procurar outro comprador.";
				link.l1 = "Obrigado...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Por que não? Talvez eu encontre uma utilidade para a sua 'carga'. Leve "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" moedas e esqueça isso.";
					link.l1 = "Não, obrigado.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "E você adivinhou certo, estou começando a esquecer disso!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Exatamente! Agora fiquei bem curioso. Suponho que se eu te pagar "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" moedas, você não vai ligar nem um pouco para esses papéis.";
						link.l1 = "Não, obrigado.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "E você está certo. Já até me esqueci deles.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Agora, essa é uma chance de pegar aquele sujeito insolente! Estou realmente, mas realmente curioso. Olha, eu te pago "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" em ouro, e você vai esquecer completamente dos documentos em cima da mesa?";
						link.l1 = "Eu não vou.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Fechado, combinado!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Tá bom, tá bom, mas para de arrumar mais inimigos.";
			link.l1 = "O mesmo pra você!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
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
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
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
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Sem negócios hoje. Tem patrulhas em todas as baías, nosso governador está procurando uma carga que foi confiscada por certo capitão de"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" e ele escondeu isso em algum lugar.";
					link.l1 = "E onde está esse capitão"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Sem negócios hoje.";
					link.l1 = "Entendi.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Sem negócios hoje.";
				link.l1 = "Entendi.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Sem negócios hoje.";
				link.l1 = "Entendi.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Como posso ajudar você, capitão?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Quero comprar ou vender mercadorias.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Preciso chegar a um lugar.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Tenho um negócio bem incomum para você.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Escute, amigo, preciso de uma remessa de vinho e rum. Quanto mais, melhor, e o quanto antes.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Preciso me encontrar com Michael Rosenkraft. Tenho uma carga que vai interessar a ele.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Preciso descobrir uma coisa, camarada.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Um colega seu e um grande amigo meu de  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" disseram que você está por dentro de alguns negócios.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Nada. Até mais.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Eu não sou seu amigo. E isso pode te custar caro.";
				link.l1 = "Hm. Preciso saber de algo que não custe mais do que "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Me dê suas moedas. E saiba que você não vai conseguir muita coisa com essa quantia.";
				link.l1 = "Olha, senti falta dos meus amigos. Cheguei atrasado para um encontro, e eles não me esperaram...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, você não tem uma moeda! Volte quando tiver algum dinheiro.";
				link.l1 = "De fato, estou nisso.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "E por que você precisa de mim?";
				link.l1 = "Eles não estão na cidade e não têm um navio. Por isso pensei: talvez algum dos seus parceiros de negócios tenha feito um favor para eles?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Entendi... Conheci alguns homens, disseram que precisavam sair da ilha e não se importavam para onde. Nessas situações, não perguntamos o motivo, só falamos de pagamento. Fizemos uma viagem para "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Town")].IslandID+"Dat")+" . Podemos te levar até lá, se chegarmos a um acordo sobre o dinheiro.";
			link.l1 = "Obrigado, mas eu já tenho meu próprio navio.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "Eu nunca fiz negócios com você.";
			link.l1 = "Podemos consertar isso. Você trouxe meus amigos aqui não faz muito tempo. Eu perdi uma reunião com "+GetSexPhrase("eles","eles")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hum, nós os deixamos em terra em "+XI_ConvertString(sGenLocation+"Gen")+"... Sabe, é melhor que sejam seus amigos, caso contrário eu não aconselharia você a incomodá-los de jeito nenhum.";
			link.l1 = "Obrigado pela preocupação, mas estou bem armado e sou bastante encantador.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Hm... e o que isso tem a ver comigo? Você deve ter se perdido, capitão. Vá até a loja e compre ou venda o que quiser por lá.";
			Link.l1 = "Não, eu preciso de você.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Obrigado pelo conselho. Tenha um bom dia.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Para quê?";
			Link.l1 = "Talvez você se interesse por algumas mercadorias especiais? Ou quem sabe tenha algo para me oferecer em troca?"Link.l1.go ="Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;
			
			float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
			if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
			
			if (GetCompanionQuantity(pchar) > 1) iTmp = true;
			if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

			// поиск мин.  те старшего класса
			/* for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			} */
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Por que você não pega um navio de guerra real da próxima vez? Seu navio pode ser visto facilmente do forte. Não vamos arriscar nossas cabeças. Venha com um único barco pequeno da próxima vez.","Preciso repetir? Encontre um navio menor e aí conversamos.","Você é mesmo tão idiota assim? Arrume uma escuna ou uma brigue. Só então teremos negócio.","Ah, que tolo...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Certo, eu entendo você.","Eu entendo, só queria esclarecer uma coisa.","Não, não é um idiota, só um pão-duro. Achei que algo tinha mudado. Eu pegaria mais umas escunas...","Olhe no espelho...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Desculpe, "+GetSexPhrase("amigo","garota")+", já estamos ocupados. Volte daqui a alguns dias.";
				Link.l1 = "Que pena...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Que tal terminarmos o que estamos fazendo primeiro?";
				Link.l1 = "Acho que você tem razão.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Eu sei que podemos fazer negócios com você. Estaremos esperando em "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Talvez a gente consiga um comprador pra você. Vamos te esperar em "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
            				}
            				Link.l1 = "Certo. Te vejo lá.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Sem negócios hoje. Volte amanhã.";
            				Link.l1 = "Certo.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Você acha mesmo que alguém vai querer trabalhar com você depois de tudo isso? É bom agradecer que a gente não mandou caçadores de recompensa atrás de você.";
        				Link.l1 = "Que pena. Não vou ter chance de virar contrabandista.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Sem negócios hoje. Volte amanhã.";
    				Link.l1 = "Certo.";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Desculpe, "+GetSexPhrase("amigo","garota")+", já estamos ocupados. Volte daqui a alguns dias.";
				Link.l1 = "Que pena.";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Eu pensei que já tínhamos fechado o acordo?";
						Link.l2 = "De fato!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Você trouxe o dinheiro?";
							Link.l1 = "Sim.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Mudei de ideia...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Ainda não.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Já te contei tudo.";
								Link.l2 = "Exatamente.";
								Link.l1 = "Mudei de ideia...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Não posso te ajudar hoje. Volte daqui a dois dias e talvez tenhamos algo para você.";
								Link.l2 = "Que pena.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Bem, podemos te levar até lá "+GetLocationNameByRef(&locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)])+" perto "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" for "+pchar.GenQuest.contraTravel.price+" ouro. Traga o dinheiro "+FindRussianDaysString(nDay)+". O navio vai estar esperando por você em "+GetLocationNameByRef(&locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)])+" exatamente 24 horas.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Por mim, tudo certo.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Não, obrigado.";
						}
						else
						{
							Dialog.Text = "Não posso te ajudar hoje. Volte daqui a dois dias e talvez a gente tenha algo pra você.";
							Link.l2 = "Que pena.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Você realmente acha que alguém vai querer trabalhar com você depois de tudo isso? Devia agradecer por não termos mandado caçadores de recompensa atrás de você. Cai fora!";
        				Link.l2 = "Puxa, nada de novo.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Não, não vamos levar todos vocês. Só um.";
					Link.l2 = RandSwear()+"Eu não preciso disso mesmo!";
				}
				else
				{
					Dialog.Text = "Por que você não usa seu próprio navio? Não, não vamos te levar.";
					Link.l2 = "Tudo bem, como quiser.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "O que você quiser.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetLocationNameByID(pchar.GenQuest.contraTravel.CurrentPlace));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetLocationNameByID(pchar.GenQuest.contraTravel.destination.loc));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "Foi um prazer fazer negócios com você. Não se atrase para o navio.";
				Link.l1 = "Vou tentar.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Parece que você não tem dinheiro suficiente."Link.l1 ="Que pena, volto mais tarde.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Muito interessante. Mostre o que você tem.";
			link.l1 = "Ouvi dizer que existe uma loja clandestina onde se pode negociar mercadorias bem 'especiais' por um preço tentador, e que você ajudou a abrir essa loja. Gostaria de falar com o dono.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Ouvi dizer que existe uma loja clandestina onde dá pra negociar mercadorias bem 'especiais' por um preço tentador. Preciso zarpar em alguns dias e não tenho dinheiro suficiente pra comprar tudo que preciso na loja local, então preciso e quero economizar umas moedas... me disseram que você pode me ajudar com isso.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "Do que você está falando? Não estou entendendo você. A gente não abriu loja nenhuma aqui, isso é bobagem, ha-ha! Se quiser negociar, traga mercadorias e conversamos como sempre... Loja, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Quer um desconto? Fácil. Venha até a porta do capitão do porto depois que escurecer. Nosso homem vai te encontrar e levar ao lugar certo. ";
			link.l1 = "Certo. Eu estarei lá!";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
		//--> Торговля по закону
		case "TPZ_smugglers_1":
			dialog.text = "Ha, aquele patife atrás do balcão te mandou, não foi?";
			link.l1 = "Isso importa? Você consegue pegar, ou devo procurar outra pessoa?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Consigo qualquer coisa que você quiser, entendeu? Desde que o pagamento seja justo. Mas aquele maldito governador apertou o cerco. Não mexemos mais com bebida – faz muito barulho, dá pra ouvir de longe, o lucro é uma miséria e o risco de acabar na forca é enorme. Então, nada pessoal.";
			link.l1 = "Hmm... E você diz que consegue qualquer coisa.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Eu posso! Só não quero. Tem um cara, mora bem do lado da mansão do governador, acredita? Ha-ha. Que idiota... O que eu tava dizendo? Ah, sim. Ele vende bebida escondido, por baixo dos panos. Bem debaixo do nariz do governador, ha-ha. Fala com ele, talvez te dê uma pista. Ele vende pouco, coisa de criança mesmo, mas já é alguma coisa.";
			link.l1 = "Não ajudou muito, mas obrigado mesmo assim.";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону

		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Tem muita gente festejando aqui, e se não tem nada pra fazer, senhor, beba ou converse com eles. Este lugar está movimentado.";
			link.l1 = "Vamos tentar de novo. Eu pago pelo seu tempo e pela minha curiosidade. Preciso de respostas.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Ele vai pagar, ha! Meu tempo não é barato, senhor, custa 3.000 pesos mais essa bebida horrível que eles por engano chamam de rum.";
				link.l1 = "Fechado! Agora me conte sobre um dos seus que passou meio ano na prisão daqui e depois morreu. O que aconteceu com ele?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "You'd better fill your pockets with silver, or gold would be even better. Then come and talk; I have no time to talk with you for free.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Eu me lembro disso, embora não entenda por que você está interessado nisso. O garoto realmente enlouqueceu atrás das grades. Virou um bêbado e vivia falando umas bobagens sobre um mal que levava as pessoas embora e que ninguém estava a salvo dele. Dizia que esse mal tinha nome e que ninguém devia ousar pronunciá-lo em voz alta. Se fizesse isso – ele viria te buscar também.";
			link.l1 = "E o que aconteceu com ele depois?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "A história teve um fim estranho, señor. No começo, os locais e marinheiros gostavam do seu conto, mas com o tempo se cansaram dele. Isso sempre acontece com qualquer fábula. Então provocaram o homem para dizer o nome. Ele resistiu, tentou aguentar, mas não suportou as zombarias e acabou gritando o nome\nNinguém sentiu nada de especial, as velas continuaram acesas, mas o pobre coitado foi encontrado morto na manhã seguinte atrás da taverna, com a garganta cortada.";
			link.l1 = "Não vejo nenhuma magia aqui. Diga o nome.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Eu lembro do nome, mas droga, não vou dizer em voz alta. Tem algo sinistro nisso tudo. Você não percebe?";
			link.l1 = "Ei, camarada, você recebeu uma carteira cheia de moedas de mim, lembra? Então, poderia me dizer o nome, por favor?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Ah, isso não vai acabar bem, señor, acredite em mim... (abaixando a voz) Ele disse - Juan...";
			link.l1 = "Maldição! Juan? É só um nome comum, muito popular por aqui. O que tem de tão especial?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Não sei, mas o homem que falou esse nome foi morto. Confie no meu instinto, tem algo muito errado com esse nome. Era só isso que você queria saber?";
			link.l1 = "Acho que sim. Pode comprar uma bebida pra você. Até mais!";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "É mesmo? Tudo bem. O senhor Rosenkraft precisa de um lote de pau-ferro, mas não menos que "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Você tem carga suficiente?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Sim. Onde posso encontrar o senhor Rosenkraft?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hum. Eu não tenho tanto assim agora.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Não incomode o senhor Rosenkraft então. Volte quando tiver carga suficiente.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "O galeão dele vai estar navegando perto das costas de "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" por vários dias. Então não se atrase – ele pode zarpar para outra parte do arquipélago.";
			link.l1 = "Tá bom, vou acelerar. Obrigado!";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "E eu preciso sobreviver até amanhã. A maldita 'Mercy' está na cidade. Vai embora.";
			link.l1 = "Tanto drama...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
