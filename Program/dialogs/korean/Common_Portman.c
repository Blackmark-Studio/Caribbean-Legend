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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("도시에 경보가 울려서 이제 모두가 자네를 찾고 있네. 내가 자네라면 거기 머무르지 않겠어.","도시 경비병 전원이 너를 찾으려고 온 시내를 뒤지고 있어. 내가 너랑 얘기할 만큼 바보는 아니지!","도망쳐, "+GetSexPhrase("동료","아가씨")+", 병사들이 너를 벌집으로 만들기 전에..."),LinkRandPhrase("무엇이 필요하오, "+GetSexPhrase("악당","악취 나는 놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았어. 더 이상 못 도망가, 더러운 해적 놈!","살인자야, 당장 내 집에서 나가라! 경비병들!","나는 너 따위 안 무서워, "+GetSexPhrase("놈","쥐")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 거야..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한텐 아무 문제도 아니지...","그놈들이 날 절대 못 잡을 거야."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 어쩌면 네 더러운 혓바닥을 뽑지 않을 수도 있지!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 그리고 거기 있는 모두가 - 해적을 잡아라! 내가 하는 말이야, 친구: 조용히 있으면 살 수 있어..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "오, 네가 누군지 알겠군. 화물을 운송하라고 계약했지만, 오히려 훔쳐 갔지! 경비병들, 이놈 잡아라!";
					Link.l1 = "아르르!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "무엇을 도와드릴까요, 나리?";
				Link.l1 = "너와 할 일이 있군...";
				Link.l1.go = "quests";
				Link.l2 = "미안하지만, 나는 가야 해.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "안녕하십니까, "+GetAddress_Form(NPChar)+". 전에 만난 적이 없는 것 같소. 나는 "+GetFullName(npchar)+" - 항만 관리자.";
				Link.l1 = "안녕, "+GetFullName(NPChar)+". 나는 "+GetFullName(PChar)+", '의 선장"+PChar.ship.name+"'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "MacArthur 선장, 내가 항상 말하지만 매번 나에게 보고할 필요는 없소. 걱정 말시오.";
					link.l1 = "그만해, 나리 "+npchar.lastname+" 나도 다른 사람들과 똑같아.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("안녕하시오, "+GetAddress_Form(NPChar)+". 나에게 볼일이 있소?","안녕하세요, "+GetFullName(Pchar)+". 당신 배가 우리 항구로 들어오는 걸 봤고, 분명 나를 만나러 올 거라 생각했소.","아이고, 선장님 "+GetFullName(Pchar)+". 무슨 일로 나를 찾아왔소?");
				Link.l1 = "안녕하세요, "+GetFullName(NPChar)+". 당신과 이야기하고 싶었습니다.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "그래서, 돈은 어떻게 된 거야? 나한테 최소한 천 페소는 있지?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "그래, 가지고 있다"+GetSexPhrase("","")+". 딱 천 페소다. 이제 정보를 내놓으시오!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("아니, 아직 아니야...","아직 아니야...","아직 아니지만, 곧 가져오겠소...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "부디, 문제의 핵심을 설명할 기회를 주십시오. 제 오랜 친구, 선장  "+PChar.GenQuest.ChurchQuest_1.CapFullName+", 서로 몇 시간 차이로 어긋나 버렸고, 나는 그와 급한 일이 있소. 이제 그를 따라잡아야 하는데, 어디로 갔는지 전혀 모르겠소\n"+GetSexPhrase("","")+" 그의 행방에 대해서.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "항만관리관 나리, '라는 이름의 배에 대해 정보를 좀 얻고 싶습니다\n"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' 선장이 소유한 "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
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
					dialog.text = "훌륭합니다. 저는 당신을 위해 대기하고 있소, "+GetFullName(PChar)+".";
					Link.l1 = "당신 식민지로 갈 화물이 내 배의 창고에 있습니다.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "훌륭하군요. 저는 당신을 위해 준비되어 있습니다, "+GetFullName(PChar)+".";
					Link.l1 = "당신 식민지로 갈 화물이 내 배의 선창에 있습니다.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "오, 결국 왔구나. 솔직히 다시 올 줄은 몰랐지. 우리는 이미 관청에 네 수배를 요청해 두었다. 자, 할 말이라도 있나?";
						Link.l1 = "예상치 못한 사정으로 인해 화물을 제때 전달하지 못했습니다. 하지만 이 갈등을 평화롭게 해결하고 싶습니다. 화물을 가져왔으니, 우리가 합의에 이를 수 있기를 바랍니다.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "오, 네가 누군지 알겠군. 화물을 운송하라고 계약했는데, 도리어 훔쳐 갔지! 경비병들, 경비병들!";
						Link.l1 = "아아악!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
					Link.l1 = "당신 식민지에 우편을 전달했소.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "오, 드디어 왔군. 솔직히 우리는 이미 네가 죽은 줄 알았지... 뭐, 멍청이로 살아 있는 게 죽은 것보단 낫겠지.";
					Link.l1 = "예상치 못한 사정 때문에 우편을 제때 전달하지 못했습니다. 하지만 여기 있습니다.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "무슨 일이야? 죽다 살아난 사람처럼 보이는데.";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+", 당신이 위험을 경고했을 때 옳았소. 항만청 바로 앞에서 검은 옷을 입은 두 놈이 나를 습격했고... 결국 그 자들이 내게서 소포를 빼앗아갔소.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "훌륭하군요. 저는 당신을 위해 대기하고 있소, "+GetFullName(PChar)+".";
					Link.l1 = "항만 관리관이 나를 여기로 보냈소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". 무기와 탄약을 실은 배를 호위해 달라는 부탁을 받았소. 여기 내 서류가 있소.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군요. 저는 당신을 위해 봉사할 준비가 되어 있습니다, "+GetFullName(PChar)+".";
					Link.l1 = "우리가 약속한 대로 무기를 실은 배를 호위해 왔소.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
					Link.l1 = "실종된 선박을 찾아서 이 항구로 데려왔습니다. 선장의 보고는 이미 받으셨을 것입니다.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
					Link.l1 = "실종된 선박을 찾아서 이 항구로 데려왔습니다. 선장은 이미 나리께 보고를 드렸을 것입니다.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
					Link.l1 = "나는 그 실종된 선박을 그 섬 해안에서 발견했소 "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". 그녀의 선장은 압도적인 해적 세력과 불공평한 싸움에 휘말려 있었소. 나는 할 수 있는 모든 방법으로 도왔지만, 안타깝게도 헛수고였소. 저 빌어먹을 악당들이 배를 침몰시켰거든. 그 순간 내가 할 수 있었던 건 그녀의 복수를 하는 것뿐이었소.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군요. 저는 당신을 위해 준비되어 있습니다, "+GetFullName(PChar)+".";
					Link.l1 = "나는 그 섬 해안에서 실종된 선박을 찾았소 "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". 음, 사실 배 자체가 아니라, 그 배의 선원 중 약 오십 명과 선장에 관한 일이오. 그들은 지금 안전하오 - 선원들은 내 배에 탔고, 선장은 지금 당신네 마을에 있소 - 이미 당신을 찾아갔다고 생각하오.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "훌륭하군요. 언제든지 명령만 내리십시오, "+GetFullName(PChar)+".";
					Link.l1 = "당신의 임무를 완수했습니다. 무역 호송대를 공격한 해적 함대는 전멸시켰습니다.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
					Link.l1 = "나는 호위선의 선장이오. 무역선을 항구로 무사히 인도했다는 것을 보고하러 왔소.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "훌륭하군요. 저는 당신을 위해 준비되어 있습니다, "+GetFullName(PChar)+".";
					Link.l1 = "나는 호위선의 선장이오. 두 척의 상선을 화물과 함께 항구로 호송하라는 명을 받았으나, 불행하게도 두 척 모두 적 호송선단과의 전투 중 침몰했소. 그래도 화물은 무사히 전달했소.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "훌륭합니다. 저는 당신을 위해 준비되어 있습니다, "+GetFullName(PChar)+".";
					Link.l1 = "나는 호위선의 선장이다. 무역선을 항구로 무사히 인도했음을 보고하러 왔다.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "그렇게 말씀해 주시니 기쁘군요. 당신 자리에 있었다면 많은 이들이 자만했을 겁니다. 자, 내가 그리고 내 기록들이 어떻게 도와드릴까요?";
			}
			else dialog.text = "훌륭하군. 나는 당신을 위해 준비되어 있소, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "내가 맡을 만한 일거리 있소? 아니면 계약이라도?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "여기 내 배 중 하나를 잠시 정박시켜도 되겠소?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "내 배를 되찾고 싶소.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "재정 문제를 논의하러 왔소.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("나는 어떤 남자의 부탁을 받고 여기 왔소. 그의 이름은 총독이오 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 나를 당신에게 보냈소. 뭔가를 받아가라고 했는데...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "귀항의 항만청에 등록된 선장들에 대해 더 알고 싶소.";
			link.l6.go = "CapitainList";
			link.l61 = "특별히 맞춤 제작된 배들과 그 전설적인 선장들에 대해 아는 바가 있소?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "나는 다른 일로 바쁘오.";
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
					link.l9 = "안녕하세요, 아드님의 초대로 왔습니다."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "이건 당신의 딸에 관한 일이오...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "우연히 이 선박 서류 꾸러미를 발견했습니다.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "나는 우연히 이 선박 서류 꾸러미를 발견했소, 누군가 잃어버린 게 분명하오.";
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
			Link.l15 = "감사합니다. 안녕히 가십시오.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "당신 문제는 쉽게 해결할 수 있습니다. 항로 관리 담당관을 찾아가면 친구의 배 항로에 관한 모든 정보를 제공해 줄 것이오.";
			link.l1 = "안타깝게도, 그렇게 간단하지 않소. 내 친구가 당신네 항구에서 자신의 배 이름을 바꿨소... 종교적인 이유 때문이오.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "알겠소. 그럼 일이 좀 더 복잡해지는군. 선박 등록부 기록을 뒤져봐야 하니 시간이 좀 걸릴 거요. 그리고 시간은 곧 돈이라는 것, 자네도 잘 알겠지.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "그 점은 잘 이해하고 있습니다, 나리 "+GetFullName(NPChar)+", 그리고 나는 당신의 시간을 평가할 준비가 충분히 되어 있소 ... 금액은, 예를 들어 천 페소 정도로 하겠소.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "지금은 수중에 돈이 없어서 아쉽군... 나중에 다시 오겠소...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "완벽하군! 이제 보자... 잠깐만... 여기... 좋아. 선박의 개명은 등록되었고, 이제부터 이 배는 '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' "+GetFullName(sld)+" 선장이 지휘하는 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 오늘 출항하여 ~을(를) 향해 나아갔소 "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "오! 자네가 내가 얼마나 바쁜 사람인지 정말로 이해해 주는군, 고맙네! 어디 보자... 잠깐만... 여기... 됐네. 배의 개명은 등록되었고, 이제부터 이 배는 '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' "+GetFullName(sld)+" 선장이 지휘하는' "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 오늘 출항하여 ...로 향했소 "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "감사합니다, 나리, 큰 은혜를 입었습니다.";
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
			dialog.text = "정확히 무엇을 알고 싶은가?";
			link.l1 = "그 선장이 소유한 배가 당신네 항구에 들른 적이 있는지 말해줄 수 있소?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "흠... 그런데 왜 묻는지 알 수 있을까?";
			link.l1 = "나는 그와 볼 일이 있소. 하지만 그가 이 항구에 들르지 않았거나, 당신이 모른다면...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "그랬지. 하지만 모든 성인들께 감사해야지, 바로 오늘 아침에 그자가 우리 곁을 떠나 저쪽으로 향했으니\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+". 그리고 그와 상대해야 하는 사람은 진심으로 안됐다고 생각하오.";
			link.l1 = "그렇다면, 행운을 빌어 주시오 - 그리고 도와줘서 고맙소.";
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
			dialog.text = "무엇을 알고 싶은가, "+GetSexPhrase("나리","아가씨")+" "+GetFullName(PChar)+"?";
			link.l1 = "이 선장이 당신네 항구에 들른 적이 있는지 말해 줄 수 있소?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "흠, 정말 그랬지. 그리고 나는 그가 마침내 이 고생 많은 항구를 떠나는 그 축복받은 순간을 애타게 기다리고 있다고 말해야겠군.";
			link.l1 = "그의 배가 아직 여기 있다는 말이오?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "예, 나리 "+GetSexPhrase("나리","아가씨")+". 항구 전체가, 가장 하급 하역 인부부터 도선사장까지 모두 그의 빠른 출항을 기도하고 있소. 그의 배는 방금 도크에서 나와 곧바로 수리를 마쳤지만, 그 사이 용감한 선장은 이미 모든 목수들과 다투고 선체용으로 엄선된 판자 세 묶음을 거절했지. 하지만 내일이면, 우리를 늘 굽어살피시는 자비로우신 주님께서 저... 저 재앙, 모두의 눈엣가시를 우리에게서 치워 주실 것이오!";
			link.l1 = "이제 진정하시오, 나리 "+NPChar.Name+", 그리고 누군가는 더 힘든 시간을 겪게 될 거요. 자네는 이미 이 시련을 통과했지만, 나는 아직 자네 선장을 만나지 못했으니. 이제, 실례하겠소...";
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
			dialog.text = "내가 한번 살펴보지! 그래, 내 서류에도 이 세트는 무효로 표시되어 있네. 일부러 시간 내어 나를 찾아와 이 서류들을 건네주다니 참 친절하군. 순풍을 빌네, 선장!";
			link.l1 = "고맙다!";
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
			dialog.text = s1+"있지, 혹시 이 금액을 고려해 보겠나 "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" 페소, 그게 적당한 보상인가?";
			link.l1 = "당연히 아니지!";
			link.l1.go = "exit";
			link.l2 = "음, 적은 금액이지만, 뭐 별일도 아니었으니. 그래, 제안을 받아들이지. "+npchar.name+".";
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
			dialog.text = "내 제안을 받아들이겠소?";
			link.l1 = "당연히 아니지!";
			link.l1.go = "exit";
			link.l2 = "아마도. 하지만 이 서류들은 훨씬 더 가치가 있을 거라고 확신하오.";
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
			dialog.text = "잘 듣고 있소.";
			link.l1 = "도망자를 데려왔소.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "아이고, 선장님, 정말 감사합니다! 그 아가씨는 괜찮습니까? 다친 데는 없습니까? 왜 도망친 겁니까? 도대체 왜요?\n모르는 겁니까? 신랑은 부유하고 신분도 높은 사람입니다! 젊음이란 순진하고 어리석지요... 심지어 잔인하기도 합니다. 명심하십시오!";
			link.l1 = "글쎄, 당신이 그녀의 아버지이고 최종 결정은 당신에게 달렸지만, 결혼을 서두르지는 마십시오...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "네가 뭘 안다고 그래? 너 자식 있어? 없어? 나중에 자식 생기면 나한테 와서 얘기해라, 그때 다시 말해보자.\n나는 그녀를 가족에게 데려오는 사람에게 보상을 약속했어.";
			link.l1 = "고맙소. 그녀를 잘 지켜보는 게 좋겠소. 내 촉으로는 저게 끝이 아닐 것 같으니.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "오, 네가 그놈이구나 "+GetSexPhrase("가져온 선장","데려온 아가씨")+" 내 방탕한 아들이 어린 신부와 함께라니?";
				link.l1 = "그래, 내가 그들이 도망치도록 도왔지.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "아, 이보시오, 은인 나리. 보상이라도 기다리는 거요?";
				link.l1 = "보상은 필요 없소, 나리의 감사면 충분하오.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "제 아이가 절박한 상황에 처했을 때 버리지 않고, 그 어려운 처지에서 벗어날 수 있도록 도와주셔서 진심으로 감사드립니다.\n감사의 뜻을 전하고 싶으니, 부디 이 소박한 금액과 저의 작은 선물을 받아 주십시오.";
			link.l1 = "감사합니다. 이 젊은 부부를 도울 수 있어 기뻤습니다.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "감사? 무슨 감사?! 저 멍청이가 백수로 빈둥거린 지도 벌써 반 년이야 - 그런데 봐라, 연애질할 시간은 있지! 내가 저 나이였을 땐 이미 내 사업을 꾸리고 있었다고! 푸핫! 총독 나리 댁에는 혼기 찬 따님도 있는데, 저 얼간이는 집안도 없는 계집을 내 집에 데려와서는 감히 내 축복을 바란다고?!";
			link.l1 = "흠... 진심을 믿지 않는 모양이군?";
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
			dialog.text = "무슨 감정? 어떤 감정을 말하는 거냐? 감정이라니... 네 나이에 그렇게 생각 없이 굴 수가 있나?! 젊은 것들 변덕에 휘둘리며 중매쟁이 노릇을 하다니, 부끄러운 줄 알아라! 네가 한 짓은 단순히 한 소녀를 집에서 데려간 것만이 아니라, 내 풋내기의 인생까지 망쳐 놓은 거다. 너한테 고마울 일은 없다. 이만 가거라.";
			link.l1 = "좋아, 너도 마찬가지야...";
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
				dialog.text = LinkRandPhrase("그래, 젠장! 너한테 시킬 일이 있어!","하! 딱 맞춰 왔군! 해결해야 할 일이 있네.","그럼요! 당연히 맡길 일이 있지요! 요즘 들어 골치 아픈 일이 너무 많아서 말입니다...");
				link.l1 = "그럼 본론만 말씀해 주십시오, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "맙소사! 선장님 "+GetFullName(PChar)+", 딱 맞춰 오셨군요! 이런 불운이 닥치다니, 이런 재앙이... 항만 관리국의 관리 하에 있던 배가 정박지에서 불타 버렸습니다! 경비대의 부주의로 배가 불에 타서... 선체만 남기고 다 타 버렸습니다...\n"+"나리, 제가 무슨 죄를 지어서 이런 벌을 받아야 한단 말입니까? 저는 수년 동안 충직한 하인이었는데...";
				link.l1 = "그래서, 그게 뭐 대수라고? 배 한 척 불탔다고? 보험 계약이 왜 있는 건데? 아니면 돈 아끼려고 보험 안 들었다가 이제 와서 속 태우는 거냐?";
				link.l1.go = "BurntShip4";
				link.l2 = "이 일은 내가 돕는 것보다 조선소에서 더 잘 도와줄 수 있을 것이오. 두어 달이면 옛 배를 복원하거나, 어쩌면 새 배를 지어줄 수도 있소. 미안하오, 나는 조선공이 아니라서...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "총독께서는 시민들의 안녕을 항상 생각하시기에 늘 맡길 일이 있소. 선술집에는 도움을 필요로 하는 상인들이 있을 수 있고, 상점에서도 화물 운송 선장을 구하고 있소.";
			Link.l1 = "질문이 하나 더 있소.";
			Link.l1.go = "node_2";
			Link.l2 = "감사합니다. 안녕히 가십시오.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "너는 선장을 찾아야 했지 "+npchar.quest.PortmansJornal.capName+" 그리고 그의 항해일지를 그에게 돌려주시오. 성공했소?";
				link.l1 = "아니, 아직 아니야...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "도난당한 것을 찾아오기로 약속했소 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. 그 임무를 끝내기 전에는 다른 임무는 없을 것이오.";
				link.l1 = "나는 계속 수색할 테니, 그냥 기다려.";
				link.l1.go = "exit";
				link.l2 = "임무를 포기하고 싶소.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "도난당한 것을 찾아주겠다고 약속했잖아 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. 했소?";
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
					link.l1 = "그래, 찾았어. 지금 항구에 있어. 가져가도 돼.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "나는 계속 수색할 테니, 그냥 기다려.";
					link.l1.go = "exit";
				}
				link.l2 = "임무를 포기하고 싶소.";
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
						dialog.text = RandPhraseSimple("그 깃발 아래 항해하는 자들에게는 일이 없소 "+NationNameGenitive(sti(pchar.nation))+"! 당장 내 사무실에서 나가라!","나는 협력하지 않을 것이다 "+NationNameAblative(sti(pchar.nation))+". 썩 꺼져라!");
						link.l1 = RandPhraseSimple("그래, 원하는 대로 하시오...","글쎄, 원하시는 대로 하십시오...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "그대의 평판으로는 신뢰가 가지 않소. 나는 그대와 협력할 생각이 없소. 안녕히 가시오.";
						link.l1 = "뭐야! 전부 거짓말이잖아.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "모욕할 생각은 없소, 선장님. 하지만... 유감스럽게도 내 의뢰를 완수하긴 어려울 것 같소 – 경험이 턱없이 부족하오. 계약을 맺을 수 없소.";
						link.l1 = "알겠소. 뭐, 나리 말대로 하겠소.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "흠... 글쎄, 그건 네가 관심 있는 일이 무엇이냐에 따라 다르지.";
					link.l1 = "화물을 운송하기 위해 내 배를 임대해 줄 수도 있소.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "상인들을 호위해서 돈을 좀 더 벌고 싶어.";
					Link.l2.go = "escort_begin";	//эскорт
					link.l3 = "나는 우편을 배달해서 돈을 더 벌고 싶어.";
					Link.l3.go = "cureer_begin";	//доставка почты
					Link.l4 = "글쎄, 혹시 네가 뭔가 제안할 수 있겠나?";
					Link.l4.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "오늘은 더 이상 할 일이 없소. 다른 날에 다시 오시오.";
					link.l1 = "좋소.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "항구에 네 배가 안 보여. 바깥에 정박하고 다시 나한테 와라. 뭔가 일거리를 찾아보지.";
				link.l1 = "알겠소, 그렇게 하겠소.";
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
					dialog.text = "유감이지만 그런 일거리는 드릴 수 없소. 며칠 후에 다시 들르시오.";
					link.l1 = "알겠소, 그렇게 하겠소.";
					link.l1.go = "exit";
				} 
				else 
				{ // если не заняты
					if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) 
					{ // 2 уровень
						dialog.text = "당신은 이미 여러 번 상선을 무사히 호위했지요. 내 생각에 당신에게 어울릴 만한 임무가 하나 있소.";
						link.l1 = "잘 듣고 있소.";
						link.l1.go = "Escort_LevelUp";
					} 
					else 
					{ // 1 уровень
						if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
							dialog.text = "너를 위한 일이 하나 있네. 항구에 이미 출항했어야 할 상선 두 척이 있는데, 문제는 그들의 호위선이 손상되어 아직 필요한 수리를 기다리고 있어서 당분간 출항할 수 없다는 거야.\n마침 네 배가 이 일에 딱 맞아. 게다가 네 창고에 추가 화물도 실어야 하네. 물론 보수는 두 배로 줄 것이네. 화물 운송과 호위 모두에 대한 대가지.";
							link.l1 = "정말 흥미로운 제안이군! 받아들이지!";
							link.l1.go = "escort_bonus";
							link.l2 = "고맙지만, 그건 내 취향의 일이 아니야.";
							link.l2.go = "exit";
						} 
						else 
						{ // просто эскорт
							dialog.text = "너를 위한 일이 하나 있네. 지금 우리 항구에 상선 두 척이 정박해 있는데, 호위가 필요하다고 하네.\n이 배들을 목적지까지 호위할 기회를 주겠네. 할 생각이 있나?";
							link.l1 = "흥미로운 제안이군! 받아들이지!";
							link.l1.go = "escort";
							link.l2 = "고맙지만, 그건 내 취향의 일이 아니야.";
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "호위대를 지키러 타르타네 한 척 끌고 오는 거나 마찬가지군. 이런 일은 제대로 된 화력을 갖춘 배, 전투함이나 습격선이 필요하지.";
				link.l1 = "알겠어.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "유감이지만, 그런 일거리는 지금 줄 수 없소. 며칠 후에 다시 들르시오.";
			link.l1 = "좋아요, 그렇게 하겠습니다.";
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
					dialog.text = "유감이지만 그런 일거리는 드릴 수 없소. 며칠 후에 다시 들르시오.";
					link.l1 = "알겠소, 그렇게 하겠소.";
					link.l1.go = "exit";
				} 
				else 
				{ 
					// если не заняты
					if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) 
					{ //если 2 уровень
						dialog.text = "그래서... 자네가 이미 여러 번 심부름꾼 일을 맡아서 제법 성공적으로 해냈다고 알고 있네. 내가 곧 맡길 일도 충분히 해낼 수 있을 것 같군.";
						link.l1 = "말씀해 보시오, "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "Postcureer_LevelUp";
					} 
					else 
					{ // первый уровень
						dialog.text = "배가 빠른 것 같군. 우편물과 상업 서류를 배달하는 심부름 일을 맡길 수 있겠어.";
						link.l1 = "이거 흥미롭군. 동의하오. 어디로 가야 하오?";
						link.l1.go = "Postcureer";
						link.l2 = "고맙지만, 그건 내 취향의 일이 아니야.";
						link.l2.go = "exit";
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "미안하지만, 지금 줄 일이 없소. 그런 임무는 민첩한 습격선이 필요하오. 자네 배로는 화물을 운송하는 것이 더 낫겠군.";
				link.l1 = "알겠어.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "유감이지만, 그런 일거리는 드릴 수 없소. 며칠 후에 다시 들르시오.";
			link.l1 = "알겠소, 그렇게 하겠소.";
			link.l1.go = "exit";
		}
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "하지만 당신의 배가 이미 전세되었다고 들었습니다. 더 이상 화물을 드릴 수 없습니다. 이미 맺은 약속부터 이행하십시오.";
					link.l1 = "그래, 아마 네 말이 맞을 거야.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "당신의 선창에는 공간이 너무 부족하오. 화물을 싣기에는 더 넓은 배가 필요하오. 상점에 가서 확인해 보시오 - 이곳 상인은 자주 소규모 화물 운송을 위해 배를 빌려주곤 하오.";
					link.l1 = "알겠소. 뭐, 나리 말대로 하겠소.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "지금 당장 적합한 일거리는 없소. 하지만 이미 여러 번 성공적으로 물품을 전달했으니, 특별히 그대에게 맡기고 싶은 일이 하나 있소.";
					link.l1 = "듣고 있소. 무슨 일입니까?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "글쎄, 몇 가지 용선 기회를 제공할 수 있소.";
				link.l1 = "그럼, 어디 한번 볼까...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "오늘은 더 이상 화물이 없습니다. 다른 날에 다시 오십시오.";
				link.l1 = "어쩔 수 없군.";
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
				dialog.text = "다음과 같은 선택지가 있습니다:\n"+"화물 "+GetGoodsNameAlt(iFrahtGoods1)+" 총 "+FindRussianQtyString(iFrahtGoodsQty1)+" 마을로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", 에 "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". 지급 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\n화물 "+GetGoodsNameAlt(iFrahtGoods2)+" 총 "+FindRussianQtyString(iFrahtGoodsQty2)+" 의 마을로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", 에 "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". 지급 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\n화물 "+GetGoodsNameAlt(iFrahtGoods3)+" 총 "+FindRussianQtyString(iFrahtGoodsQty3)+" 마을로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", 에 "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". 보수 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\n무엇을 선택하시겠습니까?";
				Link.l1 = "나는 두 번째 선택지를 고르겠소 - 그 마을로 전세 항해를 하겠소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" 로 가득 실린 "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "나는 세 번째 선택지를 고르겠소 - 그 마을로 가는 허가증이오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" 로 가득 실린 "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "나는 세 번째 선택을 하겠소 - 그 마을로 가는 허가증을. "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" 로 가득 찬 "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "다음과 같은 선택지가 있습니다:\n"+"화물 "+GetGoodsNameAlt(iFrahtGoods1)+" 총 "+FindRussianQtyString(iFrahtGoodsQty1)+" 마을로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", 에 "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". 지급 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\n화물 "+GetGoodsNameAlt(iFrahtGoods2)+" 총 "+FindRussianQtyString(iFrahtGoodsQty2)+" 마을로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", 에 "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". 보수 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\n무엇을 선택하시겠습니까?";
				Link.l1 = "나는 첫 번째 선택지를 고르겠소 - 그 마을로 가는 허가증이오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" 로 가득 실린 "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "나는 두 번째 선택지를 고르겠소 - 그 마을로 가는 허가증이오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" 로 가득 찬 "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "안타깝게도, 나한테 맞는 일은 없어.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "좋소, 훌륭하군! 내가 필요한 서류를 처리할 테니, 그대는 선적 준비를 하시오.";
			link.l1 = "최선을 다하겠습니다!";
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
			dialog.text = "좋소, 훌륭하군! 내가 필요한 서류를 처리할 테니, 그대는 선적 준비를 하시오.";
			link.l1 = "최선을 다하겠습니다!";
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
			dialog.text = "좋소, 훌륭하군! 내가 필요한 서류를 처리할 테니, 그대는 선적 준비를 하시오.";
			link.l1 = "최선을 다하겠습니다!";
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
				dialog.text = "그럼 어디 보자. 네가 가져오기로 한 화물은 "+GetGoodsNameAlt(iFrahtGoods)+" 총 "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". 하지만 보아하니, 전부를 전달하지는 않았군 - 너는 "+FindRussianQtyString(sti(amount))+" 짧다.";
				link.l1 = "천 마리 상어라니! 분명 저주받은 쥐새끼들 짓이겠지! 하지만 걱정 마, "+GetAddress_FormToNPC(NPChar)+", 부족한 양은 내가 사서 전체 물량을 제출하겠소.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "그럼 어디 보자. 네가 운반하기로 한 화물이 "+GetGoodsNameAlt(iFrahtGoods)+" 총 "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". 맞습니까?";
			link.l1 = "전적으로 맞소, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "항구에 네 배가 안 보여. 닻을 내리고 다시 나를 찾아와라 - 그때 얘기하자.";
			link.l1 = "알겠소, 그렇게 하겠소.";
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
				dialog.text = "흠... 하지만 너는 "+FindRussianDaysString(iTime)+" 늦었소. 그러므로 화물 운임에서 지급액을 줄여야 하오. 계약에 따르면, 지연된 하루마다 총액의 5퍼센트가 벌금이오. 이제, 받으시오\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", 그리고 앞으로는 계약을 잘 지키도록 하시오.";
				link.l1 = "그래도 이 정도면 다행이지.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "수고해 주셔서 감사합니다. 자, 보수 받아가십시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "고맙다!";
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
			dialog.text = "화물을 전달했나? 좋아. 사실, 우리가 직접 사서 수령인에게 넘겨야 했지! 그리고 꽤 비싼 값이 들었으니 알아두게. 그러니 자네가 신용을 회복하고 싶다면, 우리 비용을 보상하고 벌금도 내야 하네. 화물은 자네가 가져도 된다네 - 이제 우리에겐 필요 없으니.";
			link.l1 = "예, 물론입니다. 얼마입니까?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "물품 값의 세 배다. 이 금액은 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "꽤 큰 금액이군. 하지만 거래는 거래지. 좋아, 여기 네 돈이다.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "미쳤소? 그런 터무니없는 금액을 요구하다니, 이건 탐욕의 극치요! 내게선 아무것도 얻지 못할 것이오!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "현명한 결정이오. 이제 보니 그대가 정말 신중한 사람임을 알겠소. 앞으로도 함께 일할 수 있겠군.";
			link.l1 = "감사하지만, 이제 가봐야겠습니다.";
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
			dialog.text = "아, 그렇군... 그렇다면, 그 어떤 항만 당국에도 다시는 얼굴을 비추지 마시오 "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! 꺼져!";
			link.l1 = "나는 별로 놓친 게 없겠지...";
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
			dialog.text = "서둘러라, 수취인이 이미 네 배가 도착한 걸 알고 자기 화물이 걱정된다고 하더군.";
			link.l1 = "그렇다면 더 이상 시간을 낭비하지 않겠소!";
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
			dialog.text = "이 소포는 반드시 도시의 항만 당국에 전달해야 합니다 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", 위해 "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", 그리고 최대한 빨리. 보수는 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "동의하오!";
			link.l1.go = "Postcureer_1";
			link.l2 = "흠... 하지만 나는 그쪽으로 가지 않아. 미안하지만 거절해야겠어.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "훌륭하오! 자네를 믿겠소. 여기 물건이 있네.";
			link.l1 = "즉시 출항하겠습니다!";
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
				dialog.text = "흠... 하지만 너는 "+FindRussianDaysString(iTime)+" 늦었소. 그러므로 이번 일에 대한 보수를 줄여야겠군. 계약에 따르면, 지연된 하루마다 전체 금액의 5퍼센트가 벌금이오. 이제, 받으시오\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", 그리고 앞으로는 계약을 잘 지키도록 하시오.";
				link.l1 = "그래도 이 정도면 다행이지.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "수고해 주셔서 감사합니다. 자, 보수 받아가십시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "고맙소!";
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
			dialog.text = "이제 이걸 어쩌란 말이오? 사람들이 도대체 얼마를 기다렸는지 신만 아실 거요, 그런데 오늘에서야 가져오다니. 좋아, 내게 넘기시오 – 아직 쓸 데가 있을지도 모르니. 그리고 지금은 아무런 보수도 기대하지 말라는 것쯤은 알겠지.";
			link.l1 = "물론이지. 네 짐 가져가라. 잘 가라.";
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
			dialog.text = "그러니 배들을 호위해야 하오."+pchar.questTemp.WPU.Escort.ShipName1+"' 그리고 '"+pchar.questTemp.WPU.Escort.ShipName2+"' 도시로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", 위해 "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". 지급 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". 두 척 모두 무사히 목적지에 도착해야 하오. 그곳에서 현지 항만 당국의 관리에게 배들을 인계하게 될 것이오. 그 관리가 이번 일의 보수도 지급할 것이오.";
			link.l1 = "모든 게 분명해 보입니다. 진행할까요?";
			link.l1.go = "escort_1";
			link.l2 = "흠... 하지만 나는 그쪽으로 가지 않아. 미안하지만 거절해야겠어.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "가시오. 이제 그 배들은 모두 당신의 명령을 따를 것이오.";
			link.l1 = "그럼, 이제 출항한다!";
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
				dialog.text = "흠... 호위에 배가 한 척만 있는 것 같은데, 맞소?";
				link.l1 = "그래, "+GetAddress_FormToNPC(NPChar)+". 또 다른 한 척은 적 함대와의 전투에서 침몰했소.";
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
					dialog.text = "좋아, 그럼. 네가 선박을 호위하고 화물을 운송하기로 되어 있었지 "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". 하지만 보아하니 아직 전체 화물을 다 전달하지는 않았군 - 너는 "+FindRussianQtyString(sti(amount))+" 짧다.";
					link.l1 = "천 마리 상어라니! 분명 저주받은 쥐새끼들 짓이겠지! 하지만 걱정하지 마, "+GetAddress_FormToNPC(NPChar)+", 부족한 양은 내가 사서 전부 제출하겠소.";
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
				dialog.text = "흠... 하지만 너는\n "+FindRussianDaysString(iTime)+" 늦었소. 그러므로 이번 일의 보수를 삭감해야겠군. 계약에 따르면, 지연된 하루마다 총액의 5퍼센트가 벌금이오. 이제 부디, 당신의\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", 그리고 앞으로는 계약을 잘 지키도록 하시오.";
				link.l1 = "그래도 이 정도면 다행이지.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "좋아, 그럼. 네가 선박을 호위하고 화물을 운송하기로 했지 "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". 수고해 주셔서 감사합니다. 자, 보수 받아가십시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "수고해 주셔서 감사합니다. 자, 보수를 받으십시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "고마워!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "항구에 네 배가 안 보여. 바깥에 정박시키고 다시 나를 찾아와라. 그때 얘기하지.";
			link.l1 = "알겠소, 그렇게 하겠소.";
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
			dialog.text = "그러니, 배들을 호위해야 하오 "+pchar.questTemp.WPU.Escort.ShipName1+"' 그리고 '"+pchar.questTemp.WPU.Escort.ShipName2+"' 도시로 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", 위해 "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". 지급 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\n그리고 화물도 당신 배에 실어두겠소, "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+". 운송에 대한 대금 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "모든 게 분명해 보이오. 진행할까요?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "흠... 하지만 나는 그쪽으로 가지 않아. 미안하지만 거절해야겠어.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "훌륭하오! 전대의 지휘를 맡으시오.";
			link.l1 = "그럼, 이제 출항하겠다!";
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
			dialog.text = "믿기지 않는군! 그런데 우리가 너를 왜 필요로 했던 거지? 어떻게 이런 일이 벌어지게 놔둘 수 있었어?! 이제 보상은 기대하지 말라는 것쯤은 알겠지?";
			link.l1 = "물론이지... 자, 안녕히 계시오.";
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
					dialog.text = "믿을 수가 없군! 그런데 우리가 너를 왜 필요로 했던 거지? 어떻게 이런 일이 벌어지도록 놔둘 수 있었단 말이냐?! 이제 호위에 대한 보상은 생각도 하지 말라고, 알겠나... 그것뿐만 아니라 화물도 부족하잖아 - "+FindRussianQtyString(sti(amount))+"\n일반적으로, 나는 양호한 상태로 운송된 화물에 대해서만 대금을 지급하고, 분실된 물품의 가치는 차감하겠소. "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" 그리고 원하는 곳으로 가도 된다.";
					link.l1 = "뭐, 그래도 이 정도면 다행이지.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "믿을 수가 없군! 그런데 우리가 왜 자네를 필요로 했지? 어떻게 이런 일이 일어나도록 놔둘 수 있었나?! 이제 호위에 대한 보상은 기대하지도 말게... 그뿐만 아니라, 화물도 엄청나게 부족하군.\n자네가 부족한 물자를 구해올 때까지 기다릴 시간도 없네. 그러니 전액을 보상해야 하네 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". 화물은 네가 가져도 된다.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "알겠어, 너무 흥분하지 마. 여기 네 돈이다.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "다들 미쳤나? 이건 완전 강탈이잖아! 난 아무것도 안 줄 거야!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "믿을 수가 없군! 그런데 우리가 너를 왜 필요로 했던 거지? 어떻게 이런 일이 벌어지도록 놔둘 수 있었어?! 이제 호위에 대한 보상은 전혀 기대하지 말라는 걸 알겠지?\n어쨌든 네가 운반한 화물 운임만 지급하겠다. 네— "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" 그리고 원하는 곳으로 가도 됩니다.";
				link.l1 = "그래도 이 정도면 다행이지.";
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
					dialog.text = "믿기지 않는군! 그런데 우리가 너를 왜 필요로 했던 거지? 어떻게 이런 일이 벌어지도록 놔둘 수 있었어?! 이제 호위에 대한 보상은 생각도 하지 말라는 걸 알겠지... 배를 잃었고, 네가 도착했으니\n "+FindRussianDaysString(iTime)+" 늦었을 뿐만 아니라, 화물도 부족하군 - "+FindRussianQtyString(sti(amount))+"\n네가 부족한 물품을 구해올 때까지 기다릴 시간은 없소. 그러니 전액을 보상해야 하오 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". 화물은 네가 가져도 된다.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "알겠어, 너무 흥분하지 마. 여기 네 돈이야.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "다들 미쳤나? 이건 완전 강탈이잖아! 난 아무것도 안 줄 거야!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "믿을 수가 없군! 그런데 우리가 너를 왜 필요로 했던 거지? 어떻게 이런 일이 벌어지도록 놔둘 수 있었단 말이냐?! 이제 호위에 대한 보상은 있을 수 없다는 걸 알겠지... 게다가, 너는 도착했어\n "+FindRussianDaysString(iTime)+" 늦었소.\n그래서 화물 운임에서 지급액을 줄여야 했소. 계약에 따르면, 지연된 하루마다 원금의 10퍼센트가 벌금이오. 이제, 받아가시오 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", 이제 가도 된다.";
				link.l1 = "그래도 그나마 다행이군.";
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
			dialog.text = "아, 그렇군... 그렇다면, 그 어떤 항만 당국에도 다시는 얼굴을 비추지 마시오 "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"! 꺼져라!";
			link.l1 = "나는 별로 놓친 게 없겠지...";
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
			dialog.text = "이거 정말, 정말 심각하군! 우리가 자네를 왜 고용했는지 말해줄 수 있겠나? 배를 지키라고? 아니면 그냥 빈둥거리라고?";
			link.l1 = "알겠소. 적이 너무 강했으니... 하지만 이제 와서 따져 봐야 무슨 소용이 있겠소 - 이미 벌어진 일이니까. 하지만 화물은, 화물은 아직 멀쩡하잖소! 그러니 이제 정리해 봅시다.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "그럼 어디 보자. 네가 운반해야 했던 화물이 "+GetGoodsNameAlt(iFrahtGoods)+" 총 "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". 하지만 내가 보니 전체 화물을 다 전달하지 않았군 - 너는 "+FindRussianQtyString(sti(amount))+" 짧다.";
				link.l1 = "천 마리 상어라니! 분명 저주받은 쥐새끼들 짓이겠지! 하지만 걱정 마, "+GetAddress_FormToNPC(NPChar)+", 부족한 양은 내가 사서 전부 제출하겠소.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "그럼 어디 보자. 네가 운반해야 했던 화물은 "+GetGoodsNameAlt(iFrahtGoods)+" 총 "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". 맞습니까?";
			link.l1 = "전적으로 맞소, "+GetAddress_FormToNPC(NPChar)+".";
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
				dialog.text = "흠... 맡겨진 배들을 잃었을 뿐만 아니라, 게다가 늦기까지 했군 "+FindRussianDaysString(iTime)+". 그래서 화물 운임을 줄일 수밖에 없었소. 배들을 구하지 못했으니, 운임도 절반으로 깎았고, 이게 내가 줄 수 있는 최대한이오.\n그리고 계약에 따라, 지연된 하루마다 원금의 10퍼센트가 벌금으로 붙소. 이제, 받아가시오 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", 이제 가보시오.";
				link.l1 = "그래도 이 정도면 다행이지.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "글쎄, 그대에게 맡긴 배들을 지키지 못해 내가 몹시 화가 나 있지만, 적어도 화물은 잘 전달했군. 배들을 구하지 못했으니 운임의 절반만 지급하겠소, 이것이 내가 해줄 수 있는 전부요. 자, 대금을 받아가시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" 그리고 원하는 곳으로 가도 된다.";
			link.l1 = "그래도 이 정도면 다행이지.";
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
					dialog.text = "당신은 해당 도시의 총독에게 긴급 공식 서한을 전달해야 할 것이오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 늦어도 "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". 매우 조심하시오 – 우리 적들도 그 서한을 노리고 있을 수 있소. 배달에 대한 보수는 – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "동의하오!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "아니, 나는 사양하겠소.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "이 서류를 상점 주인에게 전달해야 할 것이오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 늦어도 "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". 이것이 군도 전역 상점의 최신 시세 요약이오 - 귀중한 상업 문서지. 조심해야 하오 - 경쟁자들이 추적을 벌일 수도 있소. 배달에 대한 보수는 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "동의하오!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "아니, 나는 사양하겠소.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "이 서류 뭉치를 그 도시의 고리대금업자에게 전달해야 하오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 늦어도 "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". 이것은 환율과 주가에 관한 매우 중요한 정보요. 아주 조심해야 하오 – 이미 수상한 놈들이 이 소포에 관심을 보이고 있소. 배달에 대한 보수는 – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "동의하오!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "아니, 나는 사양하겠소.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "이 꾸러미를 그 마을의 도크마스터에게 전달해야 하오 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" 늦어도 "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". 새로 만든 설계도가 들어 있습니다 "+RandPhraseSimple(LinkRandPhrase("브리그","코르벳","프리깃"),LinkRandPhrase("플루트","피나스","갤리온"))+", 독특한 기술 설계를 활용하고 있소. 다른... 관심 있는 이들이 있다는 점을 이해해 주길 바라오, 그러니 조심스럽게 행동해야 하오. 운송에 대한 보수는 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "동의하오!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "아니, 나는 사양하겠소.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "그럼 서류를 받아서 출항하게. 행운을 빌겠네... 전능하신 분께서 그대를 지켜주시길 바라오.";
			link.l1 = "고맙소!";
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
			dialog.text = "정말 안타깝군... 사실 그런 제안은 보통 쉽게 거절하지 않지. 하지만 어쨌든 결정은 자네 몫이야.";
			link.l1 = "그래, 그게 내 결정이야, "+GetAddress_FormToNPC(NPChar)+".";
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
			dialog.text = "젠장! 결국 그놈들이 자네를 찾아냈군. 선장, 자네가 군인이었더라면 상황이 달라졌을지도 모르는데... 놈들은 어떻게 생겼었나?";
			link.l1 = "검은색 반가면을 쓴 건장한 사내 둘이, 폴액스와 쌍총으로 무장하고 있군...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "즉시 총독에게 알려서 그들을 찾기 시작하라고 하겠소. 좋아, 또 보시오. "+GetAddress_Form(NPChar)+". 또다시, 당신이 군인이 아니라니 아쉽군...";
			link.l1 = "정말로 유감이오, "+GetAddress_FormToNPC(NPChar)+", 일어난 일에 대해서는 유감이오. 그럼, 안녕히 가시오.";
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
				dialog.text = "우리 식민지에서 최근 특정 상품에 대한 수요가 급격히 증가했소. 현지 상점들에는 더 이상 재고가 없네. 그러니 자네가 나에게 그것을 구해다 주었으면 하오. "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+", 그리고 나는 두 배로 지불할 용의가 있소 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 개당. 이렇게 하면 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". 아, 그리고 한 달 기한은 꼭 지키시오 - 더 이상 물건을 기다릴 수 없으니.";
				link.l1 = "좋아, 이 임무 받아들이지.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "실망시켜 드려 죄송하지만, 지금은 그럴 수 없습니다.";
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
				dialog.text = "우리 식민지에서 최근 특정 상품에 대한 수요가 급격히 늘어났소. 현지 상점들에는 더 이상 재고가 없네. 그러니 자네가 나에게 그것을 가져다주었으면 하오. "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+", 그리고 나는 두 배로 지불할 의향이 있소 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 개당. 이렇게 하면 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". 아, 그리고 한 달 기한은 꼭 지켜 주시오 - 더 이상 물건을 기다릴 수 없으니.";
				link.l1 = "좋아, 이 임무를 맡겠어.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "실망시켜 드려 죄송하지만, 지금은 할 수 없습니다.";
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
				dialog.text = "우리 식민지의 무기고가 심각하게 부족하오 "+GetGoodsNameAlt(iGoods)+". 현지 상점에는 더 이상 재고가 없소. 그러니 자네가 나에게 제공해 주었으면 하오. "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+", 그리고 나는 세 배로 지불할 의향이 있소 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 개당. 이렇게 하면 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". 아, 그리고 한 달 기한은 꼭 지키시오 - 더 이상 물건을 기다릴 수 없으니.";
				link.l1 = "좋아, 이 임무를 맡겠어.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "실망시켜 드려 죄송하지만, 지금은 그것을 할 수 없습니다.";
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
				dialog.text = "최근 우리 식민지에 열병이 돌고 난 뒤로 의료 물자가 부족해졌소. 창고에는 아무것도 남지 않았소. 총독께서 시민들의 안전을 염려하고 계시오. 그러니, 자네가 나에게 가져다주었으면 하는 것이 있소 "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+", 그리고 나는 세 배로 지불할 용의가 있소 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 한 묶음당. 이렇게 하면 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". 아, 그리고 한 달 기한은 꼭 지키시오 – 더 이상 물건을 기다릴 수 없으니.";
				link.l1 = "좋아, 이 임무를 받아들이지.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "실망시켜 드려 죄송하지만, 지금은 그것을 할 수 없습니다.";
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
				dialog.text = "흉작 이후로 우리 식민지는 계속해서 수입 식량이 필요하오. 지금은 창고에 남은 것이 거의 없고, 상점 진열대도 이미 한참 전에 비워졌소. 그러니 나에게 식량을 가져다주길 부탁하오 "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(iGoodsQty)+", 그리고 나는 두 배로 지불할 용의가 있소 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" 포장당. 이렇게 하면 \n 총액은 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". 아, 그리고 한 달 기한은 꼭 지켜주시오 - 더 이상 물건을 기다릴 수 없으니.";
				link.l1 = "좋아, 이 임무를 맡겠어.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "실망시켜 드려 죄송하지만, 지금은 그럴 수 없습니다.";
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
		dialog.text = "훌륭하군요! 당신이 동의해줘서 정말 기쁩니다. 곧 다시 뵙기를 바라겠습니다.";
		link.l1 = "물론이지, "+GetAddress_FormToNPC(NPChar)+".";
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
			dialog.text = "농담하는 거야? 내가 주문한 물건이 이만큼도 안 되잖아!";
			link.l1 = "죄송합니다, 제 실수였습니다...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "좋아, 네가 운반해야 할 화물은 "+GetGoodsNameAlt(iGoods)+" 총 "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". 훌륭하군, 정말 고맙네. 여기 보수다 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "거래하게 되어 기쁩니다, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "항구에 네 배가 안 보여. 바깥에 정박시키고 다시 나한테 와라 - 그때 얘기하자.";
		link.l1 = "알겠소, 그렇게 하겠소.";
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
				dialog.text = "이 재앙은 열흘 전에 일어났소... 우리 식민지로 향하던 상선들의 호송대가 해적들에게 습격당했지. 돌풍이 불어 해적들은 물러났지만, 상선들은 흩어져 서로를 놓치고 말았소. 결국 한 척을 제외한 모든 배가 각기 다른 항구에 도착했소. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' 사라졌으며 그녀의 행방은 여전히 알 수 없습니다. 아마도 무인도 근처에서 발견될 수 있을 것입니다. "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". 그곳에 가서, 실종된 배에 무슨 일이 있었는지 알아보고, 만약 그 배가 살아 있다면 우리 항구로 데려오길 부탁하오. 일이 끝난 뒤 보상은 결정하겠지만, 분명히 그만한 가치가 있을 것이오.";
				link.l1 = "물론이오, 동의하오!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "죄송하지만, 이 일은 저에게 맞지 않는 것 같습니다. 유감이지만 사양하겠습니다.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "우리 식민지에 무역 대상단이 도착할 예정이었으나, 항구에 들어오기 직전에 해적들에게 습격을 당했소. 전투는 지금도 벌어지고 있소. 요새의 대포 사정거리 밖이고, 현재 내가 쓸 수 있는 호위선도 없으니 불쌍한 상인들을 도울 방법이 없소. 그대는 용감한 선장이니, 상인들을 도와 해적들의 공격을 막아주길 부탁하오! 그렇게 해줄 수 있겠소?";
				link.l1 = "물론이지! 이건 명예의 문제야!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "죄송하지만, 이 일은 제게 맞지 않습니다. 유감이지만 사양하겠습니다.";
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
				dialog.text = "우리 식민지가 주문한 무기와 탄약을 실은 배가 최근에 식민지에 도착했소\n "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". 그녀의 호위선이 암초에 걸려 심하게 손상되었고, 당분간 항구를 떠날 수 없소. 그런 화물을 실은 상선을 혼자 보내는 것은 위험하오.\n우리 식민지까지 그녀를 호위해 주겠소? 보수는 이미 정해져 있소 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "물론이오, 동의하오!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "죄송하지만, 이 일은 저에게 맞지 않습니다. 유감스럽게도 사양해야겠군요.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "정말 안타깝군. 사실 자네를 믿고 있었는데...";
		link.l1 = "나도 유감이오. 그럼, 다시 만날 때까지, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "훌륭하군! 자네라면 믿고 맡길 수 있을 줄 알았지. 최대한 신속하게 처리해 주게. 내 생각엔 "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" 까지 가기에 충분할 거야 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". 자, 신분을 증명할 증서를 가져가시오. 순풍을 빕니다, 선장!";
		link.l1 = "걱정 마시오, 실망시키지 않겠소.";
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
		dialog.text = "드디어군! 그 배는 오래도록 눈엣가시였지. 이제 지휘를 맡으시오. 배 이름은 "+pchar.questTemp.WPU.Escort.ShipName+", 그리고 그녀의 선장에게 곧바로 당신의 도착이 통보될 것입니다.";
		link.l1 = "그에게 배를 출항 준비시키라고 전하시오 - 나는 가능한 한 빨리 떠날 생각이오.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "항구에 네 배가 안 보여. 지금은 떠나 있다가 나중에 다시 와라\n그때 얘기하자.";
		link.l1 = "그렇게 하겠습니다.";
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
		dialog.text = "훌륭하군! 또 한 번, 당신이 믿을 만한 사람임을 증명했소. 훌륭하게 임무를 완수해 주어 고맙소. 자, 보수를 받아 주시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". 그리고 가끔 나를 찾아오는 것도 잊지 마시오 - 당신 같은 선장에게 맡길 일이 항상 한두 가지쯤은 있으니.";
		link.l1 = "그 말 들으니 다행이군, "+GetAddress_FormToNPC(NPChar)+"! 물론이지, 우리의 협력은 계속될 것이오. 안녕히 계시오!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "항구에 네 배가 보이지 않는군. 당분간 바깥에 머물다가 나중에 다시 찾아와라 – 그때 이야기하자.";
		link.l1 = "알겠소, 그렇게 하겠소.";
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
		dialog.text = "그럼 안전한 항해가 되길 바라오. 그리고 제발, 수색을 지체하지 마시오! 그 배의 선원들이 즉각적인 도움이 필요할지도 모르오.";
		link.l1 = "알겠소. 오늘 출항하겠소!";
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
		dialog.text = "그래, 이미 통보받았네. 훌륭한 일일세, "+GetAddress_Form(NPChar)+"! 너는 또 한 번 내가 믿을 수 있는 사람임을 증명했군. 보상으로 3만 페소를 받아라.\n가끔 나를 찾아오도록 해라. 너 같은 사람은 정말 귀중하니, 언제나 너에게 맞는 일이 있을 것이네.";
		link.l1 = "그 말을 들으니 기쁘군, "+GetAddress_FormToNPC(NPChar)+"! 물론 계속 협력하겠습니다. 행운을 빕니다!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "항구에 네 배가 안 보여. 지금은 밖에서 대기하고, 나중에 다시 찾아와라 – 그때 얘기하지.";
		link.l1 = "알겠소, 그렇게 하겠소.";
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
		dialog.text = "그래, 그는 이미 해적들과의 전투와 당신이 그의 배를 얼마나 용감하게 지켰는지 내게 이야기했소. 훌륭한 일이었소, "+GetAddress_Form(NPChar)+"! 자네가 다시 한 번 믿을 만한 사람임을 증명했군. 보상으로 5만 페소를 받아가게.\n가끔 나를 찾아오게나. 자네 같은 사람은 정말 귀중하니, 언제든 어울리는 일을 찾아주겠네.";
		link.l1 = "그 말 들으니 좋군, "+GetAddress_FormToNPC(NPChar)+"! 물론이지, 우리의 협력은 계속될 것이오. 안녕히 계시오!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "항구에 네 배가 안 보여. 지금은 떠나 있다가 나중에 다시 와라\n그때 얘기하자.";
		link.l1 = "좋아, 그렇게 할게.";
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
		dialog.text = "정말 비극적인 최후로군... 신께서 그들의 영혼을 편히 쉬게 하시길.";
		link.l1 = "나는 할 수 있는 건 다 했어, "+GetAddress_FormToNPC(NPChar)+". 폭풍 때문에 상황이 더 악화되었소.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "내 생각엔, "+GetAddress_Form(NPChar)+", 그대가 배와 불운한 선원들을 구하기 위해 할 수 있는 모든 것을 다 했다는 것, 잘 알고 있소. 하지만 유감스럽게도... 자, 보상금 1만 페소를 받아 주시오. 그리고 수고에 감사하오.";
		link.l1 = "나에게 고마워할 것 없어, "+GetAddress_FormToNPC(NPChar)+". 정말 유감이오. 그럼, 안녕히 가시오.";
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
		dialog.text = "그래, 그가 이미 말해줬지. 네가 붉은 피부의 이교도들과 싸우고, 그다음엔 해적선까지 상대했다더군. 진정한 영웅답게 말이야. 훌륭한 일이었어, "+GetAddress_Form(NPChar)+"! 다시 한 번 내가 믿을 수 있는 사람임을 증명했군.\n보상으로 4만 페소를 가져가게. 가끔 나를 찾아오도록 하게나. 자네 같은 사람은 정말 귀중하니, 언제든 자네에게 맞는 일을 준비해두겠네.";
		link.l1 = "그 말 들으니 기쁘군, "+GetAddress_FormToNPC(NPChar)+"! 물론이지, 우리의 협력은 계속될 것이오. 안녕히 계시오!";
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
		dialog.text = "당신을 믿고 맡길 수 있을 줄 알았소. 행운을 빕니다, 선장님! 식민지 전체가 당신의 승리를 기원하고 있소!";
		link.l1 = "기대에 부응하도록 노력하겠습니다. 이제 출항하러 가겠으니, 신께서 우리를 도와주시길!";
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
				dialog.text = "그래, 온 마을 사람들이 그대의 전투를 지켜보고 있었소. 불쌍한 상인들, 참 안됐지. 뭐, 그래도 한 척이라도 구해냈으니 1만 페소의 보상은 충분히 받을 자격이 있소. 부디 받아주시오 – 그리고 도와줘서 고맙소.";
				link.l1 = "나에게 고마워할 것 없어... 그 싸움에서 확실히 이기지 못한 건 유감이지만, 나는 할 수 있는 건 다 했네. 안녕히 계시오, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "그래, 온 마을 사람들이 네가 싸우는 걸 지켜봤지. 아주 능숙하게 싸웠다고 말해야겠군. 그 불쌍한 상인, 참 안됐네... 하지만 네가 아니었으면 아무도 살아서 도망치지 못했을 거야. 그러니 25,000페소의 보상은 충분히 받을 자격이 있지. 받아 주게나, 그리고 도와줘서 고맙네.";
				link.l1 = "음, 내 행동에 대해 칭찬해줘서 고맙지만, 그게 내 최고의 전투였다고는 생각하지 않아. 그래도 한 척을 잃었으니 말이지. 뭐, 운명이란 그런 거고, 어쩔 수 없는 일이야. 그럼, 안녕히. "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "네, 당신이 싸운 전투를 온 마을 사람들이 다 지켜봤소 – 정말 대단했소! 그 더러운 해적 놈들 전대를 완전히 박살냈구려! 이제야 그놈들도 뼈저리게 배웠겠지 – 안타깝게도 더 이상 소용없겠지만. 보상금 5만 페소요 – 부디 받아주시오.";
				link.l1 = "제 행동을 좋게 평가해 주셔서 감사합니다! 도울 수 있어서 언제나 기쁩니다. 그리고 이제, "+GetAddress_FormToNPC(NPChar)+", 부디 물러가도록 허락해 주십시오.";
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
			dialog.text = "흠, 그거 안 좋군. 그렇다면 더 이상 나한테 맡길 일은 없겠네.";
			link.l1 = "알겠습니다. 제가 하고 싶었던 말은 이렇습니다...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "안타깝군, 선장... 네가 나를 도와줄 생각이 없다니 유감이야.";
			link.l1 = "그건 내 의지로 되는 일이 아니네, 이보게. 이해해 주게. 안녕히 가게.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "대체 왜 이러십니까, 선장님?! 부끄럽지도 않으십니까?! 어떻게 그럴 수가 있습니까?! 저는 제 일에 대해 잘 알고 있습니다, 수년간 이 일을 해왔으니까요. 보험 계약도 있고, 보험사도 지급 의사가 있습니다. 그리고 보장 금액도 꽤 괜찮다는 걸 장담합니다.";
			link.l1 = "무슨 문제라도 있나, 나리? 화약고가 폭발해서 사상자가 나왔고, 이제 자네의 과실로 재판을 받아야 하겠군?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "아니오! 당연히 아닙니다! 주님, 제 영혼을 구하소서, 아니면 제 목이 달아날 뻔했습니다. 화물창은 완전히 비어 있었습니다, 주님 감사합니다, 성모 마리아님 감사합니다!\n"+"문제는 그 배가... 아니, 정확히는 "+GetAddress_Form(ENGLAND, "man", 1)+" 나리의 것이었다는 점이오. "+sCapitainId+", 카리브 전역에 잘 알려진 배지. 그리고 특별 주문으로 유럽에서 건조되어, 비범한 특징을 지녔소. "+"그리고 그 선주란 자는 너무 자만심이 넘쳐서 여기저기 자랑만 해대더군, 정말 멍청이야, 신이시여 용서하소서... 이제 내가 그 자한테 무슨 말을 해야 하지? 차라리 내가 죽는 게 낫겠어, 맹세코...";
			link.l1 = "아, 이제야 무슨 문제인지 알겠군. 그런데 그 배가 뭐가 그리 특별했지? 선주가 그렇게 자랑스러워할 만한 특별한 점이 있었나?";
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
			link.l1 = "그리고 부두 사람들은 뭐라고 하오? 여기서 정말 또 하나 짓는 건 불가능하단 말이오?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "아무도 할 수 없어. 근처 섬까지 가서 현지인들에게도 물어봤지. 그랬더니 이슬라 테소로에 거의 모든 배를 만들 수 있는 유명한 장인이 있다고 하더군. 하지만 이슬라 테소로는 정말 멀리 있어. 이제 남은 건 너 같은 자유 선장들의 도움뿐이야. 혹시라도 그런 배를 구해다 줄 수 있겠지. 나머지는 내가 알아서 할게\n"+"제가 넉넉히 감사의 뜻을 전하겠소, 보험 회사도 마찬가지일 것이오. 이건 드문 일이오, 알겠소? 누가 그렇게 강력한 인물을 화나게 하고 싶겠소?";
			link.l1 = "그래, 그게 쉽진 않겠군. 그리고 시간이 얼마나 남았지?";
			link.l1.go = "BurntShip8";
			link.l2 = "아니, 친구, 나는 그런 일에 관여할 수 없어. 게다가 그런 조건을 가진 배가 실제로 존재한다는 보장도 없잖아. 미안하다...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "신께 감사하네, 아직 시간이 있군. 선주는 유럽으로 항해를 떠났고, 최소 반년은 돌아오지 않을 걸세.";
			link.l1 = "글쎄, 내가 알아서 해보지. 비슷한 배를 가져다주마. 하지만 명심해라 - 너무 인색하게 굴면 네 눈앞에서 그 배를 불태워버릴 거다!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "무슨 뜻이오, 선장? 물론 시간이 필요하다는 건 이해하오. 이건 근처 웅덩이에서 아무 배나 주워 오는 일이 아니지 않소... 그냥 배만 가져오시오. 우리가 최선을 다할 테니, 그건 믿어도 되오...";
			link.l1 = "그러길 바라오... 자, 나와 좋은 소식 모두 기다리시오. 그럼 이만.";
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
			dialog.text = "무슨 이야기를 하려고 했소?";
			link.l1 = "그리고 전임 항만 관리인은 어디 있소, 나리 "+NPChar.Quest.BurntShip.LastPortmanName+"? 그와 볼 일이 있소.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "그 자는 이제 여기 없어. 상상해 봐 – 유명한 인물의 배에 불을 지르고 보험금까지 챙겼다지. 관청에서 이 모든 걸 조사하는 동안, 그는 사임하고 유럽으로 슬쩍 도망쳤어. 정말 사기꾼이지, 안 그래?";
			link.l1 = "그래, 그 얘긴 들었어. 미안하지만, 난 가봐야겠어.";
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
			dialog.text = "무슨 이야기를 하고 싶으신가요?";
			link.l1 = "당신이 원하던 대로 특이한 배를 가져왔소. 이제 내 보상을 기대하겠소.";
			link.l1.go = "BurntShip14";
			link.l2 = "있잖아, "+GetFullName(NPChar)+", 아직도 당신이 원하는 조건에 맞는 배를 한 척도 찾지 못했습니다. 이 일은 포기해야 할 것 같군요. 실망시켰다면 미안합니다...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "안타깝군요, 선장님... 당신이 도와줄 생각이 없다니 유감입니다.";
			link.l1 = "그건 내 의지로 되는 일이 아니네, 자네. 이해해 주게. 안녕히 가게.";
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
			dialog.text = "오, 정말이군! 그럼 우리 새 배 이름이 뭐지?";
			
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
			
			link.l99 = "실례합니다, 나중에 다시 오겠습니다.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "아, 선장님, 저를 실망시키지 않으셔서 정말 기쁩니다! 이 얼마나 "+GetSexPhrase("훌륭한 청년","아름다운 아가씨")+" 정말 당신 덕분에 목숨을 건졌소... 제발, 며칠 후에 돈을 받으러 와줄 수 있겠소? 아시다시피, 보험 관련 서류를 정리해야 해서... 그동안 배에 간단한 수리라도 해두시오. 돛도 새로 달고, 구멍도 막고, 선체 청소도 해두면 좋겠소...";
			link.l99 = "내가 너희가 날 속이려 하면 배에 끔찍한 짓을 하겠다고 약속했지. 잊었어?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "아니, 아니, 당연히 그렇지 않소! 나는 내 약속을 반드시 지킬 것이니 걱정 마시오. 있지, 새 배를 위장하려면 추가 비용이 들 거라 생각해서, 옛 배의 보험금은 이자를 붙여 빌려주었소. 이해해 주길 바라오...";
			link.l1 = "돈이 내 금고에 들어오면 훨씬 더 잘 이해하겠지. 다시 만날 때까지.";
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
			dialog.text = "무슨 이야기를 하고 싶었소?";
			link.l1 = "보상을 받으러 왔소. 당신이 필요로 하는 배는 아직 가지고 있소.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "그 이름이 뭐였는지 다시 한 번 말씀해 주시겠소? 내 기억력이 예전 같지 않아서 말이오, 아시다시피 이런저런 번거로움이 많아서...";
			
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
			
			link.l99 = "실례합니다, 나중에 다시 오겠습니다.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "그래, 완벽하오. 이제 보상을 줄 준비가 되었소, "+FindRussianMoneyString(cn)+". 그게 바로 보험회사가 불탄 선박의 가치를 평가한 방식이오. 보험금은 신용 상자 형태로 지급되니, 현금은 없소, 미안하오.";
			link.l1 = "이런, 이 금액은 마음에 들지 않아. 이 배는 분명 훨씬 더 가치가 있을 거라고 확신해.";
			link.l1.go = "BurntShip21";
			link.l2 = "그래. 도움이 될 수 있어서 기쁘군. 또 보자.";
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
			dialog.text = "무슨 말씀이십니까, 선장님?! 저를 믿으십시오, 제가 뭘 말하는지 잘 압니다. 그 돈이면 그런 배 두 척은 살 수 있습니다!";
			link.l1 = "내가 그냥 갖고 있겠어. 있잖아, 이게 좀 마음에 들기 시작했거든... 잘 가라.";
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
				dialog.text = "선장들 중 한 명이 내 사무실에 항해일지를 두고 갔네. 정말 덜렁이군! 그를 찾아가서 이걸 돌려주게.";
				link.l1 = "오, 그거야 쉽지... 내가 가져가겠어!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "아니, 나는 그 일 안 할 거야. 사실 그건 자기 문제지.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "거기 정박지에서 배가 도난당했소. 도난당한 선박을 추적해서 되찾아 오시오.";
				link.l1 = "흠, 좋아, 이제 조사를 시작할 준비가 됐어.";
				link.l1.go = "SeekShip_1";
				link.l2 = "미안하지만, 나는 도난당한 배를 찾는 일은 하지 않소.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "훌륭하오, 여기 그의 항해일지가 있소... 정말 큰 걱정을 덜어주었구려! 배의 항해일지를 잃는 건 아주 끔찍한 일이오. 나는 항상 그런 선장들이 안타까웠소...";
			link.l1 = "글쎄, 그거 정말 걱정되는 일이군! 이제 그 건망증 심한 선장에 대해 더 말해 보시오.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "네, 물론입니다! 그의 이름은 "+npchar.quest.PortmansJornal.capName+", 그는 선장이야 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" '라 불리는"+npchar.quest.PortmansJornal.shipName+"'. 그는 얼마 전에 출항해서 다음 장소로 갔소 "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "알겠소. 좋아, 그를 찾아보겠소. 이제, 보수는 어떻게 되는 거요?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" 그가 직접 돈을 줄 거요, 그게 그에게도 이득이니까. 자네는 최대한 빨리 그를 찾아가는 데 집중하면 모든 게 잘 풀릴 거요.";
			link.l1 = "알겠소. 그럼, 나는 가보겠소...";
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
			dialog.text = "훌륭하군! 알다시피, 도난당한 그 배는 영향력 있는 인물의 소유라서 내게 매우 중요한 일이오. 이 일의 보수는 넉넉히 주겠소...";
			link.l1 = "알겠소. 그 배와 도난 당시의 상황에 대해 더 말해 보시오.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" '라는 이름을 가진"+npchar.quest.PortmansSeekShip.shipName+"'은(는) 밤사이에 도난당했소 "+FindRussianDaysString(rand(5)+10)+" 전에. 감시병이 죽었소.";
			link.l1 = "흠... 이제쯤이면 저들은 멀리 갔겠군. 흔적이 더 이상 새것이 아니니, 그게 문제로다.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "맞는 말이오. 하지만 나는 바로 경보를 울릴 필요성을 느끼지 못했소. 군함이 그들을 따라잡을 수도 있었겠지만, 그랬다면 배를 산산조각 내버렸을 거요. 그건 내가 원하는 바가 아니오.";
			link.l1 = "알겠소. 그럼 수색을 시작하겠소. 운이 따르길 바라지.";
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
			dialog.text = "안타깝군 - 하지만 성공을 기대하기는 어려웠지.";
			link.l1 = "그래, 배가 도난당한 지 너무 오래됐지.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "그래도 도와줘서 고맙소. 기대만큼 성과가 크진 않았지만 말이오.";
			link.l1 = "나는 할 수 있는 건 다 했어...";
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
				dialog.text = "훌륭하군! 하지만 이게 도둑맞은 그 배는 아닌 것 같다는 생각이 드는군... 에이, 뭐 어때! 내가 가져가겠어.";
				link.l1 = "그래, 그렇지...";
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
				dialog.text = "훌륭하군! 정말 큰 도움이 되었소. 얼마나 힘들었을지 상상도 가지 않소.";
				link.l1 = "그래, 그렇지...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "보상금을 줄 준비가 되었소. 그것은 다음과 같소\n " + makeint(sti(npchar.quest.money)) + " 도블론으로 드리겠소. 유감이지만, 그 이상은 드릴 수 없소.";
			link.l1 = "자, 이만하면 됐소. 감사합니다, 그리고 안부 전하오.";
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
				dialog.text = "등록된 선장이 몇 명 있습니다. 특별히 관심 있는 사람이 있습니까?";
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
				dialog.text = "당신에게 흥미로울 만한 선장은 내 명단에 없소.";
				link.l1 = "알겠소. 음, 정보 주어서 고맙소.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("자, 어디 보자... 아하! 저기 있군! ","아하... 아하! 저기 있다! ","좋아, 그럼. ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 년에 우리 항구를 떠나 ...으로 항해했소 "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "감사합니다. 목록을 다시 한 번 검토하고 싶습니다...";
			link.l1.go = "CapitainList";
			link.l2 = "좋아, 그게 전부야. 다른 선장에는 관심 없어.";
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
			dialog.text = LinkRandPhrase("음, 어디 보자... 아하! 저기 있군! ","아하... 아하! 저기 있다! ","좋아, 그럼. ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 년에 우리 항구를 떠나 로 항해했소 "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "감사합니다. 목록을 다시 한번 검토하고 싶군요...";
			link.l1.go = "CapitainList";
			link.l2 = "좋아, 그게 다야. 다른 선장한테는 관심 없어.";
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
			dialog.text = LinkRandPhrase("음, 어디 보자... 아하! 저기 있군! ","아하... 아하! 저기 있다! ","좋아, 그럼. ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 년에 우리 항구를 떠나 로 항해했소 "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "감사합니다. 목록을 다시 한번 검토하고 싶군요...";
			link.l1.go = "CapitainList";
			link.l2 = "좋아, 그게 다야. 다른 선장한테는 관심 없어.";
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
			dialog.text = LinkRandPhrase("음, 어디 보자... 아하! 저기 있군! ","아하... 아하! 저기 있다! ","좋아, 그럼. ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 년에 우리 항구를 떠나 로 항해했소 "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "감사합니다. 목록을 다시 한번 검토하고 싶군요...";
			link.l1.go = "CapitainList";
			link.l2 = "좋아, 그게 다야. 다른 선장한테는 관심 없어.";
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
			dialog.text = LinkRandPhrase("자, 어디 보자... 아하! 저기 있군! ","아하... 아하! 저기 있다! ","좋아, 그럼. ")+"Captain "+GetFullName(sld)+" "+arCapLocal.date+" 년에 우리 항구를 떠나 로 항해했소 "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "감사합니다. 목록을 다시 한번 검토하고 싶군요...";
			link.l1.go = "CapitainList";
			link.l2 = "좋소, 그게 전부요. 다른 선장에게는 관심 없소.";
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
			dialog.text = "듣고 있소 – 어느 배, 얼마나 오래였소?";
    		Link.l1 = "루카스 로덴부르크가 보냈소. 여기서 내 배를 무료로 정박할 수 있다고 했소.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "듣고 있소 – 어느 배, 얼마나 오래였소?";
    		Link.l1 = "리처드 플리트우드가 보냈소. 여기서 내 기함을 1만 페소에 정박할 수 있다고 했소.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "음, 맞는 말이오. 하지만 유감스럽게도 지금은 당신의 배를 받아줄 수 없소. 부두에 빈자리가 없으니.";
    			Link.l1 = "안타깝군.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "여기 두고 갈 배가 어느 것인지 말씀해 주시겠습니까?";
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
	    			Link.l17 = "신경 쓰지 마시오, 감사합니다.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "흠... 네 배는 하나도 안 보이는데.";
	    			Link.l1 = "정박 가능 여부를 여쭤보고 싶었습니다.";
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
			// dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', class "+RealShips[sti(chref.Ship.Type)].Class+", 정박 비용은 "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" 한 달 단위로, 한 달치 선불 지급.";
			// Link.l1 = "네, 그거면 괜찮습니다.";
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
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', 계급 " + RealShips[sti(chref.Ship.Type)].Class +
                     ", 정박 비용 " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " 한 달마다, 선불로 지급.";
			dialog.Text = dialog.Text + " 장교와 선원들에게 맡기면, 그들과 함께 " + FindRussianMoneyString(sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew));

			Link.l1 = "그래. 그거면 괜찮아.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip)) Link.l1.go = "ShipStock_3";
			else  Link.l2.go = "ShipStock_NoMoney";

			Link.l2 = "그래. 그거면 되네. 선장과 선원들에게 맡겨 둬.";
			if (sti(Pchar.Money) >= (sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew))) Link.l2.go = "ShipStock_4";
			else Link.l2.go = "ShipStock_NoMoney";

			Link.l3 = "아니, 마음이 바뀌었어.";  
			Link.l3.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "그리고 네가 필요한 금액을 모으는 즉시 나도 괜찮을 거야.";
			Link.l1 = "이런... 나중에 다시 올게.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
		 	LeaveShipInPort(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "알겠소. 필요할 때 언제든 배를 가져가시오.";
			Link.l1 = "감사합니다.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_4":
		 	LeaveShipInPortWithCrew(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "알겠소. 필요할 때 언제든 당신의 배를 가져가시오.";
			Link.l1 = "감사합니다.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "어떤 배를 타실 생각이십니까?";
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
	
	    			Link.l99 = "아니, 마음이 바뀌었어.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "배 한 척 더 들일 자리가 있소?";
	    			Link.l1 = "아, 맞다. 고맙소.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "흠. 네 기함이 항구에 보이지 않는군. 그리고 네 배들은 여기서만 되찾을 수 있어.";
    			Link.l1 = "좋아, 나중에 내가 데리러 올게.";
    			Link.l1.go = "exit";
			}
		break;

		case "ShipStockManBack":
			// Лимит офицеров не позволяет забрать  
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "선장님, 선원에 더 이상 장교를 들일 자리가 없는 것 같군요.";  
				link.l1 = "흠... 그럼 나중에 다시 오겠소.";  
				link.l1.go = "exit";  
				break;  
			}
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "자, 보자... 이 배는 항구를 떠난 시간이 "+chref.quest.Mutiny.date+".";
				link.l1 = "'떠났다'니 무슨 말이오? 그녀는 분명 여기, 부두에 있어야 하오!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "배를 찾으러 왔나? 정박료는 아직 안 냈어 "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "짐을 싣는 중인가?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "예.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "아니, 마음이 바뀌었어.";
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
			dialog.Text = "그것을 당신의 장교들 중 누구에게 주면 되겠소?";
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
				dialog.text = "그래, 그래, 알고 있소. 하지만 무료 정박은 한 척만 허락할 수 있소. 그러니 제발, 함대 정리를 먼저 하고 다시 오시오.";
				link.l1 = "알겠소, 기함만 데려가겠소.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "네, 네, 알고 있습니다. 로덴부르크 나리의 명령에 따라 귀하의 선박을 보관하며, 머무는 동안 내내 감시 장교를 배정하겠습니다. 여기에 서명해 주십시오... 그리고 여기도...\n";
				link.l1 = "좋아... 이제 모든 형식적인 절차가 끝난 것이오?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "예. 이제 당신은 배에 대해 더 이상 걱정하지 않아도 됩니다 - 우리가 잘 돌볼 테니까요. 이제 로덴부르흐 나리께 돌아가셔도 됩니다.";
			link.l1 = "감사합니다. 안녕히 가십시오.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "그래, 그래, 알고 있소. 하지만 무료 정박은 배 한 척만 가능하오. 그러니 함대를 정리한 뒤에 다시 오시오.";
				link.l1 = "알겠소, 기함만 데려가겠소.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "예, 물론이지. 돈은 가지고 있나?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "알겠습니다. 여기 있습니다.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "아니. 금방 돌아올게.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "알겠습니다. 당신의 선박을 잘 돌보고, 머무는 내내 감시 장교를 배치하겠습니다.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "뭐 필요한 거 있어, 선장?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "당신의 장교 "+GetFullName(chref)+" 통보함"+NPCharSexPhrase(chref,"","")+" 나에게 그것을 "+NPCharSexPhrase(chref,"그","그녀")+" 당신의 명령으로 바다에 나가야 했소. 나는 반대하지 않았소\n "+NPCharSexPhrase(chref,"그를","그녀")+".";
			link.l1 = "젠장! 그런 명령은 없었잖아! 그 놈한테 내 배를 맡기지 말았어야 했는데! 에이, 됐다, 어차피 내 손해는 어쩔 수 없지.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "이런 놀라운 일이... 했나\n "+NPCharSexPhrase(chref,"그","그녀")+" 혹시 그들이 어디로 갔는지 말해줄 수 있소?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "죄송합니다, "+GetAddress_Form(NPChar)+". 부하들을 좀 더 조심해서 다루셔야 하오.";
			link.l1 = "알아, 내가 바보지. 잘 가, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "이 군도에서 독특한 선박과 그를 맡은 인물들은 결코 눈에 띄지 않을 수 없지. 하지만 이 정보는 상당한 가치를 지니고 있어서 함부로 주지는 않네.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "알겠습니다. 25,000페소면 제 진심을 증명하기에 충분하겠습니까?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "좋아, 다음에 하자.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "확실히, 그 정도면 괜찮소. 어떤 선박에 관심이 있소?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "갤리온 '"+GetShipName("성스러운 자비")+"'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "순찰 스노우 '"+GetShipName("베스 부인")+"'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "브리그 '"+GetShipName("Memento")+"'.";
				link.l3.go = "UniqueShips_Memento";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Amsterdam_InfoPU"))
			{
				link.l4 = "회사 기함 '"+GetShipName("Amsterdam")+"'.";
				link.l4.go = "UniqueShips_Amsterdam";
			}
			link.l99 = "나는 이제 충분히 안 것 같소.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "홀리 머시는 에스코리알에서 유럽에서 파견되어 스페인 식민지를 감독하는 임무를 맡았습니다. 그 선장 도나 알라미다는 스페인 왕실의 명망 높은 충복이자, 부패와 범죄에 맞서 싸우는 무자비한 전사이며, 가톨릭 신앙의 열성 신자입니다. 홀리 머시는 식민지들 사이를 순항하며, 아바나에서 여정을 시작하고 마무리하며 오직 임무에만 집중합니다.\n각 항구마다 알라미다는 며칠씩, 때로는 더 오래 머뭅니다. 이 기간 동안에는 거리에서 그를 직접 마주칠 수도 있다고들 하지요. 하지만 현지인들은 그런 만남을 그다지 반기지 않습니다—스페인인들에게 그 나리는 오직 두려움과 경외심만을 불러일으키니까요.\n홀리 머시에는 알라미다가 직접 선발한 경험 많고 충성스러운 선원들이 탑승해 있습니다. 모든 선원이 조국과 선장을 위해 목숨을 바칠 각오가 되어 있습니다. 도나 페르난도가 홀리 머시가 결코 적에게 넘어가서는 안 된다고 명령했다는 소문이 돌고, 만약 승선전투에서 도저히 이길 수 없는 상황이 오면, 선원들은 배가 적에게 넘어가느니 차라리 바닷속으로 가라앉히겠다고 속삭인다고 합니다.";
			link.l1 = "정말 감사합니다.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "레이디 베스는 진정한 미인이지. 영국 해양 기술의 경이로움이자, 왕립 해군의 전직 장교였던 앨버트 블랙우드가 지휘하고 있어. 사실, 그렇게 화려하게 탈영에 성공하는 사람은 드물지! 그는 군복무를 버리고, 찬란했던 경력을 스스로 망치고, 군함까지 훔쳐서—전부 보물을 찾아 헤매기 위해서였어!\n그리고 헛된 짓도 아니었지. 이미 바베이도스의 절반을 살 수 있을 만큼 찾아냈지만, 여전히 더 원하고 있어. 바다에서 그를 만나면—가로채려는 시도조차 하지 마. 배가 너무 훌륭하고, 선장도 노련하고 신중하거든. 요즘 블랙우드는 카이만에 자주 들러—밤낮없이 땅을 파고, 사람들을 죽을 때까지 부려먹고 있지. 만약 직접 확인하러 갈 생각이라면—최소 예순 명과 좋은 화기를 데려가. ...사실, 그것도 부족할지 몰라\n네가 총 쏘는 법을 알길 바란다, 왜냐하면 폭스 대령 휘하의 전직 해병대원들이 그와 함께 탈영했으니까. 전문가들이라서, 평범한 깡패들과는 차원이 달라. 그리고 절대 프랑스 항구에서는 그를 공격하지 마—거기서는 후원자와 보호세력이 있어서, 그가 찾아낸 보물의 일부를 받고 있거든.";
			link.l1 = "정말 감사합니다.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "'메멘토' — 진정한 해적 전설이지. 모티머 그림이 지휘하는 검은 브리그야.\n"+"그림은 오직 노예상만을 노린다고 하오. 노예들을 풀어주고, 사형선고를 받은 자들을 금화로 사들인다고들 하더군. 고귀한 일이지, 나머지를 모른다면 말이오.\n"+"사람을 짐짝처럼 싣고 다니지 않으면, 그림은 너한테 손도 안 댄다. 괴짜긴 해도 나름 원칙이 있지. 하지만 선창에 노예가 있다면... 수평선에 검은 돛이 보이지 않길 기도해라.\n"+"'메멘토'호는 해적 소굴 사이를 오가지만 정박하는 일은 드물다. 선원들은 몇 달씩 배에서 생활하며, 마치 땅을 밟는 걸 두려워하는 것처럼 보인다. 소문에 따르면 이 배는 한때 끔찍한 역병을 견뎌냈다고 한다 — 그래서 선원들이 그렇게 죽지 않는다는 얘기가 도는 거지.\n"+"녀석들과 맞붙을 생각이라면 대포를 더 챙겨라. '메멘토'에 승선하는 건 거의 불가능하다 — 선원들이 마치 악령에 씐 것처럼, 죽음을 두려워하지 않는 듯 싸우거든. 녀석들을 이길 유일한 방법은 배를 산산조각 내서 은신처를 빼앗는 거다. 파편 따위는 겁내지 않지만, 산탄이 직격하면 이야기가 달라지지.\n"+"행운을 빌지. 그리고 죽음을 잊지 마라.";
			link.l1 = "정말 감사합니다.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Amsterdam":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "4");
			pchar.questTemp.Amsterdam_InfoPU = true;
			dialog.text = "존경받는 네덜란드 서인도 회사의 기함이다. 이 배에 관한 모든 것은 비밀에 싸여 있다. 쿠라사오 해군 등록부의 수장 헨드릭 판 도른이 지휘하고 있는데, 그는 매우 유능하여 가장 부유하고 영향력 있는 선장들에게 귀중한 서비스를 제공하는 인물이다. 그들 사이에 설 자격을 얻으려고 노력해 보라. 그러면 더 많은 것을 알게 될지도 모른다.";
			link.l1 = "정말 감사합니다.";
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
