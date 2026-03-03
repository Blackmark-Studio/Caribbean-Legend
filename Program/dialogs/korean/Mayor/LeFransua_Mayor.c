// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일이오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 묻는 것이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 몸인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소...","지금은 아니오. 장소와 때가 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 있다가...","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "당신의 죄수에 대해 이야기하고 싶소.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello "+NPChar.name+", 죄수 문제로 찾아왔소.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "그대의 죄수에 대해 이야기하고 싶소.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "포로와 관련된 사업에 종사하고 있다고 들었습니다...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "하하. 내가 여기 죄수를 한 명만 두고 있다고 생각하시오? 이름을 말해보시오.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". 그는 여기 있소?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "그랬소. 내가 그를 바베이도스에서 온 플랜테이션 소유주 비숍 대령에게 팔았소 – 그가 여기 온 지 일주일 되었을 때였지.";
				link.l1 = "젠장...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "아, 드디어 왔군. 나는 그를 바베이도스의 플랜테이션 소유주에게 팔까 생각하고 있었소, 그가 일주일이나 이주일 후에 올 것이오... 몸값을 준비했소?"+GetSexPhrase("","")+"?";
				link.l1 = "보시오, "+NPChar.name+" , 약간 문제가 있소... 사실, 내게 그만한 돈이 없소. 하지만 일할 의지는 있소.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "그를 아직 팔지 않아서 다행이오. 여기 당신의 돈이오 - 15만 페소. 그를 어디서 찾을 수 있소?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "너무 늦으셨소... 그런데 그 사람에게 왜 그렇게 신경을 쓰시오? 나는 그의 친척들과만 협상해 왔을 뿐이오.";
			link.l1 = "그들이 저를 이곳으로 오라고 요청하였습니다.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "음, 늦었군. 내가 해줄 수 있는 것이 없소.";
			link.l1 = "듣게, 혹시 비밀이 아니라면 그를 얼마에 팔았는지 말해 줄 수 있겠나?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "에이, 그건 아니야. 하지만 말 안 할 거야... 말하면 네가 웃을 테니까. 하하하하! 안녕.";
			link.l1 = "또 뵙겠습니다.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "흠, 흠... 볼일이 좀 있소... 어디서부터 말을 꺼내야 할지 모르겠구려. 도를 넘은 해적 하나를 침몰시켜야 하오.";
				link.l1 = "그를 정글에서 그냥 죽일 수는 없소?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "음, "+pchar.name+", 있잖아, 세상일이 그렇게 쉽게 되진 않아. 돈을 가져오면 네 그 약골을 돌려주지, 하하.";
				link.l1 = "좋소, 그럼 안녕히 가시오.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "그게 사업이 돌아가는 방식이 아니오... 내가 그자를 죽일 필요는 없소, 다만 내 몫의 전리품을 가로채지 말라는 교훈을 몇몇 사람들에게 주고 싶을 뿐이오. 하지만 그자가 상어 밥이 된다 해도, 나는 개의치 않을 것이오.";
			link.l1 = "왜 직접 부하들을 보내지 않으십니까?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "흠... 그렇군 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 몇몇 해적들에게 전리품 몫이 우리 은닉처, 즉 에서 멀지 않은 곳에 보관될 것이라고 설득했습니다\n "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". 그들의 두 척의 배 '"+pchar.GenQuest.CaptainComission.ShipName1+"'와 '"+pchar.GenQuest.CaptainComission.ShipName2+"'가 얼마 전에 닻을 올리고 출항하여 "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+". 이제 왜 내가 내 부하들에게 이 일을 맡길 수 없는지 알겠소?";
			link.l1 = "알겠소. 시간이 얼마나 남았소?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12일에서 15일, 그 이상은 안 되오. 그들이 은닉처에 도달하지 못하게 하는 것이 내게 중요하오; 귀중한 화물을 실은 채로 그들을 침몰시키는 것은 어리석은 일이 될 것이오. 그런 경우라면, 차라리 그들이 이것을 이리로 가져오는 편이 낫겠소...";
			link.l1 = "좋소, 나도 끼겠소. 놈들을 잡아보겠소.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "걱정하지 마시오. 내 부하들이 그를 당신 배로 데려다 줄 것이오. 그런데 그 사람에게 왜 그리 신경을 쓰시오?";
			link.l1 = "모릅니다. 그의 친척들이 저에게 그를 데려다 달라고 부탁했소.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "아, 괜찮소. 그대의 부하에게 이렇게 헐값을 제시한 것이 거의 미안할 지경이었소. 하하하하. 안녕히 가시오.";
			link.l1 = "또 뵙겠습니다.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "음, "+GetFullName(pchar)+", 내 동료를 침몰시켰나? 허허허...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "아니오. 그들을 붙잡는 데 실패했습니다. 그리고 돌아오는 길에서도 만나지 못했습니다.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "그렇소. 상어 밥이 되도록 보냈소.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "젠장! 뭐, 이제 와서 상관없소! 다음 제안은 무엇이오?";
			link.l1 = "혹시 저에게 더 쉬운 일이 있습니까?";
			link.l1.go = "CapComission4_1";
			link.l2 = "들으시오, "+NPChar.name+", 포로의 몸값을 낮추시오...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "아니오.";
			link.l1 = "그럼 작별이오...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "값을 깎으라고?! 네놈의 무능함 때문에 내 물건을 다 잃었단 말이다! 오히려 값을 올려야지! 원한다면 20만 페소에 데려가든가, 아니면 당장 꺼져라!";
			link.l1 = "너무 비싸군... 작별이오...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "제기랄, 좋아, 돈 가져가라.";
				link.l2.go = "CapComission4_5";
			}	
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
			dialog.text = "이 약골을 데려가도 좋소...";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "호호! 잘했소! 저 약골을 데려가고 행운을 빌겠소.";
			link.l1 = "감사합니다. 안녕히 가십시오.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "돈을 가져왔나, Charles? 저 사내를 플랜테이션에 팔겠다는 말, 농담이 아니었네\n";			
			link.l1 = "들으시오, "+NPChar.name+", 문제가 있소... 그만한 돈이 없소. 하지만 일할 의지는 있소.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그를 아직 팔지 않으셨다니 다행이오. 여기 당신의 돈이오 – 15만 페소요. 그를 어디에서 찾을 수 있소?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "내가 무엇을 하든 왜 신경 쓰시오? 알다시피, 그냥 떠나는 게 좋을 거요...";
			link.l1 = "쳇, 진정하시오. 당신에게 사업 제안을 하려고 왔소. 당신의 죄수에 관한 일이오.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "아, 좋소. 누구를 몸값을 받고 풀어주길 원하시오?";
			link.l1 = "잠깐. 나는 누구를 사러 온 것이 아니라, 당신에게 죄수를 사갈 기회를 주러 왔소. 그리고 그를 위해 몸값을 받을 기회도 얻게 될 것이오.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "흠. 그런데 왜 내 중개가 필요한 것이오? 직접 돈을 받는 것이 더 낫지 않소?";
			link.l1 = "저로서는 상당히 위험한 일입니다. 당국과 문제가 생길 수도 있소.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "하, 하... 좋소. 한번 봅시다. 포로가 누구요?";
			link.l1 = "이것은 "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "알겠소. 그대가 거짓말을 하지 않는다면 공정한 거래가 되겠군. 이 사람에 대해 내가 값을 치를 수 있을 것이라 생각하오. "+iTemp+" 페소를 드릴 수도 있고, 아니면 흥미로운 정보를 드릴 수도 있습니다. 선택은 당신의 몫이오.";
			link.l1 = "동전을 가져가는 게 낫겠군. 이 일도 이제 지긋지긋하군...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "하! 더 이야기해 보시오. 분명 내게 흥미로운 소식이 있을 것 같구려.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "돈이군. 가져가시오. 이제는 당신 일이 아니오. 매매 대상은 이곳에 데려오시오.";
			link.l1 = "그는 이제쯤 성문 근처에 있을 겁니다. 감사합니다! 정말 큰 도움을 주셨군요.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "천만에, 더 가져오게나... 또 보세!";
			link.l1 = "행운을 빕니다...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "똑똑한 분과 거래하게 되어 기쁩니다. 이제 들으시오: 며칠 후에\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 스페인 원정대가 본토에서 귀중한 물품을 싣고 도착할 것이오. 그들은 화물을 실어갈 배를 기다릴 것이니, 일주일 안에 도착한다면 그 화물을 차지할 기회가 있을 것이오.\n내가 그대라면 벌써 내 배로 향하고 있겠소. 그리고 포로를 이리로 데려오시오.";
					link.l1 = "감사합니다! 물품은 제 수고에 대한 충분한 보상이 될 것입니다. 그리고 제 승객은 이제쯤이면 마을 입구 근처에 있을 겁니다. 곧 당신께 데려다 드리겠습니다.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "똑똑한 분과 거래를 하니 기쁘군. 이제 들으시오: 약 일주일 후에, 스페인 브리간틴 '"+pchar.GenQuest.Marginpassenger.ShipName1+"' 값진 화물을 실은 배가 출항할 것이오 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" 에게 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". 서두르면 쉽게 잡을 수 있을 것이오.\n아직도 여기 있는 것이오? 내가 그대라면 벌써 내 배로 향하고 있었을 것이오. 그리고 죄수를 이리로 데려오시오.";
					link.l1 = "감사하오! 이 물품들이 내 수고에 대한 충분한 보상이 될 것이오. 그리고 내 승객은 마을 입구 근처에 있을 것이니, 곧 당신께 데려다 드릴 것이오.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
