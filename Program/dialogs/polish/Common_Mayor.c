// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Ośmieliłeś się pokazać swoją twarz w moim domu?! Bardzo odważne z twojej strony, albo głupie...","Jak moi idiotyczni strażnicy dopuścili do tego, że wróg włamał się do mojego pałacu? Kogoś głowa za to poleci.","Widać, że moi strażnicy nie są warci złamanego grosza, skoro jakiś łotr biega po mojej rezydencji i grzebie w moich rzeczach..."),LinkRandPhrase("Czego potrzebujesz, "+GetSexPhrase("łotrze","diabeł")+"?! Moi żołnierze już są na twoim tropie"+GetSexPhrase(", plugawy piracie","")+"!",+"Morderco, natychmiast opuść mój dom! Strażnicy!","Nie boję się ciebie, "+GetSexPhrase("łotrze","szczurze")+" ! Wkrótce zostaniesz powieszony w naszym forcie!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Twoi żołnierze są bezwartościowi.","Spróbuj mnie złapać."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar,"")+", albo zamknę ją za ciebie!","Milcz, kamracie, a pozostaniesz przy życiu."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Czego potrzebujesz?";
					link.l1 = "Chciałem porozmawiać z tobą o ważnej robocie.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Czego potrzebujesz?";
					link.l1 = "Chciałem porozmawiać z tobą o ważnej pracy.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Nie ma o czym rozmawiać, hultaju. Jestem zajęty.";
					link.l1 = "Moje przeprosiny.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "O, kogo my tu mamy! To"+GetSexPhrase("","")+" "+GetFullName(pchar)+" Wiesz, właśnie niedawno wysłałem łowców piratów, by cię tu sprowadzili. Gdybym wiedział, że przyjdziesz tu jak gdyby nigdy nic, zaoszczędziłbym swoje pieniądze.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Już miałem się zabrać za rozliczenie naszych rachunków.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Czas na szybkie wyjście.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Włamanie! Straż! Alarm! Morderstwo!";
				link.l1 = "Cholera!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Czego sobie życzysz, monsieur?";
				link.l1 = "Witaj, Wasza Wysokość. Jestem Charles de Maure, niedawno przybyłem z Paryża. Szukam Michela de Monpera.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Och, to ty, panie... Muszę przeprosić za moją niegrzeczność. Moje przeprosiny, jesteśmy daleko od uprzejmości Paryża tutaj w koloniach.";
					link.l1 = "Oczywiście, Wasza Łaskawość.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Czy czegoś potrzebujesz, Charles?";
					link.l1 = "Mam pytanie...";
					link.l1.go = "quests";
					link.l2 = "Nie, nic.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Monsieur, znalazłem zwłoki bandyty w dżungli. Został zabity przez Indian. Na jego ciele były kolczyki, wyglądają na przywiezione z Europy. Może należały do któregoś z szlachciców w waszym mieście?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Witamy na Karaibach, Kapitanie de Maure. Tym razem na serio.";
				link.l1 = "Dziękuję, Wasza Ekscelencjo.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "Dobrze cię widzieć, Gubernatorze! Jak się miewasz? Wszystko pod kontrolą na Sint Maarten.";
				link.l1 = "Nie mam czasu, by zostać. Kontynuuj dobrą robotę.";
				link.l1.go = "exit";
				link.l2 = "Chciałem porozmawiać o pracy.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "A może gra w kości?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Mój Boże, cieszę się, że cię widzę, Generale-Gubernatorze! Wszystko w porządku w naszej skromnej małej kolonii! Proszę, usiądź, rozkażę służbie nakryć do stołu...";
				link.l1 = "Nie ma potrzeby. Nie przybyłem na długo. Kontynuuj dobrą robotę.";
				link.l1.go = "exit"; 
				link.l2 = "Chciałem pomówić o pracy.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Co powiesz na grę losową?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Któż to do nas zawitał! Monsieur Gubernator Generalny Francuskich Kolonii! Czego sobie życzysz, Wasza Łaskawość? Siadaj, rozkażę moim sługom przynieść wino i świeże owoce.";
				link.l1 = "Nie martw się, przyszedłem tutaj tylko dlatego, że odwiedzałem wyspę i nie mogłem przejść obok, nie mówiąc dzień dobry.";
				link.l1.go = "exit"; 
				link.l2 = "Chciałem porozmawiać o pracy.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "A co powiesz na grę hazardową?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "O, oto jesteś, kapitanie! Muszę przyznać, że kazałeś na siebie czekać.";
				link.l1 = "Przybyłem przy najbliższej okazji, Wasza Ekscelencjo. Powiedziano mi, że masz pilną sprawę?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Moi ludzie powiedzieli mi, że byłeś bardzo natarczywy, domagając się audiencji. Nazywam się "+GetFullName(npchar)+". Jestem gubernatorem miasta "+GetCityName(NPChar.city)+", poddany "+NationKingsName(npchar)+" A teraz, proszę, czego sobie życzysz "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Me imię to "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Panno MacArthur.";
					link.l1 = TimeGreeting()+", Wasza Ekscelencjo.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Czy to wszystko?";
                        link.l1 = "Tak, sir. Nie będę cię dłużej zatrzymywać.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Przykro mi cię zmartwić, ale nie mam teraz czasu na rozmowę z tobą. Jak zapewne wiesz, nasza kolonia została zaatakowana przez "+NationNamePeople(sti(aData.nation))+"  Wciąż zajmuję się naszą obroną.";
                        link.l1 = "Chcę zaoferować swoją pomoc w obronie fortu.";
                        link.l1.go = "siege_task";
                        link.l2 = "W takim razie nie będę cię dłużej zatrzymywać.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("Mówią, że pomogłeś nam odeprzeć "+NationNameSK(sti(aData.nation))+" szwadron i bronić naszej kolonii! Jesteśmy ci wdzięczni, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "O, to ty, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", cieszę się, że cię widzę. Dobre wieści dla naszej kolonii - udało nam się odeprzeć "+NationNameSK(sti(aData.nation))+" najeźdźcy. Masz w tym swój udział, więc oto twoja nagroda - "+(sti(aData.iSquadronPower)*1500)+" pesos. Proszę bardzo.";
                        link.l1 = "Dziękuję, "+GetAddress_FormToNPC(NPChar)+"Z przyjemnością robi z panem interesy!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Mam dla ciebie zadanie, ale jest ono nieco niezwykłe.";
								link.l1 = "To są zadania, w których jestem najlepszy.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("O, to znowu ty? Czego tym razem ode mnie chcesz?","Odciągasz mnie od spraw mego miasta. Czego chcesz, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Chcę porozmawiać z tobą o pracy dla "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+"Znalazłem kilku piratów. Wszyscy "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" są obecnie na pokładzie. Chcę ich przekazać władzom.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Miałem zamiar porozmawiać z tobą na ważny temat.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Jest kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" nazwany "+pchar.GenQuest.CaptainComission.Name+", jak mogę go zobaczyć?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Były kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"zgodził się ujawnić swój skarb władzom.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Dawny kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ujawnił mi swoją skrytkę.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Data"))+" Spotkałem kapitana "+pchar.GenQuest.ShipWreck.Name+"i jego marynarze, którzy zostali wysadzeni na brzeg przez pirata"+pchar.GenQuest.ShipWreck.BadName+". "+"Niestety, miałem już zbyt wielu ludzi na moim statku i nie mogłem ich zabrać na pokład. Ale zostawiłem im zapasy i broń. Jeśli statek ratunkowy ich nie zabierze w ciągu "+(30 - iDay)+" dni, potem nie wiem, czy znajdę ich żywych, czy nie.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" Spotkałem marynarzy z rozbitego statku '"+pchar.GenQuest.ShipWreck.ShipTypeName+" z ich kapitanem. "+"Niestety, miałem już zbyt wielu ludzi na moim statku i nie mogłem ich zabrać na pokład. Ale zostawiłem im zapasy i broń. Jeśli statek ratunkowy ich nie zabierze w ciągu "+(30 - iDay)+" dni, a potem nie wiem, czy znajdzie ich żywych, czy nie.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Chcę oddać więźnia.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Muszę załatwić z tobą pewne sprawy finansowe.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Udało mi się znaleźć twój pierścień. Proszę bardzo.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Mam twoją obrączkę. Jedna z... pracujących dziewcząt w burdelu ją miała.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Niosę wiadomość z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"General")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", Znalazłem bandę przemytników, których przywódca został niedawno schwytany przez strażników. Teraz planują jego ucieczkę. Ich statek '"+PChar.GenQuest.JusticeOnSale.ShipName+"jest zacumowany w "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", banda przemytników już nie istnieje!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Jestem tutaj na regatę. Oto moje zaproszenie.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "Chciałbym wiedzieć, gdzie znajduje się Gubernator Generalny "+NationNameGenitive(sti(NPChar.nation))+"jest.";
        				link.l8 = "Może chcesz odpocząć, grając w grę hazardową?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Proszę wybaczyć, ale obowiązek wzywa.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Bardzo dobrze. Musimy wspólnymi siłami zwalczać tę wspólną plagę. Natychmiast wyślę statek, aby ich odebrać. Możesz być pewien, że za mniej niż tydzień będą wisieć na szubienicy. Och, i oczywiście należy się nagroda - "+FindRussianMoneyString(qty)+".";
			link.l1 = "Dziękuję, Wasza Wysokość. Zawsze przyjemność.";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Nie. Po namyśle, to nie wystarczy.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Zamieniam się w słuch, kapitanie.";
			link.l1 = "Chciałem opowiedzieć o pewnym kryminalnym spisku między oficerem waszego garnizonu a piratami... (wyjaśnia sprawę).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Dziękuję, "+GetSexPhrase("panie","tęsknić")+"! Natychmiast każę aresztować tego zdrajcę.\nMusiałeś wydać dużo pieniędzy, niestety, nasz skarbiec jest pusty...";
				link.l1 = "Nie zrobiłem tego dla pieniędzy, Wasza Ekscelencjo.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Dziękuję ci! Każę aresztować tego łajdaka.\nPomyśl tylko! Miałem zamiar nagrodzić go szablą ze złotą rękojeścią za dziesięcioletnią służbę! Uratowałeś mnie od poważnego wstydu!";
				link.l2 = "Sprawiedliwość jest nagrodą samą w sobie.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Zadanie"+GetSexPhrase("piwnica","s")+" de Maure, nie możesz tak po prostu zabić podejrzanego bez żadnych świadków! Teraz nie możemy nawet zdobyć dowodów jego zbrodni! Robię wszystko, co w mojej mocy, aby cię nie aresztowali za zabójstwo.";
				link.l3 = "Stój, to była samoobrona, Wasza Ekscelencjo.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Kapitanie, czy zdajesz sobie sprawę, co do diabła zrobiłeś?!! Przygotowywałem tę pułapkę przez ponad miesiąc! A teraz, tylko dla własnej rozrywki, zrujnowałeś spotkanie naszego patrolu z "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" a teraz przychodzisz tutaj, żeby się tym chwalić?!! Może teraz mi powiesz, jak mam wytłumaczyć wszystkie wydatki i koszty tej operacji?!";
				link.l1 = "Wasza Łaskawość, właśnie rozwiązałem Wasz problem, jeśli spojrzycie na to, powinniście byli mi płacić przez cały ten czas!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Pozwól, że spojrzę na tę mapę\nCzy ty poważnie? Ten podniszczony kawałek papieru to dowód?";
				link.l2 = "Chodźże Wasza Łaskawości, bądź rozsądny.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "No cóż, teraz wiemy, co się stało z moim patrolem. Przynajmniej przychodząc tutaj oszczędziłeś nam poszukiwań mordercy.";
				link.l3 = "Wasza Łaskawość! Po prostu odmawiasz zrozumienia sedna sprawy...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "Możesz być idiotą, ale przynajmniej jesteś pożytecznym idiotą. Proszę - weź tę mapę; znalazłem ją u pirata, którego powiesiliśmy w zeszłym tygodniu. Jeśli Bóg pozwoli, może znajdziesz jego skarb, choć uważam to za mało prawdopodobne...";
			link.l1 = "Dziękuję, to bardzo hojnie z twojej strony!";
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
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Twój zapał jest godny pochwały. Proszę, przyjmij ten miecz jako nagrodę - to najmniej, co mogę zrobić. Ach, i możesz zatrzymać mapę dla siebie. Jestem pewien, że na Karaibach jest wiele takich fałszywek.";
			link.l1 = "Dziękuję, to bardzo hojnie z twojej strony!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Być może, być może... Cóż, powiedzmy po prostu, że ten układ został postanowiony przez boską sprawiedliwość i wolą naszego Pana.";
			link.l1 = "Dziękuję, to bardzo hojnie z twojej strony!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Trzymaj język za zębami, chłopcze! Alboś oszalał, albo jesteś w zmowie z naszymi wrogami! Straże, schwytać tego głupca!";
			link.l1 = "Połóż na mnie rękę, a ją stracisz!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Teraz to niemożliwe. Jest aresztowany i czeka na proces.";
			link.l1 = "Czyżby? A o co jest podejrzewany?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Niestety, to nie podejrzenie, lecz udowodniony fakt. Mamy informacje, że napadał na statki pod pretekstem patrolowania. Konfiskował towary od kupców, a następnie sprzedawał je przemytnikom i piratom. Szkoda... pomyśleć, że kiedyś był uważany za jednego z najlepszych kapitanów, jakich miała Korona...";
			link.l1 = "A kto dostarczył ci dowody?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Jedna z jego ofiar napisała raport, w którym szczegółowo opisała incydent, włącznie z datą, nazwą napadniętego statku i ilością skonfiskowanych towarów."+"Uwierz mi, liczby są całkiem imponujące. Tego dnia patrol "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" kapitan "+pchar.GenQuest.CaptainComission.Name+" rzeczywiście był na służbie. Kapitan opisał to zdarzenie jako spotkanie z pirackim statkiem w swoim raporcie, ale wcale nie wspomniał o żadnym ładunku.";
			link.l1 = "Ale czy był w ogóle jakiś ładunek?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Nie ma co do tego wątpliwości. Poszkodowany jest bardzo znanym człowiekiem i nie zniżyłby się do oszczerstw i zniesławienia. Obecnie nasze patrole szukają skrytki kapitana."+"Jak tylko zostanie odnaleziony, kapitan może pojawić się na dworze\nJeśli udzielisz nam pomocy w tej sprawie, będziemy ci bardzo wdzięczni.";
			link.l1 = "Raczej nie. Nie znam wystarczająco dobrze okolic, by szukać skarbu. Wybacz, muszę iść.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Być może... Ile mam czasu?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Uważam, że za dwa dni patrole mogą zlokalizować skrytkę bez twojej pomocy, więc powinieneś się pospieszyć."; 
			link.l1 = "Aj, zajmę się tym. Ale będę musiał odwiedzić kapitana "+pchar.GenQuest.CaptainComission.Name+" . Czy można to zorganizować?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "To nie będzie problemem. Poinformuję komendanta fortu o twojej wizycie.";
			link.l1 = "Dziękuję. Teraz, proszę, wybacz mi.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Doskonale! Gdzie jest skarb?";
			link.l1 = "Nie mam jeszcze pojęcia. Nie wskazał mi dokładnej lokalizacji.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, co za zbieg okoliczności! Wiesz, on również 'nie wskazał' mi dokładnego miejsca...";
			link.l1 = "Pracuję nad tym.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Już nie\nStrażnicy! Zabrać więźnia z powrotem do lochów\nJesteś wolny, "+GetFullName(pchar)+".";
			link.l1 = "Ale gubernatorze...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Znakomicie! A gdzie będziemy szukać jego skarbu?";
			link.l1 = "W "+RandPhraseSimple(RandPhraseSimple("północny","zachodni"),RandPhraseSimple("wschodni","południowy"))+" koniec "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"General")+" u podnóża klifu znajduje się duża nisza, której wejście jest zasypane kamieniami. To jest kryjówka.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Dobra robota! A gdzie jest "+pchar.GenQuest.CaptainComission.Name+" sam? Powiedziano mi, że zabrałeś go z lochów fortu.";
			link.l1 = "Niestety, zginął w potyczce z przemytnikami.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "To źle... To bardzo źle, "+GetSexPhrase("panie","przegapić")+" "+GetFullName(pchar)+". Miałem zamiar wykonać na nim egzekucję publicznie, 'ku przestrodze dla innych.'"+"W każdym razie, nie uniknąłby szubienicy\nTak więc, skoro technicznie naruszyłeś prawo, nielegalnie uwalniając więźnia, ale mimo to go nie uratowałeś, nie mogę tego naprawić w raporcie. Dlatego nie dostaniesz nagrody... Ale chciałbym sam osobiście ci podziękować. Przyjmij mój dar - bardzo przydatną rzecz dla walczącego kapitana.";
			link.l1 = "Dziękuję. Zawsze chętnie służę.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Jak ty to robisz? To zajmuje co najmniej piętnaście dni, aby dotrzeć do tego miejsca, nawet żeglując z wiatrem!","Kapitanie "+GetFullName(pchar)+", twoja nieodpowiedzialność mnie zdumiewa! Dlaczego nie powiedziałeś mi o tym wcześniej?");
				link.l1 = "No cóż, nie wiem nawet, co powiedzieć...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "To wspaniała nowina! Już straciliśmy nadzieję, by ujrzeć "+pchar.GenQuest.ShipWreck.Name+"  znów żywy. Natychmiast wyślę ekipę ratunkową. Och, i proszę przyjąć tę nagrodę za twoją skuteczność i udział w ich ratowaniu.";
				link.l1 = "Dziękuję, Wasza Wysokość. Cieszę się, że mogłem pomóc. Jestem pewien, że ekspedycja dotrze tam na czas.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Och.... Cóż tu rzec? Idź i studiuj Prawo Morskie, chłopcze! Cokolwiek, zrobię co w mojej mocy, by ocalić tych ludzi.";
			link.l1 = "Wasza Łaskawość, ale zostawiłem im wystarczająco zapasów. Macie czas, zapewniam was ...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Wiem, że ty, jak by to powiedzieć... "+GetSexPhrase("są stałym bywalcem domów publicznych","lubię od czasu do czasu odwiedzać burdele")+" . A zatem postanowiłem zwrócić się do ciebie o pomoc\n"+"Wiesz, wstyd przyznać, ale byłem tam niedawno...";
			link.l1 = "A co z tym nie tak? Seks to całkiem naturalna rzecz, wiesz...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "O nie, nie kaznodzieję, nie. Chodzi o to, że pewnego razu wypiłem za dużo i zgubiłem obrączkę...";
			link.l1 = "To jest problem. Przykro mi.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Nie potrzebuję, by ktoś mi współczuł. Potrzebuję mojego pierścienia z powrotem. Jeśli uda ci się go odzyskać przed północą, będę bardzo hojny. Jeśli nie, moja żona mnie zabije.";
			link.l1 = "Rozumiem... A gdzie dokładnie mogłeś go zgubić? Czy pamiętasz coś szczególnego?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Niestety, nie. Nic a nic.";
			link.l1 = "Rozumiem. Cóż, poszukajmy tego zatem.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Wiesz, "+GetAddress_FormToNPC(NPChar)+"  Myślę, że tym razem sobie odpuszczę. Proszę, wybacz mi... ";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Doskonale! Ale pamiętaj - musisz go znaleźć przed północą.";
			link.l1 = "Pamiętam. Wrócę wkrótce.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "O? Cóż, to było naprawdę niespodziewane... No cóż, życzę ci więc powodzenia, kapitanie.";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "To mój pierścień! Uratowałeś mi życie!";
			link.l1 = "To nic takiego, sir.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Oto twoje pieniądze za dobrze wykonaną robotę! Jestem ci bardzo wdzięczny!";
			link.l1 = "Chętnie pomogę, proszę być ostrożniejszym następnym razem.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Panie zmiłuj się! Naprawdę powinienem przestać tyle pić...";
			link.l1 = "Na pewno! Oto twój pierścień.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Tak, tak, bardzo dziękuję. Jestem twoim dłużnikiem! Oto twoje pieniądze za dobrze wykonaną robotę!";
			link.l1 = "Dzięki, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Czy już wszystko omówiliśmy, prawda?";
                    link.l1 = "Zgadza się. Nie będę cię dłużej zatrzymywał.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Przykro mi, że cię niepokoję, ale nie mam teraz czasu na rozmowę z tobą. Jak powinieneś wiedzieć, nasza kolonia została zaatakowana przez "+NationNamePeople(sti(aData.nation))+"Muszę zająć się naszą obroną.";
                    link.l1 = "Cóż, chciałem tylko zaoferować swą pomoc w obronie fortu.";
                    link.l1.go = "siege_task";
                    link.l2 = "W takim razie nie będę cię dłużej zatrzymywał.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Och, to ty, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", Cieszę się, że cię widzę. Dobre wieści - udało nam się odeprzeć "+NationNameSK(sti(aData.nation))+" najeźdźcy. Ty również przyczyniłeś się do tego, a oto twoja nagroda - "+(sti(aData.iSquadronPower)*1500)+" sztuk srebra. Proszę bardzo.";
                    link.l1 = "Dziękuję, "+GetAddress_FormToNPC(NPChar)+"przyjemność robić z tobą interesy!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Więc jaki był powód, dla którego przyszedłeś tutaj i odciągnąłeś mnie od ważnych spraw państwowych?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Chciałem pracować dla "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dane")+" Spotkałem kilku piratów. Wszystko "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" są obecnie na pokładzie. Chcę ich przekazać władzom.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Zamierzałem porozmawiać z tobą o jednej ważnej sprawie.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Jest kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Acc"))+" nazwany "+pchar.GenQuest.CaptainComission.Name+", jak mogę się z nim spotkać?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Dawny kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"zgodził się ujawnić swój skarb władzom.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Dawny kapitan dowodzący patrolem  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ujawnił mi swój skarb.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Spotkałem kapitana "+pchar.GenQuest.ShipWreck.Name+" i jego marynarze, których wyrzucił na brzeg pirat "+pchar.GenQuest.ShipWreck.BadName+". "+"Niestety, miałem już za dużo ludzi na moim statku i dlatego nie mogłem ich zabrać na pokład. Ale zostawiłem im jedzenie i broń. Jeśli statek ratunkowy ich nie podejmie w ciągu "+(30 - iDay)+" dni, potem nie wiem, czy znajdę ich jeszcze żywymi, czy nie.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+"Spotkałem żeglarzy z rozbitego statku ofiary '"+pchar.GenQuest.ShipWreck.ShipTypeName+" z ich kapitanem. "+"Niestety, miałem już zbyt wielu ludzi na swoim statku i dlatego nie mogłem ich zabrać na pokład. Ale zostawiłem im jedzenie i broń. Jeśli statek ratunkowy ich nie odbierze w ciągu "+(30 - iDay)+" dni, to nie wiem, czy znajdę ich jeszcze żywych, czy nie.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Mam wiadomość z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Generał")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milordzie, odnalazłem bandę przemytników, których herszt został niedawno schwytany przez straże. Teraz planują jego ucieczkę. Ich statek '"+PChar.GenQuest.JusticeOnSale.ShipName+"'  zacumowany przy "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"General")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Chce przekazać pojmanego kapitana władzom.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Przybyłem na regaty. Oto moje zaproszenie.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Może chciałbyś zrobić sobie przerwę?";
        			link.l5.go = "Play_Game";
        			link.l10 = "To była tylko kurtuazyjna wizyta, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Czyż nie omówiliśmy już wszystkiego?";
                    link.l1 = "Oczywiście. Nie będę cię dłużej zatrzymywał.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Przykro mi, że cię martwię, ale nie mam teraz czasu z tobą rozmawiać. Jak zapewne wiesz, nasza kolonia została zaatakowana przez "+NationNamePeople(sti(aData.nation))+" Muszę zająć się naszymi obronami.";
                    link.l1 = "Cóż, chciałem tylko zaoferować swoją pomoc w obronie fortu.";
                    link.l1.go = "siege_task";
                    link.l2 = "Zatem nie będę cię dłużej zatrzymywać.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "O, to ty, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", cieszę się, że cię widzę. Dobre wieści - udało nam się odeprzeć "+NationNameSK(sti(aData.nation))+" najeźdźców. Ty także odegrałeś swoją rolę w tym, a oto twoja nagroda - "+(sti(aData.iSquadronPower)*1500)+" pesos. Proszę bardzo.";
                    link.l1 = "Dziękuję, "+GetAddress_FormToNPC(NPChar)+"przyjemność robić z tobą interesy!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Co cię do mnie sprowadza? Myślałem, że załatwiłeś wszystkie swoje sprawy z twoim... protektorem. Ale mów, zawsze chętnie cię wysłucham.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Chciałem pracować dla "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+"Spotkałem kilku piratów. Wszystko "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" są na pokładzie w tej chwili. Chcę ich oddać władzom.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Miałem zamiar porozmawiać z tobą o jednej ważnej sprawie.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Jest kapitan na czele patrolu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" nazwany "+pchar.GenQuest.CaptainComission.Name+", jak mogę się z nim spotkać?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Dawny kapitan dowodzący patrolem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" zgodził się ujawnić swój skarb władzom.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Dawny kapitan dowodzący patrolem  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ujawnił mi swoją skrytkę.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+"Spotkałem kapitana "+pchar.GenQuest.ShipWreck.Name+" i jego marynarze, których wyrzucił na brzeg pirat "+pchar.GenQuest.ShipWreck.BadName+". "+"Niestety, miałem już zbyt wielu ludzi na moim statku i dlatego nie mogłem ich zabrać na pokład. Ale zostawiłem im jedzenie i broń. Jeśli statek ratunkowy ich nie zabierze w ciągu "+(30 - iDay)+" dni, potem nie wiem, czy znajdę ich żywych, czy nie.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Spotkałem marynarzy z ofiary wraku statku '"+pchar.GenQuest.ShipWreck.ShipTypeName+" z ich kapitanem. "+"Niestety, miałem już zbyt wielu ludzi na moim statku i dlatego nie mogłem ich zabrać na pokład. Ale zostawiłem im jedzenie i broń. Jeśli statek ratunkowy ich nie zabierze w ciągu "+(30 - iDay)+" dni, potem nie wiem, czy znajdę ich jeszcze żywych, czy nie.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Mam wiadomość z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Generale")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milordzie, zlokalizowałem bandę przemytników, których herszt został niedawno złapany przez straże. Teraz planują jego ucieczkę. Ich statek '"+PChar.GenQuest.JusticeOnSale.ShipName+"' cumuje się przy "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"General")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Muszę przekazać pojmanego kapitana władzom.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Jestem tutaj na regaty. Oto moje zaproszenie.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Może chciałbyś zrobić sobie przerwę?";
        			link.l5.go = "Play_Game";
        			link.l10 = "To była tylko wizyta kurtuazyjna, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Nie teraz! Mamy inspekcję, don de Alamida jest w mieście. Och, co roku to samo, czym sobie na to zasłużyłem...";
				link.l1 = "Jak powiadasz. Nie będę cię rozpraszać.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, a jakie gry preferujesz?";
			link.l1 = "Chcesz zagrać w karty o poważne pieniądze?";
			link.l1.go = "Card_Game";
   			link.l2 = "Co powiesz na rzut kostkami w poker-jokera?";
			link.l2.go = "Dice_Game";
			link.l10 = "Proszę mi wybaczyć, ale obowiązki wzywają.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Przepraszam, monsignorze, ale teraz nie mam na to czasu. Może następnym razem."; // Jason НСО
                else dialog.text = "Nie hazarduję się z piratami!";
    			link.l1 = "Jak sobie życzysz.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Dlaczego nie! Relaks jest dobry dla serca, ale nie dla sakiewki...";
	    			link.l1 = "Doskonale.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Jakie są zasady naszej gry?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Nie, na dzisiaj koniec. Mam sprawy do załatwienia.";
	    			link.l1 = "Jak sobie życzysz.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "No to zaczynajmy!";
			link.l1.go = "Cards_begin";
			link.l3 = "Nie, to nie dla mnie...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Najpierw uzgodnijmy zakład.";
			link.l1 = "Zagrajmy za 1000 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Zagrajmy za 5000 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Chyba muszę iść.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grał w karty.";
                link.l1 = "To wszystko kłamstwa!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Żartujesz sobie, "+GetAddress_Form(NPChar)+" ? Nie masz pieniędzy!";
                link.l1 = "Zdarza się.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "To tyle! Skończyłem z kartami - zanim nazwą mnie rozrzutnikiem i zmuszą do opuszczenia mojego stanowiska.";
                link.l1 = "Szkoda.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy za 1000 pesos.";
			link.l1 = "Zacznijmy!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grał w karty.";
                link.l1 = "To wszystko kłamstwa! No cóż, cokolwiek.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Mówią, że jesteś bardzo dobrym graczem. Nie będę z tobą grał o wysokie stawki.";
                link.l1 = "Może obniżymy stawkę?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Przykro mi, ale muszę iść.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Żartujesz sobie, "+GetAddress_Form(npchar)+"? Nie masz 15000 sztuk złota!";
                link.l1 = "Podniosę ich!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nie, te zakłady opróżnią skarbiec miasta.";
                link.l1 = "Jak sobie życzysz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy o 5000 sztuk osiem.";
			link.l1 = "Zaczynajmy!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Proszę o wybaczenie, monsignorze, ale nie mam teraz na to czasu. Może następnym razem."; // Jason НСО
                else dialog.text = "Nie będę się hazardować z piratami!";
    			link.l1 = "Jak sobie życzysz.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Dlaczego nie! Relaks jest dobry dla serca... ale nie dla sakwy...";
	    			link.l1 = "Doskonale.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Jakie są zasady naszej gry?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Nie, na dziś skończyłem. Mam do załatwienia pewne sprawy.";
	    			link.l1 = "Jak sobie życzysz.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "No to zaczynajmy!";
			link.l1.go = "Dice_begin";
			link.l3 = "Nie, to nie dla mnie...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Najpierw zgódźmy się co do zakładu.";
			link.l1 = "Zagrajmy za 500 sztuk złota za kość.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Zagrajmy za 2000 sztuk srebra za kostkę.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Chyba muszę iść.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grał w hazard.";
                link.l1 = "To wszystko kłamstwa! No cóż, nieważne.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Żartujesz sobie, "+GetAddress_Form(NPChar)+"  ? Nie masz pieniędzy!";
                link.l1 = "Zdarza się.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "To koniec! Zrywam z hazardem - zanim nazwą mnie rozrzutnikiem i zmuszą do opuszczenia mojego stanowiska...";
                link.l1 = "Szkoda.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy o 500 sztuk osiem.";
			link.l1 = "Zaczynajmy!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grał w hazard.";
                link.l1 = "Wszystko to kłamstwa! Cóż, cokolwiek.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Mówią, że jesteś bardzo dobrym graczem. Nie będę grał z tobą o wysokie stawki.";
                link.l1 = "Może obniżymy stawkę?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Przykro mi, ale muszę iść.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Żartujesz sobie, "+GetAddress_Form(NPChar)+"? Nie masz 15000 sztuk ośmiu!";
                link.l1 = "Podniosę je!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nie, te zakłady z pewnością opróżnią miejską kasę.";
                link.l1 = "Jak sobie życzysz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy za 2000 sztuk ośmiu za kość.";
			link.l1 = "Zacznijmy!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "W takim razie proszę cię, abyś opuścił mój gabinet i przestał odciągać mnie od pracy";
			link.l1 = "Tak, tak, oczywiście. Przepraszam, że cię niepokoję.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "To błąd. Powiadomcie deweloperów o tym.";
        	link.l1 = "Dzięki, to wspaniała gra!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Nie teraz! Mamy inspekcję, don de Alamida jest w mieście. Och, co roku to samo, czym sobie na to zasłużyłem...";
				link.l1 = "Jak powiadasz. Nie będę cię rozpraszał.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Z tego, co widzę, masz już misję zleconą przez gubernatora "+XI_ConvertString("Kolonia"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+"Zakończ robotę, którą już masz, a wtedy porozmawiamy.","Hmm, czyż to nie ty byłeś w "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" gdzie przyjąłeś rozkazy od lokalnego gubernatora? Tak, to prawda. Najpierw ukończ tę misję.");
					link.l1 = RandPhraseSimple("Widzę...","Zrozumiano..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("Misja odnalezienia bandyty "+GetFullName(arName)+" została ci wydana. Teraz ją wypełnij!","Masz już misję zlokalizowania bandyty o imieniu "+GetFullName(arName)+". Czekam na wyniki!","Podczas gdy marnujesz swój czas w mojej rezydencji, "+GetFullName(arName)+" napada na naszych kolonistów! Do roboty!");
							link.l1 = RandPhraseSimple("W porządku, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Twój czas na odnalezienie i wyeliminowanie tego bandyty minął. I jakie raporty do mnie docierają, jak myślisz? A ja ci powiem - "+GetFullName(arName)+" wciąż żyje i ma się dobrze! Teraz się wytłumacz, "+GetAddress_Form(NPChar)+".","Czas dany ci na wyeliminowanie tego łotra o imieniu "+GetFullName(arName)+", skończył się. Mimo to, słyszę, że nie poczyniono żadnych postępów. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twojej pracy w wyznaczonym czasie, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("I jak? Udało ci się wyeliminować wspomnianego bandytę? "+GetFullName(arName)+" wreszcie nie żyje?","Powiedz mi tylko jedno - czy "+GetFullName(arName)+" jest martwy czy żywy?");
							link.l1 = "Niestety, wciąż żywy, "+GetAddress_FormToNPC(NPChar)+". Udało mi się go wytropić, ale nie dorównałem mu i musiałem się wycofać. Ten bandyta to naprawdę twardy drań. Przykro mi.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("I jak? Udało ci się wyeliminować wspomnianego bandytę? "+GetFullName(arName)+"w końcu nie żyje?","Powiedz mi tylko jedną rzecz - czy "+GetFullName(arName)+" jest żywy czy martwy?");
							link.l1 = "Jest martwy, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Misja przechwycenia statku kurierskiego została już ci przydzielona. Teraz ją wykonaj!","Masz już zadanie schwytać statek kuriera! Czekam na wyniki!","Podczas gdy marnujesz swój czas w mojej rezydencji, dokumenty, których potrzebuję, wpadają prosto w ręce naszych wrogów! Do roboty!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem na tropie, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Czas, który miałeś na zlokalizowanie i przechwycenie tego statku kurierskiego, minął. A jakie raporty do mnie docierają, jak sądzisz? Powiem ci - dokumenty, na które czekałem, wpadły prosto w ręce naszych wrogów! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy wyznaczone na przechwycenie dokumentów z okrętu kuriera minęły. Wciąż brak jakiegokolwiek postępu. Co to ma znaczyć?");
							link.l1 = "Nie byłem w stanie wykonać zadania na czas, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("I jak? Udało ci się zdobyć dokumenty?","Powiedz mi tylko jedno - czy udało ci się zabezpieczyć korespondencję?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Zlokalizowałem statek, ale dokumenty mi umknęły.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("I jak? Udało ci się zdobyć dokumenty?","Powiedz mi tylko jedno - udało ci się zabezpieczyć korespondencję?");
							link.l1 = "Tak, "+GetAddress_FormToNPC(NPChar)+". Mam je. Proszę.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Misja zniszczenia transportu wojskowego została już ci przydzielona. Teraz ją wypełnij!","Masz już misję zniszczenia transportu wojskowego! Czekam na wyniki!","Podczas gdy marnujesz czas w mojej rezydencji, proch i amunicja są dostarczane prosto do dział wroga! Do roboty!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Minął czas dany ci na zlokalizowanie i zniszczenie tego transportu wojskowego. A jakie raporty do mnie docierają, jak myślisz? I powiem ci - konwój wroga pomyślnie dotarł do celu! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy na zniszczenie wrogiego transportu wojskowego minęły. Wciąż nie poczyniono żadnych postępów. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twego zadania w wyznaczonym czasie, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("A więc? Udało ci się zniszczyć transport wroga?","Powiedz mi tylko jedno - czy ten wrogi ekwipunek spoczywa na dnie morskim?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Zlokalizowałem konwój, ale nie udało mi się zatopić wymaganego statku.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("A więc? Udało ci się zniszczyć ten wrogi transport?","Powiedz mi tylko jedno - czy arsenał wroga spoczywa na dnie morza?");
							link.l1 = "Tak, "+GetAddress_FormToNPC(NPChar)+". Nasz wróg nie otrzyma tego prochu i amunicji.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Misja eliminacji pirata została już ci wydana. Teraz ją wypełnij!","Masz już misję zniszczenia pirackiego statku! Czekam na wyniki!","Podczas gdy marnujesz czas w mym rezydencji, ten plugawy pirat wyłudza wszystko z kolejnej ofiary! Do roboty!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Czas, który ci dano na zlokalizowanie i wyeliminowanie pirata, minął. A jakie raporty otrzymuję, jak myślisz? A powiem ci - ten plugawy pirat wciąż napada na nasze statki! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy, które ci dano na zniszczenie pirackiego statku, minęły. Wciąż nie zrobiono żadnych postępów. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twojej pracy na czas, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("A więc? Udało ci się zniszczyć piracki statek?","Powiedz mi tylko jedno - czy ten plugawy pirat wreszcie spoczywa na dnie morza?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Udało mi się wytropić tego łotra, ale nie zdołałem zatopić jego statku.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("A więc? Udało ci się zniszczyć piracki statek?","Powiedz mi tylko jedno - czy ten plugawy pirat wreszcie spoczywa na dnie morza?");
							link.l1 = "Tak, "+GetAddress_FormToNPC(NPChar)+". Ten łotr nie będzie już niepokoił naszych statków handlowych.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("Zadanie odnalezienia przestępcy już zostało ci przydzielone. Teraz je wykonaj!","Masz już misję poszukiwania przestępcy! Czekam na wyniki!","Podczas gdy marnujesz czas w mojej rezydencji, ten plugawy łotr wciąż żegluje po okolicy! Natychmiast przystąp do misji, która została ci powierzona!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Czas, który miałeś na odnalezienie tego łotra, minął. A jakie raporty otrzymuję, jak myślisz? I powiem ci - on z powodzeniem dotarł do celu, a potem zniknął jak kamfora! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy, jakie ci dano na znalezienie przestępcy, dobiegły końca. Wciąż nie poczyniono żadnych postępów. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twojego zadania w wyznaczonym czasie, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Zatem, co powiesz? Czy pojmałeś złoczyńcę?","Powiedz mi tylko jedno - czy ten plugawy łotr jest w twoim ładowni, zakneblowany i skute kajdany?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Nie udało mi się schwytać łotra. Poszedł na dno razem ze statkiem, na którym był.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Więc, co powiesz? Czy pojmałeś łotra?","Powiedz mi tylko jedno - czy ten plugawy łotr siedzi w twojej ładowni, zakneblowany i skute łańcuchami?");
							link.l1 = "Tak, "+GetAddress_FormToNPC(NPChar)+". Proszę wysłać swoich żołnierzy na nabrzeże, a ja go wam przekażę.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("Misja wyśledzenia przemytników została już ci przydzielona. Teraz ją wykonaj!","Już masz misję, aby wytropić przemytników! Czekam na wyniki!","Podczas gdy marnujesz czas w mojej rezydencji, ci przemytnicy szykują się do kolejnego interesu! Natychmiast przystąp do misji, która została ci powierzona!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Czas, który ci dano na zlokalizowanie przemytników, minął. A jakie raporty otrzymuję, jak myślisz? Powiem ci - sprzedali wszystkie swoje towary z radością! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy, które ci dano na znalezienie przemytników, minęły. Wciąż nie poczyniono żadnych postępów. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twego zadania na czas, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Więc, co powiesz? Czy poradziłeś sobie z przemytnikami?","Powiedz mi tylko jedno - czy zepsułeś interes tych przemytników?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Nie udało mi się udaremnić planów tych łotrów.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Więc, co powiesz? Czy rozprawiłeś się z przemytnikami?","Powiedz mi tylko jedno - czy zrujnowałeś umowę tych przemytników?");
							link.l1 = "Tak, "+GetAddress_FormToNPC(NPChar)+". Dogoniłem ich i zlikwidowałem statki obu stron, zarówno kupca, jak i sprzedawcy.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("Misja poszukiwania dezertera została już tobie zlecona. Teraz ją wykonaj!","Już masz misję, by wytropić dezertera! Czekam na wyniki!","Podczas gdy marnujesz czas w mojej rezydencji, ten dezerter może zdradzać nasze tajemnice państwowe! Natychmiast przystąp do misji, która została ci powierzona!");
							link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Jestem tym zajęty, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Czas, który ci dano na odnalezienie dezertera, minął. A jakie raporty otrzymuję, jak myślisz? I powiem ci - żadnych rezultatów, zupełnie żadnych! Teraz racz się wytłumaczyć, "+GetAddress_Form(NPChar)+".","Wszystkie terminy, które ci dano na znalezienie dezertera, minęły. Wciąż nie dokonano żadnego postępu. Co się dzieje?");
							link.l1 = "Nie byłem w stanie wykonać twojego zlecenia na czas, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Więc, co powiesz? Czy pojmałeś dezertera?","Powiedz mi tylko jedno - czy ten dezerter jest w twoim ładowni, zakneblowany i zakuty w kajdany?");
							link.l1 = "Niestety, nie, "+GetAddress_FormToNPC(NPChar)+". Nie udało mi się pojmać tego łajdaka. Znalazłem jego ślad w osadzie "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", ale tuż przed moim przybyciem popłynął na południe na statku pirackim. Myślę, że teraz jest z tymi dżentelmenami fortuny.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("No cóż... Oto nasz "+pchar.GenQuest.FindFugitive.Name+"... Świetna robota, kapitanie! Czy miałeś trudności z poszukiwaniami?","O, jakież to mamy gości! Witaj, "+pchar.GenQuest.FindFugitive.Name+" ! Świetna robota, kapitanie! Czy włożyłeś wiele wysiłku w swoje poszukiwania?");
							link.l1 = "Jakby to rzec, "+GetAddress_FormToNPC(NPChar)+". Cokolwiek to było - twoja misja została wypełniona.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("Czas dany ci na dostarczenie listu minął. I wnioskuję, że poniosłeś porażkę.","Czas się skończył. Wciąż nie osiągnięto żadnego postępu. Co się dzieje?");
								link.l1 = "Nie byłem w stanie wykonać zlecenia, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Misja dostarczenia mi listu została już ci zlecona. Teraz ją wykonaj!","Masz już misję dostarczenia listu prosto do mnie! Czekam na wyniki, potrzebuję tego listu jak najszybciej!","Podczas gdy marnujesz swój czas w mojej rezydencji, informacje, których tak bardzo potrzebuję, wciąż są w rękach osoby, która ma mi je przesłać! Natychmiast przystąp do misji, która została ci powierzona!");
								link.l1 = RandPhraseSimple("Dobrze, "+GetAddress_FormToNPC(NPChar)+".","Zaraz się za to zabiorę, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Czy dostarczyłeś list, którego oczekuję?","Powiedz mi teraz - masz to?!");
							link.l1 = "Tak, mam. Jak się umawialiśmy - dostarczone osobiście Tobie.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Niestety, dzisiaj nie mam dla ciebie pracy. Ostatnia została wykonana przez "+GetFullName(&Characters[i])+" Przyjdź jutro, może coś się pojawi.";
				link.l1 = "O, cholera! Żadnego szczęścia...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "Jesteś w samą porę, kapitanie. Mam do rozwiązania pilny problem związany z przemytem towarów do naszej kolonii. Przypuszczam, że twój statek jest gotowy do żeglugi i walki.";
					link.l1 = "Mój statek zawsze jest gotowy do żeglugi i bitwy. Proszę, opowiedz mi więcej o nadchodzącej misji, wasza łaskawość.";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("Na razie nie mam dla ciebie pracy. Przyjdź jutro, przypuszczam...","Niestety, nie mam dziś dla ciebie pracy. Proszę, sprawdź za dzień lub dwa.","Dzisiaj nie mam nic, co mógłbym ci zaproponować. Będę zadowolony, gdy zobaczę cię innym razem.");
					link.l1 = "Rozumiem, "+GetAddress_FormToNPC(NPChar)+".";
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
					if (sTemp == "none")
						i = 1 + hrand(6);
					else
						i = hrand(7);
					switch (i)
					{
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 0:
							pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = sTemp; //враждебная колония
                            sTemp = ", which is on " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "Mam dla ciebie misję, która wiąże się z poważnym ryzykiem. Musisz się zakraść do "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", spotkaj się tam z pewną osobą, a następnie przekaż mi, cokolwiek ci powie.";
							link.l1 = "Hmm, nie sądzę, że w "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Będę mile widzianym gościem...";
							link.l1.go = "Intelligence";
						break;
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 1:
							pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = "Właśnie teraz mam dla ciebie misję. W dżungli niedaleko "+XI_ConvertString("Colony"+npchar.city+"Gen")+" banda rabusiów się pojawiła, i wiem, że herszt nazywa się "+GetFullName(arName)+"Zlokalizuj i wyeliminuj tę bandę oprychów.";
							link.l1 = "Czy jestem w jakiś sposób ograniczony w kwestii warunków?";
							link.l1.go = "DestroyGang";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Tak, mam dla ciebie misję. Aby ją wypełnić, musisz wykazać się szybkością i pewnymi umiejętnościami w walce morskiej. Gotów pokazać swoją wartość?";
							link.l1 = "Wasza Wysokość, czy możesz ujawnić więcej szczegółów dotyczących misji?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Tak, mam dla ciebie misję. Aby ją wykonać, musisz wykazać się niezwykłą odwagą i umiejętnościami w walce morskiej. Czy jesteś gotów pokazać swoją wartość?";
							link.l1 = "Wasza Łaskawość, czy możesz ujawnić więcej szczegółów na temat nadchodzącej misji?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Tak, mam dla ciebie ważną misję. Aby ją wypełnić, musisz użyć wszystkich swoich umiejętności. Dotyczy to piratów...";
							link.l1 = "Piraci? Czy możesz mi powiedzieć w większych szczegółach, czego się ode mnie oczekuje?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "Jesteś w samą porę, sir. Mam pilną misję, która doskonale ci odpowiada. Chodzi o odnalezienie i pojmanie pewnej osoby...";
							link.l1 = "Polowanie na człowieka? Czy możesz powiedzieć mi więcej szczegółów, czego ode mnie oczekujesz?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "Przybywasz w samą porę, kapitanie. Muszę zająć się pilnym problemem związanym z przemytem towarów do naszej kolonii. Przypuszczam, że twój statek jest w stanie żeglugi i gotów do bitwy?";
							link.l1 = "Moja łajba zawsze jest gotowa do bitwy. Proszę, powiedz mi więcej o nadchodzącej misji, wasza łaskawość.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "Mam dla ciebie misję, która wymaga odwiedzenia kilku miejsc na Karaibach. Jesteś gotowy na długą podróż?";
							link.l1 = "Tak, moi ludzie i ja jesteśmy gotowi do wyruszenia od razu. Co dokładnie będę musiał zrobić?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Dziś nie mogę zaoferować ci żadnej pracy.","Dziś nie ma już dla Ciebie żadnej pracy.","Nie mam już żadnych zadań na dzisiaj, przepraszam. Przyjdź jutro, a zobaczymy...");
				link.l1 = RandPhraseSimple("Szkoda...","Ach, co za szkoda, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Kogo chciałbyś wydać?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Nikogo.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "No więc to jest kapitan " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " Jestem gotów zapłacić okup za mojego rodaka w wysokości  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " Mogę dać " + FindRussianMoneyString(qty) + "  dla tego łachudry. A potem od razu zabijemy łajdaka.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "dla tego człowieka i ani peso więcej.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Umowa stoi. Jest cały twój, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Nie. To nie wystarczy.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "To dobrze.";
			link.l1 = "Wszystkiego najlepszego.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh! Co za skandal, de Maure? Odkąd to Francuzi atakują własnych rodaków?!";
                Link.l1 = "Na rozkaz gubernatora generalnego Francois Longvillier de Poincy, ty, monsieur Levasseur, zostajesz usunięty z urzędu gubernatora Tortugi i skazany na śmierć! A ja jestem tym, kto wykona ten wyrok!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Już wszystko zabrałeś. Czego jeszcze potrzebujesz?";
                Link.l1 = "Tak, racja, złe miasto.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Bezprecedensowa bezczelność! Wkrótce przybędą posiłki z fortu, a ty zapłacisz za to!";
                Link.l2 = "Nie zamierzam tu siedzieć, aż oni przybędą. Po prostu zapłać mi, a my opuścimy to miasto.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Tym razem wygrałeś, ale wiedz, że eskadra naszych łowców piratów będzie cię ścigać i wyrwie każdy peso z twojego plugawego pirackiego ciała!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Cisza! To miasto należy do mnie od teraz; co do waszych łowców piratów - wyślę ich prosto do skrytki Davy'ego Jones'a. Hej chłopaki, złapcie tego świniaka i wsadźcie go za kratki.";
	    				}
	    				else
	    				{
	    					Link.l1 = "To miasto teraz należy do mnie. Chłopcy, eskortujcie byłego gubernatora do jego nowych 'kwater', heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Wzmocnienia z fortu? Po prostu zapłać mi ładny okup, a opuścimy twoje miasto.";
				}
				else
				{
	            	Link.l2 = "Eskadra łowców piratów? Hmm... Po prostu mi zapłać, a opuścimy miasto.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Bezprecedensowa bezczelność! Jak śmiesz atakować kolonię należącą do "+NationNameGenitive(sti(NPChar.nation))+"? ! Słono zapłacisz za krew, którą przelałeś, i za szkody, które wyrządziłeś naszemu państwu.";
	                Link.l1 = "Od tej chwili ta kolonia należy do mnie. Ktokolwiek zdecyduje się kwestionować moją władzę, niech idzie prosto do diabła.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Spuść z tonu. Działam w imieniu "+NationNameGenitive(sti(PChar.nation))+". Od tego momentu ta kolonia należy do "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Piękne miasto, które tu macie. Byłaby to prawdziwa tragedia, gdyby zostało spalone na popiół, a jego gubernator zawisł na rynku. Powinniśmy omówić wysokość okupu, który jesteś gotowi zapłacić, aby zapobiec tej tragedii.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Do diabła z tym papistowskim łajdakiem! Zajmę się nim... a z tobą koniec, łotrze! Nie wyjdziesz stąd żywy - osobiście cię zakończę!";
			Link.l1 = "Oszczędź mi swoich kazań, heretyku. Kiedy wyślę twoją hugenocką duszę do piekła, przekaż Lucyferowi i Janowi Kalwinowi moje najlepsze życzenia. Do broni!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Tym razem wygrałeś, ale wiedz, że nasza eskadra wkrótce przybędzie i nic z ciebie nie zostawią!";
			Link.l1 = "Zamknij gębę. To miasto należy do mnie od teraz; co do twojego szwadronu - wyślę go prosto do piekła. Chłopcy, eskortujcie byłego gubernatora do jego nowej „kwatery”, heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Czego jeszcze ode mnie potrzebujesz?";
            Link.l1 = "Po prostu sprawdzam, czy czegoś nie przegapiłem...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Nie mam innego wyboru, jak tylko zgodzić się na twoje warunki. Weź swoje przeklęte pieniądze i natychmiast opuść naszą kolonię.";
            Link.l1 = "Z przyjemnością robię z tobą interesy.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Dobrze, przedstaw swoje warunki...";
            Link.l1 = "Tak, vae victis! Zaczynaj liczyć swoje pieniądze.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Dobrze, poddajemy się twojej łasce.";
			Link.l1 = "Radziłbym ci opuścić miasto jak najszybciej - nadchodzące zmiany mogą być dość niekorzystne dla twojego zdrowia. Żegnaj.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "Czego jeszcze ode mnie potrzebujesz, łotrze?";
            Link.l3 = "Jak Waszej Ekscelencji podoba się nowy pokój? Wystarczająco przestronny? No cóż, teraz muszę iść!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Osiedlić się? A jak sobie to wyobrażasz?";
            link.l1 = "Myślę, że suma "+iTotalTemp*6000+" pesos mogą mnie jeszcze ocalić, prawda?";
			link.l1.go = "arestFree_2";
			link.l2 = "Nie. I czas, bym odszedł. Z wyrazami szacunku.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Przypuszczam, że moglibyśmy rozwiązać nasz incydent w taki sposób. Jeszcze nie posunąłeś się tak daleko, by sytuacja stała się nieodwracalna.";
    		    link.l1 = "Doskonale. Bardzo się cieszę. Proszę, przyjmij moją darowiznę.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Czy próbujesz mnie przekupić? O nie! Twoje nikczemne czyny można odkupić tylko w jeden sposób... Straż! Aresztować "+GetSexPhrase("go","ją")+", w kajdanany!";
    		    link.l1 = "Poczekaj!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Oczywiście, nadszedł czas. Odprowadzimy cię. Strażnicy! Aresztować "+GetSexPhrase("go","ją")+"!";
		    link.l1 = "Nie ma mowy!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Miałeś wystarczająco dużo czasu na przemyślenie! Straże!";
			link.l1 = "Nie dostaniesz mnie łatwo!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Oczywiście. Aby wykonać tę misję, daję ci "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", a twoja nagroda w przypadku sukcesu będzie wynosiła "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Tak, przyjmuję to zadanie.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie daruję.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Zaraz, właśnie zapomniałem o wczorajszym raporcie. Chodzi o to, że ta banda już opuściła naszą wyspę. Więc muszę odwołać misję.";
				link.l1 = "Widzę. Szkoda.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Cóż, świetnie! Będę czekał na ciebie w mojej rezydencji wraz z twoimi raportami.";
				link.l1 = "Nie każę ci długo czekać, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Dziś nie mogę zaoferować ci żadnej pracy.","Dziś nie ma dla ciebie więcej zadań.","Na dziś nie ma już żadnej roboty, przykro mi. Przyjdź jutro, a zobaczymy...");
				link.l1 = RandPhraseSimple("Szkoda...","Ach, jaka szkoda, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6)+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "Oczywiście. Będziesz musiał zlokalizować statek kurierski "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" o imieniu '"+pchar.GenQuest.TakePostcureer.ShipName+", abordażuj go i przynieś mi dokumenty, które powinieneś znaleźć w kajucie kapitana. Ten statek będzie przepływał w pobliżu "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" mniej więcej w "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Dobrze, przyjmuję tę misję. A jakie dokumenty mam szukać?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie odpuszczę.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Poczta. Są tam bardzo ważne dokumenty dla mnie. Ale nie musisz szukać wśród papierów, po prostu przynieś mi cały pakiet. Zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nZatem będę czekał na ciebie i wynik twojej pracy w mojej rezydencji.";
			link.l1 = "Nie będę cię długo trzymał w niepewności, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Dziś nie mogę ci zaoferować żadnej pracy.","Dziś nie ma już dla ciebie pracy.","Na dziś nie ma już pracy, wybacz. Wróć jutro, zobaczymy...");
				link.l1 = RandPhraseSimple("Szkoda...","Ach, co za szkoda, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6)+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "Oczywiście. Będziesz musiał zlokalizować wojskowy transport "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", z prochem i amunicją na pokładzie; nazwa statku to '"+pchar.GenQuest.TakeArsenalship.ShipName+"', znajdź i zniszcz. Osłabimy naszego wroga, robiąc to\nTransport popłynie z eskortą do kolonii "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", i będzie mniej więcej w "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", więc powinieneś się pospieszyć.";
			link.l1 = "Dobrze, przyjmuję. Czy muszę zatopić okręt arsenału, czy powinienem spróbować go zdobyć?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie odpuszczę.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Nie obchodzi mnie to, to zależy od ciebie. Ważne jest, aby ten ładunek nie dotarł do miejsca przeznaczenia. Jeśli ci się uda, zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Nie będę cię dłużej zatrzymywał, kapitanie.";
			link.l1 = "Nie każę ci długo czekać, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6)+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "Oczywiście. Naprawdę doprowadza mnie do szału działalność jednego kapitana piratów, którego imię to "+pchar.GenQuest.TakePirateship.Name+". Ten łotr przyzwyczaił się do napadania na nasze statki handlowe, co ogromnie szkodzi handlowi między koloniami. Teraz jest idealny moment, by pozbyć się tego drania, ponieważ właśnie dowiedziałem się, gdzie się obecnie ukrywa. Jesteś gotów wysłać tego bękarta na Sąd Boży?";
			link.l1 = "Byłbym zaszczycony! Gdzie mogę znaleźć tego pirata?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie odpuszczę.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "W najbliższej "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" jego statek o nazwie '"+pchar.GenQuest.TakePirateship.ShipName+"będzie żeglował wzdłuż brzegów niedaleko "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Znajdź go i zabij. Wyślij na pożarcie rybom razem z jego statkiem, przejmij statek - nie obchodzi mnie to. Zależy mi tylko na tym, żeby ten przeklęty pirat przestał kalać nasze morze swoją obecnością\nZa to zadanie jestem gotów ci zapłacić "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+"Nie trać czasu, kapitanie: ten łotr nie będzie na ciebie długo czekał w "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"Idź, i niech ci Bóg pomoże!";
			link.l1 = "Już podnosze kotwicę, "+GetAddress_FormToNPC(NPChar)+"Nie będziesz długo czekać.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Dziś nie mogę zaoferować Ci żadnej pracy.","Dziś nie ma już dla ciebie zadań.","Na dzisiaj nie mam już dla ciebie zadań, przepraszam. Przyjdź jutro, a zobaczymy...");
				link.l1 = RandPhraseSimple("Szkoda...","Ach, co za szkoda, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6)+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Oczywiście. Mówię o łajdaku imieniem "+pchar.GenQuest.TakePassenger.Name+". "+sText+" Szukałem go od dłuższego czasu i teraz wreszcie zdobyłem wiarygodne informacje, gdzie można go znaleźć. Potrzebuję, abyś przyprowadził mi tego człowieka, za wszelką cenę żywego. Chcę go powiesić publicznie na naszym rynku. Czy jesteś gotów podjąć się tej misji?";
			link.l1 = "Jestem gotów, "+GetAddress_FormToNPC(NPChar)+" Gdzie mogę znaleźć tego łajdaka?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... Nie, myślę, że zrezygnuję.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Po prostu w "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", on, jako pasażer na statku o nazwie '"+pchar.GenQuest.TakePassenger.ShipName+"', wypłynie z "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" i idź do "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+".  Masz "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" aby znaleźć ten statek na określonym odcinku trasy, wejść na pokład i pojmać tego łotra. Jeśli wykonasz to polecenie, zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+"Powodzenia, kapitanie!";
			link.l1 = "Nie będę tracić więcej czasu, "+GetAddress_FormToNPC(NPChar)+"Natychmiast wypłynę w morze.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6)+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "Mam wiarygodne informacje, że jakiś kapitan umówił się na transakcję z przemytnikami dotyczącą sprzedaży niewolników. Jak zapewne wiesz, takie transakcje przez osoby prywatne w naszych koloniach są traktowane jako towary kontrabandy\nProblem polega na tym, że nie znam ani dokładnego czasu, ani daty, ani miejsca, gdzie przemytnicy się spotkają. Wiadomo jedynie, że przestępcza transakcja zostanie dokonana w ciągu najbliższych pięciu dni na naszej wyspie. Co gorsza, wszystkie moje okręty patrolowe są albo w naprawie, albo zaangażowane w inne zadania i nie mogą znaleźć tych łajdaków\nProponuję, abyś zajął się tym zadaniem - wytrop przemytników i rozpraw się z nimi w sposób najbardziej radykalny, zrób z nich przykład. Czy jesteś gotów podjąć się tej misji?";
			link.l1 = "Jestem gotów, "+GetAddress_FormToNPC(NPChar)+"Powiedz mi, czy masz jakieś dodatkowe informacje? Na przykład imię kapitana, nazwę lub typ jego statku?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie odpuszczę.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Mój informator właśnie powiedział mi, że umowa jest przygotowywana i zostanie sfinalizowana. To wszystko. Więc po prostu przyjrzyj się bliżej wszystkim podejrzanym statkom na naszych wodach. Jeśli ci się uda, zapłacę ci sumę "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nCo więcej, biorąc pod uwagę okoliczności, upoważniam cię do zebrania całego ładunku kontrabandy, który możesz znaleźć. Oczywiście nieoficjalnie, pod warunkiem, że nie sprzedasz go w naszym mieście.";
			link.l1 = "Całkiem hojnie. Dobrze, zabieram się za patrolowanie wód waszej kolonii, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6)+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "Opowiem ci wszystko szczegółowo. Zdarzyła się bardzo brzydka historia - "+sText+". Przepytując jego kolegów i przyjaciół, wierzymy, nie bez powodu, że dezerter schronił się wśród piratów w jednej z ich osad\nSugeruję odwiedzenie pirackiego gniazda, znalezienie zbiegłego, aresztowanie go i dostarczenie tutaj. Dezercja to poważne przestępstwo i nie może pozostać bezkarnie. Czy jesteś gotów podjąć się tej misji?";
			link.l1 = "Jestem gotów, "+GetAddress_FormToNPC(NPChar)+" Czy możesz mi powiedzieć, jak się nazywa dezerter?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... Nie, myślę, że sobie daruję.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Tak, oczywiście. Nazywa się "+pchar.GenQuest.FindFugitive.Name+". Wątpię, by nosił mundur, więc przyjrzyj się dokładnie wszelkiego rodzaju szumowinom. Daję ci miesiąc na poszukiwania, bo obawiam się, że po tym czasie nie będzie sensu go szukać. Jeśli ci się uda, zapłacę ci sumę "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Nie będę tracił więcej czasu, "+GetAddress_FormToNPC(NPChar)+"! Wypłynę natychmiast.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "Rozumiem. Może nagroda w wysokości "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" będzie dla ciebie dobrą zachętą.";
			link.l1 = "Tak, to niezłe pieniądze... Przyjmę tę misję.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... Nie, myślę, że odmówię. To zbyt niebezpieczne.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Chociaż nie mogę powiedzieć, że mogę ci całkowicie zaufać... Myślę, że nie dam ci tego zadania.";
				link.l1 = "Och cóż... Szkoda, ale nic nie mogę na to poradzić.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Świetnie! A teraz do rzeczy. W "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" musisz znaleźć miejscowego "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", jego imię to "+GetFullName(&characters[GetCharacterIndex(sTemp)])+" Powiesz mu moje imię, a on da ci paczkę dokumentów. Za dostarczenie tej paczki w moje ręce dam ci "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+" I miej na uwadze, że wszystko musi być zrobione potajemnie. Jeśli twoja przykrywka zostanie zdekonspirowana, agent nie zaryzykuje próby nawiązania kontaktu. Czy to jasne?";
				link.l1 = "Tak, mam to, "+GetAddress_FormToNPC(NPChar)+" . Zacznę natychmiast.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Nie udało ci się dotrzymać terminu, dlatego muszę trochę obciąć twoją nagrodę. Teraz twoja opłata wyniesie "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+"Proszę bardzo.","To dobrze. Ale nie dotrzymałeś terminu, a ja czekałem na te listy. Zepsułeś moje plany, więc jestem zmuszony nieco obciąć twoją nagrodę. Mimo to, z przyjemnością wręczam ci należną nagrodę - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Proszę.");
			link.l1 = "Nie powiedziałbym, że mnie to cieszy, ale w końcu terminy rzeczywiście zostały naruszone. Więc nie mam żadnych skarg, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("Wiesz, gubernator " + GetFullName(npchar) + " nie jest zbyt zadowolony z szybkości kapitana " + GetMainCharacterNameGen() + ".", 
				"Gubernator " + GetFullName(npchar) + " nie jest zbyt zadowolony z kapitana " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("który","która") +" wykonał rozkaz, ale nie na czas..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "Zawiodłeś mnie!";
			link.l1 = "Przykro mi, "+GetAddress_FormToNPC(NPChar)+", ale nie mogę przyjąć tej roboty.";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Cóż, to bardzo źle - co jeszcze mogę powiedzieć. Liczyłem na ciebie - a okazuje się, że tylko zmarnowałem czas. Jestem rozczarowany.","Cóż, muszę przyznać, że jestem całkowicie rozczarowany tobą... W mojej rezydencji jest wielu ludzi zawsze gotowych załatwić takie sprawy dla mnie - a ja zmarnowałem na ciebie czas. No cóż...");
			link.l1 = "Przykro mi, "+GetAddress_FormToNPC(NPChar)+". Zrobiłem wszystko, co mogłem.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Wiesz, gubernator " + GetFullName(npchar) + " jest bardzo niezadowolony z kapitana " + GetMainCharacterNameDat() + ". Wyobraźcie sobie - nie udało mu się wykonać swojego zadania na czas!", 
				"Gubernator " + GetFullName(npchar) + " jest lekko zirytowany, że kapitan " + GetFullName(pchar) + " przyłożył rękę do koła, ale nie udało mu się wykonać zadania na czas. To wielka szkoda...", 
				"Słyszałem, że gubernator " + GetFullName(npchar) + " jest z ciebie bardzo niezadowolony, kapitanie " + GetFullName(pchar) + ", ponieważ nie udało Ci się dotrzymać terminu, próbując wykonać jego zadanie."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Jestem po prostu zszokowany! Udało ci się zlokalizować cel, ale nie zadbałeś o środki zapewniające twoją przewagę - to skrajna lekkomyślność. Jestem rozczarowany!","Cóż, muszę powiedzieć, że jestem tobą rozczarowany... Znalezienie celu to za mało - musisz mieć środki, by go zniszczyć. W mojej rezydencji zawsze jest wielu łotrów gotowych podjąć się takich zadań dla mnie. Co ja sobie myślałem, zwracając się do ciebie?");
			link.l1 = "Przykro mi, "+GetAddress_FormToNPC(NPChar)+", ale po prostu nie jestem skłonny lekkomyślnie ryzykować własnego życia.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Wiesz, gubernator " + GetFullName(npchar) + " jest bardzo niezadowolony z kapitana " + GetMainCharacterNameDat() + ". Wyobraż sobie, "+ GetSexPhrase("że okazał się zwykłym tchórzem","że okazała się być całkowitym tchórzem") +"!", 
				"Gubernator " + GetFullName(npchar) + " jest lekko zirytowany, że kapitan " + GetFullName(pchar) + " podjęli się tej pracy, ale nie wykonali jej z powodu własnej niezdecydowania. Hee-hee, co za kapitanowie!", 
				"Słyszałem, że gubernator " + GetFullName(npchar) + " jest z ciebie bardzo niezadowolony, kapitanie " + GetFullName(pchar) + ". Mówią, że jesteś zwykłym tchórzem"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Doskonale wieści! Cóż, czas to wszystko podsumować. Twoje wynagrodzenie wyniesie "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Proszę bardzo.","Doskonale! To najlepszy sposób dla wszystkich... Cóż, z przyjemnością wręczam ci zasłużoną nagrodę - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Proszę bardzo.");
			link.l1 = "Dziękuję, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("przyjemność robić z tobą interesy!","Jestem mile zaskoczony przejrzystością osiedli.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Wiesz, gubernator " + GetFullName(npchar) + "  chwalił za pracowitość"+ GetSexPhrase("kapitana","młodą dame") +" " + GetMainCharacterNameGen() + ".", 
				"Gubernator " + GetFullName(npchar) + " chwali kapitana " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("jest","jest") +" jest zawsze nieskazitelnym wykonawcą, jeśli chodzi o zadania gubernatora. Niezastąpiona osoba dla gubernatora, powiadam...", 
				"Słyszałem, że gubernator " + GetFullName(npchar) + " jest bardzo zadowolony z ciebie, kapitanie " + GetFullName(pchar) + ". Określa cię jako bardzo ostrożnego i dokładnego oficera. Bardzo miło to słyszeć, kapitanie..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Bardzo dobrze. Możesz przyjść do mnie ponownie - być może znajdę dla ciebie kolejną pracę.","Cóż, świetnie! Myślę, że znów będę oferował ci takie zlecenia.");
			link.l1 = RandPhraseSimple("Świetnie.","Dobrze.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "W tych ciężkich czasach każda pomoc jest bardzo mile widziana. Akceptujemy twoją pomoc - pomóż nam bronić naszej kolonii, a zostaniesz wynagrodzony.";
			link.l1 = "Zatem nie traćmy czasu.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Szuka pan Michela de Monpera? Interesujące... A do czego jest panu potrzebny?";
			link.l1 = "Jestem jego bratem. Mój ojciec powiedział mi, że Michel ma kłopoty i potrzebuje pomocy, więc ja...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Czyżby? Nie przypominam sobie, aby monsieur de Monper miał jakichkolwiek braci... Wiesz, monsieur, wyglądasz mi bardzo podejrzanie... więc aresztuję cię do dalszego śledztwa. Poruczniku! Zatrzymaj tego człowieka!";
			link.l1 = "Że co?! Аleż Wasza Lordowska Mość!";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "I nadal chciałbym naprawić sytuację. Oto - proszę, weź ten miecz, ten pistolet i tę lekką zbroję - to mój dar dla ciebie. Wierzę, że te rzeczy będą ci bardzo przydatne.";
			link.l1 = "Dziękuję, monsieur. Biorąc pod uwagę, że twoi strażnicy zabrali wszystko, co posiadam, to bardzo się przyda.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Dziękuję, monsieur. Czy jest jakiś inny sposób, w jaki możesz mi pomóc? Dżentelmen do dżentelmena? Sam możesz zobaczyć, w jak strasznej sytuacji się znajduję!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "„Cóż, Charles... (przeszukując biurko) Proszę, trzymaj ten święty amulet na szczęście. Nie mogę już pomóc, przepraszam. Tutaj, w koloniach, będziesz musiał polegać tylko na sobie.”";
			link.l1 = "Cóż, przynajmniej coś. Dziękuję za prezent, sir.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("Otrzymałeś sprzęt");
			Log_Info("Otrzymałeś amulet „Woda Święcona");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("Otrzymałeś sprzęt");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "Toż to prawdziwa ironia losu, Charles... Rzadko kiedy widujemy kogoś, kto tak szybko pnie się w naszej hierarchii. Mam przeczucie, że ty i ja dogadamy się doskonale.";
			link.l1 = "Byłbym zaszczycony. Może masz dla mnie jakieś zadanie?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Absolutnie! Zwłaszcza po twej udanej potyczce z jednym z piratów Barbazona niedaleko Le Francois...";
			link.l1 = "Nie mogę powiedzieć, że mam miłe wspomnienia z tego spotkania. Kim dokładnie jest Barbazon?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, znany również jako Jacques Dobrodziej, prowadzi gniazdo bandytów w Le François. Jest jednym z tak zwanych baronów pirackich, sprawiających kłopoty piractwem i przemytem na Małych Antylach. Jest notorycznym przestępcą, i zapamiętaj moje słowa, pewnego dnia spotka go koniec na szubienicy w St. Pierre!";
			link.l1 = "Przepraszam, ale czyż nie jesteś prawdziwą władzą na Martynice? Czy nie możesz po prostu zlikwidować tego gniazda? Byłem tam, i uwierz mi, twój garnizon rozwaliłby tą dziure w moment.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Radziłbym nie chełpić się swoją znajomością mniej przyjemnych zakątków mojej wyspy, Charles. To nie przystoi szlachcicowi. Co do twojego pytania\nNie wszystko w naszym świecie można rozwiązać siłą. W grę wchodzą polityka i interesy handlowe. Ale nie zagłębiajmy się w niepotrzebne szczegóły: mam konkretne zadanie, które wymaga trochę siły.";
			link.l1 = "Proszę, kontynuuj.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon przyciąga małe załogi, pragnące łatwego złota. Czasami rzuca im kość, tylko po to, by patrzeć, jak się o nią biją. Od czasu do czasu zatrudnia ocalałego, ale częściej wyrzuca ich, a uwierz mi, nie ma nic bardziej niebezpiecznego niż zdesperowany pirat krążący po okolicy.";
			link.l1 = "Chyba rozumiem, ale nie jestem pewien, czy jestem na to gotowy. Niedawno objąłem dowodzenie nad moim statkiem i wciąż uczę się podstaw, że tak powiem...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Bzdury! Już zasmakowałeś zwycięstwa - bardziej niż większość leni wśród moich oficerów! Miasto nagrodzi cię pięcioma tysiącami pesos za zatopienie jednego z szczurów Barbazona, bez podatku. Osiem tysięcy, jeśli przyprowadzisz pirata żywcem - na odpowiednią egzekucję, rzecz jasna.";
			link.l1 = "Z pewnością przydałoby mi się trochę grosza. Gdzie mogę znaleźć tego pirata?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Przykro mi, ale nie sądzę, że jestem jeszcze gotowy na takie zadanie.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "To wstyd, Charles. W takim razie nie będę cię dłużej zatrzymywać.";
			link.l1 = "Żegnaj, Wasza Ekscelencjo.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Cieszę się, że jesteś na pokładzie, Charles. Nasze raporty wywiadowcze wskazują, że lugier 'Hater', obecnie przygotowuje się do wypłynięcia z Le Francois. Nie możemy sobie pozwolić na opóźnienie, więc wyruszaj i zaatakuj. Nie martw się, przyjacielu, uda ci się.";
			link.l1 = "Z łaską Bożą, Wasza Ekscelencjo.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Oczywiście, kapitanie! Dlatego cię niepokoiłem.";
			link.l1 = "W takim razie, zamieniam się w słuch.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Lokali rybacy widzieli dziwny statek w pobliżu wyspy zeszłej nocy. Jak mówią, był to ogromny okręt wojenny, jak okręt liniowy, bez żadnych flag ani sygnałowych latarni. Nie sądzę, żeby ten statek mógł być faktycznie większy niż fregata, ale nawet to już byłoby zbyt wiele!";
			link.l1 = "Strach zamienia kretowiska w góry, to pewne... ale jaki to ma sens?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Zwracam się właśnie do ciebie, kapitanie. Moi partnerzy handlowi są przerażeni tymi plotkami - wierzą, że to piraci lub hiszpańscy korsarze, i to jest złe dla handlu. Co najgorsze - obecnie nie ma okrętów wojennych w kolonii, tylko parę szalup do ochrony i stary szkuner, nadający się do polowania na przemytników\nNie mogę tego zostawić bez opieki... W każdym razie, teraz, gdy plotka o tajemniczym statku jest znana połowie miasta! Proszę, dołącz swoim statkiem, aby pomóc nam go znaleźć - znam cię jako porządnego kapitana, a nawet jeśli naprawdę jest to tylko fregata, twoje działa mogą przekonać go, by szukał zdobyczy gdzie indziej!";
			link.l1 = "Panie... Właściwie, miałem inne plany...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Proszę, kapitanie! Tylko na parę dni, aż te niespokojne plotki ucichną! I oczywiście zostaniesz wynagrodzony za swój czas. Czy 10 000 pesos ci pasuje?";
			link.l1 = "Hmm... ale, Wasza Ekscelencjo, ja...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Podwoje to, jeśli rzeczywiście weźmiesz udział w walce z tym statkiem, a potroje, jeśli go zatopisz! Teraz, co powiesz?";
			link.l1 = "Dobrze, i tak planowałem tu zostać na kilka dni.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Doskonale, nigdy nie wątpiłem w ciebie, monsieur kapitanie! Pamiętaj - tylko dwa dni na naszych wodach - a pieniądze są twoje. A jeśli będziesz zmuszony wejść do bitwy, zapłacimy ci w zależności od wyniku.";
			link.l1 = "Zrozumiałem, Wasza Ekscelencjo. Mamy umowę, a teraz wracam na mój statek.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Czekam na twój powrót, kapitanie!";
			link.l1 = "Pozwól mi się oddalić.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Kapitanie, wierzę, że mieliśmy umowę, że będziesz patrolował nasze wody przybrzeżne przez dwa dni!";
			link.l1 = "Tak, oczywiście. Pamiętam to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Cóż, wykonałeś swoją część umowy. Oto twoja nagroda - 10 000 pesos, jak się umówiliśmy.";
			link.l1 = "Dzięki! Jak widzisz, twoje obawy były bezpodstawne. Powodzenia!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", zaskoczyłeś mnie! Czy ci łajdacy rzeczywiście stali się tak bezczelni? Muszę natychmiast powiadomić komendanta i wysłać tam patrol przybrzeżny!";
			link.l1 = "Byłem zadowolony, że mogłem pomóc. Czy mogę już odejść?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Oczywiście, kapitanie. Oto - proszę, przyjmij tę skromną nagrodę osobiście ode mnie.";
			link.l1 = "Dziękuję.";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Masz rację, kapitanie! Nie możemy tego tak zostawić! Poprosiłbym cię, abyś udał się do "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", znajdź ich statek i aresztuj całą ich bandę! Jeśli będą się opierać - użyj siły i nie wahaj się!";
			link.l1 = "Pozwól mi się oddalić.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Teraz idź. Płyń tam i upewnij się, że nikt nie ucieknie przed sprawiedliwością. Myślę, że najpierw będziesz musiał zejść na brzeg, a potem możesz zająć się statkiem.";
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Dziękuję za twoją pomoc. Ci łajdacy dostali, co im się należało. Proszę, pozwól mi osobiście wręczyć ci tę skromną nagrodę ode mnie. Bardzo doceniam porządek i spokój w moim mieście.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 20)
			{
				notification("Wymagany poziom 20", "None");
				dialog.text = "Ach, cudownie, dobrze cię widzieć, kapitanie! Słyszałem o twoich talentach, ale przyjdź, gdy będziesz naprawdę gotów.";
				link.l1 = "Tak, oczywiście. Jak sobie życzysz.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "O, wspaniale, cieszę się, że cię widzę, kapitanie! Przybyłeś w samą porę - regaty mają się zacząć za kilka dni. Czy przeczytałeś zasady regat, które musiał ci wręczyć ordynans?";
				link.l1 = "Tak, panie, zrobiłem to.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = " Czy przygotowałeś 50000 pesos - swoją opłatę wejściową, która przyczyni się do puli nagród?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Tak, oczywiście. Proszę, przyjmij moją opłatę.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Obecnie brak mi nieco pieniędzy. Ale na pewno zbiorę wymaganą kwotę.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Bardzo dobrze. Jeśli wygrasz - otrzymasz swoje pieniądze z powrotem pięciokrotnie. Teraz musisz lepiej zapoznać się z zasadami regaty\nWszystkie szczegóły możesz poznać od Sir Henry'ego Stivensona, powinien być w pokoju rezydencji. Idź do niego - wszystko ci wyjaśni.";
			link.l1 = "Dobrze. Zrobię właśnie to.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Dobrze, ale proszę, nie zwlekaj zbyt długo, kapitanie. Regaty zaczynają się już wkrótce.";
			link.l1 = "Rozumiem. Postaram się przynieść ci pieniądze tak szybko, jak tylko będę mógł.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! A tutaj mamy zwycięzcę regat! Dzień dobry, Kapitanie "+GetFullName(pchar)+". Pozwól, że pogratuluję ci tego zasłużonego sukcesu! Zwycięzcy regat zawsze cieszyli się popularnością w angielskich koloniach - i to nie bez powodu.";
			link.l1 = "Dziękuję, sir!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Teraz przejdźmy do najprzyjemniejszej części - ceremonii wręczenia nagród. Nagroda za pierwsze miejsce wynosi 250 000 pesos. Gratulacje!";
			link.l1 = "Dzięki!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Ponadto otrzymasz zestaw cennych nagród: legendarny toledański stalowy rapier 'Asoleda', zestaw zbroi mediolańskiej i doskonały kompas. Wszystko twoje.";
			// <-- legendary edition
			link.l1 = "Jestem bardzo zadowolony, sir. Naprawdę, nie mogłem się spodziewać takiej hojności.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "W imieniu wszystkich poddanych angielskich kolonii dziękuję ci za udział w regatach i raz jeszcze gratuluję zwycięstwa! Jeśli postawiłeś zakład, idź do Sir Henry'ego Stevensona po odbiór wygranej, jeśli jeszcze tego nie zrobiłeś. Powodzenia, kapitanie!";
			link.l1 = "Dziękuję za miłe słowa, sir! Z kolei pozwól mi podziękować za danie mi okazji do udziału w tak wspaniałym wydarzeniu. Teraz proszę pozwolić mi odejść.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
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
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
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
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
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

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "Ten Judasz, wykorzystując swoją pozycję, sprzedał ważną tajemnicę państwową wrogowi."; break;
		case 1: sText = "Ten podły łotr zabił swojego krewnego, znanego i szlachetnego człowieka, aby odziedziczyć jego majątek."; break;
		case 2: sText = "Ten podły łobuz obraził moją rodzinę i mnie osobiście."; break;
		case 3: sText = "Ten złodziej i łotr ukradł pokaźną sumę pieniędzy z kasy naszego miasta."; break;
		case 4: sText = "Ten złoczyńca jest winny śmierci prawie tuzina naszych obywateli."; break;
		case 5: sText = "Ten łotr wykorzystał swoje koneksje, aby przejąć statek handlowy, a następnie go ukradł i sprzedał w pobliskiej stoczni."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "jeden z młodszych oficerów naszego garnizonu zdezerterował i opuścił kolonię na pokładzie statku handlowego."; break;
		case 1: sText = "jeden z naszych oficerów zdezerterował w trakcie służby i uciekł na pokładzie statku przemytniczego."; break;
		case 2: sText = "jeden z naszych oficerów marynarki wojennej służący na patrolu zdezerterował z nieznanego powodu, porwał długą łódź i zniknął na jej pokładzie."; break;
		case 3: sText = "eden z naszych strażników więziennych z nieznanego powodu zrezygnował ze służby i opuścił naszą kolonię na pokładzie prywatnego statku."; break;
		case 4: sText = "jeden z żołnierzy z naszego garnizonu opuścił swoje stanowisko, pełniąc wartę, udał się do zatoki i opuścił to miejsce na pokładzie nieznanego statku."; break;
		case 5: sText = "jeden z naszych oficerów, kapitan patrolowca, porzucił swój statek na otwartym morzu i udał się na południe długą łodzią rybacką."; break;
	}
	return sText;
}
