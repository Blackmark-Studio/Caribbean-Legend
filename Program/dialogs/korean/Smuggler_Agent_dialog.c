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
				dialog.text = "나리, 이곳을 떠나시오. 우리가 논의할 일은 없을 것 같소.";
				link.l1 = "정말이야? 내 얼굴이 마음에 안 들어? 좋아, 나 간다...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "오늘은 거래 없어.";
				link.l1 = "알겠소.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "오늘은 나와 내 친구들이 무척 바쁘다.";
				link.l1 = "하지만 나는 필요해...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "무슨 일이야, 선장?";
				link.l1 = "잠깐 이야기할 수 있을까?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "무슨 일이오, 선장? 나는 당신 이름도 모르고 내 이름도 말해줄 수 없소.";
				Link.l1 = "나는 선장이오 "+GetFullName(pchar)+".";
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
						dialog.text = "오늘은 거래 없어. 모든 만마다 순찰대가 돌아다니고 있거든, 우리 총독이 어떤 선장이 압수한 화물을 찾고 있대."+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그리고 그는 그것을 어딘가에 숨겼어.";
						link.l1 = "그 선장은 어디 있지"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "오늘은 거래 없어.";
						link.l1 = "알겠어.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "오늘은 거래 없어.";
					link.l1 = "알겠소.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "오늘은 거래 없어.";
					link.l1 = "알겠어.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "무슨 일이야, 선장?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("서둘러라, "+GetSexPhrase("친구","소녀")+", 뭐야? 너 때문에 쫓아오고 있잖아!","용건을 빨리 말해! 군인들이 널 쫓고 있어서 우리에겐 시간이 많지 않아...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "뭔가 사고팔고 싶어.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "여정에 관해서...";
				else
					Link.l2 = "나는 한 군데에 가야 해.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "나만의 '특별한' 물건이 좀 있는데, 자네라면 관심 있을 것 같군. 한번 봐봐!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "당신에게 특별한 일이 있소.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "이봐, 친구, 와인하고 럼 술 좀 실어다 줘야겠어. 많을수록, 빠를수록 좋아.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "나는 마이클 로젠크라프트를 만나야 해. 그가 관심 가질 만한 화물이 있거든.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "뭔가 알아봐야겠어, 이 친구.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = ""그쪽 동료이자 내 좋은 친구가 "+  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" 어떤 일에 대해 알고 있다고 들었습니다.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "아무것도 아니야. 또 보자.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "요새 지하실에 있지, 어디겠어? 저 선장은 언제든 당국에 은닉처를 털어놓을 수 있으니, 우리한테 남는 게 없을 거야. 이 소동이 끝나기 전엔 어떤 거래도 생각하지 마라.";
				link.l1 = "이봐, 너 이 섬 구석구석 다 알잖아. 정말로 선장이 어디 있는지 전혀 모르는 거야? "+pchar.GenQuest.CaptainComission.Name+"은닉처가 뭐야?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "하늘나라에 있겠지. 그와 그의 선원들은 교수형을 당했어. 하지만 사형 선고문에는 그 배가 해적선이었다는 말은 없었어.";
				link.l1 = "그 배가 해적선이었다고 왜 그렇게 확신하시오?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "우리는 바위 위에서 싸움을 지켜보고 있었소. 망원경으로 해적 깃발을 단 배를 봤지. 그리고 약 다섯 시간쯤 지나 어둠 속에서 번쩍임이 보였소 — 화약고에서 폭발이 일어난 것처럼 보였지. 그 정도 시간이면 화물을 육지로 옮기기에 충분했소.";
			link.l1 = "선장이 어디 있는지 모르겠어? "+pchar.GenQuest.CaptainComission.Name+"의 은닉처? 너 이 섬隅";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "아니. 우리도 그걸 찾고 있지만, 총독의 즐거움을 위해서가 아니야...";
			link.l1 = "그렇군... 좋은 하루 보내시오.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "아니. 우리도 그걸 찾고 있긴 한데, 총독을 즐겁게 해주려고 찾는 건 아니지... 헤헤";
			link.l1 = "그렇군... 좋은 하루 보내시오.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "왜 그렇게 생각하지? 나는 정직한 연안 상인이야. 다른 구매자를 찾아봐.";
				link.l1 = "고맙다...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "왜 안 되겠어? 네 '화물'을 쓸 데가 있을지도 모르지. 가져가. "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" 동전이나 챙기고 잊어버려.";
					link.l1 = "아니, 괜찮아.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "그리고 네 말이 맞아, 나도 그걸 점점 잊어가고 있어!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "정확해! 이제 정말 궁금해졌어. 내가 너한테 돈을 주면 "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" 동전만 있으면, 그 서류 따위는 전혀 신경 쓰지 않겠지.";
						link.l1 = "아니, 괜찮아.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "네 말이 맞아. 난 이미 그놈들 잊어버렸어.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "이제 저 건방진 녀석을 잡을 기회야! 진짜, 진짜 궁금하거든. 있지, 내가 돈 줄게\n "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" 금으로 주면, 탁자 위의 서류는 완전히 잊어버릴 건가?";
						link.l1 = "안 해.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "좋아, 거래하자!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "알았어, 알았어, 하지만 적을 더 만들지는 마.";
			link.l1 = "너도 마찬가지야!";
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
					dialog.text = "오늘은 거래 없어. 만마다 순찰대가 깔렸거든, 우리 총독이 어떤 선장이 압수한 화물을 찾고 있대."+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그리고 그는 그것을 어딘가에 숨겼어.";
					link.l1 = "그 선장은 어디 있지"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "오늘은 거래 없어.";
					link.l1 = "알겠소.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "오늘은 거래 없어.";
				link.l1 = "알겠어.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "오늘은 거래 없어.";
				link.l1 = "알겠어.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "무엇을 도와드릴까요, 선장님?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "물건을 사고팔고 싶어.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "나는 한 곳에 가야 해.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "당신에게 꽤 특이한 일을 맡기고 싶소.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "이봐, 친구, 와인하고 럼 술을 좀 실어다 줘야겠어. 많으면 많을수록, 빨리 가져와.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "나는 마이클 로젠크래프트를 만나야 해. 그가 관심 가질 만한 화물이 있거든.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "뭔가 알아봐야겠어, 이 친구.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = ""그대의 동료이자 내 좋은 친구가 "+  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" 당신이 어떤 일에 대해 알고 있다고 하더군.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "아무것도 아니야. 또 보자.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "나는 네 친구가 아니야. 그리고 그 대가를 치르게 될 거다.";
				link.l1 = "흠. 나는 값이 그리 비싸지 않은 정보를 알아야 하네 "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "동전 내놔. 그리고 이런 돈으론 별로 못 받을 줄 알아둬.";
				link.l1 = "있잖아, 친구들이 그리웠어. 약속에 늦었더니, 나를 기다리지도 않고 가버렸지...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "하, 너 돈 한 푼도 없잖아! 돈 좀 생기면 다시 와라.";
				link.l1 = "그래, 알겠어.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "그런데 왜 나를 필요로 하지?";
				link.l1 = "그들은 도시에 없고 배도 없어. 그래서 내가 생각했지: 혹시 네 사업 동료들 중 누가 그들에게 은혜를 베푼 건 아닐까?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "알겠소... 몇몇 남자들을 만났는데, 그자들은 섬에서 벗어나기만 하면 어디든 상관없다고 하더군. 이런 경우엔 이유는 묻지 않고, 오직 대가만 따지지. 우리는 로 항해할 일이 있었소. "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Town")].IslandID+"Dat")+" . 돈만 합의되면 거기로 데려다줄 수 있지.";
			link.l1 = "고맙지만, 내 배가 따로 있어.";
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
			dialog.text = "나는 당신과 거래한 적이 없어.";
			link.l1 = "고칠 수 있어. 네가 얼마 전에 내 친구들을 여기로 데려왔지. 나는 회의에 빠졌어\n "+GetSexPhrase("그들","그들")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "음, 우리는 그들을 상륙시켰지  "+XI_ConvertString(sGenLocation+"Gen")+"... 있잖아, 그 사람들이 네 친구라면 모를까, 아니면 괜히 건드리지 않는 게 좋을 거야.";
			link.l1 = "걱정해줘서 고맙소, 하지만 나는 무장도 잘했고 제법 매력적이오.";
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
			Dialog.Text = "흠... 그게 나랑 무슨 상관이지? 길을 잃은 것 같군, 선장. 상점에 가서 원하는 걸 사고팔도록 해.";
			Link.l1 = "아니, 나는 네가 필요해.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "조언해 주셔서 감사합니다. 좋은 하루 보내십시오.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "뭐 때문에?";
			Link.l1 = "혹시 특별한 물건에 관심 있나? 아니면 나한테 내놓을 만한 게 있나?";
			Link.l1.go ="Meeting_3";				
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
				dialog.text = NPCStringReactionRepeat("다음번엔 왕립 전함이라도 끌고 오지 그래? 네 배는 요새에서도 쉽게 눈에 띄어. 우리 목숨 걸고 싶진 않으니, 다음엔 작은 배 하나만 타고 와.","내가 다시 말해야겠어? 더 작은 배를 찾아와. 그러면 얘기하지.","정말 그렇게 멍청한 거냐? 스쿠너나 브리그 하나 구해 와라. 그래야 우리 거래가 성사되지.","아, 내가 바보였지...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("좋아, 네 말 알겠어.","알겠습니다, 그냥 한 가지를 더 분명히 하고 싶었습니다.","아니, 바보는 아니고 그냥 구두쇠지. 뭐가 좀 달라졌나 했더니. 핀네스 몇 척 더 챙겼을 텐데...","거울을 봐...",npchar,Dialog.CurrentNode);
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
				Dialog.Text = "미안해, "+GetSexPhrase("친구","소녀")+", 우리는 이미 바쁘다. 며칠 후에 다시 오시오.";
				Link.l1 = "안타깝군...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "우리 지금 하고 있는 일부터 먼저 끝내는 게 어때?";
				Link.l1 = "네 말이 맞는 것 같군.";
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
                                Dialog.Text = "당신과 거래할 수 있다는 걸 알고 있소. 우리는 다음 장소에서 기다리고 있겠소\n "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
                            }
                            else
                            {
            				    Dialog.Text = "흠... 어쩌면 너를 사줄 사람을 찾을 수 있을지도 모르지. 우리는 에서 기다리고 있겠다 "+GetLocationNameByID(Pchar.quest.contraband.CurrentPlace)+".";
            				}
            				Link.l1 = "좋아. 거기서 보자.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "오늘은 볼일 없어. 내일 다시 와.";
            				Link.l1 = "좋아.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "그 모든 일 이후에 누가 너랑 일하고 싶어 할 거라고 정말 생각하나? 현상금 사냥꾼을 보내지 않은 걸 다행으로 여겨라.";
        				Link.l1 = "안타깝군. 내가 밀수꾼이 될 기회는 없겠네.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "오늘은 볼일 없어. 내일 다시 와.";
    				Link.l1 = "좋아.";
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
				Dialog.Text = "미안해, "+GetSexPhrase("친구","소녀")+", 우리 지금 바쁘다. 며칠 후에 다시 와라.";
				Link.l1 = "안타깝군.";
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
						Dialog.Text = "우리가 이미 거래를 정한 줄 알았는데?";
						Link.l2 = "정말이군!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "돈 가져왔나?";
							Link.l1 = "그래.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "내 마음이 바뀌었어...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "아직 아니야.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "나는 이미 모든 것을 다 말했어.";
								Link.l2 = "정확히 그렇소.";
								Link.l1 = "내 마음이 바뀌었어...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "오늘은 도와줄 수 없어. 이틀 뒤에 다시 오면 뭔가 있을지도 몰라.";
								Link.l2 = "안됐군.";
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

							Dialog.Text = "글쎄, 우리가 거기로 데려다줄 수 있지 "+GetLocationNameByRef(&locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)])+" 근처 "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" 위해 "+pchar.GenQuest.contraTravel.price+" 금이다. 돈을 가져와라 "+FindRussianDaysString(nDay)+". 배가 당신을 기다리고 있을 거요 "+GetLocationNameByRef(&locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)])+" 정확히 24시간.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "나야 괜찮아.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "아니요, 괜찮습니다.";
						}
						else
						{
							Dialog.Text = "오늘은 도와줄 수 없어. 이틀 뒤에 다시 오면 뭔가 있을지도 몰라.";
							Link.l2 = "안됐군.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "그렇게 하고도 누가 너랑 일하고 싶어 할 것 같아? 우리가 현상금 사냥꾼을 보내지 않은 것만도 감사하게 생각해라. 나가!";
        				Link.l2 = "흠, 또 운이 없군.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "아니, 너희 전부를 데려가진 않겠다. 한 명만 데려가겠다.";
					Link.l2 = RandSwear()+"어차피 난 그거 필요 없어!";
				}
				else
				{
					Dialog.Text = "왜 자기 배를 안 쓰는 거야? 아니, 널 태워주지 않을 거야.";
					Link.l2 = "좋아, 네 뜻대로 해.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "원하는 대로 해.";
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
				Dialog.Text = "거래하게 되어 기쁘군. 배에 늦지 마라.";
				Link.l1 = "해볼게.";
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
				Dialog.Text = "돈이 충분하지 않은 것 같군.";
				Link.l1 = "안타깝군, 나중에 다시 오지.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "아주 흥미롭군. 가진 것 좀 보여줘.";
			link.l1 = "아주 '특별한' 물건을 유혹적인 가격에 거래할 수 있는 지하 상점이 있다고 들었어, 그리고 그 상점을 시작하는 데 네가 도움을 줬다더군. 그 상점 주인과 이야기하고 싶어.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "아주 '특별한' 물건을 유혹적인 가격에 거래할 수 있는 지하 상점이 있다는 소문을 들었어. 며칠 안에 출항해야 하는데, 현지 상점에서 필요한 걸 다 사기엔 돈이 부족해서 동전이라도 좀 아껴야겠거든... 몇몇 사람들이 네가 그 부분에서 도와줄 수 있다고 하더라.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "무슨 소리를 하는 거야? 무슨 말인지 모르겠는데. 우리가 여기서 가게를 연 적 없어, 말도 안 되는 소리군, 하하! 장사를 하고 싶으면 물건을 가져와. 그럼 평소처럼 얘기하지... 가게라니, 웃기네!";
			link.l1 = "음...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "할인 받고 싶어? 간단하지. 해가 진 후에 항만 관리소 문 앞으로 와. 우리 사람이 널 만나서 제대로 된 곳으로 데려다줄 거야. ";
			link.l1 = "알겠어. 내가 갈게!";
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
			dialog.text = "하, 저 계산대 뒤에 있는 그 놈이 널 보냈지, 안 그래?";
			link.l1 = "그게 중요해? 네가 구할 수 있어, 아니면 다른 사람을 찾아야 하나?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "원하는 건 뭐든 구해줄 수 있지, 알겠어? 돈만 맞으면 말이야. 하지만 저 빌어먹을 총독이 단속을 심하게 해서 말이지. 이제 술은 손도 안 대. 병이 달그락거려서 멀리서도 다 들리고, 남는 것도 쥐꼬리만 하고, 목 매달릴 위험은 하늘을 찌르거든. 그러니까, 기분 나쁘게 듣진 마.";
			link.l1 = "흠... 뭐든지 구할 수 있다고 했지.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "할 수 있지! 그냥 하기 싫을 뿐이야. 저기, 총독 저택 바로 옆에 사는 놈이 있는데, 믿겨져? 하하. 진짜 바보지... 내가 뭐라고 했더라? 아, 맞다. 그 자식이 몰래 술을 팔아. 총독 가발 바로 밑에서 말이야, 하하. 가서 물어봐, 뭔가 실마리라도 줄지 몰라. 양은 적고, 애들 장난 수준이긴 한데, 그래도 뭐라도 있지.";
			link.l1 = "별로 도움이 안 됐지만, 그래도 고마워.";
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
			dialog.text = "여기 흥청거리는 사람들이 많으니, 볼일이 없다면 나리, 술이나 한잔하거나 그들과 이야기나 나누시오. 이곳은 바쁘오.";
			link.l1 = "다시 시도해 봅시다. 시간과 내 호기심에 대한 대가를 지불하겠소. 나는 답이 필요하오.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "걔가 돈을 낸다고? 하! 내 시간은 싸지 않아, 나리. 3,000페소에다 이 역겨운 술, 럼이라고 부르는 것도 포함이야.";
				link.l1 = "거래지! 이제 네 동료 중에 이곳 감옥에서 반년을 보내고 죽은 자에 대해 말해 봐. 그에게 무슨 일이 있었던 거냐?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "주머니에 은화를 채워 오든지, 금화면 더 좋지. 그럼 와서 얘기해라; 공짜로 너랑 얘기할 시간 없다.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "그건 기억나. 하지만 왜 그 일에 관심이 있는지는 모르겠군. 그 녀석, 감옥에 갇힌 뒤로 정말 미쳐버렸어. 술주정뱅이가 돼서, 사람들을 데려가는 무언가가 있고 아무도 안전하지 않다고 계속 헛소리만 했지. 그 무언가에는 이름이 있다고, 감히 입 밖에 내서도 안 된다고 했어. 만약 그러면, 그게 와서 너도 데려간다고 하더군.";
			link.l1 = "그리고 그 다음에 그는 어떻게 되었지?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "이야기의 결말이 좀 이상하지, 나리. 처음에는 현지인들과 선원들이 그의 이야기를 좋아했지만, 결국엔 모두 질려버렸어. 그런 건 어떤 우화든 늘 그렇지. 그래서 사람들은 그에게 이름을 말하라고 부추겼지. 그 남자는 버티고 저항했지만 조롱을 견디지 못하고 결국 이름을 소리쳐버렸어\n특별한 일은 아무도 느끼지 못했고, 촛불도 꺼지지 않았지만, 불쌍한 그 사람은 다음 날 아침 선술집 뒤에서 목이 베인 채로 죽은 채 발견됐지.";
			link.l1 = "여기엔 아무런 마법도 안 보여. 이름을 말해.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "이름은 기억나지만, 젠장, 입 밖에 내고 싶진 않아. 이 모든 것엔 뭔가 음산한 게 있어. 너도 그거 모르겠어?";
			link.l1 = "이봐, 친구, 내가 너한테 동전 가득 든 지갑을 줬던 거 기억하지? 그럼 이름 좀 알려줄래?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "아, 이거 잘 끝나지 않을 거요, 나리, 내 말을 믿으시오... (목소리를 낮추며) 그가 말했소 - 후안...";
			link.l1 = "제기랄! 후안? 그냥 평범한 이름이고 여기선 꽤 흔한데. 뭐가 그렇게 특별하다는 거야?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "모르겠어, 하지만 이 이름을 말한 남자는 죽었어. 내 촉을 믿자면, 이 이름에는 뭔가 아주 잘못된 게 있어. 그게 다 알고 싶은 거였어?";
			link.l1 = "그런 것 같군. 술이나 한잔 사 마셔. 또 보자!";
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
			dialog.text = "그런가? 좋아. 로젠크라프트 나리가 철목 한 묶음이 필요하다네, 하지만 최소한 "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". 화물이 충분하오?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "그렇소. Rosenkraft 나리는 어디에서 찾을 수 있소?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "흠. 지금은 그 정도까지는 없어.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "그럼 로젠크라프트 나리를 방해하지 마시오. 화물이 충분해지면 오시오.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "그의 갤리온이 해안 가까이에서 순항할 거야 "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" 며칠 동안이오. 그러니 늦지 마시오 – 그가 군도의 다른 곳으로 떠날지도 모르니.";
			link.l1 = "알겠어, 더 빨리 할게. 고마워!";
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
			dialog.text = "그리고 나는 내일까지 살아남아야 해. 저주받은 '머시'가 이 도시에 와 있어. 나가.";
			link.l1 = "참 연극이로군...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
