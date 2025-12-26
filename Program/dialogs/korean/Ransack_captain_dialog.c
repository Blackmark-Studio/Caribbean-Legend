// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "무슨 일이오, 선장? 내 몸값에 대해 얘기하려는 거요? 그 아가씨의 운명이 내게도 중요하다는 걸 알아주시오...";
			link.l1 = "카테린 레이너에 대해 말하는 건가? 이미 그 소식은 들었어, "+pchar.questTemp.FalseTrace.CapName+". 그녀가 당신과 이야기해 달라고 부탁했어요.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "이봐, 후안 나리, 반역이란 더러운 짓이야...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"나는 네 포로다, "+GetAddress_Form(NPChar)+". 하지만 알아두었으면 해 "+NationNameNominative(sti(NPChar.nation))+" 자기 사람들에겐 절대 돈을 안 내지. 우리 모두 각자 알아서 살아야 해.";
				link.l1 = "흠... 너한테선 이득 볼 게 없겠군. 최소한 어느 식민지에서든 범죄자로서 몸값은 받을 수 있겠지.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "이봐, 너는 싸움에 능하잖아. 나한텐 너 같은 사람이 필요해. 내 지휘 아래에서 일해 볼 생각 있나?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"나는 당신의 포로요, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" 내 자유를 위해 좋은 값을 쳐 줄 거야.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "이봐, 너는 솜씨 좋은 선원이구나. 나한텐 너 같은 사람이 필요해. 내 지휘 아래에서 일해 볼 생각 있나?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "우리는 멀지 않아 "+GetCityName(attrLoc)+". 그리고 여기서 너를 풀어줄 수도 있지.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "갑판장에게 가서 사물함을 달라고 해라. 다음 항구에서 하선할 수 있다.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "네가 힘도 세고 충직하니, 훌륭한 노예로 삼아주마.";
			link.l4.go = "Slave_1";
			link.l5 = "네가 돛을 내리라는 명령을 무시하고 무력으로 저항했지. 그 죄로 교수형을 당하게 될 거다. 보선장에게는 이미 내 명령이 전달되었다.";
			link.l5.go = "PunishmentAction";
			link.l99 = "알고 있어.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("선장님, 제 몸값 대신 더 이득이 되는 제안을 들어보시겠습니까?","여기서 흥정할 여지는 없다는 것 압니다만, 제 제안을 들어보시겠습니까?");
						link.l1 = "듣고 있다.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "선장님, 왜 저를 그냥 풀어주지 않으십니까? 저는 선장님께 아무런 가치도 없습니다. 저를 노예상에게 팔아도 동전 몇 닢과 나쁜 평판만 얻으실 겁니다.";
						link.l1 = "그리고 그냥 널 풀어주면, 나는 아무것도 얻지 못하겠지...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "네가 돛을 내리라는 명령을 무시하고 무력으로 저항했으니, 그 죄로 교수형에 처해질 것이다. 이미 보선장이 내 명령을 받았다.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "정말 끈질기군. 네가 원하는 걸 줄 수 있을 것 같아. 이제 넌 자유인이야. 내 배에서 내려.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("내 인내심을 시험하지 마라. 네가 아직 살아 있는 것만으로도 운이 좋은 거야.","나는 너를 위한 내 계획이 따로 있다.","앞으로도 너를 쓸 일이 있을지도 모르겠군.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "선장님, 이 불확실함이 저를 미치게 만듭니다. 저를 어떻게 하실 생각이신지 알 수 있을까요?";
						link.l1 = "나한테 내놓을 게 있나?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("아직 너에 대해 아무 생각도 없어.",RandPhraseSimple("계획? 목에 대포알을 매달아 줄까? 농담이야, 하!","너는 내 포로다. 내가 네게 무엇을 하든 전적으로 내 권한이 있다. 네 의견 따위는 여기서 아무런 가치도 없어."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "선장님, 왜 저를 그냥 놓아주지 않으십니까? 저 같은 사람은 필요 없으시잖아요. 해적이 된 건 제게 남은 유일한 선택이었습니다. 쓸 만한 기술도, 배운 것도 없으니까요. 저는 그저 돈 좀 모아서 은퇴하고 싶었을 뿐입니다.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "봐라, 너는 싸움 실력이 좋지. 난 너 같은 악당이 필요해. 내 부하가 될 생각 있나?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("너한테는 자비 없다. 바다엔 깡패들이 넘쳐나지. 이제 한 놈이라도 줄겠군."," 문제 있어, '바다늑대'? 여기 가만히 있으면서 조용히 해.","너희 같은 놈들은 모두 교수대가 기다리고 있다. 나는 너를 당국에 팔아넘길 거다, 그게 모든 해적들에게 큰 교훈이 될 테니.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "선장님, 제발 부탁드립니다... 저를 풀어주십시오. 저에겐 가족과 아이들이 있습니다. 저 없이는 살아갈 수 없습니다.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "봐라, 너는 솜씨 좋은 뱃사람이니 내게 꼭 필요한 인재다. 내 지휘 아래에서 일해 볼 생각 있나?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("너를 위한 내 계획이 따로 있다.","앞으로도 내게 쓸모가 있을지도 모르겠군.","너는 내 포로다. 내가 너에게 무엇을 하든 전적으로 내 권리다.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("선장님, 제가 싸움에서 졌으니 자비를 베풀어 주시길 부탁드립니다. ","선장님, 자비를 베풀어 주시길 간청합니다. 저를 전쟁 포로로 대우하실 이유가 없다는 것 잘 압니다. 그러니 제 목숨만은 살려 주십시오. 맹세코 앞으로는 바다에서 선장님을 마주치지 않겠습니다.");
						link.l2 = LinkRandPhrase("내 인내심을 시험하지 마라. 네가 아직 살아 있는 것만으로도 운이 좋은 거야.",RandPhraseSimple("나는 너를 위한 내 계획이 따로 있다.","앞으로도 나에게 쓸모가 있을지도 모르겠군."),RandPhraseSimple("너는 내 포로다. 내가 원하는 대로 너를 다룰 권리가 내게 있다. 네 생각 따위는 여기서 아무런 가치도 없어.","너는... 아니, 너였지, 전함의 선장이었고 위험을 잘 알고 있었잖아. 여기서 성인인 척하지 마."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "봐라, 너는 싸움에 능한 놈이니 내가 너 같은 악당이 필요하다. 내 부하가 될 생각 있냐?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "우리는 멀지 않아 "+GetCityName(attrLoc)+". 그리고 여기서 널 놓아줄 수도 있지.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "갑판장에게 가서 사물함을 달라고 해라. 다음 항구에서 하선할 수 있다.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "제기랄! 갑판장한테 가서 사물함 하나 달라고 해. 다음 항구에서 내릴 수 있을 거다. 그리고 기억해둬라, 다음에 다시 만나면 그게 마지막이 될 거다.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "네가 돛을 내리라는 명령을 무시하고 무력으로 저항했으니, 그 죄로 교수형을 당하게 될 것이다. 보선장은 이미 내 명령을 받았다.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "범죄자라고? 농담하는 거야,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "농담 아니네. 너 해적이구나.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "네 밑에서 일하느니 차라리 상어 밥이 되겠다!";
				link.l1 = "입 조심해라, 안 그러면 네가 저놈들 밥이 될 테니까.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "당신의 장교가 되기 위해, "+GetAddress_Form(NPChar)+"? 동의하지. 나는 내 일을 잘 알고 있고, 잃을 것도 없어.";
				link.l1 = "거래 성사다! 가서 네 일이나 해.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "잠깐만, 마음이 바뀌었어.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("매력적인 제안이긴 하지만... 원칙상 거절해야겠소.","미안하지만, 네가 내 친구들에게 한 짓을 생각하면... 그건 불가능해.","아니요, 선장님. 이 모든 공포를 겪고 나니 더 이상 이 일을 할 수 없습니다. 축복받은 성모님께서 제 기도를 들어주시고 자유를 허락해 주신다면, 다시는 항해하지 않겠다고 맹세했습니다.");
				link.l1 = "그건 네 선택이야. 강요하지 않겠다.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "왜 안 되겠어? 나는 가난한 선장이야, 배도 잃었고, 육지에는 나한테 남은 게 아무것도 없어. 남은 거라곤 청구서랑 빚뿐이지...";
				link.l1 = "좋아! 갑판장에게 가서 네 몫을 받아라. 내 배에서 자리를 주는 건 조금 있다가 해주마.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "잠깐만, 마음이 바뀌었어.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "But "+GetAddress_Form(NPChar)+", 그러면 안 돼! 나 항복했잖아.";
            link.l1 = "입 다물어! ... 저 놈을 묶어.";
			link.l1.go = "Slave_2";
			link.l99 = "알겠어. 내가 결정할 때까지 여기 있어...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "말도 안 돼! 노예가 되느니 차라리 죽겠다!";
                link.l1 = "그만둬! 명령이다!... 보스운! 화물 정리해...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "도살자 놈이다! 얘들아, 나랑 같이 가자, 잃을 것도 없잖아!";
                        link.l1 = "잘못된 선택이야, 아가씨들. 반란은 내가 직접 처리하지, 그리고 아주 빠르게 끝내버려...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "말도 안 돼! 차라리 싸우다 죽겠어!";
						link.l1 = "원하시는 대로...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "오, 나도 동의해. 어쩔 수 없지.";
                    link.l1 = "훌륭하군. 죽은 영웅보다는 살아 있는 노예가 낫지.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "오, "+GetAddress_Form(NPChar)+", 정말 그렇게 친절하신 겁니까, 몸값도 요구하지 않고 저를 풀어주시다니?";
            link.l1 = "그래, 맞아. 이제 너는 자유야,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "흠... 네 말도 일리가 있군! 결정을 내리려면 시간이 좀 더 필요해.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "감사합니다, "+GetFullName(PChar)+"! 당신을 위해 기도하겠습니다.";
            link.l1 = "이제 가거라, 그리고 살아남도록 해라. 그렇지 않으면 내 관용이 헛될 테니.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("감사합니다, 선장님. 당신의 친절을 절대 잊지 않겠습니다. 이제 이 일을 그만두고 평화로운 항구에서 작은 배를 수리하며 살겠습니다. 그 정도는 할 수 있습니다.","감사합니다, 선장님! 맹세컨대, 이 배은망덕한 일은 그만두고 어부가 되겠습니다.");
					link.l1 = "만약 네가 진실을 말하는 거라면 행운을 빌어주지. 하지만 아니라면, 다시는 나를 마주치지 않게 기도해라...";	
				break;
				case "trade":
					dialog.text = "어떻게 감사해야 할지 모르겠어요, 선장님. 이미 희망을 잃었었죠. 당신의 친절함을 모두에게 말하겠어요. 맹세컨대, 당신을 위해 촛불을 밝히겠습니다! 교회에만 도착하면요.";
					link.l1 = "잘 가라. 그리고 다음번엔, 감히 저항할 생각도 하지 마라. 나에게 발포하면, 너와 네 선원들 모두 사형 선고를 받게 될 거다.";
				break;
				case "war":
					dialog.text = "감사합니다, 선장님. 당신을 위해 기도하겠습니다.";
					link.l1 = "행운을 빌지. 그리고 기억해, 날 사냥하려 든다면 그게 네 최후가 될 거야.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "But "+GetAddress_Form(NPChar)+", 그러면 안 돼! 나 항복했어.";
			link.l1 = "네 부하들이 떠난 뒤에야. 네가 놈들을 배신했지... 보스운! 저 자를 잡아라.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "음... 생각할 시간이 필요하군. 여기 있어.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "도살자 놈! 얘들아, 우린 잃을 게 없어!";
                    link.l1 = "잘못된 선택이야, 아가씨들. 반란은 내가 직접 처리하지, 그리고 아주 신속하게 끝내버려...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "말도 안 돼! 차라리 싸우다 죽겠어!";
					link.l1 = "원하시는 대로...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "적어도 기도할 시간은 좀 주시오...";
                link.l1 = "기도하고 싶으면 하시오.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "자네 같은 사람에게 쓸모 있을 만한 흥미로운 정보가 있지. 하지만 내 자유를 보장해 주겠다는 약속이 필요하네.";
			link.l1 = "당신의 제안을 알지도 못하는데 어떻게 보장을 해줄 수 있겠소? 당신의 정보가 내게 쓸모 있을지도 의문이군.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "내가 줄 수 있는 건 내 말뿐이오.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "좋아. 그 정도면 충분해. 이제 본론으로 들어가지, "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 부유한 상인이 거주하는 곳이다 "+NPChar.Hold_GenQuest.Name+". "+"그는 자신의 배 '에서 재산을 모았다"+NPChar.Hold_GenQuest.ShipName+" 판매 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" 항로 :  "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"짐이 너무 많을 때는 호위를 돈 주고 사지."+sTmp+" 이 정보가 한 사람의 목숨보다 당신에게 더 가치 있다고 확신하오.";
			link.l1 = "이 정보가 내게 쓸모 있을 것 같지 않군. 나는 평화로운 상인들은 사냥하지 않아.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "이 정보가 내게 쓸모가 있을지는 모르겠지만, 약속은 했으니 지키겠소. 보선장이 너를 내 선원들과 함께 두고 가장 가까운 항구에서 풀어줄 거다.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "감사합니다, 선장님! 당신의 정직함을 한순간도 의심하지 않았소!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("나도 너에 대해 그렇게 말할 수 있으면 좋겠군\n","미안하지만, 너에 대해서는 그렇게 말할 수 없겠군."),RandPhraseSimple("가라, 그리고 다음번엔 이렇게 관대하지 않을 거라는 걸 명심해라.","가서 내 앞길 막지 마라. 다음번엔 그렇게 쉽게 안 믿을 거다."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "그리고 당신에게 제안이 하나 있소. \n "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 목숨이야, 친구, "+NPChar.Hold_GenQuest.Name+" 그가 이름이야. 예전에 같이 사업을 한 적이 있지."+"거기서 그를 찾아. 분명히 네게 큰돈을 줄 거야. 그는 내게 빚이 있으니, 내가 직접 처리할 거다.";
			link.l1 = "네 친구라구? 어디 한번 보자.";	
			link.l1.go = "free_buyout1";
			link.l2 = "내가 첫 번째 항구에서 바로 몸값을 받을 수 있는데, 왜 네 친구를 찾아야 하지?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "사실, 나는 훌륭한 보물을 가진 남자를 아는데, 그놈은 그걸 쓸 배짱이 없어.";
			link.l1 = "무슨 뜻이야?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "네 이야기 따위 듣고 싶지 않아. 네 영혼이나 걱정하는 게 좋을 거다.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "나는 너에게 엄청난 보물로 이어지는 이야기를 들려주고 있어. 대신 다음 항구에서 나를 풀어주겠다고 약속해 줘야 해.";
			link.l1 = "너한테 언제 무엇을 할지는 내가 직접 결정한다. 네 '이야기' 따위는 아무 소용 없어.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "듣고 있소. 내 약속이오.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "이렇게 명예로운 "+GetSexPhrase("남자","여자")+". 너 같은 사람들은 항상 약속을 지키지! 세상이 다 불타고 있어도, 넌 반드시 약속을 지킬 거야! 맞지, 선장?";
			link.l1 = "네 이야기를 해라, 아니면 지금 당장 풀어주지... 바다로 내던져서 목 잘린 채로 말이다.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "하하, 웃긴 농담이군... 이제 들어봐. 에 어떤 녀석이 있는데\n "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 이름이 붙은 "+NPChar.Hold_GenQuest.Name+", 그는 젊었을 때 꽤 무모한 녀석이었지. 그 시절엔 '거래'도 참 많이 했어..."+"그래서 한 번은 선술집에서 그가 자신이 소속된 곳이 있다고 말했어 "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" 그 무리와 함께 있으면서, 그 해적들이 보물을 묻는 모습을 직접 봤지."+" 그 보물 때문에 자기 동료 다섯 명을 죽였지... 잡혀서 교수형을 당했다는 소문도 있었지만, 사실은 사업에서 손을 떼고 가정을 꾸렸어. 그는 보물 위치를 기억하고, 지도까지 그렸지. 나한테 같이 보물을 찾으러 가자고 제안했어. 미신이 심한 사람이었는데, 그 보물이 피로 물들었다고 믿어서 혼자 가는 걸 두려워했지. 솔직히 나도 같은 이유로 시도하지 않았어. "+"그가 지도를 팔 준비가 되어 있었지만, 어차피 내가 거길 갈 일도 없는데 그게 나한테 무슨 소용이겠어...\n그게 내 이야기야... 당신처럼 용감한 사람이라면 분명히 쓸모가 있을 거라 생각해. 그리고 지도도 꽤 싸게 팔고 있어.";
			link.l1 = "정말 내가 그 말을 믿을 거라고 생각하나? 네 이야기는 거짓이니, 우리 거래는 여기서 끝이다.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "흥미로운 이야기군, 하지만 나는 별로 믿지 않아. 하지만 내 약속은 지키지. 가서 보스운에게 네 사물함을 달라고 해. 이제 자유야.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "감사합니다, 선장님! 이제야 한 남자의 말값이 어떤 것인지 알겠군요 "+GetSexPhrase("신사 나리!","아가씨!");
			link.l1 = "가서 내 앞길 막지 마라. 다음번엔 이렇게 쉽게 넘어가지 않을 거다.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "하지만, "+GetAddress_Form(NPChar)+", 우리는 망망대해에 있어! 나를 처형한 거나 마찬가지야!";
			link.l1 = "원하던 것이었지. 작별이다. 보선장이 내 명령을 실행할 거다.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "좋아, 아직 결정하지 않았어.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "카트린! 정말 네더러 여기 오라고 부탁했단 말이야? 참 대단한 아가씨지...";
			link.l1 = "시를 논할 때가 아니오, 선장. 이제 더 중요한 이야기를 하세. 지금 상황을 설명할 테니, 자네의 대답을 듣고 싶군. 자네의 대답이 자네와 카테린의 운명을 모두 결정할 것이오.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "듣고 있소, 선장님.";
			link.l1 = "나는 아담 레이너, 카테린의 남편이 네 배에 은이 많다고 해서 네 플루이트에 올라탔다. 이 계략 덕분에 그는 한때 자기 것이었던 여자를 다시 데려갈 수 있었지. 그 여자는 네게로 도망쳤던 사람이야.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "아담? 그 자식 말이오? 전부 그놈 계획이었지! 이제야 알겠군... 그래, 내가 세 달 전에 카트린이 도망칠 수 있도록 도와줬소. 불쌍한 아가씨였지, 그놈이 어떻게 대했는지 당신은 상상도 못 할 거요...";
			link.l1 = "그 여자는 그의 아내였고, 무슨 일이 있었는지 나는 전혀 상관없어. 내 알 바 아니지. 네 플루트선에 올라탄 건 내 실수였지만, 이제 와서 얘기해 봐야 소용없어. 아담이 내 도움에 대한 보수를 주겠다고 약속했으니까.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "아담이 약속을 했다고? 하하! 그리고 그걸 믿으셨소? 선장님, 그자가 어떤 인간인지 아시기나 하오? 그 녀석은...";
			link.l1 = "카트린이 이미 그에 대해 많은 이야기를 해줬고, 정말 애썼지. 하지만 그의 제안도 일리가 있어. 이 자식을 믿을 이유는 없지만, 이번만큼은 진실을 말하고 있을지도 몰라. 그러니 본론부터 말하자고...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "나는 너를 당국에 몸값을 받고 넘기고, 아담과 카테린은 \n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", 그러니 아담에게서 사팔뜨기 솔리의 금에 대한 정보를 얻은 다음 그곳으로 항해하려 했지. 하지만 카트린이 먼저 너와 이야기해 보라고 설득했어; 네가 아담보다 더 낫고 믿을 만한 제안을 내 목숨과 자유를 대가로 내놓을 수도 있다고 하더군.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "그래서 내가 여기 서서 너와 이야기하고 있는 거야. 나는 할 말을 다 했어. 이제 네 차례야. 내 말과 카테린의 말을 곰곰이 생각해 보고, 네 생각을 말해 줘. 시간이 많지 않아.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "선장님! 당신이 좋은 사람이라고는 생각하지 않지만, 가난한 소녀의 간청을 들어주고 여기까지 와 주셨군요. 그걸 보니 당신도 명예를 알고 연민을 느낄 줄 아는 분이란 걸 알겠어요. 저는 시간이 필요하지 않아요, 지금 바로 제 제안을 드릴 준비가 되어 있습니다.";
			link.l1 = "정말인가? 훌륭하군! 그럼, 듣고 있네.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "너는 아담 레이너를 체포해서 족쇄를 채워라. 그리고 나와 캐서린을 데려가라\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". 도시에는 내리지 마라, 어차피 내 플루이트를 침몰시킨 건 너였으니, 우리 셋 다 내려주려면 "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\n무기도 하나 부탁하겠소. 우리는 정글을 지나 도시로 갈 것이고, 그 쓰레기가 저지른 죄뿐만 아니라 그대의 죄까지도 반드시 대가를 치르게 만들겠소. 그 자는 마땅히 벌을 받아야 하오\n그대의 이름이 거론되지 않도록 내가 보장하겠소. 대신, 적국의 금을 실은 배에 관한 진짜 정보를 주겠소\n그대에게 큰 어려움은 아니겠지만, 만만치 않은 상대요. 훌륭한 전리품을 얻게 될 것이오. 내 몸값이나 소위 사팔눈 솔리의 보물보다 훨씬 나을 것이오. 거래하겠소?";
			link.l1 = "네 계획은 마음에 안 들어. 내가 저기 해안을 떠나자마자 현지 당국이 나를 쫓으려고 수색대를 꾸릴 것 같아. "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"아니오, 선장님, 제 목숨을 걸 생각은 없습니다. 우리 대화는 여기까지입니다.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "음, 카테린이 맞았던 것 같군. 네 제안이 마음에 들어. 아담 레이너는 체포될 거야. 지금 바로 실행하겠다. 우리가 아담을 체포하면 넌 풀려날 거다. 또 보자, 선장!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "설교하러 온 거요, 아니면 거래하러 온 거요?";
			link.l1 = "거래를 하러 왔어. 네 범죄 동료인 베르트랑 피네트가 필요해. 그 놈 때문에 내가 큰 곤경에 빠졌거든. 어디서 찾을 수 있지, 응?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "내가 왜 너한테 이걸 말해줘야 한다고 생각하지?";
			link.l1 = "네 목숨이 걸린 일이야. 내가 너를 바세테르까지 데려가서 총독에게 넘기고, 카를로스 드 미야르의 탈출을 도운 탈영병을 잡은 포상금을 받을 거다.\n선택은 네가 해. 피네트가 어디 있는지 말하든가, 아니면 우리 둘 다 과들루프로 가는 수밖에.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "그래, 다 알고 있군... 좋아, 내가 베르트랑 피네트에 대해 아는 건 전부 말해주지. 하지만 그 대신 날 풀어줘야 해.";
			link.l1 = "계속해, 말해 봐. 지난번처럼 너를 모스키토 만에 내려주지. 하지만 나한테 거짓말하면, 돌아와서 돈 카를로스가 너한테 준 그 플랜테이션에 불을 지를 거야. 그리고 바스테르에도 네 위치를 알릴 테니, 나만 너를 쫓는 게 아니게 될 거다.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "먼저, 거기에 나를 내려줘. 그러면 내가 좀 더 안심할 수 있을 거야, 그리고 맹세컨대 전부 다 말해줄게.";
			link.l1 = "좋아. 어차피 너는 어디 갈 데도 없잖아.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
