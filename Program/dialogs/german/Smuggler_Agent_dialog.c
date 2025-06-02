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
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Herr, verlassen Sie diesen Ort. Ich bezweifle, dass wir etwas zu besprechen haben.";
				link.l1 = "Oh, wirklich? Magst du mein Gesicht nicht? Gut, ich gehe...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Kein Geschäft heute.";
				link.l1 = "Ich verstehe.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Meine Freunde und ich sind heute äußerst beschäftigt.";
				link.l1 = "Aber ich brauche...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Was wollen Sie, Kapitän?";
				link.l1 = "Können wir ein bisschen reden?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Was willst du, Kapitän? Ich kenne deinen Namen nicht und ich kann dir meinen nicht sagen.";
				Link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+".";
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
						dialog.text = "Kein Geschäft heute. Es gibt Patrouillen in jeder Bucht, unser Gouverneur sucht nach einer Fracht, die von einem Kapitän konfisziert wurde."+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akk"))+" "+pchar.GenQuest.CaptainComission.Name+" und er hat es irgendwo versteckt.";
						link.l1 = "Und wo ist dieser Kapitän"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Kein Geschäft heute.";
						link.l1 = "Ich sehe.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Kein Geschäft heute.";
					link.l1 = "Ich sehe.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Kein Geschäft heute.";
					link.l1 = "Ich sehe.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Was willst du, Kapitän?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Sei schnell, "+GetSexPhrase("Kumpel","Mädchen")+", was willst du? Sie jagen dich!","Sprechen Sie Ihr Anliegen aus und machen Sie es schnell! Soldaten verfolgen dich und wir haben nicht viel Zeit ...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Ich möchte etwas kaufen oder verkaufen.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Über die Reise...";
				else
					Link.l2 = "Ich muss an einen Ort gelangen.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Ich habe etwas 'Besonderes' und ich denke, dass es dich interessieren könnte. Schau mal!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Ich habe ein ungewöhnliches Geschäft für dich.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Hör zu, mein Freund, ich brauche eine Lieferung Wein und Rum. Viel und schnell.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону

				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Ich muss Michael Rosenkraft treffen. Ich habe die Fracht, die für ihn interessant sein wird.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Ich muss etwas herausfinden, Kumpel.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Ein Kollege von dir und mein guter Freund aus  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" hat erzählt, dass Sie von einigen Geschäften wissen.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Nichts. Bis dann.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "Im Keller der Festung, wo sonst? Dieser Kapitän kann das Versteck jederzeit den Behörden verraten und für uns bleibt nichts übrig. Denke nicht an irgendwelche Geschäfte, bis dieser Aufruhr vorbei ist.";
				link.l1 = "Hör zu, du kennst jeden einzelnen Teil dieser Insel. Hast du wirklich keine Ahnung, wo der Kapitän "+pchar.GenQuest.CaptainComission.Name+"Versteck ist?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "An den Himmeln, schätze ich. Er wurde mit seiner Besatzung gehängt. Aber in der Todesurteil wurde nicht erwähnt, dass es ein Piratenschiff war.";
				link.l1 = "Und warum bist du so sicher, dass das Schiff ein Piratenschiff war?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Wir hatten den Kampf vom Felsen aus beobachtet. In einem Fernrohr sahen wir das Schiff unter Jolly Roger. Dann, etwa fünf Stunden später, sahen wir einen Blitz in der Dunkelheit, es sah aus wie ein Schlag aus dem Pulverraum. Genug Zeit, um die Ladung an Land zu bringen.";
			link.l1 = "Weißt du nicht, wo der Kapitän ist "+pchar.GenQuest.CaptainComission.Name+"'s Versteck? Du kennst jedes Stück dieser Insel.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Nein. Und wir suchen es auch, aber nicht zum Vergnügen des Gouverneurs...";
			link.l1 = "Ich sehe.... Einen schönen Tag noch.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Nein. Und wir suchen es auch, aber nicht zum Vergnügen des Gouverneurs... he-he";
			link.l1 = "Ich verstehe... Einen schönen Tag noch.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Warum hast du dich so entschieden? Ich bin ein ehrlicher Küstenschiffer. Geh und such dir einen anderen Käufer.";
				link.l1 = "Danke...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Warum nicht? Vielleicht finde ich eine Verwendung für deine 'Fracht'. Nimm "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" Münzen und vergiss es.";
					link.l1 = "Nein, danke.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "Und du hast richtig geraten, ich fange an, das zu vergessen!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Genau! Jetzt bin ich wirklich neugierig. Ich vermute, dass wenn ich dich bezahle "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" Münzen, da werden diese Papiere dir völlig egal sein.";
						link.l1 = "Nein, danke.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Und du hast recht. Ich habe sie bereits vergessen.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Nun, das ist eine Chance, diesen frechen Kerl zu fangen! Ich bin wirklich, wirklich neugierig. Schau, ich werde dich bezahlen "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" in Gold und du wirst die Dokumente auf dem Tisch völlig vergessen?";
						link.l1 = "Ich werde nicht.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Gut, abgemacht!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "In Ordnung, in Ordnung, aber hör auf, mehr Feinde zu machen.";
			link.l1 = "Auch dir!";
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
					dialog.text = "Kein Geschäft heute. Es gibt Patrouillen in jeder Bucht, unser Gouverneur sucht nach einer Fracht, die von irgendeinem Kapitän konfisziert wurde."+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" "+pchar.GenQuest.CaptainComission.Name+" und er hat es irgendwo versteckt.";
					link.l1 = "Und wo ist dieser Kapitän"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Kein Geschäft heute.";
					link.l1 = "Ich sehe.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Kein Geschäft heute.";
				link.l1 = "Ich sehe.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Kein Geschäft heute.";
				link.l1 = "Ich sehe.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Wie kann ich Ihnen helfen, Kapitän?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Ich möchte Sachen kaufen oder verkaufen.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Ich muss an einen Ort kommen.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Ich habe ein ziemlich ungewöhnliches Geschäft für Sie.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			
			//--> Торговля по закону
			if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
			{
				Link.l8 = "Hör zu, mein Freund, ich brauche eine Lieferung Wein und Rum. Viel und schnell.";
				Link.l8.go = "TPZ_smugglers_1";
			}
			// <-- Торговля по закону

			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Ich muss Michael Rosenkraft treffen. Ich habe die Ladung, die für ihn interessant sein wird.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Ich muss etwas herausfinden, Kumpel.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Ein Kollege von Ihnen und mein guter Freund aus  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" sagte, dass Sie von einem Geschäft wissen.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Nichts. Bis dann.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Ich bin kein Kumpel für dich. Und es könnte dich kosten.";
				link.l1 = "Hm. Ich muss etwas wissen, das nicht mehr als "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Gib mir deine Münzen. Und wisse, dass du für eine Summe wie diese nicht viel bekommen wirst.";
				link.l1 = "Siehst du, ich habe meine Freunde verpasst. Ich kam zu spät zu einem Treffen und sie haben nicht auf mich gewartet...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, du hast keinen Taler! Komm wieder, wenn du etwas Geld hast.";
				link.l1 = "Tatsächlich, drauf.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "Und warum brauchst du mich?";
				link.l1 = "Sie sind nicht in der Stadt und sie besitzen kein Schiff. Deshalb dachte ich: Vielleicht haben einige Ihrer Geschäftspartner ihnen einen Gefallen getan?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Ich sehe... Ich habe einige Männer getroffen, sie sagten, sie müssen die Insel verlassen und es war ihnen egal wohin. In solchen Fällen fragen wir nicht nach Gründen, nur nach der Bezahlung. Wir hatten eine Reise nach "+XI_ConvertString("Colony"+sColony+"Akk")+", "+XI_ConvertString(locations[FindLocation(sColony+"_Stadt")].IslandID+"Dat")+" . Wir können Sie dorthin bringen, wenn wir uns über das Geld einig sind.";
			link.l1 = "Danke, aber ich habe mein eigenes Schiff.";
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
			dialog.text = "Hatte noch nie Geschäfte mit dir.";
			link.l1 = "Wir können es reparieren. Du hast meine Freunde hier vor nicht allzu langer Zeit gebracht. Ich habe ein Treffen verpasst mit "+GetSexPhrase("sie","sie")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, wir haben sie an Land gebracht bei "+XI_ConvertString(sGenLocation+"Gen")+"... Weißt du, es ist besser, sie sind deine Freunde, sonst rate ich dir nicht, sie in einem anderen Fall zu belästigen.";
			link.l1 = "Danke für deine Sorge, aber ich bin gut bewaffnet und sehr charmant.";
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
			Dialog.Text = "Hm... und wie betrifft es mich? Du hast dich wahrscheinlich verlaufen, Kapitän. Geh zum Laden und verkaufe oder kaufe dort, was du willst.";
			Link.l1 = "Nein, ich brauche dich.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Danke für deinen Rat. Hab einen schönen Tag.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Wofür?";
			Link.l1 = "Vielleicht sind Sie an einigen besonderen Waren interessiert? Oder vielleicht haben Sie mir etwas anzubieten?"Link.l1.go ="Treffen_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

			// поиск мин.  те старшего класса
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			}
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Warum nimmst du das nächste Mal nicht einen königlichen Kriegsschiff. Dein Schiff kann vom Fort aus leicht gesichtet werden. Wir riskieren nicht unsere Köpfe. Komm das nächste Mal auf einem einzelnen kleinen Schiff.","Soll ich mich wiederholen? Finde ein kleineres Schiff und dann werden wir reden.","Bist du wirklich so idiotisch? Such dir eine Schoner oder eine Brigantine. Nur in diesem Fall werden wir Geschäfte machen.","Ach, so ein Idiot...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Gut, ich habe dich verstanden.","Ich verstehe, ich wollte nur etwas klären.","Nein, kein Idiot, nur ein Geizhals. Dachte, dass sich etwas geändert hat. Ich würde ein paar weitere Pinassen nehmen...","Schau in den Spiegel...",npchar,Dialog.CurrentNode);
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
				Dialog.Text = "Entschuldigung, "+GetSexPhrase("Kumpel","Mädchen")+", wir sind bereits beschäftigt. Kommen Sie in ein paar Tagen wieder.";
				Link.l1 = "Zu Schade...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Wie wäre es, wenn wir zuerst unser aktuelles Geschäft abschließen?";
				Link.l1 = "Ich vermute, du hast recht.";
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
                                Dialog.Text = "Ich weiß, dass wir Geschäfte mit Ihnen machen können. Wir werden auf Sie warten bei "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Vielleicht können wir einen Käufer für dich finden. Wir warten auf dich bei "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
            				}
            				Link.l1 = "In Ordnung. Wir sehen uns dort.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Kein Geschäft heute. Komm morgen hierher.";
            				Link.l1 = "Gut.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Glaubst du wirklich, dass jemand nach all dem noch mit dir zusammenarbeiten will? Du solltest froh sein, dass wir keine Kopfgeldjäger nach dir geschickt haben.";
        				Link.l1 = "Schade. Keine Chance für mich, ein Schmuggler zu werden.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Heute kein Geschäft. Kommen Sie morgen hierher.";
    				Link.l1 = "Gut.";
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
				Dialog.Text = "Entschuldigung, "+GetSexPhrase("Kumpel","Mädchen")+", wir sind bereits beschäftigt. Komm in ein paar Tagen wieder.";
				Link.l1 = "Schade.";
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
						Dialog.Text = "Ich dachte, wir hätten den Handel schon abgeschlossen?";
						Link.l2 = "Tatsächlich!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Haben Sie das Geld mitgebracht?";
							Link.l1 = "Ja.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Ich habe meine Meinung geändert...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Noch nicht.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Ich habe dir bereits alles erzählt.";
								Link.l2 = "Genau.";
								Link.l1 = "Ich habe meine Meinung geändert...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Kann dir heute nicht helfen. Komm in zwei Tagen und vielleicht haben wir dann etwas für dich.";
								Link.l2 = "Schade.";
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

							Dialog.Text = "Nun, wir können dich zu "+GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id,"LocLables.txt")+" in der Nähe "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" für "+pchar.GenQuest.contraTravel.price+" Gold. Bring das Geld rein "+FindRussianDaysString(nDay)+". Das Schiff wird auf Sie warten bei "+GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id,"LocLables.txt")+" genau 24 Stunden.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Funktioniert für mich.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Nein danke.";
						}
						else
						{
							Dialog.Text = "Kann dir heute nicht helfen. Komm in zwei Tagen und vielleicht haben wir dann etwas für dich.";
							Link.l2 = "Schade.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Glaubst du wirklich, dass nach alledem noch jemand mit dir zusammenarbeiten will? Du solltest froh sein, dass wir nicht die Kopfgeldjäger nach dir geschickt haben. Verschwinde!";
        				Link.l2 = "Hmm, wieder kein Glück.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Nein, wir nehmen euch nicht alle mit. Nur einen von euch.";
					Link.l2 = RandSwear()+"Es ist mir sowieso egal!";
				}
				else
				{
					Dialog.Text = "Warum benutzt du nicht dein eigenes Schiff? Nein, wir nehmen dich nicht mit.";
					Link.l2 = "Gut, wie Sie wünschen.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Was auch immer du willst.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
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
				Dialog.Text = "Schön, Geschäfte mit dir zu machen. Sei nicht zu spät auf dem Schiff.";
				Link.l1 = "Ich werde es versuchen.";
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
				Dialog.Text = "Es sieht so aus, als hättest du nicht genug Geld."Link.l1 ="Wie schade, ich komme später wieder.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Sehr interessant. Zeig was du hast.";
			link.l1 = "Ich habe gehört, dass es einen Untergrundladen gibt, in dem man sehr 'spezielle' Waren zu einem verlockenden Preis handeln kann und du hast geholfen, diesen Laden zu eröffnen. Ich möchte mit dem Besitzer sprechen.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Ich habe gehört, dass es einen unterirdischen Laden gibt, in dem man sehr 'spezielle' Waren zu einem verlockenden Preis handeln kann. Ich muss in ein paar Tagen segeln und ich habe nicht genug Geld, um alles, was ich im örtlichen Laden brauche, zu kaufen, also muss und will ich etwas Münze sparen... einige Leute haben mir gesagt, dass du mir dabei helfen kannst.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "Wovon redest du? Ich verstehe dich nicht. Wir haben hier keinen Laden eröffnet, das ist Unsinn, ha-ha! Wenn du handeln willst, dann bring uns Waren und wir werden auf unsere übliche Weise reden... Ein Laden, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Willst du einen Rabatt? Einfach. Komm zur Tür des Hafenmeisters, wenn es dunkel ist. Unser Mann wird dich treffen und dich an den richtigen Ort bringen. ";
			link.l1 = "In Ordnung. Ich werde da sein!";
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
			dialog.text = "Ha, der Gauner hinter dem Tresen hat dich geschickt, was?";
			link.l1 = "Und wenn schon? Bekommst du die Ware oder muss ich jemand anderen suchen?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Ich kann alles besorgen, kapiert? Solange die Bezahlung stimmt. Aber dieser verfluchte Gouverneur sitzt uns im Nacken. Mit Alkohol wollen wir nichts mehr zu tun haben – die Flaschen klirren, man hört sie schon aus einer Meile Entfernung, der Profit ist mickrig, und das Risiko, am Galgen zu enden, riesig. Also, nimm's mir nicht übel.";
			link.l1 = "Tja... Und dabei behauptest du, du kannst alles besorgen.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Ich kann es auch! Ich will nur nicht. Da gibt's einen Kerl, der wohnt direkt neben der Residenz, stell dir das vor! Ha-ha. Was für ein Dummkopf... Wo war ich? Ach ja. Der vertickt heimlich ein bisschen Schnaps unter der Hand. Direkt unter der Nase des Gouverneurs, ha-ha. Frag ihn mal, vielleicht weiß er was. Die Mengen sind zwar klein, aber besser als nichts.";
			link.l1 = "Viel hast du mir nicht geholfen, aber danke trotzdem.";
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
			dialog.text = "Es gibt hier viele Feiernde und wenn Sie kein Geschäft haben, Herr, trinken Sie oder sprechen Sie mit ihnen. Dieser Ort ist beschäftigt.";
			link.l1 = "Lass es uns noch einmal versuchen. Ich werde Dich für Deine Zeit und meine Neugier bezahlen. Ich brauche Antworten.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Er wird zahlen, ha! Meine Zeit ist nicht billig, Herr, sie kostet 3000 Pesos plus dieses ekelhafte Getränk, das sie versehentlich Rum nennen.";
				link.l1 = "Abgemacht! Nun erzähl mir von einem der Deinen, der ein halbes Jahr im örtlichen Gefängnis verbracht hat und dann gestorben ist. Was ist mit ihm passiert?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "Du solltest besser deine Taschen mit Silber oder Gold füllen, was besser wäre. Dann komm und sprich, ich habe keine Zeit, kostenlos mit dir zu reden.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Ich erinnere mich daran, obwohl ich nicht verstehe, warum du daran interessiert bist. Der Bursche ist wirklich verrückt geworden hinter diesen Gittern. Er wurde zum Trunkenbold und redete immer irgendeinen Unsinn über den Verbrauch, der die Menschen wegnahm und vor dem niemand sicher war. Er sagte, dass dieser Verbrauch einen Namen hatte und man es nicht einmal wagen sollte, ihn laut auszusprechen. Wenn du es tust - wird es kommen und dich auch holen.";
			link.l1 = "Und was ist danach mit ihm passiert?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Die Geschichte hat ein seltsames Ende, Ältester. Anfangs mochten Einheimische und Seeleute seine Erzählung, aber schließlich hatten sie genug davon. Das passiert immer mit jeder Fabel. Also provozierten sie ihn, den Namen zu sagen. Der Kerl wehrte sich und sträubte sich, konnte aber das Spotten nicht ertragen und schrie ihn buchstäblich heraus\nNiemand spürte etwas Besonderes, die Kerzen erloschen nicht, aber die arme Seele wurde am nächsten Morgen tot hinter der Taverne mit durchgeschnittener Kehle gefunden.";
			link.l1 = "Ich sehe hier keine Magie. Sag mir den Namen.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Ich erinnere mich an den Namen, aber verdammt, ich werde ihn nicht laut aussprechen. Es steckt etwas Unheimliches in all dem. Siehst du das nicht?";
			link.l1 = "Hallo, Kumpel, du hast von mir eine Brieftasche voller Münzen erhalten, erinnerst du dich? Würdest du mir also freundlicherweise den Namen nennen?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Oh, das wird nicht gut enden, senor, vertrau mir... (senkt seine Stimme) Er sagte - Juan...";
			link.l1 = "Verdammt nochmal! Juan? Das ist nur ein gewöhnlicher Name und hier ziemlich beliebt. Warum ist er so besonders?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Weiß nicht, aber der Mann, der diesen Namen sagte, wurde getötet. Vertraue meinen Eingeweiden, etwas ist sehr falsch mit dem Namen. Ist das alles, was du wissen wolltest?";
			link.l1 = "Ich vermute schon. Du kannst dir selbst ein Getränk kaufen. Bis dann!";
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
			dialog.text = "Ist das so? Fein. Mynheer Rosenkraft braucht eine Charge Eisenholz, aber nicht weniger als "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Haben Sie genug Ladung?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Ich tue. Wo kann ich Mynheer Rosenkraft finden?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Ich habe jetzt gerade nicht so viel.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Stören Sie nicht Mynheer Rosenkraft. Kommen Sie, wenn Sie genug Ladung haben.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Seine Galeone wird nahe an den Küsten kreuzen "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" seit mehreren Tagen. Also komm nicht zu spät - er könnte zu einem anderen Ort des Archipels segeln.";
			link.l1 = "In Ordnung, ich werde mich beeilen. Danke!";
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
			dialog.text = "Und ich muss bis morgen leben. Die verdammte 'Barmherzigkeit' ist in der Stadt. Geh.";
			link.l1 = "So ein Drama...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
