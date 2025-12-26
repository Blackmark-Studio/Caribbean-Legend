#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		PortmanDelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		if(CheckAttribute(chref, "DontNullShip"))
		{
			DeleteAttribute(chref, "DontNullShip");
			DeleteAttribute(NPChar, "DontNullShipBeliz");
		}
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
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
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("O alarme foi disparado na cidade e agora todos estão te procurando. Se eu fosse você, não ficaria aí.","Todos os guardas da cidade estão vasculhando a cidade à sua procura. Não sou tolo de falar com você!","Corra, "+GetSexPhrase("companheiro","moça")+", antes que os soldados te encham de buracos..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","fedelho")+"?! Os guardas da cidade já sentiram o seu cheiro, você não vai longe, pirata imundo!","Assassino, saia da minha casa agora! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("canalha","rato")+"! Logo vão te enforcar no nosso forte, você não vai longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim..."," Eles nunca vão me pegar. "),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", e talvez eu não arranque essa sua língua imunda!","Heh, "+GetWorkTypeOfMan(npchar,"")+", e todo mundo lá - peguem os piratas! É o que eu te digo, amigo: fique quieto e você vai sobreviver..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Ah, eu sei quem você é. Você foi contratado para entregar a carga, mas resolveu roubá-la! Guardas, guardas!";
					Link.l1 = "Aaargh!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "O que posso fazer por você, monsieur?";
				Link.l1 = "Tenho assuntos a tratar com você...";
				Link.l1.go = "quests";
				Link.l2 = "Desculpe, mas eu preciso ir.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Saudações, "+GetAddress_Form(NPChar)+". Acho que ainda não nos conhecemos. Eu sou "+GetFullName(npchar)+" - o capitão do porto.";
				Link.l1 = "Olá, "+GetFullName(NPChar)+". Eu sou "+GetFullName(PChar)+", capitão do '"+PChar.ship.name+"'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "Capitão MacArthur, como sempre lhe digo – não precisa se apresentar a mim toda vez. Não se preocupe.";
					link.l1 = "Pare com isso, senhor "+npchar.lastname+" Eu sou como todo mundo.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Saudações, "+GetAddress_Form(NPChar)+". Você tem algum assunto comigo?","Olá, "+GetFullName(Pchar)+". Vi seu navio entrando no nosso porto e tive certeza de que viria me procurar.","Oh, capitão "+GetFullName(Pchar)+". O que te traz até mim?");
				Link.l1 = "Olá, "+GetFullName(NPChar)+". Queria falar com você.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Então, como está a situação do dinheiro? Você tem pelo menos mil pesos para mim?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Sim, eu tenho"+GetSexPhrase("","")+". Isso dá exatamente mil pesos. Agora, a informação!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Não, ainda não...","Ainda não...","Ainda não, mas vou trazer em breve...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Por favor, permita-me explicar o cerne do problema. Meu velho amigo, Capitão  "+PChar.GenQuest.ChurchQuest_1.CapFullName+", nos desencontramos por apenas algumas horas, e tenho um assunto urgente para tratar com ele. Agora vou ter que ir atrás dele, mas não faço ideia"+GetSexPhrase("","")+" sobre o paradeiro dele.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Capitão do porto, senhor, preciso de algumas informações sobre o navio chamado '"+PChar.GenQuest.ChurchQuest_1.CapShipName+" pertencente ao capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "A carga para sua colônia está no porão do meu navio.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "A carga para sua colônia está no porão do meu navio.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Ah, então você finalmente apareceu. Para ser sincero, não esperava que voltasse. Já pedimos às autoridades para colocarem você na lista de procurados. E então, o que tem a dizer?";
						Link.l1 = "Eu não consegui entregar a carga a tempo por causa de circunstâncias imprevistas. Mas quero resolver esse conflito de forma pacífica. Trouxe sua carga e espero que possamos chegar a um acordo.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Ah, eu sei quem é você. Foi contratado para entregar a carga, mas resolveu roubá-la! Guardas, guardas!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Entreguei a correspondência para sua colônia.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ah, então você finalmente apareceu. Para ser sincero, já achávamos que você tinha morrido... Bem, acho que é melhor ser um cabeça-dura do que um homem morto.";
					Link.l1 = "Não consegui entregar a correspondência a tempo por causa de imprevistos. Mas aqui está.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "O que aconteceu? Você está com uma cara péssima.";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+", você estava certo quando me alertou sobre o perigo. Dois homens vestidos de preto me atacaram bem na porta da capitania e... bem, eles levaram o pacote de mim.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Fui enviado aqui pelo mestre do porto "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Fui solicitado a escoltar um navio carregando armas e munição. Aqui estão meus documentos.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Escoltei o navio com as armas, exatamente como combinamos.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Encontrei a embarcação desaparecida e a trouxe para o seu porto. O capitão do navio já deve ter se apresentado a você.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Encontrei o navio desaparecido e o trouxe para o seu porto. O capitão da embarcação já deve ter se apresentado a você.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Encontrei a embarcação desaparecida nas margens da ilha de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". O capitão dela estava lutando em uma batalha desigual contra forças piratas esmagadoras. Ajudei como pude, mas foi em vão: aqueles malditos canalhas afundaram o navio. Tudo o que pude fazer naquele momento foi vingar ela.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Encontrei a embarcação desaparecida nas margens da ilha de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Bem, na verdade, não o navio, mas sim cerca de cinquenta homens da tripulação e o capitão. Agora estão seguros – a tripulação embarcou na minha embarcação, e o capitão está na sua cidade – imagino que ele já tenha lhe feito uma visita.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Cumpri sua missão. O esquadrão pirata que atacou o comboio mercante foi destruído.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Sou o capitão da embarcação de escolta. Vim informar que trouxe os navios mercantes ao porto.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Sou o capitão da embarcação de escolta. Fui enviado para trazer dois navios mercantes e suas cargas ao porto, mas infelizmente, ambos os navios escoltados afundaram durante uma batalha com um comboio inimigo. Ainda assim, consegui entregar a carga.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
					Link.l1 = "Sou o capitão da embarcação de escolta. Vim informar que trouxe os navios mercantes ao porto.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Que bom ouvir isso de você. Muitos teriam ficado convencidos no seu lugar. Então, como eu e meus registros podemos ajudar?";
			}
			else dialog.text = "Excelente. Estou ao seu dispor, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Você tem algum trabalho para mim? Ou talvez um contrato?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Posso atracar um dos meus navios aqui por um tempo?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Quero recuperar meu navio.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Vim discutir questões financeiras.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estou aqui a pedido de um certo homem. O nome dele é Governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me mandou até você. Disseram que é pra eu pegar alguma coisa...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Gostaria de saber mais sobre os capitães que se registraram na sua capitania.";
			link.l6.go = "CapitainList";
			link.l61 = "Você poderia compartilhar algum conhecimento sobre os navios únicos, feitos sob medida, e seus capitães lendários?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Estou lidando com outro assunto.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Olá, vim a convite do seu filho."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Isso é sobre sua filha...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Aconteceu de eu encontrar este pacote de documentos do navio.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Aconteceu de eu encontrar este pacote de documentos de navio, alguém deve tê-los perdido.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Obrigado. Adeus.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Seu problema pode ser facilmente resolvido. Procure o oficial do serviço de navegação e ele poderá lhe fornecer todas as informações sobre a rota do navio do seu amigo.";
			link.l1 = "Infelizmente, não é tão simples assim. Meu amigo renomeou o navio dele no seu porto... por motivos religiosos.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Entendo. Isso complica um pouco as coisas. Vou ter que vasculhar os registros no cadastro dos navios, e isso vai levar algum tempo. E tempo é dinheiro, como você provavelmente sabe.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Eu entendo perfeitamente isso, senhor "+GetFullName(NPChar)+", e estou devidamente preparado para avaliar o valor do seu tempo ... digamos, em mil pesos.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Que pena, porque não tenho nenhum dinheiro comigo agora... Vou voltar mais tarde...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Perfeito! Vamos ver agora... só um minuto... aqui... certo. O novo nome do navio foi registrado, e a embarcação, que a partir de agora será conhecida como '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' comandado pelo Capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+" partiu hoje em direção a "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh! Vejo que realmente entende que sou um homem muito ocupado, e fico feliz que reconheça isso! Vamos ver agora... só um instante... aqui... certo. O novo nome do navio foi registrado, e a embarcação, que a partir de agora será conhecida como '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' comandado pelo Capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+" partiu hoje em direção a "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "Muito obrigado, senhor, você me fez um grande favor.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "O que exatamente você quer saber?";
			link.l1 = "Você pode me dizer se o navio daquele capitão já passou pelo seu porto?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... E posso saber por que você pergunta?";
			link.l1 = "Tenho negócios com ele. Mas se ele não passou pelo seu porto ou você não sabe...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Sim, ele fez isso. Mas graças a todos os Santos, justamente hoje de manhã ele nos livrou de sua presença e partiu para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+". E sinceramente sinto pena de quem tiver que lidar com ele.";
			link.l1 = "Nesse caso, me deseje sorte – e obrigado pela sua ajuda.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "O que você quer saber, "+GetSexPhrase("senhor","senhorita")+" "+GetFullName(PChar)+"?";
			link.l1 = "Você poderia me dizer se esse capitão passou pelo seu porto ou não?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Sim, com certeza. E devo dizer que aguardo com impaciência o momento abençoado em que ele finalmente deixar este porto tão sofrido.";
			link.l1 = "Quer dizer que o navio dele ainda está aqui?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Sim, graciosa "+GetSexPhrase("senhor","senhora")+". Todo o porto, do mais humilde estivador ao chefe do serviço de práticos, está rezando para que ele vá embora logo. O navio dele acabou de sair do dique seco, onde foi rapidamente consertado, mas, nesse tempo, o bravo capitão já tinha brigado com todos os carpinteiros e recusado três lotes de tábuas escolhidas para o casco. Mas amanhã, nosso Senhor mais bondoso e onisciente vai nos livrar desse... dessa praga, desse espinho no caminho de todo mundo!";
			link.l1 = "Agora, acalme-se, senhor "+NPChar.Name+", e lembre-se que alguém ainda vai passar por momentos mais difíceis. Você já superou essa provação, enquanto eu ainda preciso conhecer esse seu capitão. Agora, com licença...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Deixe-me dar uma olhada! Sim, de fato, nos meus documentos este conjunto está marcado como nulo. Foi muita gentileza sua encontrar um tempo para vir até aqui e me entregar esses papéis. Bons ventos, capitão!";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go unrewarded.  ";
			dialog.text = s1+"Me diga, você consideraria uma quantia de "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos, isso é uma recompensa adequada?";
			link.l1 = "Claro que não!";
			link.l1.go = "exit";
			link.l2 = "Bem, uma quantia modesta, mas também não foi nada demais. Sim, eu aceito sua oferta, "+npchar.name+".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Você aceita minha oferta?";
			link.l1 = "Claro que não!";
			link.l1.go = "exit";
			link.l2 = "Talvez. Mas tenho certeza de que esses documentos valem muito mais.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Trouxe o seu fugitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitão, muito obrigado! Como ela está? Ela se machucou? Por que ela fugiu? Por quê?\nEla não entende? O noivo é um homem rico e importante! A juventude é ingênua e tola... até cruel. Lembre-se disso!";
			link.l1 = "Bem, você é o pai dela e a decisão final é sua, mas eu não me apressaria com o casamento...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "O que você sabe? Tem filhos? Não? Quando tiver um, venha falar comigo, aí a gente conversa.\nPrometi uma recompensa para quem trouxer ela de volta para a família.";
			link.l1 = "Obrigado. Você deveria ficar de olho nela. Tenho um pressentimento de que ela não vai parar por aí.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, você é aquele(a) "+GetSexPhrase("capitão que trouxe","jovem moça que trouxe")+" meu filho pródigo com uma jovem esposa?";
				link.l1 = "Sim, eu ajudei eles a escapar.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, vamos lá, benfeitor. Está esperando uma recompensa?";
				link.l1 = "Bem, não preciso de recompensa, sua gratidão já é o bastante.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sou muito grato a você por não ter abandonado meu filho em um momento tão difícil e por tê-lo ajudado a sair daquela situação delicada. Permita-me agradecer e, por favor, aceite esta quantia modesta e um presente pessoal meu.";
			link.l1 = "Obrigado. Foi um prazer ajudar esse jovem casal.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Obrigado? Que obrigado o quê?! Já faz meio ano que aquele cabeça-oca está por aí sem trabalho – e olha pra ele, tem tempo de sobra pra namoricos! Quando eu tinha a idade dele, já tocava meus próprios negócios! Pff! Um governador tem uma filha em idade de casar – e esse paspalho me aparece com uma moça sem eira nem beira em casa e ainda tem a ousadia de pedir minha bênção!";
			link.l1 = "Hmm... Pelo visto, você não acredita em sentimentos de verdade?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Que sentimentos? Que tipo de sentimentos você está falando? Sentimentos... como alguém pode ser tão irresponsável na sua idade?! Que vergonha, incentivando os jovens em seus caprichos e agindo como um intermediário! Você não só tirou uma moça de sua casa, como também arruinou a vida do meu novato. Não espere agradecimentos. Adeus.";
			link.l1 = "Certo, e o mesmo pra você...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Sim, droga! Tenho um trabalho pra você!","Ha! Chegou na hora certa! Tenho um assunto que precisa ser resolvido.","Mas é claro! Claro que tenho trabalho para você! Sabe, estou simplesmente atolado de problemas ultimamente...");
				link.l1 = "Então, por favor, vá direto ao ponto, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Deus! Capitão "+GetFullName(PChar)+", você chegou na hora certa! Que desgraça aconteceu, que calamidade... O navio pegou fogo na ancoragem enquanto estava sob os cuidados da autoridade portuária! Por descuido da segurança, o navio queimou... queimou até a linha d'água...\n"+"Senhor, o que eu fiz para merecer um castigo desses? Fui um servo fiel por tantos anos...";
				link.l1 = "Então, qual é o problema? Um navio pegou fogo? E para que servem os contratos de seguro? Ou você resolveu não segurar para economizar dinheiro, e agora está se remoendo de arrependimento?";
				link.l1.go = "BurntShip4";
				link.l2 = "O estaleiro poderá te ajudar com isso melhor do que eu. Em alguns meses, eles vão restaurar o antigo, ou até construir um novo. Desculpe, não sou construtor de navios...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "O governador se preocupa com o bem-estar dos seus cidadãos, então sempre tem algum trabalho para oferecer. Pode haver mercadores na taverna interessados em ajuda, e a loja também está precisando de capitães para transporte.";
			Link.l1 = "Tenho mais uma pergunta.";
			Link.l1.go = "node_2";
			Link.l2 = "Obrigado. Adeus.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Era para você encontrar o capitão "+npchar.quest.PortmansJornal.capName+" e devolver o diário de bordo do navio para ele. Você conseguiu?";
				link.l1 = "Não, ainda não...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Você se comprometeu a procurar por um(a) [[[VARx]]] roubado(a) "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'.   Não haverá outras tarefas para você até que termine essa.";
				link.l1 = "Vou continuar minha busca, apenas espere.";
				link.l1.go = "exit";
				link.l2 = "Quero desistir da tarefa.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Você me prometeu que procuraria o que foi roubado "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Você fez isso?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Sim, eu encontrei, está agora no porto. Você pode pegar.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Vou continuar minha busca, só espere.";
					link.l1.go = "exit";
				}
				link.l2 = "Quero desistir da missão.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("Não há trabalho para quem navega sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+"! Saia do meu escritório agora mesmo!","Eu não vou colaborar com "+NationNameAblative(sti(pchar.nation))+". Vá embora!");
						link.l1 = RandPhraseSimple("Bem, como quiser...","Bem, como quiser...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "Sua reputação não me inspira confiança. Não vou colaborar com você. Adeus.";
						link.l1 = "O quê! É tudo mentira.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Não quero ofendê-lo, capitão, mas... receio que você não conseguiria cumprir minha tarefa – simplesmente lhe falta experiência. Não posso assinar um contrato com você.";
						link.l1 = "Entendo. Bem, como preferir.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hum... Bem, isso depende do tipo de trabalho que você procura.";
					link.l1 = "Posso oferecer meu navio para transportar carga.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Quero ganhar um dinheiro extra escoltando mercadores.";
					Link.l2.go = "escort_begin";	//эскорт
					link.l3 = "Quero ganhar um dinheiro extra entregando correspondências.";
					Link.l3.go = "cureer_begin";	//доставка почты
					Link.l4 = "Bem, talvez você possa oferecer alguma coisa?";
					Link.l4.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Não há mais nada para hoje. Volte outro dia.";
					link.l1 = "Certo.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Não vejo seu navio no porto. Atracar ao largo e depois venha falar comigo de novo – vamos tentar arranjar algo para você.";
				link.l1 = "Certo, vou fazer exatamente isso.";
				link.l1.go = "exit";
			}
		break;
			
		case "escort_begin"://эскорт
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		
		if (hrand(5) > 1)
		{
			if (GetCompanionQuantity(pchar) < 3 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) 
			{
				if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) 
				{ // если заняты
					dialog.text = "Infelizmente, não posso te oferecer nada desse tipo. Volte daqui a alguns dias.";
					link.l1 = "Certo, vou fazer exatamente isso.";
					link.l1.go = "exit";
				} 
				else 
				{ // если не заняты
					if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) 
					{ // 2 уровень
						dialog.text = "Você já escoltou navios mercantes com sucesso várias vezes. Acho que tenho uma tarefa que combina com você.";
						link.l1 = "Estou ouvindo.";
						link.l1.go = "Escort_LevelUp";
					} 
					else 
					{ // 1 уровень
						if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
							dialog.text = "Tenho um trabalho perfeito para você. Há dois navios mercantes no porto que já deveriam ter partido. O problema é que o navio de escolta deles foi danificado e ainda está esperando os reparos necessários, então não vai poder zarpar tão cedo.\nAcontece que seu navio é ideal para essa missão – além disso, preciso embarcar uma carga extra no seu porão. Claro, o pagamento será em dobro – tanto pelo frete quanto pela escolta.";
							link.l1 = "Que oferta interessante! Eu aceito!";
							link.l1.go = "escort_bonus";
							link.l2 = "Obrigado, mas esse tipo de trabalho não é pra mim.";
							link.l2.go = "exit";
						} 
						else 
						{ // просто эскорт
							dialog.text = "Tenho um trabalho só para você. Dois navios mercantes estão atracados em nosso porto neste momento – eles precisam de escolta. Estou lhe oferecendo a chance de escoltar esses navios até o destino deles. Vai aceitar?";
							link.l1 = "Uma oferta interessante! Eu aceito!";
							link.l1.go = "escort";
							link.l2 = "Obrigado, mas esse tipo de trabalho não é pra mim.";
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Você bem que poderia aparecer com uma tartana para escoltar um comboio. Esse tipo de trabalho exige um navio com poder de fogo de verdade — um guerreiro ou um saqueador.";
				link.l1 = "Tá bom, entendi.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Infelizmente, não posso te oferecer nada desse tipo. Volte daqui a alguns dias.";
			link.l1 = "Certo, farei exatamente isso.";
			link.l1.go = "exit";
		}
		break;
		
		case "cureer_begin"://доставка почты
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
		
		if (hrand(5) > 1)
		{
			if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)
			{
				if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp"))
				{ 
					// если заняты
					dialog.text = "Infelizmente, não posso te oferecer nada desse tipo. Volte daqui a alguns dias.";
					link.l1 = "Certo, vou fazer exatamente isso.";
					link.l1.go = "exit";
				} 
				else 
				{ 
					// если не заняты
					if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) 
					{ //если 2 уровень
						dialog.text = "Então... Pelo que sei, você já fez vários trabalhos como mensageiro e se saiu muito bem. Acho que pode dar conta da tarefa que estou prestes a lhe passar.";
						link.l1 = "Estou ouvindo, "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "Postcureer_LevelUp";
					} 
					else 
					{ // первый уровень
						dialog.text = "Vejo que você tem um navio rápido. Posso te oferecer um trabalho de mensageiro – entregar correspondências e documentos comerciais.";
						link.l1 = "Isto é interessante. Concordo. Para onde preciso ir?";
						link.l1.go = "Postcureer";
						link.l2 = "Obrigado, mas esse tipo de trabalho não é pra mim.";
						link.l2.go = "exit";
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Desculpe, mas não tenho nada para você. Essas tarefas exigem um navio ágil de saqueador. Com o seu, é melhor transportar carga.";
				link.l1 = "Tá bom, entendi.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Infelizmente, não posso te oferecer nada desse tipo. Volte daqui a alguns dias.";
			link.l1 = "Certo, vou fazer exatamente isso.";
			link.l1.go = "exit";
		}
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Mas ouvi dizer que seu navio já está fretado. Não posso lhe dar mais carga. Cumpra os compromissos que já assumiu.";
					link.l1 = "Sim, você provavelmente está certo.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Seu porão é pequeno demais. Preciso de um navio mais espaçoso para o frete. Sugiro que procure na loja – o comerciante local costuma fretar embarcações para entregar pequenas cargas.";
					link.l1 = "Entendi. Bem, como preferir.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "No momento, não tenho nada adequado. Mas você já fez várias entregas bem-sucedidas. Tenho um trabalho específico que gostaria de confiar justamente a você.";
					link.l1 = "Estou ouvindo. Que tipo de trabalho?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Bem, posso lhe oferecer várias oportunidades de fretamento.";
				link.l1 = "Vamos ver, então...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Não há mais cargas disponíveis para hoje. Volte outro dia.";
				link.l1 = "Ah, tudo bem.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "Existem as seguintes opções disponíveis:\n"+"carga "+GetGoodsNameAlt(iFrahtGoods1)+" no valor de "+FindRussianQtyString(iFrahtGoodsQty1)+" para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", em "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncarga "+GetGoodsNameAlt(iFrahtGoods2)+" no valor de "+FindRussianQtyString(iFrahtGoodsQty2)+" para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", em "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods3)+" no valor de "+FindRussianQtyString(iFrahtGoodsQty3)+" para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", em "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\nQual é a sua escolha?";
				Link.l1 = "Vou escolher a segunda opção - fretar para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" carregado com "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Vou escolher a terceira opção - uma carta para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" carregado com "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Vou escolher a terceira opção - uma carta para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" carregado com "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Há as seguintes variantes disponíveis:\n"+"carga "+GetGoodsNameAlt(iFrahtGoods1)+" no valor de "+FindRussianQtyString(iFrahtGoodsQty1)+" para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", em "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncarga "+GetGoodsNameAlt(iFrahtGoods2)+" no valor de "+FindRussianQtyString(iFrahtGoodsQty2)+" para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", em "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nQual é a sua escolha?";
				Link.l1 = "Vou escolher a primeira opção - uma carta para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" carregado com "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Vou escolher a segunda opção - uma carta de navegação para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" carregado com "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Infelizmente, não há nada adequado para mim.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Ótimo! Vou providenciar a documentação necessária, e você pode preparar seu navio para o carregamento.";
			link.l1 = "Vou fazer o meu melhor!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Ótimo! Vou providenciar os documentos necessários, e você pode preparar seu navio para o carregamento.";
			link.l1 = "Vou fazer o meu melhor!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Ótimo! Vou providenciar a papelada necessária, e você pode preparar seu navio para o carregamento.";
			link.l1 = "Vou fazer o meu melhor!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Vamos ver, então. Você deveria entregar uma carga de "+GetGoodsNameAlt(iFrahtGoods)+" no valor de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Mas pelo que vejo, você não entregou toda a carga - você está "+FindRussianQtyString(sti(amount))+" curto.";
				link.l1 = "Mil tubarões! Devem ser aqueles malditos ratos! Mas não se preocupe, "+GetAddress_FormToNPC(NPChar)+", vou comprar o que falta e entregar todo o lote.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Vamos ver, então. Você deveria entregar uma carga de "+GetGoodsNameAlt(iFrahtGoods)+" no valor de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Correto?";
			link.l1 = "Está absolutamente certo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Não vejo seu navio no porto. Lance âncora e depois venha falar comigo de novo – aí conversamos.";
			link.l1 = "Certo, vou fazer exatamente isso.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mas você era "+FindRussianDaysString(iTime)+" atrasado. Portanto, preciso reduzir seu pagamento pelo frete. Segundo o contrato, sua multa é de cinco por cento do valor total para cada dia de atraso. Agora, por favor, pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", e tente cumprir o contrato da próxima vez.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Obrigado!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Você entregou a carga? Que bonito. Na verdade, tivemos que comprá-la nós mesmos para entregar ao destinatário! E não foi nada barato, veja bem. Então, se quiser recuperar sua reputação, terá que nos ressarcir pelos gastos e ainda pagar a multa. Quanto à carga, pode ficar com ela – não precisamos mais dela.";
			link.l1 = "Sim, claro. Quanto?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Três vezes o valor das mercadorias. Isso dá "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "É uma quantia considerável. Mas negócios são negócios. Tudo bem, aqui está o seu dinheiro.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Você ficou louco? Exigir uma quantia absurda dessas é o cúmulo da ganância! Não vai receber nada de mim!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Uma decisão sábia. Agora vejo que você é realmente uma pessoa séria. Suponho que ainda podemos trabalhar juntos no futuro.";
			link.l1 = "Obrigado, mas agora preciso ir.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Ah, entendi... Bem, nesse caso, é melhor nunca mais aparecer em nenhuma autoridade portuária de "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! Cai fora!";
			link.l1 = "Com certeza não perdi muita coisa...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Apresse-se, o destinatário já sabe que seu navio chegou e está preocupado com a carga dele.";
			link.l1 = "Nesse caso, não vou perder mais tempo!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Este pacote deve ser entregue à autoridade portuária na cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", por "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", e o quanto antes. Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Concordo!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hum... Mas não vou por esse caminho. Desculpe, mas vou ter que recusar.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Excelente! Estou contando com você. Aqui está o pacote.";
			link.l1 = "Vou zarpar imediatamente!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mas você estava "+FindRussianDaysString(iTime)+" atrasado. Portanto, preciso reduzir seu pagamento pelo serviço. Segundo o contrato, sua penalidade é de cinco por cento do valor total por cada dia de atraso. Agora, por favor, pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", e tente cumprir o contrato da próxima vez.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "Obrigado!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "E o que vamos fazer com isso agora? As pessoas estão esperando por isso há séculos, e você só trouxe hoje. Tudo bem, me dê isso – talvez ainda sirva para alguma coisa. E imagino que você entende que não há pagamento devido agora.";
			link.l1 = "Claro que sim. Pegue seu embrulho. Adeus.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Então, você vai precisar escoltar navios."+pchar.questTemp.WPU.Escort.ShipName1+"' e '"+pchar.questTemp.WPU.Escort.ShipName2+"' para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", por "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Ambas as embarcações devem chegar ao destino em segurança. Você entregará os navios ao oficial da autoridade portuária local. Ele também será o responsável por lhe pagar pelo serviço.";
			link.l1 = "Tudo parece claro. Posso prosseguir?";
			link.l1.go = "escort_1";
			link.l2 = "Hum... Mas não vou por esse caminho. Desculpe, mas vou ter que recusar.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Pode ir em frente. Esses navios estão sob seu comando a partir de agora.";
			link.l1 = "Então estou zarpando!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hum... Vejo apenas um navio na sua escolta. Está correto?";
				link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Outro foi afundado em uma batalha contra um esquadrão inimigo.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Certo, então. Você deveria escoltar navios e entregar a carga de "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Mas vejo que você não entregou toda a carga - você está "+FindRussianQtyString(sti(amount))+" curto.";
					link.l1 = "Mil tubarões! Devem ser aqueles malditos ratos! Mas não se preocupe, "+GetAddress_FormToNPC(NPChar)+", eu vou comprar a quantidade que falta e entregar todo o lote.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Mas você era "+FindRussianDaysString(iTime)+" atrasado. Portanto, terei que descontar do seu pagamento pelo serviço. Segundo o contrato, sua multa é de cinco por cento do valor total por cada dia de atraso. Agora, por favor, pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", e tente cumprir o contrato da próxima vez.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Certo, então. Você deveria escoltar os navios e entregar a carga de "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "Obrigado!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Não vejo seu navio no porto. Ancore ao largo e depois venha falar comigo de novo – aí conversaremos.";
			link.l1 = "Certo, vou fazer exatamente isso.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Então, você vai precisar escoltar navios "+pchar.questTemp.WPU.Escort.ShipName1+"' e '"+pchar.questTemp.WPU.Escort.ShipName2+"' para a cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", por "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\nAlém disso, vou colocar a carga no seu navio, "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+". Pagamento pela entrega - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Tudo parece claro. Devo prosseguir?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hum... Mas não vou por esse caminho. Desculpe, mas vou ter que recusar.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Excelente! Assuma o comando do esquadrão.";
			link.l1 = "Então estou zarpando, hein!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Inacreditável! E para que precisávamos de você, então? Como pôde deixar isso acontecer?! Espero que entenda que uma recompensa agora está fora de questão.";
			link.l1 = "Claro, eu tenho... Bem, minhas saudações.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Inacreditável! E pra que precisamos de você, então? Como pôde deixar isso acontecer?! Espero que entenda que qualquer recompensa pela escolta está fora de questão agora... E não só isso, ainda está faltando carga também - "+FindRussianQtyString(sti(amount))+"\nNo geral, vou te pagar apenas pelo frete das mercadorias entregues em condições aceitáveis, descontando o valor dos itens que faltarem. Pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" e você pode ir para onde quiser.";
					link.l1 = "Bem, pelo menos é alguma coisa.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Incrível! E para que precisávamos de você, então? Como pôde deixar isso acontecer?! Espero que entenda que qualquer recompensa pela escolta está fora de cogitação agora... E não só isso, você também está com uma grande falta de carga.\nNão tenho tempo para esperar que consiga as mercadorias que faltam. Então, terá que compensar o valor total - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Quanto à carga, pode ficar com ela.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Certo, não se exalte. Aqui está o seu dinheiro.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Vocês ficaram todos loucos? Isso é pura extorsão! Não vou dar nada a vocês!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Incrível! E para que precisávamos de você então? Como pôde deixar isso acontecer?! Espero que entenda que qualquer recompensa pela escolta está fora de questão agora.\nNo geral, vou pagar apenas pelo frete das mercadorias que você trouxe. Pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" e você pode ir para onde quiser.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Inacreditável! E para que precisávamos de você, então? Como pôde deixar isso acontecer?! Espero que entenda que qualquer recompensa pela escolta agora está fora de questão... Você perdeu um navio, chegou "+FindRussianDaysString(iTime)+" atrasado, e além disso, ainda está com pouca carga - "+FindRussianQtyString(sti(amount))+"\nNão tenho tempo para esperar você conseguir as mercadorias que faltam. Então, terá que me ressarcir o valor total "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Quanto à carga, pode ficar com ela.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Certo, não se exalte. Aqui está seu dinheiro.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Vocês ficaram todos loucos? Isso é pura extorsão! Não vou dar nada para vocês!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Inacreditável! E pra que precisávamos de você, então? Como pôde deixar isso acontecer?! Espero que entenda que qualquer recompensa pela escolta está fora de questão agora... Além disso, você chegou "+FindRussianDaysString(iTime)+" atrasado.\nEntão tive que reduzir o pagamento pelo frete. Pelo acordo, a penalidade é de 10 por cento do valor original para cada dia de atraso. Agora, pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", e você pode ir.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Ah, entendi... Bem, nesse caso, é melhor nunca mais aparecer em nenhuma autoridade portuária de "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"! Cai fora!";
			link.l1 = "Com certeza não perdi muita coisa...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "Isso é muito, muito ruim! Para que te contratamos, pode me dizer? Para proteger os navios? Ou só para ficar à toa?";
			link.l1 = "Entendo. O inimigo era simplesmente forte demais, e... mas não adianta discutir - o que aconteceu, aconteceu. Mas a carga - a carga ainda está intacta! Então vamos resolver isso.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Vamos ver, então. Você deveria entregar uma carga de "+GetGoodsNameAlt(iFrahtGoods)+" no valor de "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Mas vejo que você não entregou toda a carga - você está "+FindRussianQtyString(sti(amount))+" curto.";
				link.l1 = "Mil tubarões! Devem ser aqueles malditos ratos! Mas não se preocupe, "+GetAddress_FormToNPC(NPChar)+", eu vou comprar a quantidade que falta e entregar o lote inteiro.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Vamos ver, então. Você deveria entregar uma carga de "+GetGoodsNameAlt(iFrahtGoods)+" no valor de "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Correto?";
			link.l1 = "Está absolutamente certo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hmm... Além de perder os navios que lhe foram confiados, você ainda chegou atrasado por "+FindRussianDaysString(iTime)+". Então eu tive que reduzir o pagamento pelo frete. Como você não conseguiu salvar os navios, cortei o pagamento pela metade, e isso é o máximo que posso te oferecer.\nAlém disso, conforme o contrato, a multa é de 10 por cento do valor original para cada dia de atraso. Agora, pegue seu "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", e lá vai você.";
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Bem, embora eu esteja extremamente desapontado por você não ter conseguido proteger os navios que lhe foram confiados, pelo menos entregou a mercadoria. Já que não foi capaz de salvar os navios, reduzi pela metade o pagamento pelo frete, e isso é o máximo que posso lhe oferecer. Agora, pegue seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" e você pode ir para onde quiser.";
			link.l1 = "Bem, pelo menos é alguma coisa.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Você precisará entregar um despacho oficial urgente ao governador da cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" não mais tarde que "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Tome muito cuidado – nossos inimigos podem estar atrás dessa mensagem também. O pagamento pela entrega – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Concordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Não, acho que vou deixar passar.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Você vai precisar entregar estes documentos ao dono da loja de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" não mais tarde que "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Este é o resumo mais recente dos preços nas lojas de todo o arquipélago - um documento comercial valioso. É preciso ter cuidado - concorrentes podem armar uma emboscada. O pagamento pela entrega - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Concordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Não, acho que vou deixar passar.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Você precisará entregar este maço de documentos ao agiota na cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" até o final de "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Estas são informações muito importantes sobre taxas de câmbio e preços das ações. Tome muito cuidado – alguns sujeitos suspeitos já estão de olho nesse pacote. O pagamento pela entrega – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Concordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Não, acho que vou deixar passar.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Você deve entregar este pacote ao mestre do cais na cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" até no máximo "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Contém os projetos para o novo "+RandPhraseSimple(LinkRandPhrase("brig","corveta","fragata"),LinkRandPhrase("flauta","pinnace","galeão"))+", empregando designs tecnológicos únicos. Espero que compreenda que há outros... interessados, então você terá que agir com discrição. O pagamento pela entrega - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Concordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Não, acho que vou deixar passar.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Então pegue os documentos e zarpe. Boa sorte... e que o Todo-Poderoso te proteja.";
			link.l1 = "Obrigado!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Que pena, de fato... Na verdade, propostas desse tipo não costumam ser descartadas assim. Mas a decisão é sua, de qualquer forma.";
			link.l1 = "Sim, essa é a minha decisão, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap(false);
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap(false);
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Maldição! Então eles te encontraram, afinal. Uma pena que você não seja um soldado, capitão – nesse caso, as coisas poderiam ter sido diferentes... Como eles eram?";
			link.l1 = "Dois homens fortes e robustos, vestidos de preto com meias-máscaras no rosto, armados com alabardas e espingardas de dois canos...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Vou avisar o governador imediatamente para que comece a procurá-los. Certo, até mais. "+GetAddress_Form(NPChar)+". De novo, é uma pena que você não seja um soldado...";
			link.l1 = "Sinto muito de verdade, "+GetAddress_FormToNPC(NPChar)+", pelo que aconteceu. Bem, adeus.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A demanda por uma certa mercadoria aumentou drasticamente em nossa colônia recentemente. As lojas locais já não têm mais em estoque. Portanto, gostaria que você me trouxesse "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+", e estou disposto a pagar o dobro - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" por item. Isso vai totalizar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, e tente cumprir o prazo de um mês – não vou poder esperar mais pelos produtos.";
				link.l1 = "Certo, vou aceitar essa missão.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sinto muito em decepcioná-lo, mas não posso fazer isso neste momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A demanda por uma certa mercadoria aumentou drasticamente em nossa colônia recentemente. As lojas locais já não têm mais em estoque. Portanto, gostaria que você me trouxesse "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+", e estou disposto a pagar o dobro - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" por item. Isso vai totalizar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, e tente cumprir o prazo de um mês – não posso esperar mais pelos produtos.";
				link.l1 = "Certo, eu aceito essa missão.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sinto muito em decepcioná-lo, mas não posso fazer isso neste momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "O arsenal da nossa colônia está drasticamente defasado "+GetGoodsNameAlt(iGoods)+". As lojas locais não têm mais em estoque. Portanto, gostaria que você me providenciasse "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+", e estou disposto a pagar o triplo - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" por item. Isso vai totalizar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, e tente cumprir o prazo de um mês – não posso esperar mais pelos produtos.";
				link.l1 = "Certo, eu aceito essa missão.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sinto muito em decepcioná-lo, mas não posso fazer isso neste momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Após o recente surto de febre em nossa colônia, estamos sem suprimentos médicos – e não restou nada nos estoques. O governador teme pela segurança dos habitantes da cidade. Por isso, gostaria que você me trouxesse "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+", e estou disposto a pagar o triplo - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" por pacote. Isso vai dar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, e tente cumprir o prazo de um mês – não vou poder esperar mais pelos produtos.";
				link.l1 = "Certo, vou aceitar essa missão.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sinto muito em decepcioná-lo, mas não posso fazer isso neste momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Depois de uma colheita ruim, nossa colônia está constantemente precisando de alimentos importados. Neste momento, nosso estoque está quase vazio, e tudo já foi retirado das prateleiras há bastante tempo. Gostaria de pedir que você me trouxesse "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(iGoodsQty)+", e estou disposto a pagar o dobro - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" por pacote. Isso vai dar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, e tente cumprir o prazo de um mês – não posso mais esperar por essas mercadorias.";
				link.l1 = "Certo, vou aceitar esta missão.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sinto muito em decepcioná-lo, mas não posso fazer isso neste momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Excelente! Fico muito satisfeito que você aceitou. Espero vê-lo novamente em breve.";
		link.l1 = "Claro, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Está brincando comigo? Você não tem a quantidade de mercadorias que eu pedi!";
			link.l1 = "Desculpe, foi meu erro...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Certo, você deveria entregar uma carga de "+GetGoodsNameAlt(iGoods)+" no valor de "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Excelente, muito obrigado. Aqui está o seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Foi um prazer fazer negócios com você, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Não vejo seu navio no porto. Ancore ao largo e depois venha falar comigo de novo – aí conversaremos.";
		link.l1 = "Certo, vou fazer exatamente isso.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Essa calamidade aconteceu há dez dias... Uma caravana de navios mercantes a caminho da nossa colônia foi atacada por piratas. Uma tempestade repentina obrigou os piratas a recuar, mas os navios mercantes se dispersaram e perderam uns aos outros de vista. No fim, todos os navios chegaram a portos diferentes, exceto um. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' desapareceu e seu destino continua desconhecido. Presumivelmente, ela pode ser encontrada perto da ilha desabitada de "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Peço que vá até lá, descubra o que aconteceu com o navio desaparecido e, se ele tiver sobrevivido, traga-o para o nosso porto. Decidiremos sua recompensa depois que o trabalho estiver feito, mas garanto que valerá a pena.";
				link.l1 = "Claro, eu concordo!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Desculpe, mas esse trabalho não é para mim. Acho que vou recusar.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Uma caravana comercial deveria chegar à nossa colônia, mas, pouco antes de entrar no porto, foi atacada por piratas. A batalha está acontecendo neste exato momento. Está fora do alcance dos canhões do forte, e no momento não tenho navios de escolta disponíveis, então não posso ajudar os pobres mercadores. Você é um capitão valente, por isso estou pedindo que intervenha e ajude os mercadores a repelir o ataque! Vai fazer isso?";
				link.l1 = "Claro! É uma questão de honra!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Desculpe, mas esse trabalho não é para mim. Acho que vou recusar.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "Um navio trazendo as armas e munições que nossa colônia encomendou chegou recentemente à colônia "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". O navio de escolta dela atingiu um recife, ficou seriamente danificado e não poderá deixar o porto tão cedo. Não podemos arriscar enviar um navio mercante com uma carga dessas sozinho.\nVocê aceitaria escoltá-la até nossa colônia? O pagamento pelo serviço está definido em "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Claro, eu concordo!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Desculpe, mas esse trabalho não é para mim. Infelizmente, vou ter que recusar.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Uma pena, de fato. Eu realmente estava contando com você...";
		link.l1 = "Também sinto muito. Bem, até nos encontrarmos de novo, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Excelente! Eu sabia que podia contar com você. Por favor, tente ser o mais rápido possível. Acho que "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" será o suficiente para chegar a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Aqui, pegue estes documentos para confirmar sua identidade. Bons ventos, capitão!";
		link.l1 = "Não se preocupe, eu não vou te decepcionar.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Finalmente! Aquele navio já estava me incomodando há tempo demais. Assuma o comando, então. O nome do navio é "+pchar.questTemp.WPU.Escort.ShipName+", e o capitão dela será imediatamente informado da sua chegada.";
		link.l1 = "Diga a ele para preparar o navio para zarpar - vou partir assim que surgir a primeira oportunidade.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Não vejo seu navio no porto. Fique afastado por enquanto e volte a me procurar mais tarde – aí conversaremos.";
		link.l1 = "É isso que vou fazer.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Excelente! Mais uma vez, você mostrou que é alguém em quem se pode confiar. Obrigado pelo trabalho bem feito. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". E não se esqueça de me visitar de vez em quando – sempre tem um ou outro trabalho para um capitão como você.";
		link.l1 = "Que bom ouvir isso, "+GetAddress_FormToNPC(NPChar)+"! Claro, nossa colaboração vai continuar. Saudações!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Não vejo seu navio no porto. Fique afastado por enquanto e venha me procurar mais tarde – aí conversamos.";
		link.l1 = "Certo, vou fazer exatamente isso.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Então, desejo-lhe uma viagem segura. E, por favor, não demore em sua busca! A tripulação daquele navio pode precisar de ajuda imediata.";
		link.l1 = "Entendi. Vou zarpar hoje!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Sim, já fui informado. Excelente trabalho, "+GetAddress_Form(NPChar)+"! Mais uma vez você provou que é alguém em quem posso confiar. Pegue sua recompensa - 30.000 pesos.\nLembre-se de me visitar de vez em quando - pessoas como você são valiosas, e sempre terei um trabalho adequado para você.";
		link.l1 = "Fico feliz em saber disso, "+GetAddress_FormToNPC(NPChar)+"! Claro, continuaremos cooperando. Tudo de bom!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Não vejo seu navio no porto. Fique afastado por enquanto e volte a me procurar mais tarde – aí conversaremos.";
		link.l1 = "Certo, vou fazer exatamente isso.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Sim, ele já me contou sobre a batalha com os piratas e como você foi heroico ao defender o navio dele. Excelente trabalho, "+GetAddress_Form(NPChar)+"! Mais uma vez você provou que é alguém em quem posso confiar. Pegue sua recompensa - 50.000 pesos.\nLembre-se de me visitar de vez em quando - pessoas como você são valiosas, e sempre terei um trabalho adequado para você.";
		link.l1 = "Que bom ouvir isso, "+GetAddress_FormToNPC(NPChar)+"! Claro, nossa colaboração vai continuar. Saudações!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Não vejo seu navio no porto. Fique afastado por enquanto e volte a me procurar mais tarde – aí conversaremos.";
		link.l1 = "Certo, vou fazer exatamente isso.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Que fim trágico... Que Deus os tenha em paz.";
		link.l1 = "Fiz tudo o que pude, "+GetAddress_FormToNPC(NPChar)+". A tempestade só piorou a situação.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Acredito, "+GetAddress_Form(NPChar)+", que você fez tudo o que pôde para salvar o navio e aqueles pobres marinheiros. Mas, infelizmente... Bem, por favor, aceite sua recompensa - 10.000 pesos - e obrigado pelo seu serviço.";
		link.l1 = "Não há pelo que me agradecer, "+GetAddress_FormToNPC(NPChar)+". Sinto muito de verdade. Bem, adeus.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Sim, ele já me contou sobre você lutando contra os pagãos de pele vermelha e depois contra um navio pirata – como um verdadeiro herói. Excelente trabalho, "+GetAddress_Form(NPChar)+"! Mais uma vez você provou ser alguém em quem posso confiar.\nPegue sua recompensa - 40.000 pesos. Lembre-se de me visitar de vez em quando - pessoas como você são valiosas, e sempre terei um trabalho à sua altura.";
		link.l1 = "Fico feliz em ouvir isso, "+GetAddress_FormToNPC(NPChar)+"! Claro, nossa colaboração vai continuar. Saudações!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Eu sabia que podia contar com você. Boa sorte, Capitão! Toda a colônia deseja a sua vitória!";
		link.l1 = "Vou tentar estar à altura das suas expectativas. Agora vou zarpar, e que Deus nos ajude!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Sim, a cidade inteira assistiu à sua batalha. Pobres mercadores, sinto pena deles. Bem, pelo menos você conseguiu salvar um navio, então sua recompensa de 10.000 pesos é mais do que merecida. Por favor, aceite – e obrigado pela sua ajuda.";
				link.l1 = "Não há pelo que me agradecer... É uma pena que eu não tenha vencido aquela luta de forma decisiva, mas fiz tudo o que estava ao meu alcance. Adeus, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Sim, a cidade inteira assistiu à batalha que você travou – e devo dizer que foi com muita habilidade. Aquele pobre comerciante, sinto muito por ele... Mas, se não fosse por você, ninguém teria escapado com vida, então sua recompensa de 25.000 pesos é mais do que merecida. Por favor, aceite – e obrigado pela sua ajuda.";
				link.l1 = "Bem, obrigado pela avaliação generosa das minhas ações, mas não acho que essa tenha sido minha melhor batalha – ainda perdi um navio. Enfim, destino é destino, e não há nada a fazer quanto a isso. Adeus, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Sim, a cidade inteira assistiu à batalha que você travou – foi simplesmente magnífico! Você acabou com todo o esquadrão daqueles piratas imundos! Agora eles aprenderam a lição – pena que já não vai adiantar para eles. Sua recompensa é de 50.000 pesos – por favor, aceite.";
				link.l1 = "Obrigado pela sua avaliação generosa das minhas ações! Sempre um prazer ajudar. E agora, "+GetAddress_FormToNPC(NPChar)+", por favor, permita-me me retirar.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Hmm, isso é ruim. Nesse caso, qualquer outro trabalho para mim está fora de questão.";
			link.l1 = "Entendido. Aqui está o que eu queria dizer...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Que pena, capitão... É uma lástima que você não esteja disposto a me ajudar.";
			link.l1 = "Isso não depende da minha vontade, meu bom homem. Você precisa entender. Adeus.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "O que há de errado com você, capitão?! Não sente vergonha?! Como pôde fazer isso?! Eu sei muito bem do meu trabalho, estou nesse serviço há muitos anos. Existem contratos de seguro, e a seguradora está disposta a pagar, e garanto que o valor segurado é bastante razoável.";
			link.l1 = "Qual é o seu problema, senhor? O depósito de pólvora explodiu, houve vítimas, e agora você vai ter que responder por sua negligência?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Não! Claro que não! Deus me livre, senão eu perderia a cabeça. O porão estava absolutamente vazio, graças a Deus, graças à Virgem Maria!\n"+"E o problema é que o navio pertence a... ou melhor, pertencia ao Sr. "+sCapitainId+", bem conhecida em todo o Caribe. E ela foi construída na Europa sob encomenda especial, com características extraordinárias. "+"E esse armador era orgulhoso demais e se gabava pra todo lado, um verdadeiro idiota, Deus me perdoe... O que eu digo pra ele agora? É melhor eu me matar, juro...";
			link.l1 = "Ah, agora entendo qual é o problema, de fato. E o que havia de tão especial nesse navio? Que características incomuns ele tinha para deixar o dono tão orgulhoso?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me in the yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "E o que o pessoal do cais está dizendo? Será mesmo impossível construir outro aqui?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Ninguém pode. Eu até fui até a ilha próxima para perguntar aos moradores. Disseram que há um mestre renomado na Isla Tesoro que consegue quase tudo em construção naval. Mas a Isla Tesoro fica tão longe, pelo amor de Deus. Só me resta contar com a ajuda de capitães livres como você. Quem sabe você acaba encontrando um navio desses pra mim. O resto, eu resolvo\n"+"Vou lhe agradecer generosamente, e a seguradora fará o mesmo. É uma situação incomum, sabe. Quem ousaria contrariar um homem tão poderoso?";
			link.l1 = "É, isso não vai ser fácil. E quanto tempo eu tenho?";
			link.l1.go = "BurntShip8";
			link.l2 = "Não, amigo, não posso me envolver em um assunto desses. Sem contar que não há garantias de que exista um navio com tais características. Sinto muito...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Graças a Deus, ainda temos tempo. O dono partiu para a Europa e só volta daqui a pelo menos meio ano.";
			link.l1 = "Bem, acho que vou dar um jeito nisso. Vou trazer um navio parecido para você. Mas lembre-se disso – se resolver economizar demais, eu queimo ele bem na sua frente!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "O que você está insinuando, capitão? Claro, entendo que você precisa de tempo – não se trata de encontrar qualquer embarcação em qualquer poça... Apenas traga o navio para nós e faremos o nosso melhor, pode contar com isso...";
			link.l1 = "Assim espero... Bem, aguarde por mim e por boas notícias. Até logo.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "Sobre o que queria conversar?";
			link.l1 = "E onde está o antigo mestre do porto, senhor "+NPChar.Quest.BurntShip.LastPortmanName+"? Tenho negócios com ele.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Ele não está mais por aqui. Imagine só – ele incendiou um navio de uma pessoa importante e embolsou o dinheiro do seguro. Enquanto as autoridades tentavam resolver tudo isso, ele pediu demissão e fugiu para a Europa. Um verdadeiro trapaceiro, não acha?";
			link.l1 = "Sim, já ouvi essa história. Desculpe, mas preciso ir.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "Sobre o que queria conversar?";
			link.l1 = "Trouxe um navio incomum, como você pediu. Agora espero minha recompensa.";
			link.l1.go = "BurntShip14";
			link.l2 = "Sabe, "+GetFullName(NPChar)+", ainda não encontrei nenhum navio que atenda ao que você precisa. Acho que vou ter que desistir desse trabalho. Desculpe se te decepcionei...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Que pena, capitão... É uma lástima que você não queira me ajudar.";
			link.l1 = "Isso não depende da minha vontade, meu bom homem. Por favor, compreenda. Adeus.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Oh, é mesmo! E qual é o nome do nosso novo navio?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Com licença, volto mais tarde.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Ah, capitão, estou tão feliz que você não me decepcionou! Que "+GetSexPhrase("bom rapaz","moça de respeito")+" você me salvou, literalmente salvou minha vida... Por favor, poderia vir buscar seu pagamento em alguns dias? Sabe como é, preciso resolver as formalidades com o seguro... Enquanto isso, você pode fazer pequenos reparos no navio – trocar as velas, tapar os buracos, uma careenagem também não faria mal...";
			link.l99 = "Eu prometi que faria algo desagradável com o navio se você tentasse me enganar. Já esqueceu?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Não, não, claro que não! Vou cumprir minha palavra, pode ficar tranquilo. Veja, sabendo que haveria mais despesas para, digamos, disfarçar o novo navio, emprestei o dinheiro do seguro que recebi pelo navio antigo a juros. Espero que compreenda...";
			link.l1 = "Vou entender muito melhor quando o dinheiro chegar ao meu baú. Até a próxima.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "O que você queria conversar?";
			link.l1 = "Vim buscar minha recompensa. Ainda tenho o navio que você precisa.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Você poderia me lembrar o nome? Minha memória já não é mais a mesma — sabe como é, toda aquela correria...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Com licença, volto mais tarde.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Sim, perfeito. Estou pronto para lhe dar sua recompensa, "+FindRussianMoneyString(cn)+". Foi assim que a seguradora avaliou o valor da embarcação incendiada. A indenização será paga em baús de crédito – nada de dinheiro, desculpe.";
			link.l1 = "Ah não, esse valor não me serve. Tenho certeza de que este navio vale muito mais.";
			link.l1.go = "BurntShip21";
			link.l2 = "Isso mesmo. Fico feliz por ter ajudado você. Até logo.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "O que está dizendo, capitão?! Confie em mim, eu sei do que estou falando. Esse dinheiro daria para comprar dois navios como aquele!";
			link.l1 = "Acho que vou ficar com ele. Sabe, acabei pegando gosto por isso... Adeus.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "Um dos capitães esqueceu o diário de bordo no meu escritório. Que cabeça de vento! Preciso que você o alcance e devolva o diário para ele.";
				link.l1 = "Ah, isso vai ser fácil... Eu vou pegar isso!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Não, não vou me envolver nisso. Na verdade, é problema dele.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Um navio foi roubado do cais ali. Quero que você encontre a embarcação roubada e a traga de volta.";
				link.l1 = "Hum, bem, estou pronto para começar a investigação.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Desculpe, mas não me envolvo em buscas por navios roubados.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Excelente, aqui está o diário de bordo dele... Você realmente tirou um peso das minhas costas! Perder o diário de bordo de um navio é algo terrível. Sempre tive pena desses capitães...";
			link.l1 = "Bem, isso sim é motivo pra preocupação! Agora, me conte mais sobre esse capitão distraído.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Sim, claro! O nome dele é "+npchar.quest.PortmansJornal.capName+", ele é o capitão do "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" chamado de '"+npchar.quest.PortmansJornal.shipName+"'. Ele partiu há pouco tempo e foi para "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "Entendi. Certo, vou encontrá-lo. Agora, e quanto ao pagamento?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" Ele mesmo vai te pagar, é do interesse dele. Só se preocupe em chegar até ele o quanto antes e tudo vai dar certo.";
			link.l1 = "Entendi. Bem, então vou indo...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Excelente! Sabe, o navio roubado pertence a uma pessoa influente, então isso é muito importante para mim. Vou te pagar muito bem por esse serviço...";
			link.l1 = "Entendo. Conte-me mais sobre o navio e as circunstâncias em que ele foi roubado.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" chamado de '"+npchar.quest.PortmansSeekShip.shipName+"' foi roubado durante a noite "+FindRussianDaysString(rand(5)+10)+" atrás. O vigia foi morto.";
			link.l1 = "Hmm... Eles já devem estar bem longe agora. O rastro não está mais fresco, e esse é o problema.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "É verdade, mas mesmo assim não vi motivo para soar o alarme imediatamente. O navio militar poderia alcançá-los, mas só iria destruir o navio inteiro — e isso não é exatamente o que eu preciso.";
			link.l1 = "Entendi. Bem, vou começar minha busca. Espero ter sorte.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Uma pena – mas não podíamos mesmo contar com o sucesso.";
			link.l1 = "Sim, já faz tempo demais desde que o navio foi roubado.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Bem, obrigado pela sua ajuda de qualquer forma, mesmo que seus esforços não tenham sido tão frutíferos quanto esperávamos.";
			link.l1 = "Eu fiz tudo o que pude...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Excelente! Embora eu suspeite que este não seja exatamente o navio que foi roubado... Ah, quem se importa! Eu vou ficar com ele.";
				link.l1 = "Sim, de fato...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Excelente! Você me ajudou muito. Nem consigo imaginar o quanto isso deve ter sido difícil.";
				link.l1 = "Sim, de fato...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Estou pronto para lhe pagar sua recompensa. Ela consiste em "+makeint(sti(npchar.quest.money))+" em dobrões. Infelizmente, não posso lhe pagar mais do que isso.";
			link.l1 = "Bem, isso é o suficiente. Obrigado e um cordial cumprimento.";
			link.l1.go = "exit";
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.money));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Há vários capitães registrados. Você está interessado em alguém em especial?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "Não tenho nenhum capitão na minha lista que possa ser do seu interesse.";
				link.l1 = "Entendi. Bem, obrigado pela informação.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bem, vejamos... Ahá! Ali! ","Ah-ha... A-ha! Aí está! ","Certo, então. ")+"Capitão "+GetFullName(sld)+" "+arCapLocal.date+" ano deixou nosso porto e partiu para "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Obrigado. Gostaria de revisar a lista novamente...";
			link.l1.go = "CapitainList";
			link.l2 = "Certo, é só isso. Não tenho interesse em nenhum outro capitão.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bem, vejamos... Ahá! Ali! ","Ah-ha... A-ha! Aí está! ","Certo, então. ")+"Capitão "+GetFullName(sld)+" "+arCapLocal.date+" ano deixou nosso porto e partiu para "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Obrigado. Gostaria de revisar a lista novamente...";
			link.l1.go = "CapitainList";
			link.l2 = "Certo, é só isso. Não tenho interesse em nenhum outro capitão.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bem, vejamos... Ahá! Ali! ","Ah-ha... A-ha! Aí está! ","Certo, então. ")+"Capitão "+GetFullName(sld)+" "+arCapLocal.date+" ano deixou nosso porto e partiu para "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Obrigado. Gostaria de revisar a lista novamente...";
			link.l1.go = "CapitainList";
			link.l2 = "Certo, é só isso. Não tenho interesse em nenhum outro capitão.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bem, vejamos... Ahá! Ali! ","Ah-ha... A-ha! Aí está! ","Certo, então. ")+"Capitão "+GetFullName(sld)+" "+arCapLocal.date+" ano deixou nosso porto e navegou para "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Obrigado. Gostaria de revisar a lista novamente...";
			link.l1.go = "CapitainList";
			link.l2 = "Certo, é só isso. Não me interesso por nenhum outro capitão.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bem, vejamos... Ahá! Ali! ","Ah-ha... A-ha! Aí está! ","Certo, então. ")+"Capitão "+GetFullName(sld)+" "+arCapLocal.date+" ano deixou nosso porto e partiu para "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Obrigado. Gostaria de revisar a lista novamente...";
			link.l1.go = "CapitainList";
			link.l2 = "Certo, é só isso. Não tenho interesse em nenhum outro capitão.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Estou ouvindo – qual navio, por quanto tempo?";
    		Link.l1 = "Lucas Rodenburg me enviou. Ele disse que posso atracar meu navio aqui de graça.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Estou ouvindo – qual navio, por quanto tempo?";
    		Link.l1 = "Richard Fleetwood me enviou. Ele disse que eu poderia atracar minha nau capitânia aqui por 10.000 pesos.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Bem, isso está correto. Mas infelizmente, não posso aceitar seu navio no momento. Não há espaço disponível no cais.";
    			Link.l1 = "Que pena.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "E qual navio em particular você pretende deixar aqui?";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "Não importa, obrigado.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... Não vejo nenhum dos seus navios.";
	    			Link.l1 = "Eu só queria perguntar sobre a possibilidade de atracar.";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStock_2":
			// --> andre270925 оставаил тут комментом старый код чтобы забрать куски перевода, если нужно
      //       chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && npchar.id == "Beliz_portman" && !CheckAttribute(npchar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)	// В Белизе скидка 50%
			// {
			// 	NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref)/2;
			// }
			// else
			// {
			// 	if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = MOD_SKILL_ENEMY_RATE/2*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			// 	else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			// }
			// dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', class "+RealShips[sti(chref.Ship.Type)].Class+", os custos de atracação são "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" por mês, pagamento adiantado de um mês.";
			// Link.l1 = "Sim, isso me serve.";
			// if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			// {
			//     Link.l1.go = "ShipStock_3";
			// }
			// else
			// {
      //           Link.l1.go = "ShipStock_NoMoney";
			// }
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			PortmanCalculatePrices(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', class "+RealShips[sti(chref.Ship.Type)].Class+", custo de atracação "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" por mês, pago adiantado.";
			dialog.Text = dialog.Text+" Se você deixar com um oficial e a tripulação, então junto com eles "+FindRussianMoneyString(sti(NPChar.MoneyForShip)+sti(NPChar.MoneyForCrew));

			Link.l1 = "Sim. Isso serve para mim.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip)) Link.l1.go = "ShipStock_3";
			else  Link.l2.go = "ShipStock_NoMoney";

			Link.l2 = "Sim. Por mim está ótimo. Deixe com o capitão e a tripulação";
			if (sti(Pchar.Money) >= (sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew))) Link.l2.go = "ShipStock_4";
			else Link.l2.go = "ShipStock_NoMoney";

			Link.l3 = "Não, mudei de ideia.";  
			Link.l3.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "E isso também vai me servir, assim que você juntar a quantia necessária.";
			Link.l1 = "Opa... Eu volto mais tarde.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
		 	LeaveShipInPort(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Certo. Você pode pegar seu navio de volta quando precisar.";
			Link.l1 = "Obrigado.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_4":
		 	LeaveShipInPortWithCrew(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Certo. Você pode pegar seu navio de volta quando precisar.";
			Link.l1 = "Obrigado.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Qual navio exatamente você vai levar?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and my officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "Não, mudei de ideia.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Você tem espaço para mais um navio?";
	    			Link.l1 = "Ah, certo. Obrigado.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hum. Não vejo sua nau capitânia no porto. E você só pode recuperar seus navios aqui.";
    			Link.l1 = "Certo, eu volto para buscá-los depois.";
    			Link.l1.go = "exit";
			}
		break;

		case "ShipStockManBack":
			// Лимит офицеров не позволяет забрать  
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "Capitão, parece que não há espaço na sua tripulação para mais um oficial.";  
				link.l1 = "Hum... Então volto mais tarde.";  
				link.l1.go = "exit";  
				break;  
			}
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Vamos ver... Este navio partiu do porto às "+chref.quest.Mutiny.date+".";
				link.l1 = "O que você quer dizer com 'foi embora'? Ela deve estar aqui, no cais!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Quer pegar seu navio? Pela atracação, você ainda deve "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "Pegando?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Sim.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Não, mudei de ideia.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			if(CheckAttribute(chref, "DontNullShip"))
			{
				DeleteAttribute(chref, "DontNullShip");
				DeleteAttribute(NPChar, "DontNullShipBeliz");
			}
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "Para qual dos seus oficiais devo entregar isso?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring an officer with me for this ship.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I've changed my mind..";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Sim, sim, eu sei. Mas só posso oferecer ancoragem gratuita para um navio. Então, por favor, resolva isso com o seu esquadrão e depois volte aqui.";
				link.l1 = "Certo, vou trazer só a nau capitânia.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Sim, sim, eu sei. Por ordem do senhor Rodenburg, aceitamos sua embarcação para armazenamento e vamos designar um oficial de guarda durante todo o tempo em que seu navio permanecer aqui. Por favor, assine aqui... e aqui...";
				link.l1 = "Certo... Imagino que todas as formalidades já estejam resolvidas?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Sim. Não precisa mais se preocupar com seu navio – nós cuidaremos dela. Pode voltar para o senhor Rodenburg.";
			link.l1 = "Obrigado. Adeus.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Sim, sim, eu sei. Mas só posso oferecer ancoragem gratuita para um navio. Então, por favor, resolva isso com o seu esquadrão e depois volte aqui.";
				link.l1 = "Certo, vou levar só a nau capitânia.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Sim, claro. Você está com o dinheiro aí?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Claro. Aqui está.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Não. Eu volto já.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Certo. Cuidaremos da sua embarcação e disponibilizaremos um oficial de vigilância durante todo o tempo em que seu navio permanecer aqui.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Queria alguma coisa, capitão?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Seu oficial "+GetFullName(chref)+" informado"+NPCharSexPhrase(chref,"","")+" me diga isso "+NPCharSexPhrase(chref,"ele","ela")+" Eu tive que ir para o mar por sua ordem. Eu não reclamei "+NPCharSexPhrase(chref,"ele","ela")+".";
			link.l1 = "Merda! Não houve nenhuma ordem assim! Eu não devia ter confiado meu navio àquele desgraçado! Ah, tanto faz, não tem mais nada que eu possa fazer sobre essa perda mesmo.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Que surpresa... Será que "+NPCharSexPhrase(chref,"ele","ela")+" por acaso, você sabe para onde eles foram?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Me desculpe, "+GetAddress_Form(NPChar)+". Você deveria ser mais cuidadoso com seus subordinados.";
			link.l1 = "Eu sei, fui um tolo. Adeus, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Navios únicos e as pessoas a quem são confiados não passam despercebidos no arquipélago. No entanto, essa informação tem grande valor e não é compartilhada facilmente.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Entendo. A quantia de 25.000 pesos seria suficiente para demonstrar minhas intenções sinceras?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "Certo, talvez em outra ocasião.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "De fato, isso seria aceitável. Em qual embarcação específica você está interessado?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galeão '"+GetShipName("Santíssima Misericórdia")+"'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Patrulha Snow '"+GetShipName("Lady Beth")+"'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "Brigue '"+GetShipName("Memento")+"'.";
				link.l3.go = "UniqueShips_Memento";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Amsterdam_InfoPU"))
			{
				link.l4 = "Nau Capitânia da Companhia '"+GetShipName("Amsterdam")+"'.";
				link.l4.go = "UniqueShips_Amsterdam";
			}
			link.l99 = "Acho que já sei o suficiente.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "A Santa Misericórdia foi enviada pelo Escorial da Europa para supervisionar as colônias espanholas. Seu capitão, Dom Alamida, é um renomado servidor da coroa espanhola, um combatente implacável contra a corrupção e o crime, e um fervoroso defensor da fé católica. A Santa Misericórdia navega entre as colônias, começando e terminando sua jornada em Havana, dedicada exclusivamente à sua missão.\nEm cada porto, Alamida passa vários dias, às vezes até mais. Dizem que, nesses períodos, ele pode até ser visto andando pelas ruas, mas os moradores locais não ficam muito animados com esse encontro—entre os espanhóis, o senhor inspira apenas medo e respeito.\nA Santa Misericórdia conta com uma tripulação experiente e leal, escolhida pessoalmente por Alamida. Cada marinheiro está pronto para defender sua pátria e seu capitão com a própria vida. Dizem que Dom Fernando ordenou que a Santa Misericórdia jamais seja capturada, e há rumores de que, se a tripulação se visse diante de uma situação impossível durante um abordo, prefeririam afundar o navio a deixá-lo ser tomado.";
			link.l1 = "Muito obrigado.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "Lady Beth é uma verdadeira beleza. Uma maravilha do gênio marítimo inglês, comandada por Albert Blackwood, um ex-oficial da Marinha Real. De fato, nem todo mundo consegue desertar de forma tão espetacular! Ele abandonou o serviço, destruiu uma carreira brilhante e roubou um navio de guerra—tudo para caçar tesouros!\nE não foi em vão. Já encontrou o suficiente para comprar metade de Barbados, mas ainda quer mais. Se encontrá-lo no mar—nem pense em interceptá-lo. O navio é excelente, e o capitão é experiente e cauteloso. Ultimamente, Blackwood tem frequentado Cayman—escavando dia e noite, fazendo o povo trabalhar até a morte. Se decidir conferir—leve pelo menos sessenta homens e boas armas de fogo... Na verdade, talvez nem isso baste\nEspero que saiba atirar, pois uma companhia de ex-fuzileiros navais sob o comando do Coronel Fox desertou junto com ele. Profissionais, nada a ver com bandidos comuns. E nunca o ataque em portos franceses—lá ele tem proteção e padrinhos, recebendo uma parte dos achados.";
			link.l1 = "Muito obrigado.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "O 'Memento' — uma verdadeira lenda pirata. Um brigue negro comandado por Mortimer Grim.\n"+"Grim caça exclusivamente traficantes de escravos. Dizem que ele liberta os cativos e compra a liberdade dos condenados com ouro de verdade. Uma causa nobre — se você não souber do resto.\n"+"Se você não transporta carga humana, Grim não vai mexer com você. Ele é estranho, mas tem seus princípios. Mas se você tiver escravos no porão... reze para não avistar velas negras no horizonte.\n"+"O 'Memento' navega entre refúgios de piratas, mas raramente atraca. A tripulação vive a bordo por meses, como se tivesse medo de pisar em terra firme. Dizem que o navio já sobreviveu a uma epidemia monstruosa — por isso sua tripulação é tão difícil de matar.\n"+"Se você pretende enfrentá-los, leve mais canhões. Abordar o 'Memento' é quase impossível — a tripulação luta como se estivesse possuída, como se não temesse a morte. A única maneira de vencê-los é despedaçar o navio e tirar o abrigo deles. Lasca de madeira não assusta, mas tiro de metralha direto — aí é outra história.\n"+"Boa sorte. E lembre-se da morte.";
			link.l1 = "Muito obrigado.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Amsterdam":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "4");
			pchar.questTemp.Amsterdam_InfoPU = true;
			dialog.text = "A nau capitânia da respeitada Companhia Holandesa das Índias Ocidentais. Tudo sobre este navio é envolto em mistério. Ele é comandado por Hendrik van Doorn, chefe do departamento de registro naval em Curaçao — um homem de eficiência excepcional que presta serviços inestimáveis aos capitães mais ricos e influentes. Tente conquistar um lugar entre eles, e talvez descubra mais.";
			link.l1 = "Muito obrigado.";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 10) + (sti(pchar.rank)*5); //вознаграждение
	// npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты



void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
